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

class Graph
{
public:
	Graph(vector<int>& vtxList, vector<vector<int>>& adjMat);  // adjacent matrix initialization
	Graph(vector<int>& vtxList, vector<vector<int>>& adjMat);  // adjacent list

	~Graph();

private:
	vector<int> vtxListBymat;
	vector<vector<int>> adjMat;
	pVtxNode vtxListBylist;
	int vtxNum, arcNum;
};

Graph::Graph(vector<int>& vtxList, vector<vector<int>>& adjMat) :vtxList(vtxList), adjMat(adjMat)
{

}

Graph::~Graph()
{

}