#include "GameEngineString.h"
#include <WinSock2.h>
#include "GameEngineSerializer.h"


std::string GameEngineString::GetConvertMultiByteString(int _encoding) const
{
	std::vector<wchar_t> StrUniCode;
	StrUniCode.resize(1024 * 4);

	std::vector<char> StrMulti;
	StrMulti.resize(1024 * 4);

	wcscpy_s(&StrUniCode[0], 1024 * 4, m_String.c_str());

	int Len = WideCharToMultiByte(_encoding, 0, &StrUniCode[0], -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(_encoding, 0, &StrUniCode[0], -1, &StrMulti[0], Len, NULL, NULL);
	return &StrMulti[0];
}

void GameEngineString::SetConvertMultiByteString(const std::string& _Str, int encoding /*= CP_ACP*/)
{
	std::vector<wchar_t> StrUniCode;
	StrUniCode.resize(1024 * 4);

	std::vector<char> StrMulti;
	StrMulti.resize(1024 * 4);

	strcpy_s(&StrMulti[0], 1024 * 4, _Str.c_str());

	int Len = MultiByteToWideChar(encoding, 0, &StrMulti[0], static_cast<int>(strlen(&StrMulti[0])), NULL, NULL);
	MultiByteToWideChar(encoding, 0, &StrMulti[0], static_cast<int>(strlen(&StrMulti[0])), &StrUniCode[0], Len);

	m_String = &StrUniCode[0];
}

GameEngineString GameEngineString::GlobalSetConvertMultiByteString(const std::string& _Str, int encoding)
{
	GameEngineString NewStr;
	NewStr.SetConvertMultiByteString(_Str, encoding);
	return NewStr;
}


// Constructer Destructer ----------------------------------------------------
GameEngineString::GameEngineString() 
{

}
GameEngineString::~GameEngineString() 
{

}
// GameEngineString::GameEngineString(const GameEngineString& _Other) {}
// GameEngineString::GameEngineString(GameEngineString&& _Other) {}

// operator -----------------------------------------------------------------
// GameEngineString& GameEngineString::operator=(const GameEngineString& _Other) {}
// GameEngineString& GameEngineString::operator=(GameEngineString&& _Other) {}


// member Function -----------------------------------------------------------





