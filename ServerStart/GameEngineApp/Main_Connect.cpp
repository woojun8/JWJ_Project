#include "Main.h"
#include <ClientToServer.h>
#include <ServerToClient.h>
#include "ClientValue.h"


#include <iostream>
#include <ClientConnecter.h>
#include <conio.h>
#include <PacketUpdater.h>
#include "ClientPacketFunc.h"
#include <LogicValue.h>




bool ConnectProgress() 
{
    ClientConnecter::GetInst().ClientStart(30000);

    while (CONNECTSTATE::CONNECTWAIT == ClientConnecter::GetInst().IsConnectState())
    {
        Sleep(1);
        std::cout << "서버 접속중" << std::endl;
    }

    if (CONNECTSTATE::CONNECTERROR == ClientConnecter::GetInst().IsConnectState())
    {
        std::cout << "서버 접속에 실패했습니다." << std::endl;
        // 재접속을 해야할지말지 결정해야한다.
        exit(0);
    }

    while (true)
    {
        std::cout << "1. 로그인" << std::endl;
        std::cout << "2. 회원가입" << std::endl;
        std::cout << "3. 종료하기" << std::endl;
        // 입력 때문에 슬립이 걸린다.
        switch (_getch())
        {
        case '1':
        {
            LoginPacket Packet;
            std::cout << "회원 아이디를 입력해주세요" << std::endl;
            std::wcin >> Packet.ID.m_String;
            std::cout << "회원 패스워드를 입력해주세요" << std::endl;
            std::wcin >> Packet.PASS.m_String;
            ClientConnecter::GetInst().Send(Packet);

            std::cout << "로그인 결과 패킷 기다리는중" << std::endl;

            while (true)
            {
                LoginResultType ResultType = (LoginResultType)ClientValue::m_LoginCheck;

                if (ResultType != LoginResultType::Wait)
                {
                    system("cls");
                    switch (ResultType)
                    {
                    case LoginResultType::OK:
                        std::cout << "로그인에 성공" << std::endl;
                        return TRUE;
                    case LoginResultType::IDERROR:
                        std::cout << "존재하지 않는 ID입니다." << std::endl;
                        break;
                    case LoginResultType::PWERROR:
                        std::cout << "패스워드가 틀렸습니다." << std::endl;
                        break;
                    case LoginResultType::ServerError:
                        std::cout << "서버에서 치명적인 오류가 발생했습니다." << std::endl;
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
            break;
        }
        case '2':
        {
            InterlockedExchange(&ClientValue::m_AccountCheck, (int)AccountResultType::Wait);

            // WorldData WorldPacket;
            AccountPacket Packet;
            std::cout << "회원 아이디를 입력해주세요" << std::endl;
            std::wcin >> Packet.ID.m_String;
            std::cout << "회원 패스워드를 입력해주세요" << std::endl;
            std::wcin >> Packet.PASS.m_String;
            ClientConnecter::GetInst().Send(Packet);

            std::cout << "가입완료 결과 패킷 기다리는중" << std::endl;

            while (true)
            {
                AccountResultType ResultType = (AccountResultType)ClientValue::m_AccountCheck;

                if (ResultType != AccountResultType::Wait)
                {
                    system("cls");
                    switch (ResultType)
                    {
                    case AccountResultType::OK:
                        std::cout << "회원가입이 성공" << std::endl;
                        break;
                    case AccountResultType::OverAccount:
                        std::cout << "더이상 회원가입을 할수 없는 서버입니다" << std::endl;
                        break;
                    case AccountResultType::IDOverlap:
                        std::cout << "이미 존재하는 ID입니다." << std::endl;
                        break;
                    case AccountResultType::ServerError:
                        std::cout << "서버에서 치명적인 오류가 발생했습니다." << std::endl;
                        break;
                    default:
                        break;
                    }
                    break;
                }

            }
            break;
        }
        case '3':
            ClientConnecter::GetInst().Close();
            return false;
        default:
            break;
        }
    }

    return true;
}