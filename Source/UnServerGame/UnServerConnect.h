// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

// �ڵ��ϼ��� �ȵɰ̴ϴ�.
#include "Sockets.h"
#include "SocketSubSystem.h"
#include "Networking.h"
#include <MessageQueue.h>
#include <LogicDataClass.h>
#include <ServerToClient.h>
// �̳༮ ���ο� �ִ� ������ 

class CharacterData;
class ConnectTask : public FNonAbandonableTask
{
//public:
//	static int Check;

public:
	ConnectTask() {}
	~ConnectTask() {}

	// �̰� �����ϴ� �Լ��� ������ �������� �մϴ�.
	FORCEINLINE TStatId GetStatId() const
	{
		// �̳༮�� ������ Ǯ�� TASK�� ����ɼ��� �ִ�.
		RETURN_QUICK_DECLARE_CYCLE_STAT(ConnectTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	// ���Լ��� ������
	// task�� �������� ���ϹǷ� �� �������� �մϴ�.
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
	TAtomic<uint32> m_ThreadProcess; // ���� ����� �����带 ó���ϱ� ���� ��.
	TAtomic<uint32> m_Login; // �α��� ���� ���п� ���� ó�� ��
	TAtomic<uint32> m_GameStart; // �α��� ���� ���п� ���� ó�� ��

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

	// Count�� ������ ��Ŷ�� ������ ������ �մϴ�.
	void Send(const uint8* Data, int32 Count/*, int32& BytesSent*/);

public:
	UnServerConnect();
	~UnServerConnect();
};
