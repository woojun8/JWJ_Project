#include "RedisResultFunc.h"
#include <ServerConnecter.h>
#include <ServerToClient.h>

void RedisResultFunc::RankResultProcess(RedisResult _Result, ServerConnecter* _Socket, int _Start, int _End)
{
    // add는 돼어있을 것이고
    // ok아닐때 예외처리를 걸어주는것이 좋을것이다.

    // 문제가 생기면 이쪽은 고쳐야 겠죠.

    RedisResult Result = 
        RedisManager::GetInst().GetConnecter().CommandArgResult<RedisCommand::ZREVRANGE>("RANK", 0, 4);

    //RedisManager::GetInst().RedisCommandPush<RedisCommand::ZREVRANGE>(
    //std::bind(&RedisResultFunc::RankResultProcess, std::placeholders::_1, _Socket, 0, 5),
    //"RANK", 0, 4);


    std::vector<RedisResult::RedisValue> RankResult = Result.ListValueParse();
    RankPacket Packet;
    for (int i = 0; i < RankResult.size(); i += 2)
    {

        char Name[45] = {};

        std::string_view& NameView = RankResult[i].ValueView;

        for (size_t i = 0; i < NameView.size(); i++)
        {
            Name[i] = NameView.at(i);
        }

        RankData Rank;
        Rank.Rank = (int)(i * 0.5f) + 1;
        Rank.Name = GameEngineString::GlobalSetConvertMultiByteString(Name);
        Rank.Score = std::atoi(RankResult[i + 1].ValueView.data());

        Packet.m_RankDataList.push_back(Rank);
    }

    _Socket->Send(Packet);
}

void RedisResultFunc::UserRankResultProcess(RedisResult _Result, ServerConnecter* _Socket)
{
    int AllRankUserCount = -1;
    int MyRankCount = -1;

    {
        RedisResult AllUserCount =
            RedisManager::GetInst().GetConnecter().CommandArgResult<RedisCommand::ZCOUNT>("RANK", 0, 100000000);
        AllRankUserCount = std::atoi(AllUserCount.StartValue.ValueView.data());
    }


    {
        RedisResult MyRankResult =
            RedisManager::GetInst().GetConnecter().CommandArgResult<RedisCommand::ZREVRANK>("RANK", _Socket->GetCharacterData()->Name);
        MyRankCount = std::atoi(MyRankResult.StartValue.ValueView.data());
    }

    // 0 ...... 23
    //   1
    // 

    // 1
    int RevRangeStart = MyRankCount - 2;
    int RevRangeEnd = MyRankCount + 2;

    // 0~4

    if (0 > RevRangeStart)
    {
        //                -1
        //                1
        int ChangeValue = abs(RevRangeStart);
        RevRangeStart += ChangeValue;
        RevRangeEnd += ChangeValue;
    } else if (AllRankUserCount <= RevRangeEnd)
    {
        //                -1
        //                1
        int ChangeValue = RevRangeEnd - AllRankUserCount;
        RevRangeStart -= ChangeValue;
        RevRangeEnd -= ChangeValue;
    }

    // 이상황은 아마 인원수가
    if (5 > AllRankUserCount)
    {
        RevRangeStart = RevRangeStart < 0 ? 0 : RevRangeStart;
        RevRangeEnd = RevRangeEnd > AllRankUserCount ? 0 : AllRankUserCount;
    }


    RedisResult Result =
        RedisManager::GetInst().GetConnecter().CommandArgResult<RedisCommand::ZREVRANGE>("RANK", RevRangeStart, RevRangeEnd);

    //RedisManager::GetInst().RedisCommandPush<RedisCommand::ZREVRANGE>(
    //std::bind(&RedisResultFunc::RankResultProcess, std::placeholders::_1, _Socket, 0, 5),
    //"RANK", 0, 4);


    std::vector<RedisResult::RedisValue> RankResult = Result.ListValueParse();
    RankPacket Packet;
    for (int i = 0; i < RankResult.size(); i += 2)
    {

        char Name[45] = {};

        std::string_view& NameView = RankResult[i].ValueView;

        for (size_t i = 0; i < NameView.size(); i++)
        {
            Name[i] = NameView.at(i);
        }

        RankData Rank;
        Rank.Rank = ++RevRangeStart;
        Rank.Name = GameEngineString::GlobalSetConvertMultiByteString(Name);
        Rank.Score = std::atoi(RankResult[i + 1].ValueView.data());

        Packet.m_RankDataList.push_back(Rank);
    }

    _Socket->Send(Packet);
}