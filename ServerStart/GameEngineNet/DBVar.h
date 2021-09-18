#pragma once
#include <string>

class DBVar
{
protected:
	void* m_SettingData;


public:
	void DataBind(void* _Data)
	{
		m_SettingData = _Data;
	}

	template<typename DataType>
	void DataChange(const DataType& _Data)
	{
		memcpy_s(m_SettingData, sizeof(DataType), &_Data, sizeof(DataType));
	}

	void DataChange(void* _Data, unsigned int _Size)
	{
		memcpy_s(m_SettingData, _Size, _Data, _Size);
	}



public:
	template<typename T>
	void Link(T& _Data) 
	{
		m_SettingData = &_Data;
	}

public:
	virtual void Setting(char* _DBData) = 0;
	virtual std::string ToString() = 0;

public:
	DBVar() {}
	~DBVar() {}
};

class DB__Int64 : public DBVar
{
public:
	void Setting(char* _DBData) 
	{
		if (NULL != _DBData)
		{
			DataChange(std::stoll(_DBData));
		}		
	}

	std::string ToString() 
	{
		__int64* Ptr = reinterpret_cast<__int64*>(m_SettingData);
		return std::to_string(*Ptr);
	}
};


template<typename int Count>
class DBchar : public DBVar
{
public:
	char String[Count];

public:
	void Setting(char* _DBData)
	{
		if (NULL != _DBData)
		{
			DataChange(static_cast<void*>(_DBData), Count);
		}		
	}

	std::string ToString()
	{
		char* Ptr = reinterpret_cast<char*>(m_SettingData);
		return Ptr;
	}
};



class DBInt : public DBVar
{
public:
	void Setting(char* _DBData)
	{
		if (NULL != _DBData)
		{
			DataChange(std::stoi(_DBData));
		}
	}

	std::string ToString()
	{
		int* Ptr = reinterpret_cast<int*>(m_SettingData);
		return std::to_string(*Ptr);
	}
};
