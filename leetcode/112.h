/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


bool hasPathSum(struct TreeNode* root, int targetSum)
{
    if (!root)
        return false;
    if (hasPathSum (root->left, targetSum - root->val))
        return true;
    if (hasPathSum (root->right, targetSum - root->val))
        return true;
    if (!root->left && !root->right && root->val == targetSum)
        return true;
    return false;
}