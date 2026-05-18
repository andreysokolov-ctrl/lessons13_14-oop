#include <iostream>
#include <cstring>
using namespace std;

class Microorganism {
protected:
    char name[64];
    double size;

    static int count;
    static double minSize;

public:
    Microorganism(const char* n, double s) : size(s) {
        strncpy(name, n, 63);
        name[63] = '\0';
        count++;
        if (minSize < 0 || s < minSize) minSize = s;
    }

    virtual ~Microorganism() { count--; }

    virtual void describe() const { cout << name; }

    static int    getCount()   { return count; }
    static double getMinSize() { return minSize; }
};

int    Microorganism::count   = 0;
double Microorganism::minSize = -1;

class Bacterium : public Microorganism {
    bool gram;
public:
    Bacterium(const char* n, double s, bool g) : Microorganism(n, s), gram(g) {}

    void describe() const override {
        cout << "[Бактерия] " << name << " | " << size << " мкм | Грам: " << (gram ? "+" : "-") << "\n";
    }
};

class Virus : public Microorganism {
    char host[32];
public:
    Virus(const char* n, double s, const char* h) : Microorganism(n, s) {
        strncpy(host, h, 31);
        host[31] = '\0';
    }

    void describe() const override {
        cout << "[Вирус]    " << name << " | " << size << " нм | хозяин: " << host << "\n";
    }
};

ostream& operator<<(ostream& os, Microorganism* m) {
    if (m) m->describe();
    return os;
}

template<typename T>
class TList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;
    int sz;

    void copy(const TList& other) {
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
        while (head) { Node* t = head; head = head->next; delete t; }
        sz = 0;
    }

public:
    TList() : head(nullptr), sz(0) {}
    TList(const TList& o) { copy(o); }
    ~TList() { free(); }

    TList& operator=(const TList& o) {
        if (this != &o) { free(); copy(o); }
        return *this;
    }

    TList operator+(const T& item) const {
        TList r(*this);
        Node* n = new Node(item);
        if (!r.head) {
            r.head = n;
        } else {
            Node* cur = r.head;
            while (cur->next) cur = cur->next;
            cur->next = n;
        }
        r.sz++;
        return r;
    }

    TList& operator--() {
        if (!head) return *this;
        if (!head->next) { delete head; head = nullptr; sz = 0; return *this; }
        Node* cur = head;
        while (cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
        sz--;
        return *this;
    }

    TList operator--(int) {
        TList before(*this);
        --(*this);
        return before;
    }

    bool operator==(const TList& o) const {
        if (sz != o.sz) return false;
        Node* a = head;
        Node* b = o.head;
        while (a) {
            if (a->data != b->data) return false;
            a = a->next;
            b = b->next;
        }
        return true;
    }

    bool operator!=(const TList& o) const { return !(*this == o); }

    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "  [size=" << sz << "]\n";
    }
};

int main() {
    cout << "--- TList<char> ---\n";

    TList<char> chars;
    chars = chars + 'M';
    chars = chars + 'i';
    chars = chars + 'c';
    chars = chars + 'r';
    chars = chars + 'o';
    cout << "chars: "; chars.print();

    TList<char> snap = chars--;
    cout << "снимок: "; snap.print();
    cout << "chars после --: "; chars.print();

    --chars;
    cout << "chars после --chars: "; chars.print();

    TList<char> chars2;
    chars2 = chars2 + 'M';
    chars2 = chars2 + 'i';
    chars2 = chars2 + 'c';
    cout << "chars2: "; chars2.print();
    cout << "chars != chars2: " << (chars != chars2 ? "true" : "false") << "\n";

    cout << "\n--- TList<Microorganism*> ---\n";

    Microorganism* b1 = new Bacterium("E. coli", 2.0,  false);
    Microorganism* b2 = new Bacterium("Staph",   1.0,  true);
    Microorganism* v1 = new Virus    ("HIV",      0.12, "T-лимфоцит");

    TList<Microorganism*> bio;
    bio = bio + b1;
    bio = bio + v1;
    bio = bio + b2;
    bio.print();

    cout << "Объектов: " << Microorganism::getCount()
         << ", мин. размер: " << Microorganism::getMinSize() << "\n";

    bio--;
    cout << "После bio--: "; bio.print();

    delete b1; delete b2; delete v1;
    cout << "После delete: " << Microorganism::getCount() << "\n";

    return 0;
}
