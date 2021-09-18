#pragma once
#include "GEMath.h"
#include <vector>
#include <algorithm>
#include <numeric> // 정수 특정한 알고리짐을 사용할수 있게 하는 확장 알고리즘
#include <exception> // 곧 알게 될겁니다.

// using  KDTreeKey = float4;

template<typename KDTreeKey>
class KDTree 
{
public:
    // std::vector<KDNode> PoolNode = std::vector<KDNode>(10000);

private:
    class KDNode
    {
    public:
        //KDTreeKey
        int idx;
        // 0 왼쪽 자식
        // 1 오른쪽 자식
        KDNode* next[2];
        int axis; // 차원 x[0] y[1] z[2]

    public:
        KDNode() : next{nullptr, nullptr}
        {

        }
    };

    int DIM;
    KDNode* Root;
    const std::vector<KDTreeKey>* PointVector;

public:
    KDNode* BuildNodes(int* _ArrIndex, int _MaxSize, int _Depth)
    {
        if (_MaxSize <= 0)
        {
            return nullptr;
        }

        // 차원축 x y
        const int axis = _Depth % DIM;
        const int mid = (_MaxSize - 1)/ 2;

        // _ArrIndex
        // PointVector
        // 이녀석의 크기에 따라서 _ArrIndex를 변경하려는 

        std::nth_element(_ArrIndex, _ArrIndex + mid, _ArrIndex + _MaxSize, [&](int _Left, int _Right)
            {
                return (*PointVector)[_Left][axis] < (*PointVector)[_Right][axis];
            }
        );

        KDNode* Node = new KDNode();
        Node->idx = _ArrIndex[mid];
        Node->axis = axis;

        // 0~ 49
        Node->next[0] = BuildNodes(_ArrIndex, mid, _Depth + 1);
        // 50~99
        // 그중에서 다음 자기 부모를 정하는 녀석ㅇ비니다.
        Node->next[1] = BuildNodes(_ArrIndex + mid + 1, _MaxSize - mid - 1, _Depth + 1);

        return Node;
    }

    // 이미 여기서 원충돌을 해주는것
    // kd트리의 궁극적인 의미는 1000 * 1000을 
    // 1 * 10 이런식으로 극단적으로 줄여줄수 있다는것이다.
    float Distance(const KDTreeKey& _Left, const KDTreeKey& _Right)
    {
        float Dist = 0;
        for (int i = 0; i < DIM; i++)
        {
            Dist += (_Left[i] - _Right[i]) * (_Left[i] - _Right[i]);
        }
        return sqrtf(Dist);
    }

    void RadiusSearchRecursive(const KDTreeKey& _Pivot, KDNode* _Node, std::vector<int>& _Result, float radius) 
    {
        if (nullptr == _Node)
        {
            return;
        }

        const KDTreeKey& CheckKey = (*PointVector)[_Node->idx];
        float Dis = Distance(_Pivot, CheckKey);

        if (Dis < radius)
        {
            _Result.push_back(_Node->idx);
        }

        const int axis = _Node->axis;
        const int Dir = _Pivot[axis] < CheckKey[axis] ? 0 : 1;

        // 왼쪽일수도 있고 오른쪽일수도 있는것
        RadiusSearchRecursive(_Pivot, _Node->next[Dir], _Result, radius);

        // 
        const float OutRangeCheck = static_cast<float>(fabs((double)(_Pivot[axis] - CheckKey[axis])));

        // 그 반대죠?
        if (OutRangeCheck < radius)
        {
            RadiusSearchRecursive(_Pivot, _Node->next[!Dir], _Result, radius);
        }
    }

public:
    std::vector<int> RadiusSearch(const KDTreeKey& _Pivot, float radius)
    {
        std::vector<int> indices;
        RadiusSearchRecursive(_Pivot, Root, indices, radius);
        return indices;
    }

    void Build(const std::vector<KDTreeKey>* _Points)
    {
        // 기존에 kd트리가 있었다고 하더라도 파괴하고 다시 만들기 시작합니다.
        Clear();

        if (nullptr == _Points)
        {
            return;
        }

        PointVector = _Points;

        // 이러면 리사이즈죠?
        std::vector<int> indices(_Points->size());
        std::iota(std::begin(indices), std::end(indices), 0);

        // 첫번째 포인터를 줍니다.
        Root = BuildNodes(indices.data(), static_cast<int>(_Points->size()), 0);

        //for (int  i = 0; i < _Points->size(); i++)
        //{
        //    indices[i] = i;
        //}

        

    }

    void Clear() 
    {
        ClearNode(Root);
        // Clear
        Root = nullptr;
        PointVector = nullptr;
    }

private:
    void ClearNode(KDNode* _Node)
    {
        if (nullptr == _Node)
        {
            return;
        }

        ClearNode(_Node->next[0]);

        ClearNode(_Node->next[1]);

        delete _Node;
    }


public:
    KDTree(int _Dim = 2) : Root(nullptr), PointVector(nullptr), DIM(_Dim)
    {}

    // 포인터로 받도록 하겠습니다.
    KDTree(const std::vector<KDTreeKey>* _PointVector, int _Dim = 2) : Root(nullptr), PointVector(nullptr), DIM(_Dim)
    {
        Build(_PointVector);
    }

    ~KDTree() 
    {
        Clear();
    }

};