#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

// ===== ЗАДАЧА a) Однонаправленный список =====

template <class T>
class List {
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* head;
    int sz;
public:
    List() : head(nullptr), sz(0) {}

    List(const List& other) : head(nullptr), sz(0) {
        Node* cur = other.head;
        while (cur) {
            *this + cur->data;
            cur = cur->next;
        }
    }

    ~List() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    List& operator+(T val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = newNode;
        }
        sz++;
        return *this;
    }

    List& operator--() {
        if (!head) return *this;
        if (!head->next) {
            delete head;
            head = nullptr;
            sz--;
            return *this;
        }
        Node* cur = head;
        while (cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
        sz--;
        return *this;
    }

    bool operator!=(const List& other) const {
        Node* a = head;
        Node* b = other.head;
        while (a && b) {
            if (!(a->data == b->data)) return true;
            a = a->next;
            b = b->next;
        }
        return a != nullptr || b != nullptr;
    }

    void show() const {
        Node* cur = head;
        cout << "[";
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "]" << endl;
    }

    int size() const { return sz; }
};

// ===== ЗАДАЧА b) Иерархия классов: Микроорганизмы =====

class Microorganism {
protected:
    char name[50];
    double size_um;
    static double minSize;
    static int count;
public:
    Microorganism(const char* n, double s) : size_um(s) {
        strcpy(name, n);
        count++;
        if (count == 1 || s < minSize) minSize = s;
    }

    virtual ~Microorganism() { count--; }

    virtual void info() const {
        cout << "Microorganism: " << name << ", size: " << size_um << " um" << endl;
    }

    virtual double getSize() const { return size_um; }

    static double getMinSize() { return minSize; }
    static int getCount() { return count; }

    const char* getName() const { return name; }
};

double Microorganism::minSize = 0.0;
int Microorganism::count = 0;

class Bacterium : public Microorganism {
    char shape[30];
public:
    Bacterium(const char* n, double s, const char* sh) : Microorganism(n, s) {
        strcpy(shape, sh);
    }

    void info() const override {
        cout << "Bacterium: " << name << ", size: " << size_um << " um, shape: " << shape << endl;
    }
};

class Virus : public Microorganism {
    char type[30];
public:
    Virus(const char* n, double s, const char* t) : Microorganism(n, s) {
        strcpy(type, t);
    }

    void info() const override {
        cout << "Virus: " << name << ", size: " << size_um << " um, type: " << type << endl;
    }
};

class Protozoa : public Microorganism {
    bool hasNucleus;
public:
    Protozoa(const char* n, double s, bool nucleus) : Microorganism(n, s), hasNucleus(nucleus) {}

    void info() const override {
        cout << "Protozoa: " << name << ", size: " << size_um << " um, nucleus: " << (hasNucleus ? "yes" : "no") << endl;
    }
};

// ===== ЗАДАЧА c) Шаблонный класс однонаправленного списка =====
// Класс List уже шаблонный (объявлен выше).
// Демонстрируем его работу с Microorganism* и char.

int main() {
    // --- Демонстрация задачи a) и c) для char ---
    cout << "=== List<char> ===" << endl;
    List<char> charList;
    charList + 'A';
    charList + 'B';
    charList + 'C';
    charList + 'D';
    cout << "Initial list: ";
    charList.show();

    --charList;
    cout << "After --(remove last): ";
    charList.show();

    List<char> charList2;
    charList2 + 'A';
    charList2 + 'B';
    charList2 + 'X';

    cout << "charList != charList2: " << (charList != charList2 ? "true" : "false") << endl;

    List<char> charList3;
    charList3 + 'A';
    charList3 + 'B';
    charList3 + 'C';
    cout << "charList != charList3 (same): " << (charList != charList3 ? "true" : "false") << endl;

    // --- Демонстрация задачи b) ---
    cout << "\n=== Hierarchy: Microorganisms ===" << endl;

    Bacterium b1("E.coli", 2.0, "rod");
    Virus v1("Influenza", 0.1, "RNA");
    Protozoa p1("Amoeba", 500.0, true);
    Bacterium b2("Staphylococcus", 1.0, "sphere");
    Virus v2("SARS-CoV-2", 0.12, "RNA");

    Microorganism* organisms[5] = {&b1, &v1, &p1, &b2, &v2};

    for (int i = 0; i < 5; i++) {
        organisms[i]->info();
    }

    cout << "\nTotal organisms created: " << Microorganism::getCount() << endl;
    cout << "Minimum size: " << Microorganism::getMinSize() << " um" << endl;

    // --- Демонстрация задачи c) для List<Microorganism*> ---
    cout << "\n=== List<Microorganism*> ===" << endl;
    List<Microorganism*> bioList;
    bioList + static_cast<Microorganism*>(&b1);
    bioList + static_cast<Microorganism*>(&v1);
    bioList + static_cast<Microorganism*>(&p1);
    bioList + static_cast<Microorganism*>(&b2);
    cout << "List size: " << bioList.size() << endl;

    --bioList;
    cout << "After remove last, size: " << bioList.size() << endl;

    List<Microorganism*> bioList2;
    bioList2 + static_cast<Microorganism*>(&b1);
    bioList2 + static_cast<Microorganism*>(&v1);
    bioList2 + static_cast<Microorganism*>(&p1);

    cout << "bioList != bioList2 (should be false): " << (bioList != bioList2 ? "true" : "false") << endl;

    return 0;
}
