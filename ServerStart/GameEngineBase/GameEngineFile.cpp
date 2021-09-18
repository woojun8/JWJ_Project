#include "GameEngineFile.h"
#include <iostream>
#include "GameEngineDirectory.h"


// Constructer Destructer ----------------------------------------------------
GameEngineFile::GameEngineFile() : m_File(nullptr), m_OpenMode(FILEOPENMODE::NOTOPEN)
{

}
GameEngineFile::GameEngineFile(const EngineString& _String)
	: GameEnginePath(_String), m_File(nullptr), m_OpenMode(FILEOPENMODE::NOTOPEN)
{
	// GameEngineDirectory NewDir
}
GameEngineFile::GameEngineFile(const wchar_t* _String) 
	: GameEnginePath(_String), m_File(nullptr), m_OpenMode(FILEOPENMODE::NOTOPEN)
{
}

GameEngineFile::~GameEngineFile() 
{
	Close();
}
// GameEngineFile::GameEngineFile(const GameEngineFile& _Other) {}
// GameEngineFile::GameEngineFile(GameEngineFile&& _Other) {}

// operator -----------------------------------------------------------------
// GameEngineFile& GameEngineFile::operator=(const GameEngineFile& _Other) {}
// GameEngineFile& GameEngineFile::operator=(GameEngineFile&& _Other) {}


// member Function -----------------------------------------------------------
//GameEngineString GameEngineFile::Ext() 
//{
//
//}

bool GameEngineFile::FileCreateWriteOpen()
{
	if (false == IsExist())
	{

		return FileOpen(L"w");
	}
	else 
	{

		return FileOpen(L"a");
	}
}

bool GameEngineFile::FileOpen(const wchar_t* _Mode)
{
	// 기존에 파일을 열고 있던 파일이라면
	Close();

	int Count = 0;
	while (0 != _Mode[Count])
	{
		if (toupper(_Mode[Count]) == L'W')
		{
			m_OpenMode = FILEOPENMODE::WRITE;
			break;
		}
		else if (toupper(_Mode[Count]) == L'R')
		{
			m_OpenMode = FILEOPENMODE::READ;
			break;
		}
	}


	_wfopen_s(&m_File, m_Path.ConstStringPtr(), _Mode);

	if (nullptr == m_File)
	{
		GameEngineDebug::AssertMsg("if (nullptr == m_File)");

		return false;
	}

	return true;
}

void GameEngineFile::Close()
{
	if (nullptr != m_File)
	{
		fclose(m_File);
		m_File = nullptr;
	}
}

void GameEngineFile::Read(void* _Buffer, 
	size_t _BufferSize, 
	size_t _ElementSize, 
	size_t _ElementCount) const
{
	// _Buffer 배열의 포인터
	// _BufferSize 배열의 크기
	// _ElementSize 읽으려는 양 10
	// _ElementCount 읽으려는 횟수 10
	fread_s(_Buffer, _BufferSize, _ElementSize, _ElementCount, m_File);
}

void GameEngineFile::Write(
	const void* _Buffer,
	size_t _ElementSize,
	size_t _ElementCount
)  const
{
	// _ElementSize 버퍼와
	fwrite(_Buffer, _ElementSize, _ElementCount, m_File);
}

size_t GameEngineFile::FileByteLen() 
{
	if (m_OpenMode == FILEOPENMODE::NOTOPEN)
	{
		GameEngineDebug::AssertMsg("if (m_OpenMode == FILEOPENMODE::NOTOPEN)");
	}

	// 파일을 탐색하는 위치를 파일의 끝으로 보냅니다.
	fseek(m_File, 0, SEEK_END);

	// 파일의 크기가 100이면
	// 100 바이트가 리턴되겠죠?
	// 파일을 탐색하는 위치를 얻어온다.
	size_t Len = (size_t)ftell(m_File);

	// 처음으로 돌려줍니다.
	fseek(m_File, 0, SEEK_SET);

	// 파일을 탐색하는 위치를 파일의 처음으로 보냅니다.
	return Len;
}

GameEngineString GameEngineFile::ToString() 
{
	// 학생들한테 하는 이야기는
	// 문자열과 파일입출력은 기본기와 같아서
	// 그냥 잘해야합니다.
	// EX) 어떤파일 읽어와서 XXX 데이터만 뽑아내
	//     바이너리 파일일경우
	//     저장된 구조체나 바이트단위를 알려줄 것이고
	//     텍스트일 경우에는 사실 그냥 보면 알죠?
	size_t Size = FileByteLen();

	if (0 == Size)
	{
		return GameEngineString();
	}


	std::string Str;
	Str.resize(Size, 0);
	fread(&Str[0], Str.size(), 1, m_File);

	GameEngineString Text;
	Text.SetConvertMultiByteString(Str);

	return Text;
}