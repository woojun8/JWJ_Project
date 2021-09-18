#pragma once
#ifndef UNREALDEFINE
#include <GameEngineDebug.h>
#include <string>
#include <vector>

class KEYVALUE
{
public:
    std::string Key;
    std::string Value;
};

class CONSTKEYVALUE
{
public:
    const std::string& Key;
    const std::string& Value;
};

class StringViewHelper
{
public:

};

class RedisConnecter;
class RedisResult
{
public:
    enum RESULTTYPE
    {
        Result_SimpleString,// 1. 그 결과가 단순한 문자열이라면 + 가 맨앞에 온다.
        Result_Error,// 2. 그 결과가 에러라면 - 가 맨앞에 온다.
        Result_Integer,// 3. 그 결과가 정수라면 ":"
        Result_BulkString, // 4. 그 결과가 Bulk Strings(개수가 많은 문자열)라면 "$"
        Result_Array, // 5. 그 결과가 Arrays()라면 "*"
    };

    class RedisValue
    {
    public:
        std::string_view View;
        std::string_view ValueView; // 값만을 확인하고 저장하기 위한 view
        unsigned int Size;
        RESULTTYPE Type;
    };

public:
    RedisConnecter* m_Connecter;
    std::string Result;
    std::string_view MainStringView;
    unsigned int Count;
    RESULTTYPE Type;
    RedisValue StartValue;
    RedisValue* PrevValue;

    // std::vector<RedisValue> Vector;

public:
    bool ValueParse(RedisValue& _Data);
    std::vector<RedisValue> ListValueParse();

    void Parse();
    void ParseStart();

public:
    RedisResult(const std::string& _Result) : Result(_Result), MainStringView(Result), PrevValue(nullptr)
    {
        ParseStart();
    }

    // RValue도 만들어주는것이 좋다.
    RedisResult(std::string&& _Result) : Result(_Result), MainStringView(Result), PrevValue(nullptr)
    {
        ParseStart();
    }

    RedisResult(RedisConnecter* _Connecter, const std::string& _Result) : Result(_Result), MainStringView(Result), PrevValue(nullptr), m_Connecter(_Connecter)
    {
        ParseStart();
    }

    // RValue도 만들어주는것이 좋다.
    RedisResult(RedisConnecter* _Connecter, std::string&& _Result) : Result(_Result), MainStringView(Result), PrevValue(nullptr), m_Connecter(_Connecter)
    {
        ParseStart();
    }

};

class RedisCommand
{
public:
    class ResultParse
    {
    public:
    };

    class CommandBase
    {
    protected:
        std::string QueryCommand;

    public:
        const char* GetCommandPtr() const
        {
            return QueryCommand.c_str();
        }

        size_t GetCommandSize() const
        {
            return QueryCommand.size();
        }

        void TrimPlus(const std::string& _Value)
        {
            QueryCommand += _Value;
            QueryCommand += " ";
        }

        void Plus(const std::string& _Value)
        {
            QueryCommand += _Value;
        }

        void PlusInt(size_t intValue)
        {
            QueryCommand += std::to_string(intValue);
            QueryCommand += " ";
        }

        void ValueEnd()
        {
            QueryCommand += "\r\n";
        }

    public:
        CommandBase() {}
        CommandBase(const std::string& _Query)
        {
            TrimPlus(_Query);
        }
    };

public:
    class MSET : public CommandBase
    {
    public:
        template<typename ... REST>
        void ArgValue(KEYVALUE& _Data, REST&& ... _Arg) 
        {
            PushConstKeyValue(_Data, _Arg...);
        }

        template<typename ... REST>
        void PushConstKeyValue(KEYVALUE& _Data, REST&& ... _Arg)
        {
            TrimPlus(_Data.Key);
            TrimPlus(_Data.Value);
            PushConstKeyValue(_Arg...);
        }

        void PushConstKeyValue()
        {
            ValueEnd();
        }


        template<typename ... REST>
        void PushKeyValue(const std::string& _Key, const std::string& _Value, const REST& ... _Arg)
        {
            TrimPlus(_Key);
            TrimPlus(_Value);
            PushKeyValue(_Arg...);
        }

        void PushKeyValue()
        {
            ValueEnd();
        }

    public:
        template<typename ... REST>
        MSET(const REST& ... _Arg)
            : CommandBase("MSET")
        {
            if (0 != (sizeof...(REST) % 2))
            {
                GameEngineDebug::AssertMsg("if (0 != (sizeof(_Arg...) % 2))");
            }

            PushKeyValue(_Arg...);
        }

        template<typename ... REST>
        MSET(KEYVALUE& _Value, REST ... _Arg)
            : CommandBase("MSET")
        {
            PushConstKeyValue(_Arg...);
        }

    };


    class ZADD : public CommandBase
    {
    public:
        void ArgValue(const std::string& _RootKey, const int& _Score, const std::string& _Key)
        {
            TrimPlus(_RootKey);
            TrimPlus(std::to_string(_Score));
            TrimPlus(_Key);
            ValueEnd();
        }


