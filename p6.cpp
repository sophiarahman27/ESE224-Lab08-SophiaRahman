// F26 ESE224 LAB08 EX5 SOPHIA RAHMAN
// P6: Two Different BST Nodes with a Given Sum
#include <iostream>
#include <string>
using namespace std;

template <typename Type>
class Node {
private:
    Type data;
    Node<Type>* left;
    Node<Type>* right;
public:
    Node(const Type& value) : data(value), left(nullptr), right(nullptr) {}
    Type getData() const { return data; }
    Node<Type>* getLeft() const { return left; }
    Node<Type>* getRight() const { return right; }
    void setLeft(Node<Type>* child) { left = child; }
    void setRight(Node<Type>* child) { right = child; }
};

template <typename Type>
class BinaryTree {
private:
    Node<Type>* root;

    Node<Type>* insertHelper(Node<Type>* node, const Type& value);
    void printHelper(const Node<Type>* node, ostream& out, bool& first) const;
    void clearHelper(Node<Type>* node);

    const Node<Type>* findNode(const Node<Type>* node, const Type& value) const;
    bool pairHelper(const Node<Type>* node, const Type& target) const;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(); }
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    void insert(const Type& value) { root = insertHelper(root, value); }
    void printInOrder(ostream& out) const;
    void clear() { clearHelper(root); root = nullptr; }

    bool hasPair(Type target) const { return pairHelper(root, target); }
};

template <typename Type>
Node<Type>* BinaryTree<Type>::insertHelper(Node<Type>* node, const Type& value) {
    if (node == nullptr) {
        return new Node<Type>(value);
    }
    if (value < node->getData()) {
        node->setLeft(insertHelper(node->getLeft(), value));
    } else if (node->getData() < value) {
        node->setRight(insertHelper(node->getRight(), value));
    }
    return node;
}

template <typename Type>
void BinaryTree<Type>::printHelper(const Node<Type>* node, ostream& out, bool& first) const {
    if (node == nullptr) {
        return;
    }
    printHelper(node->getLeft(), out, first);
    if (!first) {
        out << ' ';
    }
    out << node->getData();
    first = false;
    printHelper(node->getRight(), out, first);
}

template <typename Type>
void BinaryTree<Type>::printInOrder(ostream& out) const {
    if (root == nullptr) {
        out << "(empty)";
        return;
    }
    bool first = true;
    printHelper(root, out, first);
}

template <typename Type>
void BinaryTree<Type>::clearHelper(Node<Type>* node) {
    if (node == nullptr) {
        return;
    }
    clearHelper(node->getLeft());
    clearHelper(node->getRight());
    delete node;
}

template <typename Type>
const Node<Type>* BinaryTree<Type>::findNode(const Node<Type>* node, const Type& value) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->getData()) {
        return findNode(node->getLeft(), value);
    }
    if (node->getData() < value) {
        return findNode(node->getRight(), value);
    }
    return node;
}

template <typename Type>
bool BinaryTree<Type>::pairHelper(const Node<Type>* node, const Type& target) const {
    if (node == nullptr) {
        return false;
    }

    const Node<Type>* partner = findNode(root, target - node->getData());
    if (partner != nullptr && partner != node) {
        return true;
    }

    if (pairHelper(node->getLeft(), target)) {
        return true;
    }
    return pairHelper(node->getRight(), target);
}

static string boolStr(bool b) {
    if (b) {
        return "true";
    }
    return "false";
}

int main() {
    int n;
    cin >> n;

    BinaryTree<int> tree;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        tree.insert(v);
    }

    cout << "Tree: ";
    tree.printInOrder(cout);
    cout << endl;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int target;
        cin >> target;
        cout << "Target " << target << ": " << boolStr(tree.hasPair(target)) << endl;
    }

    return 0;
}