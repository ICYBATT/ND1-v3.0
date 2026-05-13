#pragma once
#include <string>
#include <vector>
#include <list>
#include <deque>
#include "studentas.h"

enum KonteinerioTipas {
    KONTEINERIS_VECTOR = 1,
    KONTEINERIS_LIST = 2,
    KONTEINERIS_DEQUE = 3
};

enum StrategijosTipas {
    STRATEGIJA1 = 1,
    STRATEGIJA2 = 2,
    STRATEGIJA3 = 3
};

struct TyrimoRezultatasV1 {
    std::string failas;
    std::string konteineris;
    int strategija = 0;
    size_t studentu_kiekis = 0;
    int praleista = 0;
    double nuskaitymas = 0.0;
    double rikiavimas = 0.0;
    double skirstymas = 0.0;
    double visas = 0.0;
};

std::string konteinerio_pavadinimas(int tipas);

void spausdinti_v1_rezultata(const TyrimoRezultatasV1& r);
void spausdinti_v1_lentele(const std::vector<TyrimoRezultatasV1>& visi);