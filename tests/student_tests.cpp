#include "TreeExplorer.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void showValues(const string& label, const vector<int>& values)
{
    cout << label;

    for (size_t i = 0; i < values.size(); i++)
    {
        if (i > 0)
        {
            cout << " ";
        }

        cout << values[i];
    }

    cout << endl;
}

void showTree(TreeNode* root)
{
    showValues("Preorder:     ", preorder(root));
    showValues("Inorder:      ", inorder(root));
    showValues("Postorder:    ", postorder(root));
    showValues("Level order:  ", levelOrder(root));
    cout << "Nodes:        " << countNodes(root) << endl;
    cout << "Leaves:       " << countLeaves(root) << endl;
    cout << "Height:       " << treeHeight(root) << endl;
    cout << "Sum:          " << sumValues(root) << endl;
    cout << endl;
}

int main()
{
    cout << "Empty tree" << endl;
    TreeNode* root = nullptr;
    showTree(root);

    if (!preorder(root).empty() || !inorder(root).empty()
        || !postorder(root).empty() || !levelOrder(root).empty()
        || countNodes(root) != 0 || countLeaves(root) != 0
        || treeHeight(root) != 0 || sumValues(root) != 0)
    {
        cout << "Empty tree did not match." << endl;
        return 1;
    }

    destroyTree(root);
    destroyTree(root);
    cout << "Root: ";
    if (root == nullptr)
    {
        cout << "null" << endl << endl;
    }
    else
    {
        cout << "not null" << endl;
        return 1;
    }

    cout << "Singleton -4" << endl;
    root = new TreeNode{-4};
    showTree(root);

    if (preorder(root) != vector<int>{-4} || inorder(root) != vector<int>{-4}
        || postorder(root) != vector<int>{-4} || levelOrder(root) != vector<int>{-4}
        || countNodes(root) != 1 || countLeaves(root) != 1
        || treeHeight(root) != 1 || sumValues(root) != -4)
    {
        cout << "Singleton did not match." << endl;
        destroyTree(root);
        return 1;
    }

    destroyTree(root);

    cout << "Left-only chain" << endl;
    cout << "3, 2, 1, 0 down the left side." << endl;
    root = new TreeNode{3};
    root->left = new TreeNode{2};
    root->left->left = new TreeNode{1};
    root->left->left->left = new TreeNode{0};
    showTree(root);

    if (preorder(root) != vector<int>{3, 2, 1, 0}
        || inorder(root) != vector<int>{0, 1, 2, 3}
        || postorder(root) != vector<int>{0, 1, 2, 3}
        || levelOrder(root) != vector<int>{3, 2, 1, 0}
        || countNodes(root) != 4 || countLeaves(root) != 1
        || treeHeight(root) != 4 || sumValues(root) != 6)
    {
        cout << "Left chain did not match." << endl;
        destroyTree(root);
        return 1;
    }

    destroyTree(root);

    cout << "Right-only chain" << endl;
    cout << "0, 1, 2, 3 down the right side." << endl;
    root = new TreeNode{0};
    root->right = new TreeNode{1};
    root->right->right = new TreeNode{2};
    root->right->right->right = new TreeNode{3};
    showTree(root);

    if (preorder(root) != vector<int>{0, 1, 2, 3}
        || inorder(root) != vector<int>{0, 1, 2, 3}
        || postorder(root) != vector<int>{3, 2, 1, 0}
        || levelOrder(root) != vector<int>{0, 1, 2, 3}
        || countNodes(root) != 4 || countLeaves(root) != 1
        || treeHeight(root) != 4 || sumValues(root) != 6)
    {
        cout << "Right chain did not match." << endl;
        destroyTree(root);
        return 1;
    }

    destroyTree(root);

    cout << "Duplicate, zero, and negative values" << endl;
    root = new TreeNode{5};
    root->left = new TreeNode{0};
    root->right = new TreeNode{5};
    root->left->left = new TreeNode{-3};
    root->left->right = new TreeNode{0};
    showTree(root);

    if (preorder(root) != vector<int>{5, 0, -3, 0, 5}
        || inorder(root) != vector<int>{-3, 0, 0, 5, 5}
        || postorder(root) != vector<int>{-3, 0, 0, 5, 5}
        || levelOrder(root) != vector<int>{5, 0, 5, -3, 0}
        || countNodes(root) != 5 || countLeaves(root) != 3
        || treeHeight(root) != 3 || sumValues(root) != 7)
    {
        cout << "Mixed tree did not match." << endl;
        destroyTree(root);
        return 1;
    }

    vector<int> first = preorder(root);
    first[0] = 999;
    first.clear();
    showValues("Next preorder: ", preorder(root));

    if (preorder(root) != vector<int>{5, 0, -3, 0, 5} || sumValues(root) != 7)
    {
        cout << "Editing the returned vector changed the tree." << endl;
        destroyTree(root);
        return 1;
    }

    cout << endl;
    destroyTree(root);

    cout << "Destroy, rebuild, destroy again" << endl;
    root = new TreeNode{4};
    root->left = new TreeNode{1};
    destroyTree(root);
    cout << "Root: ";
    if (root == nullptr)
    {
        cout << "null" << endl;
    }
    else
    {
        cout << "not null" << endl;
        return 1;
    }

    root = new TreeNode{-4};
    showTree(root);

    if (preorder(root) != vector<int>{-4} || sumValues(root) != -4)
    {
        cout << "Rebuilt tree did not match." << endl;
        destroyTree(root);
        return 1;
    }

    destroyTree(root);
    destroyTree(root);
    cout << "Root: ";
    if (root == nullptr)
    {
        cout << "null" << endl << endl;
    }
    else
    {
        cout << "not null" << endl;
        return 1;
    }

    cout << "One-child nodes and a repeated value" << endl;
    root = new TreeNode{7};
    root->left = new TreeNode{4};
    root->right = new TreeNode{9};
    root->left->left = new TreeNode{2};
    root->left->left->right = new TreeNode{2};
    showTree(root);

    if (preorder(root) != vector<int>{7, 4, 2, 2, 9}
        || inorder(root) != vector<int>{2, 2, 4, 7, 9}
        || postorder(root) != vector<int>{2, 2, 4, 9, 7}
        || levelOrder(root) != vector<int>{7, 4, 9, 2, 2}
        || countNodes(root) != 5 || countLeaves(root) != 2
        || treeHeight(root) != 4 || sumValues(root) != 24)
    {
        cout << "Extra tree did not match." << endl;
        destroyTree(root);
        return 1;
    }

    destroyTree(root);
    destroyTree(root);
    cout << "Root: ";
    if (root == nullptr)
    {
        cout << "null" << endl;
    }
    else
    {
        cout << "not null" << endl;
        return 1;
    }

    return 0;
}
