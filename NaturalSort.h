#pragma once
#include <string>
#include "studentas.h"

bool palyginti_nat(const std::string& a, const std::string& b);

bool compareByName(const Studentas& a, const Studentas& b);
bool compareBySurname(const Studentas& a, const Studentas& b);
bool compareByAvg(const Studentas& a, const Studentas& b);
bool compareByMed(const Studentas& a, const Studentas& b);