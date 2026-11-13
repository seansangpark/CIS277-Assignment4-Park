#include "TreeExplorer.h"
#include <algorithm>
#include <queue>

static void collectPreorder(const TreeNode* node, std::vector<int>& result)
{
    if (node == nullptr)
        return;

    result.push_back(node->value);
    collectPreorder(node->left, result);
    collectPreorder(node->right, result);
}

static void collectInorder(const TreeNode* node, std::vector<int>& result)
{
    if (node == nullptr)
        return;

    collectInorder(node->left, result);
    result.push_back(node->value);
    collectInorder(node->right, result);
}

static void collectPostorder(const TreeNode* node, std::vector<int>& result)
{
    if (node == nullptr)
        return;

    collectPostorder(node->left, result);
    collectPostorder(node->right, result);
    result.push_back(node->value);
}

static void destroyNodes(TreeNode* node)
{
    if (node == nullptr)
        return;

    destroyNodes(node->left);
    destroyNodes(node->right);
    delete node;
}

std::vector<int> preorder(const TreeNode* root)
{
    std::vector<int> result;
    collectPreorder(root, result);
    return result;
}

std::vector<int> inorder(const TreeNode* root)
{
    std::vector<int> result;
    collectInorder(root, result);
    return result;
}

std::vector<int> postorder(const TreeNode* root)
{
    std::vector<int> result;
    collectPostorder(root, result);
    return result;
}

std::vector<int> levelOrder(const TreeNode* root)
{
    std::vector<int> result;
    if (root == nullptr)
        return result;

    std::queue<const TreeNode*> waiting;
    waiting.push(root);

    while (!waiting.empty())
    {
        const TreeNode* current = waiting.front();
        waiting.pop();
        result.push_back(current->value);

        if (current->left != nullptr)
            waiting.push(current->left);
        if (current->right != nullptr)
            waiting.push(current->right);
    }

    return result;
}

std::size_t countNodes(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

std::size_t countLeaves(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    if (root->left == nullptr && root->right == nullptr)
        return 1;

    return countLeaves(root->left) + countLeaves(root->right);
}

int treeHeight(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}

long long sumValues(const TreeNode* root)
{
    if (root == nullptr)
        return 0;

    return root->value + sumValues(root->left) + sumValues(root->right);
}

void destroyTree(TreeNode*& root)
{
    destroyNodes(root);
    root = nullptr;
}
