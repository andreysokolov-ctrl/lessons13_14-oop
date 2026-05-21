#include <iostream>
#include <cstring>
using namespace std;

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

int main() {
    Microorganism* b1 = new Bacteria("E.coli", 5.0);
    Microorganism* v1 = new Virus("Influenza", 0.08);
    Microorganism* b2 = new Bacteria("Staph", 2.5);

    b1->describe();
    v1->describe();
    b2->describe();

    cout << "Bacteria volume: " << b1->getVolume() << "\n";
    Microorganism::showMinSize();

    delete b1; delete v1; delete b2;
    return 0;
}
