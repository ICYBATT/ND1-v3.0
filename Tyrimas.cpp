#include "Tyrimas.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;

std::string konteinerio_pavadinimas(int tipas) {
    if (tipas == KONTEINERIS_VECTOR) return "vector";
    if (tipas == KONTEINERIS_LIST) return "list";
    if (tipas == KONTEINERIS_DEQUE) return "deque";
    return "nezinomas";
}

void spausdinti_v1_rezultata(const TyrimoRezultatasV1& r) {
    cout << "\n===== V1.0 TYRIMO REZULTATAS =====\n";
    cout << "Failas:       " << r.failas << "\n";
    cout << "Konteineris:  " << r.konteineris << "\n";
    cout << "Strategija:   " << r.strategija << "\n";
    cout << "Studentu:     " << r.studentu_kiekis << "\n";
    cout << "Praleista:    " << r.praleista << "\n";
    cout << "Nuskaitymas:  " << r.nuskaitymas << " s\n";
    cout << "Rikiavimas:   " << r.rikiavimas << " s\n";
    cout << "Skirstymas:   " << r.skirstymas << " s\n";
    cout << "Visas laikas: " << r.visas << " s\n";
}

void spausdinti_v1_lentele(const vector<TyrimoRezultatasV1>& visi) {
    cout << "\n========================= V1.0 TYRIMO LENTELE =========================\n";
    cout << std::left
         << std::setw(20) << "Failas"
         << std::setw(12) << "Kont."
         << std::setw(12) << "Strateg."
         << std::setw(12) << "Studentai"
         << std::setw(14) << "Nuskaitym."
         << std::setw(14) << "Rikiav."
         << std::setw(14) << "Skirst."
         << std::setw(14) << "Visas"
         << "\n";

    cout << string(112, '-') << "\n";

    cout << std::fixed << std::setprecision(6);

    for (const auto& r : visi) {
        cout << std::left
             << std::setw(20) << r.failas
             << std::setw(12) << r.konteineris
             << std::setw(12) << r.strategija
             << std::setw(12) << r.studentu_kiekis
             << std::setw(14) << r.nuskaitymas
             << std::setw(14) << r.rikiavimas
             << std::setw(14) << r.skirstymas
             << std::setw(14) << r.visas
             << "\n";
    }
}