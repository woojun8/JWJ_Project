#include "ClientActor.h"
#include "ConosleHelper.h"
#include <GameActor.h>

// Static Var
// Static Func

// constructer destructer
ClientActor::ClientActor(GameActor& _GameActor) : m_GameActor(_GameActor), m_OldPos(), m_RenderChar(L'¢Ï')
{

}

ClientActor::~ClientActor() 
{

}
// member Func

void ClientActor::OldClear() 
{
	if (m_OldPos != m_GameActor.GetPos())
	{
		ConosleHelper::ConsolePosPrint(m_OldPos, L'¡¡');
	}
}

void ClientActor::CurClear()
{
	ConosleHelper::ConsolePosPrint(m_GameActor.GetPos(), L'¡¡');
}

void ClientActor::Render() 
{
	//if (m_GameActor.GetPos() == m_OldPos)
	//{
	//	return;
	//}
	ConosleHelper::ConsolePosPrint(m_GameActor.GetPos(), m_RenderChar);
}

void ClientActor::SetClientMove(float4 _Pos)
{
	m_OldPos = m_GameActor.GetPos();
	m_GameActor.SetMove(_Pos);
}
void ClientActor::SetClientPos(float4 _Pos)
{
	m_OldPos = m_GameActor.GetPos();
	m_GameActor.SetPos(_Pos);
}