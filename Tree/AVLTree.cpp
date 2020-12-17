#include "AVLTree.h"


template<typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree)
{
	root = copy(tree.root);
}

template<typename T>
AVLTree<T>::AVLTree(vector<T> vec)
{
	sort(vec.begin(), vec.end());
	buildBalancedTreeFromVector(vec, 0, vec.size());
}

template<typename T>
void AVLTree<T>::clear()
{
	std::stack<pTreeNode> nodeStk;
	pTreeNode tmp = root;
	while (tmp || !nodeStk.empty())
	{
		if (tmp != nullptr)
		{
			nodeStk.push(tmp);
			tmp = tmp->left;
		}
		else
		{
			tmp = nodeStk.top()->right;
			delete nodeStk.top();
			nodeStk.pop();
		}
	}
	root = nullptr;
}

template<typename T>
void AVLTree<T>::insert(const T& ele)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>(ele);
		return;
	}
	pTreeNode tmp = root, * preNode;
	while (tmp != nullptr)
	{
		preNode = tmp;
		if (tmp->data > ele)
			tmp = tmp->left;
		else if (tmp->data < ele)
			tmp = tmp->right;
		else // already exists
			return;
	}
	pTreeNode newNode = new TreeNode<T>(ele);
	if (preNode->data > ele)
		preNode->left = newNode;
	else if (preNode->right < ele)
		pTreeNode newNode = new TreeNode<T>(ele);
}

template<typename T>
void AVLTree<T>::erase(const T& ele)
{
	if (empty())
	{
		count << "The tree is empty!";
		return;
	}
	pTreeNode tmp = root, * preNode;
	// find node to be erased
	while (tmp != nullptr)
	{
		if (tmp->data == ele)
			break;
		preNode = tmp;
		if (tmp->data > ele)
			tmp = tmp->left;
		else if (tmp->data < ele)
			tmp = tmp->right;
	}
	if (tmp == nullptr)   // not found
	{
		cout << "Element is not in the tree!";
		return;
	}

	// leaf node or only one child
	deleteByMerging(tmp);
	//deleteByCopying(tmp);
}

template<typename T>
void AVLTree<T>::deleteByMerging(pTreeNode node)
{
	pTreeNode tmp = node;

	// leaf node or only one child
	if (node->left == nullptr)
		node = node->right;
	else if (node->right == nullptr)
		node = node->left;
	else  // two children
	{
		pTreeNode tmp = node->left;
		while (tmp->right != nullptr)
			tmp = tmp->right;
		tmp->right = node->right;
		tmp = node;
		node = node->left;
	}
	delete tmp;
}

template<typename T>
void AVLTree<T>::deleteByCopying(pTreeNode node)
{
	pTreeNode tmp = node, * prevNode = node;

	// leaf node or only one child
	if (node->left == nullptr)
		node = node->right;
	else if (node->right == nullptr)
		node = node->left;
	else  // two children
	{
		pTreeNode tmp = node->left;
		while (tmp->right != nullptr)
		{
			prevNode = tmp;
			tmp = tmp->right;
		}
		node->data = tmp->data;
		if (prevNode == node)
			node->left = tmp->left;
		else
			prevNode->right = tmp->left;
	}
	delete tmp;
}

template<typename T>
void AVLTree<T>::buildBalancedTreeFromVector(vector<T>& vec, int start, int end)
{
	if (start > mid)
		return;
	int mid = (start + end) / 2;
	insert(vec[mid]);
	buildBalancedTreeFromVector(vec, start, mid);
	buildBalancedTreeFromVector(vec, mid + 1, end);
}

template<typename T>
bool AVLTree<T>::search(const T& ele)
{
	pTreeNode tmp = root;
	while (tmp != nullptr)
	{
		if (tmp->data < ele)
			tmp = tmp->right;
		else if (tmp->data > ele)
			tmp = tmp->left;
		else
			return true;
	}
	return false;
}

