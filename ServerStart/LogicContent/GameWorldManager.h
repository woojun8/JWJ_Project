#pragma once
#include <WorldManager.h>
#include <map>
#include <GEMath.h>
#include <GameEngineDebug.h>

// □□□
// □□□
// □□□

class PosToKeyConvert
{
public:
    union
    {
        struct
        {
            int X;
            int Y;
        };
        __int64 Key;
    };

public:
    std::string ToString() 
    {
        std::string KeyX = std::to_string(X);
        std::string KeyY = std::to_string(Y);
        return KeyX + "," + KeyY;
    }

public:
    PosToKeyConvert(const Posfloat4& _Pos)  : X(_Pos.ix()), Y(_Pos.iy())
    {

    }

    PosToKeyConvert(const std::string& _String) 
    {
        size_t Size = _String.find(",");

        if (std::string::npos == Size)
        {
            GameEngineDebug::AssertMsg("if (std::string::npos == Size)");
        }

        std::string StrX = _String.substr(0, Size);
        std::string StrY = _String.substr(Size + 1, _String.size());

        X = atoi(StrX.c_str());
        Y = atoi(StrX.c_str());

        int a = 0;

        // : X(_Pos.ix()), Y(_Pos.iy())
    }
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class GameWorld;
class GameWorldManager : public WorldManager
{
private: // Static Var
public: // Static Func
private: // member Var

public: // constructer destructer
    GameWorldManager();
    ~GameWorldManager();

public: // delete constructer 
    GameWorldManager(const GameWorldManager& _Other) = delete;
    GameWorldManager(const GameWorldManager&& _Other) = delete;

public: // delete operator
    GameWorldManager& operator=(const GameWorldManager& _Other) = delete;
    GameWorldManager& operator=(const GameWorldManager&& _Other) = delete;

public: // member Func
    void UpdateCheck(const Posfloat4& _Pos);


    // virtual std::shared_ptr<GameWorld> CreateGameWorld(const Posfloat4& _Pos, const Sizefloat4& _Size);
    //std::shared_ptr<GameWorld> FindWorld(const Posfloat4& _Pos);
    //std::shared_ptr<GameWorld> FindWorld(const PosToKeyConvert& _Key);
};

