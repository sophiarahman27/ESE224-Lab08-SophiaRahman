// F26 ESE224 LAB08 EX2 SOPHIA RAHMAN
// P3: Copy a Range from a BST to a Linked List
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <typename Type>
struct ListNode {
    Type value;
    ListNode<Type>* next;
};

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
    void rangeHelper(const Node<Type>* node, const Type& low, const Type& high,
                     ListNode<Type>*& head, ListNode<Type>*& tail) const;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(); }
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    bool empty() const { return root == nullptr; }
    void insert(const Type& value) { root = insertHelper(root, value); }
    void printInOrder(ostream& out) const;
    void clear() { clearHelper(root); root = nullptr; }

    bool copyRangeToList(const Type& low, const Type& high,
                         ListNode<Type>*& head,
                         ListNode<Type>*& tail) const;
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
void BinaryTree<Type>::rangeHelper(const Node<Type>* node, const Type& low, const Type& high,
                                   ListNode<Type>*& head, ListNode<Type>*& tail) const {
    if (node == nullptr) {
        return;
    }

    if (low < node->getData()) {                
        rangeHelper(node->getLeft(), low, high, head, tail);
    }

    if (!(node->getData() < low) && !(high < node->getData())) {   
        ListNode<Type>* added = new ListNode<Type>{node->getData(), nullptr};
        if (tail == nullptr) {
            head = added;
            tail = added;
        } else {
            tail->next = added;
            tail = added;
        }
    }

    if (node->getData() < high) {              
        rangeHelper(node->getRight(), low, high, head, tail);
    }
}

template <typename Type>
bool BinaryTree<Type>::copyRangeToList(const Type& low, const Type& high,
                                       ListNode<Type>*& head,
                                       ListNode<Type>*& tail) const {
    if (high < low) {
        return false;                            
    }
    rangeHelper(root, low, high, head, tail);
    return true;                                 
}

template <typename Type>
void printList(const ListNode<Type>* head, ostream& out) {
    if (head == nullptr) {
        out << "(empty)";
        return;
    }
    const ListNode<Type>* cur = head;
    while (cur != nullptr) {
        out << cur->value << " -> ";
        cur = cur->next;
    }
    out << "NULL";
}

template <typename Type>
void deleteList(ListNode<Type>*& head, ListNode<Type>*& tail) {
    while (head != nullptr) {
        ListNode<Type>* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
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
    int low;
    int high;
    cin >> low >> high;

    ListNode<int>* head = nullptr;
    ListNode<int>* tail = nullptr;

    ostringstream beforeText;
    tree.printInOrder(beforeText);

    bool valid = tree.copyRangeToList(low, high, head, tail);
    cout << "Valid range: " << boolStr(valid) << endl;
    cout << "Tree before copy: " << beforeText.str() << endl;

    cout << "Tree after copy: ";
    tree.printInOrder(cout);
    cout << endl;

    cout << "List: ";
    printList(head, cout);
    cout << endl;

    tree.clear();
    cout << "Tree empty after clear: " << boolStr(tree.empty()) << endl;

    cout << "List after tree clear: ";
    printList(head, cout);
    cout << endl;

    deleteList(head, tail);
    return 0;
}