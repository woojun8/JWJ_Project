#pragma once
#include <string>
// Window 에서 지원해주는 String 편의 함수들
#include <list>
#include <Vector>

// 설명 : 
class GameEngineString
{
private:	// static Var
public:		// static Func
public:	// Member Var
	std::wstring m_String;

public:	// Constructer Destructer
	GameEngineString();
	GameEngineString(wchar_t* _Str) : m_String(_Str)
	{
	}
	GameEngineString(const wchar_t* _Str) : m_String(_Str)
	{
	}
	GameEngineString(std::wstring _Str) : m_String(_Str)
	{
	}
	GameEngineString(const GameEngineString& _Other) : m_String(_Other.m_String)
	{
	}
	GameEngineString(GameEngineString&& _Other) noexcept : m_String(_Other.m_String)
	{
	}

	~GameEngineString();

public:
	std::string GetConvertMultiByteString(int _encoding = 0) const;

	void SetConvertMultiByteString(const std::string& _Str, int encoding = 0);

	static GameEngineString GlobalSetConvertMultiByteString(const std::string& _Str, int encoding = 0);

	void ReSize(size_t _Size)
	{
		m_String.resize(_Size);
		return;
	}

	size_t size() const
	{
		return m_String.size();
	}

	wchar_t& At(size_t _Index)
	{
		return m_String.at(_Index);
	}

	size_t FindOf(const wchar_t* _Char)
	{
		return m_String.find(_Char);
	}

	size_t FindLastOf(wchar_t _Char, size_t _Offset = static_cast<size_t>(-1))
	{
		return m_String.find_last_of(_Char, _Offset);
	}

	GameEngineString GetCutString(size_t _Start, size_t _Count)
	{
		GameEngineString Return = m_String.substr(_Start, _Count);

		return Return;
	}

	void DeleteString(size_t _Start, size_t _End)
	{
		m_String = m_String.replace(_Start, _End, L"");
		return;
	}

	const wchar_t* ConstStringPtr() const
	{
		return m_String.c_str();
	}

	GameEngineString DeleteString(const wchar_t _DeletStr) const
	{
		GameEngineString Str;

		for (size_t i = 0; i < m_String.size(); i++)
		{
			if (_DeletStr == m_String[i])
			{
				continue;
			}
			Str.m_String.push_back(m_String[i]);
		}

		return Str;
	}

	std::vector<GameEngineString> StringCutToVector(const wchar_t _Pivot)
	{
		std::vector<GameEngineString> StrList;
		size_t Start = 0;
		size_t End = 0;
		while (true)
		{
			// 앞에서 부터 찾아서 인덱스 리턴
			End = m_String.find_first_of(_Pivot, Start);

			if (End == std::wstring::npos)
			{
				std::wstring Text = m_String.substr(Start, m_String.size() - Start);
				// Text.push_back(0);
				StrList.push_back(Text);
				break;
			}

			std::wstring Text = m_String.substr(Start, End - Start);
			Start = End + 1;
			// Text.push_back(0);

			StrList.push_back(Text);
		}


		return StrList;
	}

	std::list<GameEngineString> StringCutToList(const wchar_t _Pivot) const
	{
		std::list<GameEngineString> StrList;
		size_t Start = 0;
		size_t End = 0;
		while (true)
		{
			// 앞에서 부터 찾아서 인덱스 리턴
			End = m_String.find_first_of(_Pivot, Start);

			if (End == std::wstring::npos)
			{
				std::wstring Text = m_String.substr(Start, m_String.size() - Start);
				// Text.push_back(0);
				StrList.push_back(Text);
				break;
			}

			std::wstring Text = m_String.substr(Start, End - Start);
			Start = End + 1;
			//Text.push_back(0);

			StrList.push_back(Text);
		}


		return StrList;
	}

	// 문자 2개 넣어주면 그 사이에 있는 글자들을 리턴해준다.
	std::list<GameEngineString> CenterCut(const wchar_t _Start, const wchar_t _End)
	{
		std::list<GameEngineString> StrList;

		size_t Start = 0;
		size_t End = 0;

		while (true)
		{
			// 앞에서 부터 찾아서 인덱스 리턴
			Start = m_String.find_first_of(_Start, End);
			End = m_String.find_first_of(_End, Start);

			if (Start == std::wstring::npos || End == std::wstring::npos)
			{
				break;
			}

			std::wstring Text = m_String.substr(Start + 1, End - Start - 1);
			Text.push_back(0);
			Start = End;
			StrList.push_back(Text);
		}

		
		return StrList;
	}

public:	// operator
	GameEngineString& operator=(GameEngineString&& _Other) noexcept
	{
		m_String = _Other.m_String;
		return *this;
	}


	GameEngineString operator+(const GameEngineString& _Other)
	{
		GameEngineString Str = m_String + _Other.m_String;
		return Str;
	}

	GameEngineString& operator+=(const GameEngineString& _Other)
	{
		m_String += _Other.m_String;
		return *this;
	}

	GameEngineString& operator=(const GameEngineString& _Other) 
	{
		m_String = _Other.m_String;
		return *this;
	}
	GameEngineString& operator = (const wchar_t* _Str)
	{
		m_String = _Str;
		return *this;
	}

	GameEngineString& operator = (const std::wstring& _Str)
	{
		m_String = _Str;
		return *this;
	}
	GameEngineString& operator = (std::wstring&& _Str)
	{
		m_String = _Str;
	}

	bool operator < (const GameEngineString& _Other) const
	{
		return m_String < _Other.m_String;
	}

	bool operator > (const GameEngineString& _Other) const
	{
		return m_String > _Other.m_String;
	}

	bool operator == (const GameEngineString& _Other) const
	{
		return m_String == _Other.m_String;
	}

	bool operator != (const GameEngineString& _Other) const
	{
		return m_String != _Other.m_String;
	}

	wchar_t& operator [](size_t _Index) 
	{
		return m_String[_Index];
	}

	operator std::wstring& ()
	{
		return m_String;
	}

	// Convert Func
public:
	int Toint() 
	{
		return _wtoi(m_String.c_str());
	}

public: // member Function
};

typedef GameEngineString EngineString;