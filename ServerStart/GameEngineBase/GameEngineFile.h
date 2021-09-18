#pragma once
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include <vector>
#include <list>
#include <map>

enum class FILEOPENMODE
{
	READ,
	WRITE,
	NOTOPEN,
};

// 분류1 : Base
// 분류2 : 
// 설명 : 파일 입출력및 파일의 기본기능들을 담당한다.
class GameEngineFile : public GameEnginePath
{
private:	// static Var
public:		// static Func
private:	// Member Var
	FILEOPENMODE m_OpenMode;
	FILE* m_File;

public:	// Constructer Destructer
	GameEngineFile();
	GameEngineFile(const EngineString& _String);
	GameEngineFile(const wchar_t* _String);
	~GameEngineFile();
	GameEngineFile(const GameEngineFile& _Other) : GameEnginePath(_Other), m_File(_Other.m_File), m_OpenMode(_Other.m_OpenMode)
	{

	}
	GameEngineFile(GameEngineFile&& _Other) noexcept : GameEnginePath(_Other),m_File(_Other.m_File), m_OpenMode(_Other.m_OpenMode)
	{

	}

public:	// operator
	GameEngineFile& operator=(const GameEngineFile& _Other) 
	{
		m_Path = _Other.m_Path;
		m_File = _Other.m_File;
		return *this;
	}
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept
	{
		m_Path = _Other.m_Path;
		m_File = _Other.m_File;
		return *this;
	}


public: //////////////////////////////////////////////////////// stl
	template<typename T>
	void operator << (const std::vector<T>& _Value)
	{
		int Size = (int)_Value.size();
		Write(&Size, sizeof(int), 1);
		for (size_t i = 0; i < _Value.size(); i++)
		{
			Write(&_Value[i], sizeof(T), 1);
		}
	}

	template<typename T>
	void operator << (const std::list<T>& _Value)
	{
		int Size = (int)_Value.size();
		Write(&Size, sizeof(int), 1);

		std::list<int>::iterator Iter;

		auto StartCIter = _Value.begin();
		auto StartCEnd = _Value.end();
		for (; StartCIter != StartCEnd; ++StartCIter)
		{
			Write(&(*StartCIter), sizeof(T), 1);
		}
	}

	template<typename KEY, typename VALUE>
	void operator << (const std::map<KEY, VALUE>& _Value)
	{
		int Size = (int)_Value.size();
		Write(&Size, sizeof(int), 1);

		auto StartCIter = _Value.cbegin();
		auto StartCEnd = _Value.cend();
		for (; StartCIter != StartCEnd; ++StartCIter)
		{
			Write(&StartCIter->first, sizeof(KEY), 1);
			Write(&StartCIter->second, sizeof(VALUE), 1);
		}
	}

	/////////////////////////////////////////// Read

	template<typename T>
	void operator >> (std::vector<T>& _Value)
	{
		int Size = 0;
		Read(&Size, sizeof(int), sizeof(int), 1);
		_Value.resize(Size);
		for (size_t i = 0; i < _Value.size(); i++)
		{
			Read(&_Value[i], sizeof(T), sizeof(T), 1);
		}
	}

	template<typename T>
	void operator >> (std::list<T>& _Value)
	{
		int Size = (int)_Value.size();
		Read(&Size, sizeof(int), sizeof(int), 1);

		for (int i = 0; i < Size; i++)
		{
			T NewT =  T();
			Read(&NewT, sizeof(T), sizeof(int), 1);
			_Value.push_back(NewT);
		}
	}

	template<typename KEY, typename VALUE>
	void operator >> (std::map<KEY, VALUE>& _Value)
	{
		int Size = (int)_Value.size();
		Write(&Size, sizeof(int), 1);

		auto StartCIter = _Value.cbegin();
		auto StartCEnd = _Value.cend();
		for (; StartCIter != StartCEnd; ++StartCIter)
		{
			Write(&StartCIter->first, sizeof(KEY), 1);
			Write(&StartCIter->second, sizeof(VALUE), 1);
		}
	}


public:
	template<typename T>
	void operator << (const T& _Value) 
	{
		if (nullptr == m_File)
		{
			GameEngineDebug::AssertMsg("if (nullptr == m_File)");
		}
		Write(&_Value, sizeof(T), 1);
	}

	template<>
	void operator << (const EngineString& _Value)
	{
		if (nullptr == m_File)
		{
			GameEngineDebug::AssertMsg("if (nullptr == m_File)");
		}

		int Size = (int) _Value.size();
		Write(&Size, sizeof(int), 1);
		if (0 != Size)
		{
			Write(_Value.ConstStringPtr(), _Value.size() * sizeof(wchar_t), 1);
		}
	}

	template<typename T>
	void operator >> (T& _Value)
	{
		if (nullptr == m_File)
		{
			GameEngineDebug::AssertMsg("if (nullptr == m_File)");
		}
		Read(&_Value, sizeof(T), sizeof(T), 1);
	}

	template<>
	void operator >> (EngineString& _Value)
	{
		if (nullptr == m_File)
		{
			GameEngineDebug::AssertMsg("if (nullptr == m_File)");
		}

		int Size = (int)_Value.size();
		Read(&Size, sizeof(int), sizeof(int), 1);

		if (0 != Size)
		{
			_Value.ReSize(Size);
			Read(&_Value.At(0), Size * sizeof(wchar_t), Size * sizeof(wchar_t), 1);
		}
	}


public: // member Function
	bool FileCreateWriteOpen();
	bool FileOpen(const wchar_t* _Mode);
	void Close();
	void Read(void* _Buffer, size_t _BufferSize, size_t _ElementSize, size_t _ElementCount) const;
	void Write(const void* _Buffer, size_t _ElementSize, size_t _ElementCount) const;


public:
	size_t FileByteLen();
	GameEngineString ToString();


};