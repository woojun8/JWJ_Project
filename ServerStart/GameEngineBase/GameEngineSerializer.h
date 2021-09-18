#pragma once
#include <vector>
#include <type_traits>
#include "GameEngineString.h"
#include "GEMath.h"

enum class SerializerMode
{
    Serializer,
    DeSerializer,
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class GameEngineSerializer;
class GameEngineSerializerObject
{
public:
    virtual void Serialize(GameEngineSerializer& _Serializer) = 0;
    virtual void DeSerialize(GameEngineSerializer& _Serializer) = 0;
};

class GameEngineSerializer
{
private: // Static Var
public: // Static Func
private: // member Var
    size_t m_Offset;
    SerializerMode m_Mode;
    std::vector<char> m_Buffer;

public:
    char* GetBuffer() {
        return &m_Buffer[0];
    }

    char& operator[](size_t _Index)
    {
        return m_Buffer[_Index];
    }

    unsigned char* GetUnsignedBuffer()
    {
        return reinterpret_cast<unsigned char*>(&m_Buffer[0]);
    }

    size_t GetOffset() {
        return m_Offset;
    }

    int GetOffsetInt() {
        return (int)m_Offset;
    }


public: // constructer destructer
    GameEngineSerializer(char* _Ptr, size_t _Size) : m_Offset(_Size), m_Mode(SerializerMode::Serializer)
    {
        m_Buffer.resize(_Size);
        memcpy_s(&m_Buffer[0], _Size, _Ptr, _Size);
    }
    GameEngineSerializer(unsigned int _BufferSize = 1024);
    ~GameEngineSerializer();

public: // delete constructer 
    GameEngineSerializer(const GameEngineSerializer& _Other) : m_Offset(_Other.m_Offset), m_Mode(_Other.m_Mode), m_Buffer(_Other.m_Buffer)
    {

    }

    GameEngineSerializer(GameEngineSerializer&& _Other) noexcept : m_Offset(_Other.m_Offset), m_Mode(_Other.m_Mode), m_Buffer(_Other.m_Buffer)
    {

    }

public: // delete operator
    GameEngineSerializer& operator=(const GameEngineSerializer& _Other)
    {
        m_Buffer = _Other.m_Buffer;
        m_Offset = _Other.m_Offset;
        m_Mode = _Other.m_Mode;
    }
    GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept
    {
        m_Buffer = _Other.m_Buffer;
        m_Offset = _Other.m_Offset;
        m_Mode = _Other.m_Mode;
    }

public:
    void Write(void* _Data, size_t _Size)
    {
        if (m_Mode != SerializerMode::Serializer)
        {
            m_Offset = 0;
            m_Mode = SerializerMode::Serializer;
        }

        if (m_Offset + sizeof(_Data) >= m_Buffer.size())
        {
            m_Buffer.resize(m_Buffer.size() * 2);
        }

        memcpy_s(&m_Buffer[m_Offset], _Size, _Data, _Size);

        m_Offset += _Size;
    }


    void Read(void* _Data, size_t _Size)
    {
        if (m_Mode != SerializerMode::DeSerializer)
        {
            m_Offset = 0;
            m_Mode = SerializerMode::DeSerializer;
        }

        memcpy_s(_Data, _Size, &m_Buffer[m_Offset], _Size);
        m_Offset += _Size;
    }

    void Write(bool data)
    {
        Write(&data, sizeof(data));
    }

    void Write(short data)
    {
        Write(&data, sizeof(data));
    }

    void Write(unsigned short data)
    {
        Write(&data, sizeof(data));
    }

    void Write(int data)
    {
        Write(&data, sizeof(data));
    }

    void Write(unsigned int data)
    {
        Write(&data, sizeof(data));
    }

    void Write(__int64 data)
    {
        Write(&data, sizeof(data));
    }

    void Write(unsigned __int64 data)
    {
        Write(&data, sizeof(data));
    }

    void Write(float data)
    {
        Write(&data, sizeof(data));
    }

    void Write(double data)
    {
        Write(&data, sizeof(data));
    }

    void Write(GameEngineSerializerObject& data)
    {
        data.Serialize(*this);
    }

    void Write(GameEngineString& data)
    {
        Write(data.m_String.size());
        if (!data.m_String.empty())
        {
            Write((void*)(data.m_String.c_str()), data.m_String.size() * sizeof(wchar_t));
        }
    }

    void Write(float4& data)
    {
        Write(data.x);
        Write(data.y);
        Write(data.z);
        Write(data.w);
    }

    template <typename T>
    void operator << (T& data)
    {
        if constexpr (std::is_enum_v<T>)
        {
            Write((void*)&data, sizeof(data));
        }
        if constexpr (!std::is_enum_v<T>)
        {
            Write(data);
        }
    }

    template <typename T>
    void operator << (std::vector<T>& data)
    {
        Write(data.size());
        if (!data.empty())
        {
            for (T& tmp : data)
            {
                *this << tmp;
            }
        }
    }

    void Read(bool& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(short& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(unsigned short& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(int& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(unsigned int& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(__int64& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(unsigned __int64& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(float& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(double& data)
    {
        Read(&data, sizeof(data));
    }

    void Read(GameEngineSerializerObject& data)
    {
        data.DeSerialize(*this);
    }

    void Read(GameEngineString& data)
    {
        size_t size = 0;
        Read(size);
        if (0 != size)
        {
            data.m_String.resize(size);
            Read((void*)&data.m_String[0], size * sizeof(wchar_t));
        }
    }

    void Read(float4& data)
    {
        Read(data.x);
        Read(data.y);
        Read(data.z);
        Read(data.w);
    }

    template <typename T>
    void operator >> (T& data)
    {
        if constexpr (std::is_enum_v<T>)
        {
            Read((void*)&data, sizeof(data));
        }
        if constexpr (!std::is_enum_v<T>)
        {
            Read(data);
        }
    }

    template <typename T>
    void operator >> (std::vector<T>& data)
    {
        size_t size = 0;
        Read(size);
        for (size_t n = 0; n < size; ++n)
        {
            T tmp = {};
            *this >> tmp;
            data.push_back(tmp);
        }
    }

    template<typename T>
    void Change(const T& _Data, int _Offset)
    {
        // 기존의 데이터가 수정되고
        // 모든 패킷을 만든다음 마지막에 사이즈만 사이즈 위치에 수정(덮어 씌워서)
        // 패킷의 사이지를 정확하게 보낼 예정.
        memcpy_s(&m_Buffer[_Offset], sizeof(T), &_Data, sizeof(T));
    }

    void ChangeToOffset(int _Offset)
    {
        // 기존의 데이터가 수정되고
        // 모든 패킷을 만든다음 마지막에 사이즈만 사이즈 위치에 수정(덮어 씌워서)
        // 패킷의 사이지를 정확하게 보낼 예정.
        Change(GetOffsetInt(), _Offset);
    }

};