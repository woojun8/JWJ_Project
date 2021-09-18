// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

// 자동완성이 안될겁니다.
#include "Sockets.h"
#include "SocketSubSystem.h"
#include "Networking.h"
#include <MessageQueue.h>
#include <LogicDataClass.h>
#include <ServerToClient.h>
// 이녀석 내부에 있는 내용이 

class CharacterData;
class ConnectTask : public FNonAbandonableTask
{
//public:
//	static int Check;

public:
	ConnectTask() {}
	~ConnectTask() {}

	// 이걸 리턴하는 함수를 무조건 만들어줘야 합니다.
	FORCEINLINE TStatId GetStatId() const
	{
		// 이녀석이 쓰레드 풀에 TASK로 적용될수가 있다.
		RETURN_QUICK_DECLARE_CYCLE_STAT(ConnectTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	// 이함수가 없으면
	// task로 인정받지 못하므로 꼭 만들어줘야 합니다.
	void DoWork();

	void DoWorkMain();
};


class UnrealRecvThread : public FRunnable
{
public:
	UnrealRecvThread();


	uint32 Run() override;
	void Stop() override;
	void Exit() override;
};


/**
 * 
 */
class ClientToServer;
class UNSERVERGAME_API UnServerConnect
{
public:
	TAtomic<uint32> m_ThreadProcess; // 게임 종료시 쓰레드를 처리하기 위한 값.
	TAtomic<uint32> m_Login; // 로그인 성공 실패에 대한 처리 값
	TAtomic<uint32> m_GameStart; // 로그인 성공 실패에 대한 처리 값

	bool IsServer;


public:
	CharacterPacket m_CharacterData;


public:
	static UnServerConnect& GetInst();
	FSocket* ConnectSocket;
	FIPv4Address ip;
	FIPv4Endpoint EndPoint;
	bool m_IsConnect;
	// ISocketSubsystem* SSS;

	int m_SendByte;

	UnrealRecvThread* RecvThread;
	FRunnableThread* RecvFRunnable;
	FAutoDeleteAsyncTask<ConnectTask>* ConnectTaskAsync;

public: // Msg
	UWorld* MainWorld;
	MessageQueue MainProcess;

	template<typename FuncType, typename ... Rest>
	void MsgInsert(FuncType _Func, Rest ... _Arg)
	{
		if (nullptr == MainWorld)
		{
			UE_LOG(LogTemp, Error, TEXT("if (nullptr == MainWorld)"));
			return;
		}

		MainProcess.MsgInsert(_Func, MainWorld, _Arg...);
	}

public:
	bool IsConnect();

public:
	void ConnectSocketCreate();
	bool Connect();
	void ConnectTaskStart();
	void Close();
	void ThreadStop();
	void Init(UWorld* _World);


	void Send(ClientToServer& _Data);

	// Count가 보내는 패킷의 사이즈 역할을 합니다.
	void Send(const uint8* Data, int32 Count/*, int32& BytesSent*/);

public:
	UnServerConnect();
	~UnServerConnect();
};
