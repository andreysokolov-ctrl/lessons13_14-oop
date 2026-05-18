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

    virtual void describe()  const { cout << name << "\n"; }
    virtual void reproduce() const { cout << name << ": размножение не указано\n"; }

    static int    getCount()   { return count; }
    static double getMinSize() { return minSize; }
};

int    Microorganism::count   = 0;
double Microorganism::minSize = -1;

class Bacterium : public Microorganism {
    bool gramPositive;
public:
    Bacterium(const char* n, double s, bool gram)
        : Microorganism(n, s), gramPositive(gram) {}

    void describe() const override {
        cout << "[Бактерия] " << name
             << " | " << size << " мкм"
             << " | Грам: " << (gramPositive ? "+" : "-") << "\n";
    }

    void reproduce() const override {
        cout << name << " -> бинарное деление\n";
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
        cout << "[Вирус]    " << name
             << " | " << size << " нм"
             << " | хозяин: " << host << "\n";
    }

    void reproduce() const override {
        cout << name << " -> внедрение в " << host << "\n";
    }
};

class Fungus : public Microorganism {
    bool pathogenic;
public:
    Fungus(const char* n, double s, bool p)
        : Microorganism(n, s), pathogenic(p) {}

    void describe() const override {
        cout << "[Гриб]     " << name
             << " | " << size << " мкм"
             << " | патоген: " << (pathogenic ? "да" : "нет") << "\n";
    }

    void reproduce() const override {
        cout << name << " -> споруляция\n";
    }
};

void info(const Microorganism* m) {
    m->describe();
    m->reproduce();
    cout << "\n";
}

int main() {
    Microorganism* zoo[4];
    zoo[0] = new Bacterium("E. coli",         2.0,  false);
    zoo[1] = new Bacterium("Staphylococcus",  1.0,  true);
    zoo[2] = new Virus    ("HIV",             0.12, "T-лимфоцит");
    zoo[3] = new Fungus   ("Candida",         5.0,  true);

    cout << "describe() через Microorganism*:\n";
    for (int i = 0; i < 4; i++) zoo[i]->describe();

    cout << "\nreproduce() через Microorganism*:\n";
    for (int i = 0; i < 4; i++) zoo[i]->reproduce();

    cout << "\nПолиморфный вызов info():\n";
    info(zoo[0]);
    info(zoo[2]);

    cout << "Объектов: " << Microorganism::getCount() << "\n";
    cout << "Мин. размер: " << Microorganism::getMinSize() << "\n";

    for (int i = 0; i < 4; i++) delete zoo[i];

    cout << "После удаления: " << Microorganism::getCount() << "\n";

    return 0;
}
