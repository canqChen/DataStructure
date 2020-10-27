#pragma once
#include<iostream>
#include <stack>
#include <Queue>
#include<string>

using namespace std;


// adjacent list representation
typedef struct VtxNode
{
	int val;
	struct VtxNode* firstArc;

}VtxNode, pVtxNode;

typedef struct ActNode
{
	struct ActNode* nextArc;
	int adjAct;
	int weight;
}ActNode, pActNode;

class AMGraph
{
public:
	AMGraph(vector<int>& vtxList, vector<vector<int>> & adjMat);

	~AMGraph();

private:
	vector<int> vtxList;
	vector<vector<int>> adjMat;
};

AMGraph::AMGraph(vector<int>& vtxList, vector<vector<int>>& adjMat) :vtxList(vtxList), adjMat(adjMat)
{

}

AMGraph::~AMGraph()
{

}