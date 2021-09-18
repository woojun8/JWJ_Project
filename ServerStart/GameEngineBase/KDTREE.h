#pragma once
#include "GEMath.h"
#include <vector>
#include <algorithm>
#include <numeric> // ���� Ư���� �˰����� ����Ҽ� �ְ� �ϴ� Ȯ�� �˰���
#include <exception> // �� �˰� �ɰ̴ϴ�.

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
        // 0 ���� �ڽ�
        // 1 ������ �ڽ�
        KDNode* next[2];
        int axis; // ���� x[0] y[1] z[2]

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

        // ������ x y
        const int axis = _Depth % DIM;
        const int mid = (_MaxSize - 1)/ 2;

        // _ArrIndex
        // PointVector
        // �̳༮�� ũ�⿡ ���� _ArrIndex�� �����Ϸ��� 

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
        // ���߿��� ���� �ڱ� �θ� ���ϴ� �༮����ϴ�.
        Node->next[1] = BuildNodes(_ArrIndex + mid + 1, _MaxSize - mid - 1, _Depth + 1);

        return Node;
    }

    // �̹� ���⼭ ���浹�� ���ִ°�
    // kdƮ���� �ñ����� �ǹ̴� 1000 * 1000�� 
    // 1 * 10 �̷������� �ش������� �ٿ��ټ� �ִٴ°��̴�.
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

        // �����ϼ��� �ְ� �������ϼ��� �ִ°�
        RadiusSearchRecursive(_Pivot, _Node->next[Dir], _Result, radius);

        // 
        const float OutRangeCheck = static_cast<float>(fabs((double)(_Pivot[axis] - CheckKey[axis])));

        // �� �ݴ���?
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
        // ������ kdƮ���� �־��ٰ� �ϴ��� �ı��ϰ� �ٽ� ����� �����մϴ�.
        Clear();

        if (nullptr == _Points)
        {
            return;
        }

        PointVector = _Points;

        // �̷��� ����������?
        std::vector<int> indices(_Points->size());
        std::iota(std::begin(indices), std::end(indices), 0);

        // ù��° �����͸� �ݴϴ�.
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

    // �����ͷ� �޵��� �ϰڽ��ϴ�.
    KDTree(const std::vector<KDTreeKey>* _PointVector, int _Dim = 2) : Root(nullptr), PointVector(nullptr), DIM(_Dim)
    {
        Build(_PointVector);
    }

    ~KDTree() 
    {
        Clear();
    }

};