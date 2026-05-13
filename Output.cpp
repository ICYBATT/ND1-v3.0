#include "Output.h"
#include "Input.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::ofstream;
using std::string;
using std::vector;

void isvesti_i_ekrana(const vector<Studentas>& grupe, char vm) {
    cout << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(20) << ((vm == 'M' || vm == 'm') ? "Galutinis (Med.)" : "Galutinis (Vid.)")
         << "\n";

    cout << string(60, '-') << "\n";

    cout << fixed << setprecision(2);

    for (const auto& a : grupe) {
        double gal = galutinis_pagal(a, vm);

        cout << left << setw(20) << a.getVardas()
             << setw(20) << a.getPavarde()
             << setw(20) << gal
             << "\n";
    }
}

void isvesti_i_faila(const vector<Studentas>& grupe, const string& failas, char vm) {
    ofstream out(failas);
    if (!out) {
        cout << "Nepavyko sukurti failo: " << failas << endl;
        return;
    }

    out << left << setw(20) << "Vardas"
        << setw(20) << "Pavarde"
        << setw(20) << ((vm == 'M' || vm == 'm') ? "Galutinis (Med.)" : "Galutinis (Vid.)")
        << "\n";

    out << string(60, '-') << "\n";

    out << fixed << setprecision(2);

    for (const auto& a : grupe) {
        double gal = galutinis_pagal(a, vm);

        out << left << setw(20) << a.getVardas()
            << setw(20) << a.getPavarde()
            << setw(20) << gal
            << "\n";
    }
}

void isvedimo_pasirinkimas(const vector<Studentas>& grupe, char vm) {
    if (grupe.empty()) {
        cout << "Grupe tuscia.\n";
        return;
    }

    cout << "\nKur isvesti rezultatus?\n";
    cout << "1 - I ekrana\n";
    cout << "2 - I faila\n";

    int kur = ivesti_skaiciu("Pasirinkimas: ", 1, 2);

    if (kur == 1) {
        isvesti_i_ekrana(grupe, vm);
    } else {
        string outname;
        cout << "Failo pavadinimas (pvz. rezultatai.txt): ";
        std::cin >> outname;
        isvesti_i_faila(grupe, outname, vm);
        cout << "Rezultatai irasyti i faila: " << outname << endl;
    }
}