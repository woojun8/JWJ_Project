#include "ClientWorldManager.h"
#include "ClientWorld.h"

// Static Var

ClientWorldManager* ClientWorldManager::m_Inst = nullptr;

// Static Func

// constructer destructer
ClientWorldManager::ClientWorldManager() 
{
	m_Inst = this;
}

ClientWorldManager::~ClientWorldManager() 
{

}
// member Func

std::shared_ptr<ClientWorld> ClientWorldManager::CreateClientWorld(const WorldData& _Data)
{
	PosToKeyConvert Convert = _Data.Index;
	std::shared_ptr<ClientWorld> World = CreateWorld<ClientWorld>(Convert.ToString());
	World->MsgListInit(3, 1000);
	World->SetSize(_Data.Size);

	for (const PotalData& _Potal: _Data.m_PotalData)
	{
		World->CreatePotal(_Potal);
	}

	return World;
}

