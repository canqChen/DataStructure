#pragma once
#include<iostream>
#include <stack>
#include <Queue>

#define ElemType int
typedef struct BiTreeNode {
	ElemType data;
	struct BiTreeNode *lChild, *rChild;
}BiTreeNode, * pBiTreeNode;

class BiTree
{
public:
	BiTree();

	~BiTree();

	void printTree(int order=0);
	
private:
	pBiTreeNode root;

	void preOrderTraverse(pBiTreeNode node);
	void midOrderTraverse(pBiTreeNode node);
	void postOrderTraverse(pBiTreeNode node);
	void levelOrderTraverse(pBiTreeNode node);
	void visit(pBiTreeNode node);
};

BiTree::BiTree()
{

}

// print the data of all nodes in the tree, order is to select the traverse approaches, 
//0 for pre-order, 1 for mid-order and 2 for post-order
inline void BiTree::printTree(int order=0)
{
	if (root == nullptr)
		std::cout << "tree is empty!";
	switch (order)
	{
	case 0:
		preOrderTraverse(root);
		break;
	case 1:
		midOrderTraverse(root);
		break;
	case 2:
		postOrderTraverse(root);
		break;
	default:
		std::cout << "bad order!";
		break;
	}
}

inline void BiTree::preOrderTraverse(pBiTreeNode node)
{
	if (node == nullptr)
		return;
	else
	{
		visit(node);
		preOrderTraverse(node->lChild);
		preOrderTraverse(node->rChild);
	}
	
}

inline void BiTree::midOrderTraverse(pBiTreeNode node)
{
	/* recursive implementation
	if (node == nullptr)
		return;
	else
	{
		preOrderTraverse(node->lChild);
		visit(node);
		preOrderTraverse(node->rChild);
	}
	*/
	// non-recursive implementation, exploit stack
	std::stack<pBiTreeNode> nodeStk;
	pBiTreeNode tmp = node;
	while (tmp || !nodeStk.empty())
	{
		if (tmp !=nullptr)
		{
			nodeStk.push(tmp);
			tmp = tmp->lChild;
		}
		else
		{
			visit(nodeStk.top());
			tmp = nodeStk.top()->rChild;
			nodeStk.pop();
		}
	}
}


inline void BiTree::postOrderTraverse(pBiTreeNode node)
{
	if (node == nullptr)
		return;
	else
	{
		preOrderTraverse(node->lChild);
		preOrderTraverse(node->rChild);
		visit(node);
	}
}

inline void BiTree::levelOrderTraverse(pBiTreeNode node)
{
	if (node == nullptr)
		return;
	std::queue<pBiTreeNode> nodeQ;
	nodeQ.push(node);
	while (!nodeQ.empty())
	{
		visit(nodeQ.front());
		if (nodeQ.front()->lChild != nullptr)
			nodeQ.push(nodeQ.front()->lChild);
		if (nodeQ.front()->rChild != nullptr)
			nodeQ.push(nodeQ.front()->rChild);
		nodeQ.pop();
	}
}

// do something to the node, print its data here.
inline void BiTree::visit(pBiTreeNode node)
{
	if(node!=nullptr)
		std::cout << node->data;
}

BiTree::~BiTree()
{

}
