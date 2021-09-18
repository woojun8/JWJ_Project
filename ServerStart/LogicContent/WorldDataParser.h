#pragma once
#include <GEMath.h>
#include <list>
#include <GameEngineString.h>

class PotalData 
{
public:
    float4 Pos; // 어떤 위치에 있고
    float4 Index; // 어떤 맵과 연결된다.
    float4 MovePos; // 이동했을때 내가 위치해야하는 곳.
};

class WorldData 
{
public:
    float4 Index;
    float4 Size;
    std::list<PotalData> m_PotalData;
};

// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class WorldDataParser
{
private: // Static Var
public: // Static Func
    static WorldData GetStringToWorldData(const GameEngineString& _MapText) 
    {
        WorldData ReturnWorldData;

        GameEngineString DeleteTrimData = _MapText.DeleteString(L' ');

        std::list<GameEngineString> ListStr = DeleteTrimData.StringCutToList(L';');

        for (GameEngineString Data : ListStr)
        {
            std::vector<GameEngineString> ParsingData = Data.StringCutToVector(L':');

            if (ParsingData[0] == L"Index")
            {
                std::vector<GameEngineString> Value = ParsingData[1].StringCutToVector(L',');

                ReturnWorldData.Index = { Value[0].Toint(), Value[1].Toint() };
            }
            else if(ParsingData[0] == L"Size")
            {
                std::vector<GameEngineString> Value = ParsingData[1].StringCutToVector(L',');
                ReturnWorldData.Size = { Value[0].Toint(), Value[1].Toint() };
            }
            else if (ParsingData[0] == L"PotalData")
            {
                std::vector<GameEngineString> PosAndIndex = ParsingData[1].StringCutToVector(L'|');

                std::vector<GameEngineString> PosData = PosAndIndex[0].StringCutToVector(L',');
                std::vector<GameEngineString> IndexData = PosAndIndex[1].StringCutToVector(L',');
                std::vector<GameEngineString> MovePosData = PosAndIndex[2].StringCutToVector(L',');

                PotalData NewPotalData;
                NewPotalData.Pos = { PosData[0].Toint(), PosData[1].Toint() };
                NewPotalData.Index = { IndexData[0].Toint(), IndexData[1].Toint() };
                NewPotalData.MovePos = { MovePosData[0].Toint(), MovePosData[1].Toint() };
                ReturnWorldData.m_PotalData.push_back(NewPotalData);
            }

        }

        return ReturnWorldData;
    }


private: // member Var

private: // constructer destructer
    WorldDataParser();
    ~WorldDataParser();

public: // delete constructer 
    WorldDataParser(const WorldDataParser& _Other) = delete;
    WorldDataParser(const WorldDataParser&& _Other) = delete;

public: // delete operator
    WorldDataParser& operator=(const WorldDataParser& _Other) = delete;
    WorldDataParser& operator=(const WorldDataParser&& _Other) = delete;

public: // member Func
};

