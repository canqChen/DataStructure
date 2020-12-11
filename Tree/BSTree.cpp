#include "BSTree.h"


template<typename T>
BSTree<T>::BSTree(const BSTree<T>& tree)
{
	root = copy(tree.root);
}

template<typename T>
BSTree<T>::BSTree(vector<T> vec)
{
	sort(vec.begin(), vec.end());
}

template<typename T>
void BSTree<T>::clear()
{
	std::stack<TreeNode<T>*> nodeStk;
	TreeNode<T>* tmp = root;
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
void BSTree<T>::insert(const T& ele)
{
	if (root == nullptr)
	{
		root = new TreeNode<T>(ele);
		return;
	}
	TreeNode<T>* tmp = root, * preNode;
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
	TreeNode<T>* newNode = new TreeNode<T>(ele);
	if (preNode->data > ele)
		preNode->left = newNode;
	else if (preNode->right < ele)
		TreeNode<T>* newNode = new TreeNode<T>(ele);
}

template<typename T>
void BSTree<T>::erase(const T& ele)
{
	if (empty())
	{
		count << "The tree is empty!";
		return;
	}
	TreeNode<T>* tmp = root, * preNode;
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
void BSTree<T>::deleteByMerging(TreeNode<T>* node)
{
	TreeNode<T>* tmp = node;

	// leaf node or only one child
	if (node->left == nullptr)
		node = node->right;
	else if (node->right == nullptr)
		node = node->left;
	else  // two children
	{
		TreeNode<T>* tmp = node->left;
		while (tmp->right != nullptr)
			tmp = tmp->right;
		tmp->right = node->right;
		tmp = node;
		node = node->left;
	}
	delete tmp;
}

template<typename T>
void BSTree<T>::deleteByCopying(TreeNode<T>* node)
{
	TreeNode<T>* tmp = node, * prevNode = node;

	// leaf node or only one child
	if (node->left == nullptr)
		node = node->right;
	else if (node->right == nullptr)
		node = node->left;
	else  // two children
	{
		TreeNode<T>* tmp = node->left;
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
TreeNode<T>* BSTree<T>::search(const T& ele)
{
	TreeNode<T>* tmp = root;
	while (tmp != nullptr)
	{
		if (tmp->data < ele)
			tmp = tmp->right;
		else if (tmp->data > ele)
			tmp = tmp->left;
		else
			return tmp;
	}
	return nullptr;
}

template<typename T>
vector<T>& BSTree<T>::preOrderTraverse(TreeNode<T>* node)
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
	stack<TreeNode<T>*> nodeStk;
	TreeNode<T>* tmp = node;
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
vector<T>& BSTree<T>::midOrderTraverse(TreeNode<T>* node)
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
	std::stack<TreeNode<T>*> nodeStk;
	TreeNode<T>* tmp = node;
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
vector<T>& BSTree<T>::postOrderTraverse(TreeNode<T>* node)
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
vector<T>& BSTree<T>::levelOrderTraverse(TreeNode<T>* node)
{
	if (node == nullptr)
		return;
	std::queue<TreeNode<T>*> nodeQ;
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
TreeNode<T>* BSTree<T>::copy(TreeNode<T>* node)
{
	if (node == nullptr)
		return nullptr;
	else
	{
		TreeNode<T>* newNode = new TreeNode<T>();
		newNode->data = node->data;
		newNode->left = copy(node->left);
		newNode->right = copy(node->right);
		return newNode;
	}
}

template<typename T>
BSTree<T>::size_type BSTree<T>::depth()
{
	return calDepth(root);
}

template<typename T>
BSTree<T>::size_type BSTree<T>::calDepth(TreeNode<T>* node)
{
	if (node == nullptr)
		return 0;
	else
	{
		size_type lDepth = calDepth(node->left);
		size_type rDepth = calDepth(node->right);
		return lDepth > rDepth ? lDepth + 1 : rDepth + 1;
		return max(lDepth, rDepth) + 1;
	}
}

template<typename T>
BSTree<T>::size_type BSTree<T>::numOfNode()
{
	return calNodeNum(root);
}

template<typename T>
BSTree<T>::size_type BSTree<T>::calNodeNum(TreeNode<T>* node)
{
	if (node == nullptr)
		return 0;
	else
		return calNodeNum(node->left) + calNodeNum(node->right) + 1;
}

template<typename T>
BSTree<T>::size_type BSTree<T>::numOfLeaf()
{
	return calNodeNum(root);
}

template<typename T>
BSTree<T>::size_type BSTree<T>::calLeafNum(TreeNode<T>* node)
{
	if (node == nullptr)
		return 0;
	if (node->left == nullptr && node->right == nullptr)
		return 1;
	else
		return calLeafNum(node->left) + calLeafNum(node->right);
}

template<typename T>
BSTree<T>::~BSTree()
{
	clear();
}