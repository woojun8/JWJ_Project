#ifndef UNREALDEFINE

#include "RedisCommand.h"
#include <string>
#include <string_view>

bool RedisResult::ValueParse(RedisValue& _Data)
{
    size_t Result = MainStringView.find("\r\n");

    if (Result == std::string::npos)
    {
        // 이게 끝이 됩니다.
        return false;
    }

    //SimpleString,// 1. 그 결과가 단순한 문자열이라면 + 가 맨앞에 온다.
    //Error,// 2. 그 결과가 에러라면 - 가 맨앞에 온다.
    //Integer,// 3. 그 결과가 정수라면 ":"
    //BulkString, // 4. 그 결과가 Bulk Strings(개수가 많은 문자열)라면 "$"
    //Array, // 5. 그 결과가 Arrays()라면 "*"
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