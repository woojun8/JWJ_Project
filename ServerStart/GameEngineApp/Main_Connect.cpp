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
        std::cout << "���� ������" << std::endl;
    }

    if (CONNECTSTATE::CONNECTERROR == ClientConnecter::GetInst().IsConnectState())
    {
        std::cout << "���� ���ӿ� �����߽��ϴ�." << std::endl;
        // �������� �ؾ��������� �����ؾ��Ѵ�.
        exit(0);
    }

    while (true)
    {
        std::cout << "1. �α���" << std::endl;
        std::cout << "2. ȸ������" << std::endl;
        std::cout << "3. �����ϱ�" << std::endl;
        // �Է� ������ ������ �ɸ���.
        switch (_getch())
        {
        case '1':
        {
            LoginPacket Packet;
            std::cout << "ȸ�� ���̵� �Է����ּ���" << std::endl;
            std::wcin >> Packet.ID.m_String;
            std::cout << "ȸ�� �н����带 �Է����ּ���" << std::endl;
            std::wcin >> Packet.PASS.m_String;
            ClientConnecter::GetInst().Send(Packet);

            std::cout << "�α��� ��� ��Ŷ ��ٸ�����" << std::endl;

            while (true)
            {
                LoginResultType ResultType = (LoginResultType)ClientValue::m_LoginCheck;

                if (ResultType != LoginResultType::Wait)
                {
                    system("cls");
                    switch (ResultType)
                    {
                    case LoginResultType::OK:
                        std::cout << "�α��ο� ����" << std::endl;
                        return TRUE;
                    case LoginResultType::IDERROR:
                        std::cout << "�������� �ʴ� ID�Դϴ�." << std::endl;
                        break;
                    case LoginResultType::PWERROR:
                        std::cout << "�н����尡 Ʋ�Ƚ��ϴ�." << std::endl;
                        break;
                    case LoginResultType::ServerError:
                        std::cout << "�������� ġ������ ������ �߻��߽��ϴ�." << std::endl;
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
            std::cout << "ȸ�� ���̵� �Է����ּ���" << std::endl;
            std::wcin >> Packet.ID.m_String;
            std::cout << "ȸ�� �н����带 �Է����ּ���" << std::endl;
            std::wcin >> Packet.PASS.m_String;
            ClientConnecter::GetInst().Send(Packet);

            std::cout << "���ԿϷ� ��� ��Ŷ ��ٸ�����" << std::endl;

            while (true)
            {
                AccountResultType ResultType = (AccountResultType)ClientValue::m_AccountCheck;

                if (ResultType != AccountResultType::Wait)
                {
                    system("cls");
                    switch (ResultType)
                    {
                    case AccountResultType::OK:
                        std::cout << "ȸ�������� ����" << std::endl;
                        break;
                    case AccountResultType::OverAccount:
                        std::cout << "���̻� ȸ�������� �Ҽ� ���� �����Դϴ�" << std::endl;
                        break;
                    case AccountResultType::IDOverlap:
                        std::cout << "�̹� �����ϴ� ID�Դϴ�." << std::endl;
                        break;
                    case AccountResultType::ServerError:
                        std::cout << "�������� ġ������ ������ �߻��߽��ϴ�." << std::endl;
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