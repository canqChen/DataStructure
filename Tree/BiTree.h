#ifndef __BiTree__
#define __BiTree__


#include<iostream>
#include <stack>
#include <Queue>
#include<string>

#define ElemType char
typedef struct BiTreeNode {
	ElemType data;
	struct BiTreeNode *lChild, *rChild;
}BiTreeNode, * pBiTreeNode;

class BiTree
{
public:
	BiTree(const char* nodeStr, int order = 0);
	BiTree(std::string nodeStr, int order = 0);
	BiTree(const BiTree & tree);

	~BiTree();

	void printTree(int order=0);
	int depth();
	int numOfNode();
	int numOfLeaf();
	void destroyTree();
private:
	pBiTreeNode root = nullptr;
	pBiTreeNode buildPreOrderBiTree(const char * nodeStr);
	void preOrderTraverse(pBiTreeNode node);
	void midOrderTraverse(pBiTreeNode node);
	void postOrderTraverse(pBiTreeNode node);
	void levelOrderTraverse(pBiTreeNode node);
	void visit(pBiTreeNode node);
	pBiTreeNode copy(pBiTreeNode node);
	int calDepth(pBiTreeNode node);
	int calNodeNum(pBiTreeNode node);
	int calLeafNum(pBiTreeNode node);
};

BiTree::BiTree(const char * nodeStr, int order = 0)
{
	buildPreOrderBiTree(nodeStr);
}

BiTree::BiTree(std::string nodeStr, int order = 0)
{
	buildPreOrderBiTree(nodeStr.c_str());
}

BiTree::BiTree(const BiTree& tree)
{
	root = copy(tree.root);
}

// print the data of all nodes in the tree, order is to select the traverse approaches, 
//0 for pre-order, 1 for mid-order and 2 for post-order
void BiTree::printTree(int order=0)
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

void BiTree::destroyTree()
{
	std::stack<pBiTreeNode> nodeStk;
	pBiTreeNode tmp = root;
	while (tmp || !nodeStk.empty())
	{
		if (tmp != nullptr)
		{
			nodeStk.push(tmp);
			tmp = tmp->lChild;
		}
		else
		{
			tmp = nodeStk.top()->rChild;
			delete nodeStk.top();
			nodeStk.pop();
		}
	}
	root = nullptr;
}

pBiTreeNode BiTree::buildPreOrderBiTree(const char* nodeStr)
{
	static int idx = 0;
	if (nodeStr[idx] == '\0')
	{
		idx = 0;
		return;
	}
	pBiTreeNode newNode = nullptr;
	if (nodeStr[idx] != '#')
	{
		newNode = new BiTreeNode;
		newNode->data = nodeStr[idx];
		if (root == nullptr) root = newNode;
		idx++;
		newNode->lChild = buildPreOrderBiTree(nodeStr);
		newNode->rChild = buildPreOrderBiTree(nodeStr);
	}
	return newNode;
}

void BiTree::preOrderTraverse(pBiTreeNode node)
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

void BiTree::midOrderTraverse(pBiTreeNode node)
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


void BiTree::postOrderTraverse(pBiTreeNode node)
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

void BiTree::levelOrderTraverse(pBiTreeNode node)
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
void BiTree::visit(pBiTreeNode node)
{
	if(node!=nullptr)
		std::cout << node->data;
}

pBiTreeNode BiTree::copy(pBiTreeNode node)
{
	if (node == nullptr)
		return nullptr;
	else
	{
		pBiTreeNode newNode = new BiTreeNode;
		newNode->data = node->data;
		newNode->lChild = copy(node->lChild);
		newNode->rChild = copy(node->rChild);
		return newNode;
	}
}

int BiTree::depth()
{
	return calDepth(root);
}

int BiTree::calDepth(pBiTreeNode node)
{
	if (node == nullptr)
		return 0;
	else
	{
		int lDepth = calDepth(node->lChild);
		int rDepth = calDepth(node->rChild);
		return lDepth > rDepth ? lDepth + 1 : rDepth + 1;
	}
}

int BiTree::numOfNode()
{
	return calNodeNum(root);
}

int BiTree::calNodeNum(pBiTreeNode node)
{
	if (node == nullptr)
		return 0;
	else
		return calNodeNum(node->lChild) + calNodeNum(node->rChild) + 1;
}

int BiTree::numOfLeaf()
{
	return calNodeNum(root);
}

int BiTree::calLeafNum(pBiTreeNode node)
{
	if (node == nullptr)
		return 0;
	if (node->lChild == nullptr && node->rChild == nullptr)
		return 1;
	else
		return calLeafNum(node->lChild) + calLeafNum(node->rChild);
}

BiTree::~BiTree()
{
	destroyTree();
}


#endif