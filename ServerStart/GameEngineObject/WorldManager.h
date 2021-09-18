#pragma once
#include "World.h"
#include <map>
#include <string>
#include <queue>

// �з�1 : Management Object
// �з�2 : 
// �뵵 : Management
// ���� : Ŭ���̾�Ʈ�� ���带 ������ ����� �����Ƿ�
//        �׿� ���� ������ �̳༮�� ó�����ش�.
//        
class WorldManager
{
private: // Static Var
public: // Static Func


    
private:
    // ���ο� ���͸� ������.
    // ������ ��������.
    // �������� ȹ���ߴ�.
    // �̷��͵��� ���⿡�� �װ�
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
    // �̹��� ��� ���.
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

