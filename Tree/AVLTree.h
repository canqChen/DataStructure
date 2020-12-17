#ifndef __BSTREE__
#define __BSTREE__

#include<iostream>
#include <stack>
#include <queue>
#include<vector>

using namespace std;


// binary sort tree
template<typename T>
class AVLTree
{
public:
	typedef T value_type;
	typedef size_t size_type;
	

	AVLTree() :root(nullptr) {};
	AVLTree(const AVLTree<T>& tree);   // copy constructor
	AVLTree(vector<T> vec);   // build AVLTree from a vector

	~AVLTree();

	size_type depth();
	size_type numOfNode();
	size_type numOfLeaf();
	bool empty() const { return root == nullptr ? true : false; }
	void clear();
	void insert(const T& ele);
	void erase(const T& ele);
	bool search(const T& ele);

	vector<T>& preOrderTraverse() const { return preOrderTraverse(root); }
	vector<T>& midOrderTraverse() const { return midOrderTraverse(root); }
	vector<T>& postOrderTraverse() const { return postOrderTraverse(root); }
	vector<T>& levelOrderTraverse() const { return levelOrderTraverse(root); }

protected:
	template<typename T>
	struct TreeNode 
	{
	private:
		T data;
		TreeNode<T>* left, * right;
		int BF;
	public:
		TreeNode() : data(T()), BF(0), left(nullptr), right(nullptr) {};
		TreeNode(T& data, int BF=0, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) 
			: data(data), BF(0), left(left), right(right) {};
	};

	typedef TreeNode<T>* pTreeNode;
private:
	pTreeNode root;

	vector<T>& preOrderTraverse(pTreeNode node);
	vector<T>& midOrderTraverse(pTreeNode node);
	vector<T>& postOrderTraverse(pTreeNode node);
	vector<T>& levelOrderTraverse(pTreeNode node);

	pTreeNode copy(pTreeNode node);
	size_type calDepth(pTreeNode node);
	size_type calNodeNum(pTreeNode node);
	size_type calLeafNum(pTreeNode node);

	void deleteByMerging(pTreeNode node);
	void deleteByCopying(pTreeNode node);

	void buildBalancedTreeFromVector(vector<T>& vec, int start, int end);
};


#endif