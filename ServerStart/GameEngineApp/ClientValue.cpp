#include "ClientValue.h"
#include "ConosleHelper.h"


ClientMode ClientValue::mClientMode = ClientMode::Client;
unsigned __int64 ClientValue::m_AccountCheck = static_cast<unsigned __int64>(AccountResultType::Wait);
unsigned __int64 ClientValue::m_LoginCheck = static_cast<unsigned __int64>(AccountResultType::Wait);
DWORD ClientValue::m_GameStartCheck = 1;


//void ClientValue::CurWorldSizeSet(const float4& _CurWorldSize) 
//{
//	m_CurWorldSize = _CurWorldSize;
//	ConosleHelper::SetSize(m_CurWorldSize);
//}

// Static Var
// Static Func

// constructer destructer
ClientValue::ClientValue() 
{

}

ClientValue::~ClientValue() 
{

}
// member Func