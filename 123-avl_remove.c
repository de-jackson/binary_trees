#include "binary_trees.h"

/**
 * min_value - count the minimum value from a Binary Search Tree
 * @node: pointer to root node of tree
 *
 * Return: pointer to the new root node of the tree
 */
avl_t *min_value(avl_t *node)
{
	avl_t *current;

	current = (avl_t *)node;

	while (current && current->left != NULL)
		current = current->left;

	return (current);
}

/**
 * height - count the minimum value from a Binary Search Tree
 * @root: pointer to root node of tree
 *
 * Return: pointer to the new root node of the tree
 */
int height(avl_t *root)
{
	if (root == NULL)
		return (-1);

	int lheight = height(root->left);
	int rheight = height(root->right);

	if (lheight > rheight)
		return (lheight + 1);
	else
		return (rheight + 1);
}

/**
 * getBalanceFactor - count the minimum value from a Binary Search Tree
 * @node: pointer to root node of tree
 *
 * Return: pointer to the new root node of the tree
 */
int getBalanceFactor(avl_t *node)
{
	if (node == NULL)
		return (-1);
	return (height(node->left) - height(node->right));
}

/**
 * rightRotate - balances right side
 * @y: pointer to root node of tree
 *
 * Return: pointer to the new root node of the tree
 */
avl_t *rightRotate(avl_t *y)
{
	avl_t *x = y->left;
	avl_t *T2 = x->right;

	x->right = y;
	y->left = T2;
	return (x);
}

/**
 * leftRotate - balances left side
 * @x: pointer to root node of tree
 *
 * Return: pointer to the new root node of the tree
 */
avl_t *leftRotate(avl_t *x)
{
	avl_t *y = x->right;
	avl_t *T2 = y->left;

	y->left = x;
	x->right = T2;
	return (y);
}


/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to root of tree
 * @value: value to be removed
 * Return: pointer to the new root node of the tree after removing the desired
 * value, and after rebalancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	if (root == NULL)
		return (root);
	else if (value < root->n)
		root->left = avl_remove(root->left, value);
	else if (value > root->n)
		root->right = avl_remove(root->right, value);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			root = NULL;
		}
		else if (root->left == NULL)
		{
			avl_t *temp = root;

			root = root->right;
			free(temp);
		}
		else if (root->right == NULL)
		{
			avl_t *temp;

			temp = (avl_t *)root;
			root = root->left;
			free(temp);
		}
		else
		{
			avl_t *temp = min_value(root->right);

			root->n = temp->n;
			root->right = avl_remove(root->right, temp->n);
		}
	}

	int bf = getBalanceFactor(root);

	if (bf == 2 && getBalanceFactor(root->left) >= 0)
		return (rightRotate(root));
	else if (bf == 2 && getBalanceFactor(root->left) == -1)
	{
		root->left = (leftRotate(root->left));
		return (rightRotate(root));
	}
	else if (bf == -2 && getBalanceFactor(root->right) <= -0)
	{
		return (leftRotate(root));
	}
	else if (bf == -2 && getBalanceFactor(root->right) == 1)
	{
		root->right = rightRotate(root->right);
		return (leftRotate(root));
	}

	return (root);
}
