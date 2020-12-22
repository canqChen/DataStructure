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
			tmp = tmp->getLeft();
		}
		else
		{
			tmp = nodeStk.top()->getRight();
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
		if (tmp->getVal() > ele)
			tmp = tmp->getLeft();
		else if (tmp->getVal() < ele)
			tmp = tmp->getRight();
		else // already exists, do nothing
			return;
	}
	pTreeNode newNode = new TreeNode<T>(ele);
	if (preNode->getVal() > ele)
		preNode->setLeft(newNode);
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
		if (tmp->getVal() == ele)
			break;
		preNode = tmp;
		if (tmp->getVal() > ele)
			tmp = tmp->getLeft();
		else if (tmp->getVal() < ele)
			tmp = tmp->getRight();
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
	if (node->getLeft() == nullptr)
		newNode = node->getRight();
	else if (node->getRight() == nullptr)
		newNode = node->getLeft();
	else  // two children
	{
		tmp = node->getLeft();   // cannot be nullptr
		while (tmp->getRight() != nullptr)
			tmp = tmp->getRight();
		tmp->setRight(node->getRight());
		tmp = node;
		newNode = node->getLeft();
	}

	if (parent->getLeft() == node)  // the node to be removed is the left child of parent
		parent->setLeft(newNode);
	else		//  the node to be removed is the right child of parent
		parent->setRight(newNode);

	delete tmp;
}

template<typename T>
void AVLTree<T>::deleteByCopying(pTreeNode & node)
{
	pTreeNode tmp = node, prevNode = node, newNode = nullptr;

	// leaf node or only one child, directly replace it
	if (node->getLeft() == nullptr)
	{
		if (parent->getLeft() == node)  // the node to be removed is the left child of parent
			parent->setLeft(node->getRight());
		else		//  the node to be removed is the right child of parent
			parent->setRight(node->getRight());
	}
	else if (node->getRight() == nullptr)
	{
		if (parent->getLeft() == node)  // the node to be removed is the left child of parent
			parent->setLeft(node->getLeft());
		else		//  the node to be removed is the right child of parent
			parent->setRight(node->getLeft());
	}
	else  // two children, copy by precursor node
	{
		tmp = node->getLeft();  // cannot be nullptr
		while (tmp->getRight() != nullptr)  // use the previous node to replace it
		{
			prevNode = tmp;
			tmp = tmp->getRight();
		}
		node->setVal(tmp->getVal());
		if (prevNode == node)
			node->setLeft(tmp->getLeft());
		else
			prevNode->setRight(tmp->getLeft());
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
		if (tmp->getVal() < ele)
			tmp = tmp->getRight();
		else if (tmp->getVal() > ele)
			tmp = tmp->getLeft();
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
	//	preOrderTraverse(node->getLeft());
	//	preOrderTraverse(node->getRight());
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
			ret.push_back(nodeStk.top()->getVal());
			nodeStk.push(tmp);
			tmp = tmp->getLeft();
		}

		tmp = nodeStk.top()->getRight();
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
	//	preOrderTraverse(node->getLeft());
	//	ret.push_back(node->data);
	//	preOrderTraverse(node->getRight());
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
			tmp = tmp->getLeft();
		}

		ret.push_back(nodeStk.top()->getVal());
		tmp = nodeStk.top()->getRight();
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
	//	preOrderTraverse(node->getLeft());
	//	preOrderTraverse(node->getRight());
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
			ret.push_back(nodeStk.top()->getVal());
			nodeStk.push(tmp);
			tmp = tmp->getRight();
		}

		tmp = tmp->getLeft();
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
		ret.push_back(nodeQ.front()->getVal());
		if (nodeQ.front()->getLeft() != nullptr)
			nodeQ.push(nodeQ.front()->getLeft());
		if (nodeQ.front()->getRight() != nullptr)
			nodeQ.push(nodeQ.front()->getRight());
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
		pTreeNode newNode = createNode(node->getVal(), node->getBalancedFactor());
		newNode->setLeft(copy(node->getLeft()));
		newNode->setRight(copy(node->getRight()));
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
		size_type lDepth = calDepth(node->getLeft());
		size_type rDepth = calDepth(node->getRight());
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
		return calNodeNum(node->getLeft()) + calNodeNum(node->getRight()) + 1;
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
	if (node->getLeft() == nullptr && node->getRight() == nullptr)
		return 1;
	else
		return calLeafNum(node->getLeft()) + calLeafNum(node->getRight());
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	clear();
}