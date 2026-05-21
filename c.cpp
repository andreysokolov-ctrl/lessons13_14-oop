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

class Microorganism {
private:
    char name[64];
    double size;
    static double minSize;
protected:
    void setName(const char* n) { strncpy(name, n, 63); name[63] = '\0'; }
    double getSize() const { return size; }
    const char* getName() const { return name; }
public:
    Microorganism(const char* n, double s) : size(s) {
        setName(n);
        if(s < minSize) minSize = s;
    }
    virtual ~Microorganism() {}
    virtual void describe() const = 0;
    virtual double getVolume() const = 0;
    static void showMinSize() { cout << "Min size: " << minSize << "\n"; }
};
double Microorganism::minSize = 1e18;

class Bacteria : public Microorganism {
public:
    Bacteria(const char* n, double s) : Microorganism(n, s) {}
    void describe() const { cout << "Bacteria: " << getName() << ", Size: " << getSize() << "\n"; }
    double getVolume() const { return getSize() * getSize() * getSize() * 0.5; }
};

class Virus : public Microorganism {
public:
    Virus(const char* n, double s) : Microorganism(n, s) {}
    void describe() const { cout << "Virus: " << getName() << ", Size: " << getSize() << "\n"; }
    double getVolume() const { return getSize() * getSize() * getSize() * 0.1; }
};

void printMicro(Microorganism* m) { if(m) m->describe(); }
void printChar(char c) { cout << c << " "; }
void deleteMicro(Microorganism* m) { delete m; }

int main() {
    List<Microorganism*> molList;
    molList + new Bacteria("E.coli", 5.0);
    molList + new Virus("Influenza", 0.05);
    molList + new Bacteria("Staph", 2.0);
    molList--;

    cout << "=== Microorganisms List ===\n";
    molList.forEach(printMicro);
    Microorganism::showMinSize();

    List<char> charList;
    charList + 'A'; charList + 'B'; charList + 'C';
    List<char> charList2;
    charList2 + 'A'; charList2 + 'B';

    cout << "\n=== Chars List ===\n";
    charList.forEach(printChar);
    cout << "\nLists != : " << (charList != charList2) << "\n";

    molList.forEach(deleteMicro);
    return 0;
}
