#pragma once
#include <vector>
#include <string>
#include "studentas.h"

void isvesti_i_ekrana(const std::vector<Studentas>& grupe, char vm);
void isvesti_i_faila(const std::vector<Studentas>& grupe, const std::string& failas, char vm);
void isvedimo_pasirinkimas(const std::vector<Studentas>& grupe, char vm);