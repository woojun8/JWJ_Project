#include "ClientWorld.h"
#include "ClientWall.h"
#include "ClientPotal.h"

// Static Var
// Static Func

// constructer destructer
ClientWorld::ClientWorld() 
{

}

ClientWorld::~ClientWorld() 
{

}
// member Func

void ClientWorld::CreateWallPos(const Sizefloat4& _Pos)
{
	std::shared_ptr<ClientWall> Wall = CreateActor<ClientWall>(0);
	Wall->SetPos(_Pos);
}

void ClientWorld::CreatePotalPos(const PotalData& _PotalData)
{
	std::shared_ptr<ClientPotal> Potal = CreateActor<ClientPotal>(1);
	Potal->SetPotalData(_PotalData);

	// Wall->SetPos(_Pos);
}