#include "Input.h"
#include <iostream>
#include <limits>
#include <stdexcept>

using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;

static int readIntOrThrow() {
    int x;
    if (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw std::runtime_error("Klaida: ivesta ne skaicius.");
    }
    return x;
}

int ivesti_skaiciu(const std::string& tekstas, int nuo, int iki) {
    while (true) {
        try {
            cout << tekstas;
            int x = readIntOrThrow();
            if (x < nuo || x > iki) {
                throw std::runtime_error("Klaida: skaicius uz ribu.");
            }
            return x;
        } catch (const std::exception& e) {
            cout << e.what() << " Iveskite skaiciu nuo " << nuo << " iki " << iki << ".\n";
        }
    }
}

int ivesti_kieki(const std::string& tekstas) {
    while (true) {
        try {
            cout << tekstas;
            int x = readIntOrThrow();
            if (x <= 0) throw std::runtime_error("Klaida: skaicius turi buti bent 1.");
            return x;
        } catch (const std::exception& e) {
            cout << e.what() << " Bandykite dar karta.\n";
        }
    }
}

char ivesti_vm() {
    while (true) {
        cout << "Skaiciuoti pagal (V)idurkis ar (M)ediana? ";
        char p;
        cin >> p;
        if (p == 'V' || p == 'v' || p == 'M' || p == 'm') return p;

        cout << "Klaida: iveskite V arba M.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}