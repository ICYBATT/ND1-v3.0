#include "Generator.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>

bool generuoti_studentu_faila(const std::string& failas, int kiekis, int nd_kiekis) {
    std::ofstream out(failas);
    if (!out) {
        std::cout << "Nepavyko sukurti failo: " << failas << "\n";
        return false;
    }

    out << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde";

    for (int i = 1; i <= nd_kiekis; i++) {
        out << std::setw(8) << ("ND" + std::to_string(i));
    }
    out << std::setw(8) << "Egz." << "\n";

    for (int i = 1; i <= kiekis; i++) {
        out << std::left << std::setw(20) << ("Vardas" + std::to_string(i))
            << std::setw(20) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < nd_kiekis; j++) {
            out << std::setw(8) << (std::rand() % 10 + 1);
        }

        out << std::setw(8) << (std::rand() % 10 + 1) << "\n";

        if (i % 1000000 == 0) {
            std::cout << failas << ": sugeneruota " << i << " irasu\n";
        }
    }

    out.close();

    if (!out) {
        std::cout << "Klaida uzdarant faila: " << failas << "\n";
        return false;
    }

    std::cout << "Baigtas failas: " << failas << "\n";
    return true;
}

void generuoti_visus_testinius_failus() {
    generuoti_studentu_faila("studentai1000.txt", 1000);
    generuoti_studentu_faila("studentai10000.txt", 10000);
    generuoti_studentu_faila("studentai100000.txt", 100000);
    generuoti_studentu_faila("studentai1000000.txt", 1000000);
    generuoti_studentu_faila("studentai10000000.txt", 10000000);
}