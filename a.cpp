#include <iostream>
#include <cstring>
using namespace std;

template<typename T>
class List {
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    Node* head;
public:
    List() : head(nullptr) {}
    ~List() { clear(); }
    List(const List& other) : head(nullptr) {
        Node* cur = other.head;
        while(cur) { add(cur->data); cur = cur->next; }
    }
    List& operator=(const List& other) {
        if(this != &other) { clear(); Node* cur = other.head; while(cur) { add(cur->data); cur = cur->next; } }
        return *this;
    }
    void clear() {
        while(head) { Node* tmp = head; head = head->next; delete tmp; }
    }
    void add(const T& val) {
        Node* n = new Node(val);
        if(!head) { head = n; return; }
        Node* cur = head;
        while(cur->next) cur = cur->next;
        cur->next = n;
    }
    List& operator+(const T& item) {
        add(item);
        return *this;
    }
    void operator--(int) {
        if(!head) return;
        if(!head->next) { delete head; head = nullptr; return; }
        Node* cur = head;
        while(cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
    }
    bool operator!=(const List& other) const {
        Node* c1 = head;
        Node* c2 = other.head;
        while(c1 && c2) {
            if(!(c1->data == c2->data)) return true;
            c1 = c1->next;
            c2 = c2->next;
        }
        return c1 != nullptr || c2 != nullptr;
    }
    void forEach(void (*f)(const T&)) const {
        Node* cur = head;
        while(cur) { f(cur->data); cur = cur->next; }
    }
};

void printInt(int i) { cout << i << " "; }

int main() {
    List<int> l1;
    l1 + 1; l1 + 2; l1 + 3;
    l1--;
    cout << "List1: ";
    l1.forEach(printInt);
    cout << "\n";

    List<int> l2;
    l2 + 1; l2 + 2;

    cout << "l1 != l2: " << (l1 != l2) << "\n";
    return 0;
}
