// F26 ESE224 LAB08 EX1 SOPHIA RAHMAN
// P1: Queries at a Tree Level
#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* makeNode(int value, TreeNode* l = nullptr, TreeNode* r = nullptr) {
    return new TreeNode{value, l, r};
}

static void printHelper(const TreeNode* root, int level, ostream& out, bool& first) {
    if (root == nullptr){
        return;
    }             
    if (level == 0) {                         
        if (!first) out << ' ';
        out << root->data;
        first = false;
        return;
    }
    printHelper(root->left,  level - 1, out, first);   
    printHelper(root->right, level - 1, out, first);
}

int countAtLevel(const TreeNode* root, int level) {
    if (root == nullptr){
        return 0;
    }
    if (level == 0){
        return 1;
    }
    return countAtLevel(root->left, level - 1) + countAtLevel(root->right, level - 1);
}

int sumAtLevel(const TreeNode* root, int level) {
    if (root == nullptr){
        return 0;
    }
    if (level == 0){
        return root->data;
    }
    return sumAtLevel(root->left, level - 1) + sumAtLevel(root->right, level - 1);
}

void printAtLevel(const TreeNode* root, int level, ostream& out) {
    if (countAtLevel(root, level) == 0) {
        out << "(empty)";
        return;
    }
    bool first = true;
    printHelper(root, level, out, first);
}

void clearTree(TreeNode*& root) {
    if (root == nullptr){
        return;
    }
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}

TreeNode* buildTree(const string& name) {
    if (name == "A") {
        return makeNode(18,
                 makeNode(7, nullptr, makeNode(12)),
                 makeNode(31, makeNode(24, nullptr, makeNode(27)), makeNode(40)));
    }
    if (name == "B") {
        return makeNode(18,
                 makeNode(7, nullptr, makeNode(12)),
                 makeNode(31, makeNode(24), makeNode(40)));
    }
    if (name == "SINGLE"){
        return makeNode(-6);
    }
    if (name == "ZERO"){
        return makeNode(0);
    }
    return nullptr;
}

int main() {
    string name;
    int q;
    cin >> name >> q;

    TreeNode* root = buildTree(name);
    cout << "Tree: " << name << endl;

    for (int i = 0; i < q; i++) {
        int level;
        cin >> level;
        cout << "Level " << level << ": ";
        printAtLevel(root, level, cout);
        cout << " | Count: " << countAtLevel(root, level)
             << " | Sum: " << sumAtLevel(root, level) << endl;
    }

    clearTree(root);
    return 0;
}