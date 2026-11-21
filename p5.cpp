// F26 ESE224 LAB08 EX5 SOPHIA RAHMAN
// P5: Flags in a Singly Linked List
#include <iostream>
using namespace std;

const unsigned int READY    = 1;  
const unsigned int SELECTED = 2;  
const unsigned int LOCKED   = 4;  

struct FlagNode {
    unsigned int flags;
    FlagNode* next;
};

class FlagList {
private:
    FlagNode* head;
    FlagNode* tail;

public:
    FlagList() : head(nullptr), tail(nullptr) {}

    ~FlagList() {
        while (head != nullptr) {
            FlagNode* next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;
    }

    FlagList(const FlagList&) = delete;             
    FlagList& operator=(const FlagList&) = delete;

    void append(unsigned int flags) {
        FlagNode* added = new FlagNode;
        added->flags = flags;
        added->next = nullptr;
        if (tail == nullptr) {
            head = added;
        } else {
            tail->next = added;
        }
        tail = added;
    }

    void makeReady() {
        FlagNode* cur = head;
        while (cur != nullptr) {
            if ((cur->flags & LOCKED) == 0) {
                cur->flags = cur->flags | READY;
            }
            cur = cur->next;
        }
    }

    void toggleSelected() {
        FlagNode* cur = head;
        while (cur != nullptr) {
            if (((cur->flags & READY) != 0) && ((cur->flags & LOCKED) == 0)) {
                cur->flags = cur->flags ^ SELECTED;
            }
            cur = cur->next;
        }
    }

    void printForward(ostream& out) const {
        if (head == nullptr) {
            out << "(empty)";
            return;
        }
        const FlagNode* cur = head;
        while (cur != nullptr) {
            out << cur->flags;
            if (cur->next != nullptr) {
                out << ' ';
            }
            cur = cur->next;
        }
    }

    int countReady() const {
        int count = 0;
        const FlagNode* cur = head;
        while (cur != nullptr) {
            if ((cur->flags & READY) != 0) {
                count++;
            }
            cur = cur->next;
        }
        return count;
    }

    int countSelected() const {
        int count = 0;
        const FlagNode* cur = head;
        while (cur != nullptr) {
            if ((cur->flags & SELECTED) != 0) {
                count++;
            }
            cur = cur->next;
        }
        return count;
    }

    int countLocked() const {
        int count = 0;
        const FlagNode* cur = head;
        while (cur != nullptr) {
            if ((cur->flags & LOCKED) != 0) {
                count++;
            }
            cur = cur->next;
        }
        return count;
    }
};

int main() {
    int n;
    cin >> n;

    FlagList list;
    FlagList extra;  
    for (int i = 0; i < n; i++) {
        unsigned int f;
        cin >> f;
        list.append(f);
        extra.append(f);
    }

    cout << "Initial: ";
    list.printForward(cout);
    cout << endl;

    list.makeReady();
    cout << "Ready: ";
    list.printForward(cout);
    cout << endl;

    list.toggleSelected();
    cout << "Selected: ";
    list.printForward(cout);
    cout << endl;

    list.toggleSelected();
    cout << "Selected again: ";
    list.printForward(cout);
    cout << endl;

    cout << "Ready count: " << list.countReady() << endl;
    cout << "Selected count: " << list.countSelected() << endl;
    cout << "Locked count: " << list.countLocked() << endl;

    extra.makeReady();
    cerr << "[extra] after 1st makeReady: ";
    extra.printForward(cerr);
    cerr << endl;
    extra.makeReady();
    cerr << "[extra] after 2nd makeReady: ";
    extra.printForward(cerr);
    cerr << endl;

    return 0;
}