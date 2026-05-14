#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <fstream>

#include "studentas.h"
#include "Vector.h"
#include "KonteineriuStrategijos.h"

template <typename Container>
double matuoti_studentu_apdorojima(
    const std::string& failas,
    char vm,
    int rikiavimo_budas,
    int strategija,
    std::size_t& kiekis,
    std::size_t& vargsiukai_kiekis,
    std::size_t& kietiakai_kiekis
) {
    Container studentai;
    Container vargsiukai;
    Container kietiakai;

    int praleista = 0;

    auto pradzia = std::chrono::high_resolution_clock::now();

    bool pavyko = nuskaityti_i_konteineri(failas, studentai, praleista);

    if (!pavyko) {
        kiekis = 0;
        vargsiukai_kiekis = 0;
        kietiakai_kiekis = 0;
        return -1.0;
    }

    rikiuoti_konteineri(studentai, rikiavimo_budas);

    if (strategija == 1) {
        skirstyti_strategija1(studentai, vargsiukai, kietiakai, vm);
    } else if (strategija == 2) {
        skirstyti_strategija2(studentai, vargsiukai, vm);
        kietiakai = studentai;
    } else {
        skirstyti_strategija3(studentai, vargsiukai, kietiakai, vm);
    }

    auto pabaiga = std::chrono::high_resolution_clock::now();

    kiekis = studentai.size();
    vargsiukai_kiekis = vargsiukai.size();
    kietiakai_kiekis = kietiakai.size();

    std::chrono::duration<double> trukme = pabaiga - pradzia;
    return trukme.count();
}

bool failas_egzistuoja(const std::string& failas) {
    std::ifstream in(failas);
    return in.good();
}

int main() {
    std::vector<std::string> failai = {
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    char vm = 'V';
    int rikiavimo_budas = 3;
    int strategija = 1;

    std::cout << "Studentu apdorojimo spartos analize\n";
    std::cout << "Lyginama std::vector<Studentas> ir Vector<Studentas>\n";
    std::cout << "Rikiavimas: pagal galutini vidurki\n";
    std::cout << "Strategija: 1\n\n";

    std::cout << std::left
              << std::setw(24) << "Failas"
              << std::setw(18) << "std::vector (s)"
              << std::setw(18) << "Vector (s)"
              << std::setw(14) << "Studentai"
              << std::setw(14) << "Vargsiukai"
              << std::setw(14) << "Kietiakai"
              << "\n";

    std::cout << std::string(102, '-') << "\n";

    for (const auto& failas : failai) {
        if (!failas_egzistuoja(failas)) {
            std::cout << std::left
                      << std::setw(24) << failas
                      << "Failas nerastas. Praleidziama.\n";
            continue;
        }

        std::size_t std_kiekis = 0;
        std::size_t std_vargsiukai = 0;
        std::size_t std_kietiakai = 0;

        std::size_t vector_kiekis = 0;
        std::size_t vector_vargsiukai = 0;
        std::size_t vector_kietiakai = 0;

        double std_laikas = matuoti_studentu_apdorojima<std::vector<Studentas>>(
            failas,
            vm,
            rikiavimo_budas,
            strategija,
            std_kiekis,
            std_vargsiukai,
            std_kietiakai
        );

        double vector_laikas = matuoti_studentu_apdorojima<Vector<Studentas>>(
            failas,
            vm,
            rikiavimo_budas,
            strategija,
            vector_kiekis,
            vector_vargsiukai,
            vector_kietiakai
        );

        std::cout << std::left
                  << std::setw(24) << failas
                  << std::setw(18) << std::fixed << std::setprecision(6) << std_laikas
                  << std::setw(18) << std::fixed << std::setprecision(6) << vector_laikas
                  << std::setw(14) << vector_kiekis
                  << std::setw(14) << vector_vargsiukai
                  << std::setw(14) << vector_kietiakai
                  << "\n";
    }

    return 0;
}