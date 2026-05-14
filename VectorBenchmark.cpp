#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>

#include "Vector.h"

template <typename Konteineris>
double matuoti_uzpildyma(std::size_t kiekis, std::size_t& perskirstymai) {
    Konteineris v;
    perskirstymai = 0;

    auto pradzia = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < kiekis; ++i) {
        if (v.capacity() == v.size()) {
            ++perskirstymai;
        }

        v.push_back(static_cast<int>(i));
    }

    auto pabaiga = std::chrono::high_resolution_clock::now();

    volatile std::size_t kontrole = v.size();
    (void)kontrole;

    std::chrono::duration<double> trukme = pabaiga - pradzia;
    return trukme.count();
}

int main() {
    std::vector<std::size_t> dydziai = {
        10000,
        100000,
        1000000,
        10000000,
        100000000
    };

    std::cout << "std::vector vs Vector push_back spartos analize\n";
    std::cout << "Pastaba: 100000000 elementu testas gali uztrukti ilgiau.\n\n";

    std::cout << std::left
              << std::setw(15) << "Elementai"
              << std::setw(20) << "std::vector (s)"
              << std::setw(20) << "Vector (s)"
              << std::setw(25) << "std perskirstymai"
              << std::setw(25) << "Vector perskirstymai"
              << "\n";

    std::cout << std::string(105, '-') << "\n";

    for (std::size_t kiekis : dydziai) {
        std::size_t std_perskirstymai = 0;
        std::size_t vector_perskirstymai = 0;

        double std_laikas = matuoti_uzpildyma<std::vector<int>>(kiekis, std_perskirstymai);
        double vector_laikas = matuoti_uzpildyma<Vector<int>>(kiekis, vector_perskirstymai);

        std::cout << std::left
                  << std::setw(15) << kiekis
                  << std::setw(20) << std::fixed << std::setprecision(6) << std_laikas
                  << std::setw(20) << std::fixed << std::setprecision(6) << vector_laikas
                  << std::setw(25) << std_perskirstymai
                  << std::setw(25) << vector_perskirstymai
                  << "\n";
    }

    return 0;
}