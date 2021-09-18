#pragma once
#include "World.h"
#include <map>
#include <string>
#include <queue>

// 분류1 : Management Object
// 분류2 : 
// 용도 : Management
// 설명 : 클라이언트를 월드를 여러개 만들수 있으므로
//        그에 대한 관리를 이녀석이 처리해준다.
//        
class WorldManager
{
private: // Static Var
public: // Static Func


    
private:
    // 새로운 액터를 만들어라.
    // 유저가 움직였다.
    // 아이템을 획득했다.
    // 이런것들을 여기에다 쌓고
    std::map<std::string, std::shared_ptr<World>> m_AllWorld;
    std::list<std::shared_ptr<World>> m_UpdateWorldList;
    std::map<std::string, std::shared_ptr<World>> m_UpdateWorldMap;

private:
    int m_FrameRate;
    float FrameRateTime;
    float CurFrameRateTime;
    float FrameRateDeltaTime;

public:
    void SetUpdateFrameRate(int FrameRate) 
    {
        m_FrameRate = FrameRate;
        FrameRateTime = 1.0f / static_cast<float>(m_FrameRate);
        CurFrameRateTime = 0.0f;
        FrameRateDeltaTime = 0.0f;
    }

    

public:
    // 이번건 상속 방식.
    template<typename T>
    std::shared_ptr<T> CreateWorld(std::string _Name)
    {
        if (m_AllWorld.end() != m_AllWorld.find(_Name))
        {
            return nullptr;
        }

        T* NewWorld = new T();
        NewWorld->SetManager(this);
        std::shared_ptr<World> Ptr(NewWorld);
        m_AllWorld[_Name] = Ptr;
        return std::dynamic_pointer_cast<T, World>(Ptr);
    }
    std::shared_ptr<World> FindWorld(std::string _Name);
    virtual void UpdateCheck(std::string _Name);


public: // constructer destructer
    WorldManager();
    ~WorldManager();

public: // delete constructer 
    WorldManager(const WorldManager& _Other) = delete;
    WorldManager(const WorldManager&& _Other) = delete;

public: // delete operator
    WorldManager& operator=(const WorldManager& _Other) = delete;
    WorldManager& operator=(const WorldManager&& _Other) = delete;

public: // member Func
    void Progress(float _DeltaTime);
    
};

