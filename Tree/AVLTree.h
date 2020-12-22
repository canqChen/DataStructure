#ifndef __BSTREE__
#define __BSTREE__

#include<iostream>
#include <stack>
#include <queue>
#include<vector>
#include<exception>

using namespace std;


// binary sort tree
template<typename T>
class AVLTree
{
public:
	typedef T value_type;
	typedef vector<T>::size_type size_type;
	

	AVLTree() :root(nullptr) {};
	AVLTree(const AVLTree<T>& tree);   // copy constructor
	AVLTree(vector<T> vec);   // build AVLTree from a vector

	~AVLTree();

	size_type depth() const;
	size_type nodeNum() const;
	size_type leafNum() const;
	bool empty() const { return root == nullptr ? true : false; }
	void clear();
	void insert(const T& ele);
	void erase(const T& ele);
	bool search(const T& ele);

	vector<T>& preOrderTraverse() const { return preOrderTraverse(root); }
	vector<T>& midOrderTraverse() const { return midOrderTraverse(root); }
	vector<T>& postOrderTraverse() const { return postOrderTraverse(root); }
	vector<T>& levelOrderTraverse() const { return levelOrderTraverse(root); }

	
private:
	template<typename _T>
	struct TreeNode
	{
	public:
		typedef TreeNode<_T>* pointer;
		TreeNode() : value(_T()), BF(0), left(nullptr), right(nullptr) {};
		TreeNode(const _T & val, int BF = 0, pointer left = nullptr, pointer right = nullptr)
			: value(val), BF(0), left(left), right(right) {};
		void setVal(const _T& val) { this->value = val; }
		const _T& getVal() const { return this->value; }
		void setBalancedFactor(const int& bf) { this->BF = bf; }
		const int& getBalancedFactor() const { return this->BF; }
		void setLeft(const pointer & node) { this->left = node; }
		void setRight(const pointer & node) { this->right = node; }
		const pointer& getLeft() const { return this->left; }
		const pointer& getRight() const { return this->right; }
	private:
		_T value;
		TreeNode<_T>* left, *right,  *parent;
		int BF;    // left height - right height
	};
	typedef TreeNode<T>* pTreeNode;

	pTreeNode root;

	vector<T>& preOrderTraverse(const pTreeNode &node) const;
	vector<T>& midOrderTraverse(const pTreeNode &node) const;
	vector<T>& postOrderTraverse(const pTreeNode &node) const;
	vector<T>& levelOrderTraverse(const pTreeNode &node) const;

	pTreeNode copy(const pTreeNode & node);
	size_type calDepth(const pTreeNode & node) const;
	size_type calNodeNum(const pTreeNode &node) const;
	size_type calLeafNum(const pTreeNode & node) const;

	pTreeNode& createNode(const T& ele, int BF = 0, pTreeNode left = nullptr, pTreeNode right = nullptr)
	{ return new TreeNode<T>(ele, BF, left, right); }

	void deleteByMerging(pTreeNode & node, pTreeNode & parent);
	void deleteByCopying(pTreeNode & node);
	void buildBalancedTreeFromVector(vector<T>& vec, int start, int end);
};


#endif