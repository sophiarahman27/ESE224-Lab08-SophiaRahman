// F26 ESE224 LAB08 EX4 SOPHIA RAHMAN
// P4: A Four-Bit Class
#include <iostream>
using namespace std;

class FourBit {
private:
    unsigned int value;
public:
    FourBit() : value(0) {}
    FourBit(unsigned int initial) : value(initial) {}

    unsigned int getValue() const {
        return value;
    }

    FourBit operator|(const FourBit& other) const {
        return FourBit(value | other.value);
    }

    FourBit operator&(const FourBit& other) const {
        return FourBit(value & other.value);
    }

    FourBit operator^(const FourBit& other) const {
        return FourBit(value ^ other.value);
    }

    FourBit operator~() const {
        return FourBit((~value) & 0xFu);   
    }

    void print(ostream& out) const {
        out << value << ' ';
        for (int bit = 3; bit >= 0; bit--) {
            if ((value >> bit) & 1u) {
                out << '1';
            } else {
                out << '0';
            }
        }
    }
};

static void show(const char* label, const FourBit& f) {
    cout << label << ": ";
    f.print(cout);
    cout << endl;
}

int main() {
    unsigned int inA;
    unsigned int inB;
    cin >> inA >> inB;

    FourBit A(inA);
    FourBit B(inB);

    show("A", A);
    show("B", B);
    show("A | B", A | B);
    show("A & B", A & B);
    show("A ^ B", A ^ B);
    show("~A", ~A);
    show("(A | B) & ~B", (A | B) & ~B);
    show("A unchanged", A);
    show("B unchanged", B);

    return 0;
}