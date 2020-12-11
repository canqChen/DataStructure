#ifndef __BSTREE__
#define __BSTREE__

#include<iostream>
#include <stack>
#include <Queue>
#include<string>
#include<vector>

using namespace std;



template<typename T>
class TreeNode {
private:
	T data;
	TreeNode<T>* left, * right;
public:
	friend class BSTree<T>;
	TreeNode() : data(T()), left(nullptr), right(nullptr) {};
	TreeNode(T& data, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) : data(data), left(left), right(right) {};
};

// binary sort tree
template<typename T>
class BSTree
{
public:
	typedef T value_type;
	typedef std::size_t size_type;

	BSTree() :root(nullptr) {};
	BSTree(const BSTree<T>& tree);   // copy constructor
	BSTree(vector<T> vec);   // build BSTree from a vector

	~BSTree();

	size_type depth();
	size_type numOfNode();
	size_type numOfLeaf();
	bool empty() const { return root == nullptr ? true : false; }
	void clear();
	void insert(const T& ele);
	void erase(const T& ele);
	TreeNode<T>* search(const T& ele);

	vector<T>& preOrderTraverse() const { return preOrderTraverse(root); }
	vector<T>& midOrderTraverse() const { return midOrderTraverse(root); }
	vector<T>& postOrderTraverse() const { return postOrderTraverse(root); }
	vector<T>& levelOrderTraverse() const { return levelOrderTraverse(root); }

private:
	TreeNode<T>* root;

	vector<T>& preOrderTraverse(TreeNode<T>* node);
	vector<T>& midOrderTraverse(TreeNode<T>* node);
	vector<T>& postOrderTraverse(TreeNode<T>* node);
	vector<T>& levelOrderTraverse(TreeNode<T>* node);

	TreeNode<T>* copy(TreeNode<T>* node);
	size_type calDepth(TreeNode<T>* node);
	size_type calNodeNum(TreeNode<T>* node);
	size_type calLeafNum(TreeNode<T>* node);

	void deleteByMerging(TreeNode<T>* node);
	void deleteByCopying(TreeNode<T>* node);
};


#endif