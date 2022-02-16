#include "binary_trees.h"

/**
 * min_value - count the minimum value from a Binary Search Tree
 * @node: pointer to root node of tree
 *
 * Return: pointer to the new root node of the tree
 */
bst_t *min_value(bst_t *node)
{
	bst_t *current;

	current = (bst_t *)node;

	while (current && current->left != NULL)
		current = current->left;

	return (current);
}


/**
 * bst_remove - removes a node from a Binary Search Tree
 * @root: pointer to root of tree
 * @value: input value
 * Return: pointer to the new root node of the tree after removing the
 * desired value
 */
bst_t *bst_remove(bst_t *root, int value)
{
	if (root == NULL)
		return (root);
	else if (value < root->n)
		root->left = bst_remove(root->left, value);
	else if (value > root->n)
		root->right = bst_remove(root->right, value);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			root = NULL;
		}
		else if (root->left == NULL)
		{
			bst_t *temp = root;

			root = root->right;
			free(temp);
		}
		else if (root->right == NULL)
		{
			bst_t *temp;

			temp = (bst_t *)root;
			root = root->left;
			free(temp);
		}
		else
		{
			bst_t *temp = min_value(root->right);

			root->n = temp->n;
			root->right = bst_remove(root->right, temp->n);
		}
	}

	return (root);
}
