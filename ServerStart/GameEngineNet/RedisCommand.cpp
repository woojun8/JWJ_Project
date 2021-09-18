#ifndef UNREALDEFINE

#include "RedisCommand.h"
#include <string>
#include <string_view>

bool RedisResult::ValueParse(RedisValue& _Data)
{
    size_t Result = MainStringView.find("\r\n");

    if (Result == std::string::npos)
    {
        // �̰� ���� �˴ϴ�.
        return false;
    }

    //SimpleString,// 1. �� ����� �ܼ��� ���ڿ��̶�� + �� �Ǿտ� �´�.
    //Error,// 2. �� ����� ������� - �� �Ǿտ� �´�.
    //Integer,// 3. �� ����� ������� ":"
    //BulkString, // 4. �� ����� Bulk Strings(������ ���� ���ڿ�)��� "$"
    //Array, // 5. �� ����� Arrays()��� "*"
    _Data.View = MainStringView.substr(0, Result);

    switch (MainStringView[0])
    {
    case '+'://SimpleString
        _Data.Size = 1;
        _Data.Type = Result_SimpleString;
        break;
    case '-'://Error
        _Data.Size = 1;
        _Data.Type = Result_Error;
        break;
    case ':'://Integer
        _Data.ValueView = _Data.View.substr(1, Result - 1);
        _Data.Size = std::stoi(&_Data.ValueView[0]);
        _Data.Type = Result_Integer;
        break;
    case '$'://BulkString
    {
        if ('-' != _Data.View[1])
        {
            _Data.ValueView = _Data.View.substr(1, Result - 1);
            _Data.Size = std::stoi(&_Data.ValueView[0]);;
            _Data.ValueView = MainStringView.substr(_Data.View.size() + 2, _Data.Size);
            Result = _Data.View.size() + 2 + _Data.Size;
            _Data.View = MainStringView.substr(0, Result);;
            _Data.Type = Result_BulkString;
        }
        else 
        {
            // _Data.View.substr(1, Result - 1);
            _Data.Type = Result_Error;
        }
        break;
    }
    case '*'://Array
    {
        _Data.ValueView = _Data.View.substr(1, Result - 1);
        _Data.Size = std::stoi(&_Data.ValueView[0]);
        _Data.Type = Result_Array;
        break;
    }
    default:
        break;
    }

    MainStringView = MainStringView.substr(Result + 2, -1);
    PrevValue = &_Data;
    return true;
}

void RedisResult::ParseStart()
{
    ValueParse(StartValue);
}

std::vector<RedisResult::RedisValue> RedisResult::ListValueParse()
{
    if (nullptr == PrevValue)
    {
        return std::vector<RedisResult::RedisValue>();
    }

    if (PrevValue->Type != Result_Array)
    {
        return std::vector<RedisResult::RedisValue>();
    }

    std::vector<RedisValue> Return;

    int Size = PrevValue->Size;

    Return.resize(PrevValue->Size);
    for (size_t i = 0; i < Return.size(); i++)
    {
        ValueParse(Return[i]);
    }

    return Return;
}

void RedisResult::Parse()
{
    StartValue;
}

#endif