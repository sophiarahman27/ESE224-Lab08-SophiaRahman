// F26 ESE224 LAB08 EX2 SOPHIA RAHMAN
// P2: A Binary Search Tree for Two Data Types
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
    bool containsHelper(const Node<Type>* node, const Type& value) const;
    void printHelper(const Node<Type>* node, ostream& out, bool& first) const;
    void clearHelper(Node<Type>* node);

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(); }
    BinaryTree(const BinaryTree&) = delete;             
    BinaryTree& operator=(const BinaryTree&) = delete;

    bool empty() const { return root == nullptr; }
    void insert(const Type& value) { root = insertHelper(root, value); }
    bool contains(const Type& value) const { return containsHelper(root, value); }
    bool minimum(Type& result) const;
    bool maximum(Type& result) const;
    void printInOrder(ostream& out) const;
    void clear() { clearHelper(root); root = nullptr; }
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
bool BinaryTree<Type>::containsHelper(const Node<Type>* node, const Type& value) const {
    if (node == nullptr) {
        return false;
    }
    if (value < node->getData()) {
        return containsHelper(node->getLeft(), value);
    }
    if (node->getData() < value) {
        return containsHelper(node->getRight(), value);
    }
    return true;
}

template <typename Type>
bool BinaryTree<Type>::minimum(Type& result) const {
    if (root == nullptr) {
        return false;   
    }
    const Node<Type>* cur = root;
    while (cur->getLeft() != nullptr) {
        cur = cur->getLeft();
    }
    result = cur->getData();
    return true;
}

template <typename Type>
bool BinaryTree<Type>::maximum(Type& result) const {
    if (root == nullptr) {
        return false;
    }
    const Node<Type>* cur = root;
    while (cur->getRight() != nullptr) {
        cur = cur->getRight();
    }
    result = cur->getData();
    return true;
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

static string boolStr(bool b) {
    if (b) {
        return "true";
    }
    return "false";
}

template <typename Type>
void runDemo(int n, const Type& sentinel, const Type& reuseValue) {
    BinaryTree<Type> tree;
    cout << "Empty before insert: " << boolStr(tree.empty()) << endl;   
    for (int i = 0; i < n; i++) {
        Type v;
        cin >> v;
        tree.insert(v);
    }
    Type searchValue;
    cin >> searchValue;

    {
        BinaryTree<Type> probe;
        Type out = sentinel;
        bool a = probe.minimum(out);
        bool unchangedMin = (!a && !(out < sentinel) && !(sentinel < out));
        out = sentinel;
        bool b = probe.maximum(out);
        bool unchangedMax = (!b && !(out < sentinel) && !(sentinel < out));
        cerr << "[check] empty min/max unchanged: "
             << boolStr(unchangedMin && unchangedMax) << endl;
    }

    cout << "Inorder: ";
    tree.printInOrder(cout);
    cout << endl;

    Type r = sentinel;
    if (tree.minimum(r)) {
        cout << "Minimum: " << r << endl;
    } else {
        cout << "Minimum: none" << endl;
    }
    r = sentinel;
    if (tree.maximum(r)) {
        cout << "Maximum: " << r << endl;
    } else {
        cout << "Maximum: none" << endl;
    }

    cout << "Contains " << searchValue << ": " << boolStr(tree.contains(searchValue)) << endl;

    tree.clear();
    cout << "Empty after clear: " << boolStr(tree.empty()) << endl;
    r = sentinel;
    cout << "Minimum after clear: ";
    if (tree.minimum(r)) {
        cout << r << endl;
    } else {
        cout << "none" << endl;
    }
    r = sentinel;
    cout << "Maximum after clear: ";
    if (tree.maximum(r)) {
        cout << r << endl;
    } else {
        cout << "none" << endl;
    }
    cout << "Contains after clear: " << boolStr(tree.contains(searchValue)) << endl;

    tree.insert(reuseValue);
    cout << "After reuse: ";
    tree.printInOrder(cout);
    cout << endl;
}

int main() {
    string kind;
    int n;
    cin >> kind >> n;
    if (kind == "INT") {
        runDemo<int>(n, -999, 99);
    } else {
        runDemo<string>(n, "unchanged", "reset");
    }
    return 0;
}