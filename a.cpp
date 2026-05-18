#include <iostream>
using namespace std;

class List {
private:
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };

    Node* head;
    int sz;

    void copy(const List& other) {
        head = nullptr;
        sz = 0;
        Node* cur = other.head;
        Node* tail = nullptr;
        while (cur) {
            Node* n = new Node(cur->data);
            if (!tail) head = n;
            else tail->next = n;
            tail = n;
            sz++;
            cur = cur->next;
        }
    }

    void free() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        sz = 0;
    }

public:
    List() : head(nullptr), sz(0) {}
    List(const List& other) { copy(other); }
    ~List() { free(); }

    List& operator=(const List& other) {
        if (this != &other) { free(); copy(other); }
        return *this;
    }

    List operator+(int item) const {
        List result(*this);
        Node* n = new Node(item);
        if (!result.head) {
            result.head = n;
        } else {
            Node* cur = result.head;
            while (cur->next) cur = cur->next;
            cur->next = n;
        }
        result.sz++;
        return result;
    }

    List& operator--() {
        if (!head) return *this;
        if (!head->next) {
            delete head;
            head = nullptr;
            sz = 0;
            return *this;
        }
        Node* cur = head;
        while (cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
        sz--;
        return *this;
    }

    List operator--(int) {
        List before(*this);
        --(*this);
        return before;
    }

    bool operator==(const List& other) const {
        if (sz != other.sz) return false;
        Node* a = head;
        Node* b = other.head;
        while (a) {
            if (a->data != b->data) return false;
            a = a->next;
            b = b->next;
        }
        return true;
    }

    bool operator!=(const List& other) const {
        return !(*this == other);
    }

    void print() const {
        Node* cur = head;
        cout << "[";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "]  size=" << sz << "\n";
    }
};

int main() {
    List l1;
    l1 = l1 + 10;
    l1 = l1 + 20;
    l1 = l1 + 30;
    l1 = l1 + 40;
    cout << "l1: "; l1.print();

    List l2;
    l2 = l2 + 10;
    l2 = l2 + 20;
    l2 = l2 + 99;
    cout << "l2: "; l2.print();

    cout << "l1 != l2: " << (l1 != l2 ? "true" : "false") << "\n";

    List l3 = l1;
    cout << "l3 (копия l1): "; l3.print();
    cout << "l1 != l3: " << (l1 != l3 ? "true" : "false") << "\n";

    cout << "\nПостфиксный l1--:\n";
    List snap = l1--;
    cout << "  снимок: "; snap.print();
    cout << "  l1:     "; l1.print();

    cout << "\nПрефиксный --l1 три раза:\n";
    --l1; cout << "  "; l1.print();
    --l1; cout << "  "; l1.print();
    --l1; cout << "  "; l1.print();

    return 0;
}
