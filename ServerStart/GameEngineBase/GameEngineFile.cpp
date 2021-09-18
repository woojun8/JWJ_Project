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
	// ������ ������ ���� �ִ� �����̶��
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
	// _Buffer �迭�� ������
	// _BufferSize �迭�� ũ��
	// _ElementSize �������� �� 10
	// _ElementCount �������� Ƚ�� 10
	fread_s(_Buffer, _BufferSize, _ElementSize, _ElementCount, m_File);
}

void GameEngineFile::Write(
	const void* _Buffer,
	size_t _ElementSize,
	size_t _ElementCount
)  const
{
	// _ElementSize ���ۿ�
	fwrite(_Buffer, _ElementSize, _ElementCount, m_File);
}

size_t GameEngineFile::FileByteLen() 
{
	if (m_OpenMode == FILEOPENMODE::NOTOPEN)
	{
		GameEngineDebug::AssertMsg("if (m_OpenMode == FILEOPENMODE::NOTOPEN)");
	}

	// ������ Ž���ϴ� ��ġ�� ������ ������ �����ϴ�.
	fseek(m_File, 0, SEEK_END);

	// ������ ũ�Ⱑ 100�̸�
	// 100 ����Ʈ�� ���ϵǰ���?
	// ������ Ž���ϴ� ��ġ�� ���´�.
	size_t Len = (size_t)ftell(m_File);

	// ó������ �����ݴϴ�.
	fseek(m_File, 0, SEEK_SET);

	// ������ Ž���ϴ� ��ġ�� ������ ó������ �����ϴ�.
	return Len;
}

GameEngineString GameEngineFile::ToString() 
{
	// �л������� �ϴ� �̾߱��
	// ���ڿ��� ����������� �⺻��� ���Ƽ�
	// �׳� ���ؾ��մϴ�.
	// EX) ����� �о�ͼ� XXX �����͸� �̾Ƴ�
	//     ���̳ʸ� �����ϰ��
	//     ����� ����ü�� ����Ʈ������ �˷��� ���̰�
	//     �ؽ�Ʈ�� ��쿡�� ��� �׳� ���� ����?
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