#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "studentas.h"

template <typename Container>
bool nuskaityti_i_konteineri(const std::string& failas, Container& studentai, int& praleista) {
    std::ifstream in(failas);

    if (!in) {
        return false;
    }

    studentai.clear();
    praleista = 0;

    std::string eilute;

    // Praleidziame antraste
    std::getline(in, eilute);

    while (std::getline(in, eilute)) {
        if (eilute.empty()) {
            continue;
        }

        std::istringstream iss(eilute);

        std::string vardas;
        std::string pavarde;

        if (!(iss >> vardas >> pavarde)) {
            ++praleista;
            continue;
        }

        std::vector<int> skaiciai;
        int x;

        while (iss >> x) {
            skaiciai.push_back(x);
        }

        if (skaiciai.empty()) {
            ++praleista;
            continue;
        }

        bool blogi_duomenys = false;

        for (int pazymys : skaiciai) {
            if (pazymys < 1 || pazymys > 10) {
                blogi_duomenys = true;
                break;
            }
        }

        if (blogi_duomenys) {
            ++praleista;
            continue;
        }

        int egzaminas = skaiciai.back();
        skaiciai.pop_back();

        Studentas s(vardas, pavarde, skaiciai, egzaminas);
        s.skaiciuotiGalutinius();

        studentai.push_back(s);
    }

    return true;
}

template <typename Container>
void rikiuoti_konteineri(Container& studentai, int rikiavimo_budas) {
    std::vector<Studentas> laikinas;

    for (const auto& s : studentai) {
        laikinas.push_back(s);
    }

    if (rikiavimo_budas == 1) {
        std::stable_sort(laikinas.begin(), laikinas.end(),
            [](const Studentas& a, const Studentas& b) {
                return a.getVardas() < b.getVardas();
            });
    } else if (rikiavimo_budas == 2) {
        std::stable_sort(laikinas.begin(), laikinas.end(),
            [](const Studentas& a, const Studentas& b) {
                return a.getPavarde() < b.getPavarde();
            });
    } else if (rikiavimo_budas == 3) {
        std::stable_sort(laikinas.begin(), laikinas.end(),
            [](const Studentas& a, const Studentas& b) {
                return a.getGalVid() < b.getGalVid();
            });
    } else if (rikiavimo_budas == 4) {
        std::stable_sort(laikinas.begin(), laikinas.end(),
            [](const Studentas& a, const Studentas& b) {
                return a.getGalMed() < b.getGalMed();
            });
    }

    studentai.clear();

    for (const auto& s : laikinas) {
        studentai.push_back(s);
    }
}

inline bool yra_vargsiukas(const Studentas& s, char vm) {
    return galutinis_pagal(s, vm) < 5.0;
}

template <typename Container>
void skirstyti_strategija1(
    const Container& studentai,
    Container& vargsiukai,
    Container& kietiakai,
    char vm
) {
    vargsiukai.clear();
    kietiakai.clear();

    for (const auto& s : studentai) {
        if (yra_vargsiukas(s, vm)) {
            vargsiukai.push_back(s);
        } else {
            kietiakai.push_back(s);
        }
    }
}

template <typename Container>
void skirstyti_strategija2(
    Container& studentai,
    Container& vargsiukai,
    char vm
) {
    vargsiukai.clear();

    auto it = studentai.begin();

    while (it != studentai.end()) {
        if (yra_vargsiukas(*it, vm)) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

template <typename Container>
void skirstyti_strategija3(
    Container& studentai,
    Container& vargsiukai,
    Container& kietiakai,
    char vm
) {
    vargsiukai.clear();
    kietiakai.clear();

    auto riba = std::stable_partition(
        studentai.begin(),
        studentai.end(),
        [vm](const Studentas& s) {
            return yra_vargsiukas(s, vm);
        }
    );

    for (auto it = studentai.begin(); it != riba; ++it) {
        vargsiukai.push_back(*it);
    }

    for (auto it = riba; it != studentai.end(); ++it) {
        kietiakai.push_back(*it);
    }
}