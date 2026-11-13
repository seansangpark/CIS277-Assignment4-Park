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
    cout << "Binary Tree Explorer" << endl << endl;

    TreeNode* treeA = new TreeNode{50};
    treeA->left = new TreeNode{30};
    treeA->right = new TreeNode{70};
    treeA->left->left = new TreeNode{20};
    treeA->left->right = new TreeNode{40};
    treeA->right->left = new TreeNode{60};
    treeA->right->right = new TreeNode{80};

    cout << "Tree A" << endl;
    cout << "        50" << endl;
    cout << "       /  \\" << endl;
    cout << "     30    70" << endl;
    cout << "    / \\   / \\" << endl;
    cout << "   20 40 60 80" << endl;
    showTree(treeA);

    TreeNode* treeB = new TreeNode{10};
    treeB->left = new TreeNode{30};
    treeB->right = new TreeNode{20};
    treeB->left->right = new TreeNode{5};
    treeB->right->right = new TreeNode{15};

    cout << "Tree B" << endl;
    cout << "        10" << endl;
    cout << "       /  \\" << endl;
    cout << "     30    20" << endl;
    cout << "       \\     \\" << endl;
    cout << "        5     15" << endl;
    cout << "Each child pointer was assigned in main." << endl;
    showTree(treeB);

    destroyTree(treeA);
    destroyTree(treeB);

    cout << "Tree A root: ";
    if (treeA == nullptr)
    {
        cout << "null" << endl;
    }
    else
    {
        cout << "not null" << endl;
    }

    cout << "Tree B root: ";
    if (treeB == nullptr)
    {
        cout << "null" << endl;
    }
    else
    {
        cout << "not null" << endl;
    }

    return 0;
}