        ZADD() : CommandBase("ZADD")
        {
        }
    };

    class MGET : public CommandBase
    {
    public:
        template<typename ... REST>
        void ArgValue(REST&& ... _Arg)
        {
            PushKey(_Arg...);
        }

        template<typename ... REST>
        void PushKey(const std::string& _Key, const REST& ... _Arg)
        {
            TrimPlus(_Key);
            PushKey(_Arg...);
        }

        void PushKey()
        {
            ValueEnd();
        }

    public:
        template<typename ... REST>
        MGET(REST ... _Arg)
            : CommandBase("MGET")
        {
            PushKey(_Arg...);
        }

    };

    class SET : public CommandBase
    {
    public:
        void ArgValue(const std::string& _Key, const std::string& _Value)
        {
            TrimPlus(_Key);
            TrimPlus(_Value);
            ValueEnd();
        }

        SET() 
            : CommandBase("SET")
        {

        }


        SET(const std::string& _Key, const std::string& _Value)
            : CommandBase("SET")
        {
            TrimPlus(_Key);
            TrimPlus(_Value);
            ValueEnd();
        }
    };


    class ZRANGE : public CommandBase
    {
    public:
        void ArgValue(const std::string& _Key, const int& _Start, const int& _End, bool _IsWithScores = true)
        {
            TrimPlus(_Key);
            TrimPlus(std::to_string(_Start));
            TrimPlus(std::to_string(_End));
            if (true == _IsWithScores)
            {
                TrimPlus("WITHSCORES");
            }
            ValueEnd();
        }

        ZRANGE()
            : CommandBase("ZRANGE")
        {

        }
    };



    class ZREVRANGE : public CommandBase
    {
    public:
        void ArgValue(const std::string& _Key, const int& _Start, const int& _End, bool _IsWithScores = true)
        {
            TrimPlus(_Key);
            TrimPlus(std::to_string(_Start));
            TrimPlus(std::to_string(_End));
            if (true == _IsWithScores)
            {
                TrimPlus("WITHSCORES");
            }
            ValueEnd();
        }

        ZREVRANGE(const std::string& _Key, const int& _Start, const int& _End, bool _IsWithScores = true)
            : CommandBase("ZREVRANGE")
        {
            ArgValue(_Key, _Start, _End, _IsWithScores);
        }

        ZREVRANGE()
            : CommandBase("ZREVRANGE")
        {

        }
    };

    class ZCOUNT : public CommandBase
    {
    public:
        void ArgValue(const std::string& _Key, const int& _Start, const int& _End)
        {
            TrimPlus(_Key);
            TrimPlus(std::to_string(_Start));
            TrimPlus(std::to_string(_End));
            ValueEnd();
        }

        ZCOUNT(const std::string& _Key, const int& _Start, const int& _End)
            : CommandBase("ZCOUNT")
        {
            ArgValue(_Key, _Start, _End);
        }

        ZCOUNT()
            : CommandBase("ZCOUNT")
        {

        }
    };


    class ZREVRANK : public CommandBase
    {
    public:
        void ArgValue(const std::string& _Key, const std::string& _Name)
        {
            TrimPlus(_Key);
            TrimPlus(_Name);
            ValueEnd();
        }

        ZREVRANK(const std::string& _Key, const std::string& _Name)
            : CommandBase("ZREVRANK")
        {
            ArgValue(_Key, _Name);
        }

        ZREVRANK()
            : CommandBase("ZREVRANK")
        {

        }
    };

    class GET : public CommandBase
    {
    public:
        GET(const std::string& _Key, const std::string& _Value)
            : CommandBase("GET")
        {
            TrimPlus(_Key);
            TrimPlus(_Value);
            ValueEnd();
        }
    };

    class ScriptLoad : public CommandBase
    {
    public:
        ScriptLoad(const std::string& script)
            : CommandBase("script load")
        {
            //Plus("\"");
            TrimPlus(script);
            //Plus("\"");
            ValueEnd();
        }
    };

    class EVALSHA : public CommandBase
    {
    public:
        EVALSHA(const std::string& sha, const std::vector<std::string>* keys = nullptr, const std::vector<std::string>* argvs = nullptr)
            :
            CommandBase("EVALSHA")
        {
            Plus("\"");
            Plus(sha);
            Plus("\"");
            Plus(" ");

            if (nullptr != keys && !keys->empty())
            {
                PlusInt(keys->size());
                for (const std::string& key : *keys)
                {
                    TrimPlus(key);
                }
            }

            if (nullptr != argvs && !argvs->empty())
            {
                for (const std::string& argv : *argvs)
                {
                    TrimPlus(argv);
                }
            }

            ValueEnd();
        }
    };

private:
    RedisCommand() {}
    ~RedisCommand() {}
};


#endif

