#pragma once
#include<iostream>
#include <stack>
#include <Queue>
#include<string>

using namespace std;

// linked list implementation
//typedef struct HuffmanTreeNode {
//	ElemType weight;
//	struct HuffmanTreeNode *parent, *lChild, *rChild;
//	HuffmanTreeNode(ElemType weight=0): weight(weight), parent(nullptr), lChild(nullptr), rChild(nullptr)
//	{}
//}HfmTreeNode, * pHfmTreeNode;

// linear list implementation
typedef struct HuffmanTreeNode {
	int weight;
	int parent, lChild, rChild;
	HuffmanTreeNode(int weight = 0) : weight(weight), parent(0), lChild(0), rChild(0)
	{}
}HfmTreeNode, * pHfmTreeNode;

class HuffmanTree
{
public:
	HuffmanTree(vector<int>& weights);

	~HuffmanTree();

private:
	pHfmTreeNode hfmTree = nullptr;
	vector<int> weights;
	//void buildHfmTreeByLinkedList(vector<ElemType> &weights);
	void buildHfmTreeByArray();
};

HuffmanTree::HuffmanTree(vector<int>& weights) :weights(weights)
{
	// buildHfmTreeByLinkedList(weights);
}

void HuffmanTree::buildHfmTreeByArray()
{
	if (weights.size() < 1)
	{
		return;
	}
	int m = 2 * weights.size() - 1;
	hfmTree = new HfmTreeNode[m];
	for (int i = 0; i < weights.size(); i++)
	{
		hfmTree[i].weight = weights[i];
	}
	for (int i = weights.size();i<m;i++)
	{
		// find the smallest two weights
		int min, secMin, j, minIdx=0, secMinIdx=0;
		for (j=0;j<i-1;j++)
		{
			if (hfmTree[j].parent==0)
			{
				min = hfmTree[j].weight;
				secMin = hfmTree[j].weight;
				minIdx = secMinIdx = j;
				break;
			}
		}
		for (int k=j;k<i-1;k++)
		{
			if (hfmTree[k].parent == 0&& hfmTree[k].weight<min)
			{
				min = hfmTree[k].weight;
				minIdx = k;
			}
			else if (hfmTree[k].parent == 0 && hfmTree[k].weight < secMin)
			{
				secMin = hfmTree[k].weight;
				secMinIdx = k;
			}
		}

		hfmTree[i].weight = hfmTree[minIdx].weight + hfmTree[secMinIdx].weight;
		hfmTree[i].lChild = minIdx;
		hfmTree[i].rChild = secMinIdx;
		hfmTree[minIdx].parent = hfmTree[secMinIdx].parent = i;
	}
}

// linked list implementation
//void HuffmanTree::buildHfmTreeByLinkedList(vector<int> & weights)
//{
//	vector<pHfmTreeNode> forest;
//	for (auto itm : weights)
//	{
//		forest.push_back(new HfmTreeNode(itm));
//	}
//	while (forest.size()>1)
//	{
//		int minW = forest[0]->weight > forest[1]->weight ? forest[1]->weight : forest[0]->weight;
//		int secMinW = forest[0]->weight > forest[1]->weight ? forest[0]->weight : forest[1]->weight;
//		int minIdx = forest[0]->weight > forest[1]->weight ? 1 : 0 , secMinIdx = forest[0]->weight > forest[1]->weight ? 0 : 1;
//		if (forest.size() > 2)
//		{
//			for (int i = 2; i<forest.size();i++)
//			{
//				if (forest[i]->weight<minW)
//				{
//					minW = forest[i]->weight;
//					minIdx = i;
//				}
//				else if (forest[i]->weight < secMinIdx)
//				{
//					secMinW = forest[i]->weight;
//					secMinIdx = i;
//				}
//			}
//		}
//		pHfmTreeNode t1 = forest[minIdx], t2 = forest[secMinIdx];
//		forest.erase(forest.begin() + minIdx);
//		forest.erase(forest.begin() + secMinIdx);
//		pHfmTreeNode newTree = new HfmTreeNode(t1->weight + t2->weight);
//		newTree->lChild = t2;
//		newTree->rChild = t1;
//		t1->parent = t2->parent = newTree;
//		forest.push_back(newTree);
//	}
//	root = forest[0];
//}

HuffmanTree::~HuffmanTree()
{
	if (hfmTree!=nullptr)
	{
		delete[] hfmTree;
	}
}