template<typename T>
vector<T>& AVLTree<T>::preOrderTraverse(pTreeNode node)
{
	// recursive implementation
	//vector<T> ret;
	//if (node == nullptr)
	//	return;
	//else
	//{
	//	ret.push_back(node->data);
	//	preOrderTraverse(node->left);
	//	preOrderTraverse(node->right);
	//}
	//return ret;

	// iterative implementation
	vector<T> ret;
	stack<pTreeNode> nodeStk;
	pTreeNode tmp = node;
	while (tmp || !nodeStk.empty())
	{
		while (tmp != nullptr)
		{
			ret.push_back(nodeStk.top()->data);
			nodeStk.push(tmp);
			tmp = tmp->left;
		}

		tmp = nodeStk.top()->right;
		nodeStk.pop();
	}
	return ret;
}

template<typename T>
vector<T>& AVLTree<T>::midOrderTraverse(pTreeNode node)
{
	// recursive implementation
	// vector<T> ret;
	//if (node == nullptr)
	//	return;
	//else
	//{
	//	preOrderTraverse(node->left);
	//	ret.push_back(node->data);
	//	preOrderTraverse(node->right);
	//}
	//return ret;

	// iterative implementation, exploit stack
	vector<T> ret;
	std::stack<pTreeNode> nodeStk;
	pTreeNode tmp = node;
	while (tmp || !nodeStk.empty())
	{
		while (tmp != nullptr)
		{
			nodeStk.push(tmp);
			tmp = tmp->left;
		}

		ret.push_back(nodeStk.top()->data);
		tmp = nodeStk.top()->right;
		nodeStk.pop();
	}
	return ret;
}

template<typename T>
vector<T>& AVLTree<T>::postOrderTraverse(pTreeNode node)
{
	// recursive implementation
	//vector<T> ret;
	//if (node == nullptr)
	//	return;
	//else
	//{
	//	preOrderTraverse(node->left);
	//	preOrderTraverse(node->right);
	//	ret.push_back(node->data);
	//}
	//return ret;

	// iterative implementation
	vector<T> ret;
	stack<TreeNode*> nodeStk;
	TreeNode* tmp = node;
	while (tmp || !nodeStk.empty())
	{
		while (tmp != nullptr)
		{
			ret.push_back(nodeStk.top()->data);
			nodeStk.push(tmp);
			tmp = tmp->right;
		}

		tmp = tmp->left;
		nodeStk.pop();
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

template<typename T>
vector<T>& AVLTree<T>::levelOrderTraverse(pTreeNode node)
{
	if (node == nullptr)
		return;
	std::queue<pTreeNode> nodeQ;
	vector<T> ret;
	nodeQ.push(node);
	while (!nodeQ.empty())
	{
		ret.push_back(nodeQ.front()->data);
		if (nodeQ.front()->left != nullptr)
			nodeQ.push(nodeQ.front()->left);
		if (nodeQ.front()->right != nullptr)
			nodeQ.push(nodeQ.front()->right);
		nodeQ.pop();
	}
}

template<typename T>
AVLTree<T>::pTreeNode AVLTree<T>::copy(pTreeNode node)
{
	if (node == nullptr)
		return nullptr;
	else
	{
		pTreeNode newNode = new TreeNode<T>();
		newNode->data = node->data;
		newNode->left = copy(node->left);
		newNode->right = copy(node->right);
		return newNode;
	}
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::depth()
{
	return calDepth(root);
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::calDepth(pTreeNode node)
{
	if (node == nullptr)
		return 0;
	else
	{
		size_type lDepth = calDepth(node->left);
		size_type rDepth = calDepth(node->right);
		return max(lDepth, rDepth) + 1;
	}
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::numOfNode()
{
	return calNodeNum(root);
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::calNodeNum(pTreeNode node)
{
	if (node == nullptr)
		return 0;
	else
		return calNodeNum(node->left) + calNodeNum(node->right) + 1;
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::numOfLeaf()
{
	return calNodeNum(root);
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::calLeafNum(pTreeNode node)
{
	if (node == nullptr)
		return 0;
	if (node->left == nullptr && node->right == nullptr)
		return 1;
	else
		return calLeafNum(node->left) + calLeafNum(node->right);
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	clear();
}