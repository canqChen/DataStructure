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
		root = createNode(ele);
		return;
	}
	pTreeNode tmp = root, * preNode;
	while (tmp != nullptr)
	{
		preNode = tmp;
		if (tmp->value > ele)
			tmp = tmp->left;
		else if (tmp->value < ele)
			tmp = tmp->right;
		else // already exists, do nothing
			return;
	}
	pTreeNode newNode = new TreeNode<T>(ele);
	if (preNode->value > ele)
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
		if (tmp->value == ele)
			break;
		preNode = tmp;
		if (tmp->value > ele)
			tmp = tmp->left;
		else if (tmp->value < ele)
			tmp = tmp->right;
	}
	if (tmp == nullptr)   // not found
	{
		cout << "Element is not in the tree!";
		return;
	}

	// leaf node or only one child
	deleteByMerging(tmp, preNode);
	//deleteByCopying(tmp, preNode);
}

template<typename T>
void AVLTree<T>::deleteByMerging(pTreeNode & node, pTreeNode & parent)
{
	pTreeNode tmp = node, newNode = nullptr;

	// leaf node or only one child
	if (node->left == nullptr)
		newNode = node->right;
	else if (node->right == nullptr)
		newNode = node->left;
	else  // two children
	{
		tmp = node->left;   // cannot be nullptr
		while (tmp->right != nullptr)
			tmp = tmp->right;
		tmp->right = node->right;
		tmp = node;
		newNode = node->left;
	}

	if (parent->left == node)  // the node to be removed is the left child of parent
		parent->left = newNode;
	else		//  the node to be removed is the right child of parent
		parent->right = newNode;

	delete tmp;
}

template<typename T>
void AVLTree<T>::deleteByCopying(pTreeNode & node)
{
	pTreeNode tmp = node, prevNode = node, newNode = nullptr;

	// leaf node or only one child, directly replace it
	if (node->left == nullptr)
	{
		if (parent->left == node)  // the node to be removed is the left child of parent
			parent->left = node->right;
		else		//  the node to be removed is the right child of parent
			parent->right =  node->right;
	}
	else if (node->right == nullptr)
	{
		if (parent->left == node)  // the node to be removed is the left child of parent
			parent->left = node->left;
		else		//  the node to be removed is the right child of parent
			parent->right = node->left;
	}
	else  // two children, copy by precursor node
	{
		tmp = node->left;  // cannot be nullptr
		while (tmp->right != nullptr)  // use the previous node to replace it
		{
			prevNode = tmp;
			tmp = tmp->right;
		}
		node->value = tmp->value;
		if (prevNode == node)
			node->left  = tmp->left;
		else
			prevNode->right  = tmp->left;
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
		if (tmp->value < ele)
			tmp = tmp->right;
		else if (tmp->value > ele)
			tmp = tmp->left;
		else
			return true;
	}
	return false;
}

template<typename T>
vector<T>& AVLTree<T>::preOrderTraverse(const pTreeNode & node) const
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
			ret.push_back(nodeStk.top()->value);
			nodeStk.push(tmp);
			tmp = tmp->left;
		}

		tmp = nodeStk.top()->right;
		nodeStk.pop();
	}
	return ret;
}

template<typename T>
vector<T>& AVLTree<T>::midOrderTraverse(const pTreeNode & node) const
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

		ret.push_back(nodeStk.top()->value);
		tmp = nodeStk.top()->right;
		nodeStk.pop();
	}
	return ret;
}

template<typename T>
vector<T>& AVLTree<T>::postOrderTraverse(const pTreeNode &node) const
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
	stack<pTreeNode> nodeStk;
	pTreeNode tmp = node;
	while (tmp || !nodeStk.empty())
	{
		while (tmp != nullptr)
		{
			ret.push_back(nodeStk.top()->value);
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
vector<T>& AVLTree<T>::levelOrderTraverse(const pTreeNode & node)  const
{
	if (node == nullptr)
		return;
	std::queue<pTreeNode> nodeQ;
	vector<T> ret;
	nodeQ.push(node);
	while (!nodeQ.empty())
	{
		ret.push_back(nodeQ.front()->value);
		if (nodeQ.front()->left != nullptr)
			nodeQ.push(nodeQ.front()->left);
		if (nodeQ.front()->right != nullptr)
			nodeQ.push(nodeQ.front()->right);
		nodeQ.pop();
	}
}

template<typename T>
AVLTree<T>::pTreeNode AVLTree<T>::copy(const pTreeNode & node)
{
	if (node == nullptr)
		return nullptr;
	else
	{
		pTreeNode newNode = createNode(node->value, node->BF);
		newNode->left = copy(node->left);
		newNode->right = copy(node->right);
		return newNode;
	}
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::depth()  const
{
	return calDepth(root);
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::calDepth(const pTreeNode &node)  const
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
AVLTree<T>::size_type AVLTree<T>::nodeNum()  const
{
	return calNodeNum(root);
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::calNodeNum(const pTreeNode &node)  const
{
	if (node == nullptr)
		return 0;
	else
		return calNodeNum(node->left) + calNodeNum(node->right) + 1;
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::leafNum()  const
{
	return calNodeNum(root);
}

template<typename T>
AVLTree<T>::size_type AVLTree<T>::calLeafNum(const pTreeNode & node)  const
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