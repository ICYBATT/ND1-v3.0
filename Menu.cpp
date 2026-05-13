#include "Menu.h"
#include "Input.h"
#include <iostream>

int meniu() {
    std::cout << "\n========== MENIU ==========\n";
    std::cout << "1 - Vesti studentus ranka\n";
    std::cout << "2 - Vesti vardus, pazymiai generuojami\n";
    std::cout << "3 - Viska generuoja programa\n";
    std::cout << "4 - Nuskaityti studentus is failo\n";
    std::cout << "5 - Suskirstyti studentus i vargsiukus ir kietiakus\n";
    std::cout << "6 - Rikiuoti ir isvesti dabartine grupe\n";
    std::cout << "7 - Sugeneruoti testinius failus\n";
    std::cout << "8 - Atlikti vieno failo spartos tyrima (v0.4)\n";
    std::cout << "9 - Atlikti visu failu spartos tyrima (v0.4)\n";
    std::cout << "10 - V1.0 vieno failo konteineriu tyrimas\n";
    std::cout << "11 - V1.0 visu failu konteineriu tyrimas\n";
    std::cout << "12 - V1.5 Studentas klases testai\n";
    std::cout << "13 - Baigti\n";

    return ivesti_skaiciu("Pasirinkimas: ", 1, 13);
}