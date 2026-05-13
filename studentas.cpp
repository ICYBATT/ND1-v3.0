#include "studentas.h"
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>

Studentas::Studentas()
    : Zmogus(), paz_(), egz_(0), gal_vid_(0.0), gal_med_(0.0) {}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& paz, int egz)
    : Zmogus(vardas, pavarde), paz_(paz), egz_(egz), gal_vid_(0.0), gal_med_(0.0) {
    skaiciuotiGalutinius();
}

Studentas::Studentas(const Studentas& kitas)
    : Zmogus(kitas.vardas_, kitas.pavarde_),
      paz_(kitas.paz_),
      egz_(kitas.egz_),
      gal_vid_(kitas.gal_vid_),
      gal_med_(kitas.gal_med_) {}

Studentas::Studentas(Studentas&& kitas) noexcept
    : Zmogus(std::move(kitas.vardas_), std::move(kitas.pavarde_)),
      paz_(std::move(kitas.paz_)),
      egz_(kitas.egz_),
      gal_vid_(kitas.gal_vid_),
      gal_med_(kitas.gal_med_) {

    kitas.egz_ = 0;
    kitas.gal_vid_ = 0.0;
    kitas.gal_med_ = 0.0;
}

Studentas& Studentas::operator=(const Studentas& kitas) {
    if (this != &kitas) {
        vardas_ = kitas.vardas_;
        pavarde_ = kitas.pavarde_;
        paz_ = kitas.paz_;
        egz_ = kitas.egz_;
        gal_vid_ = kitas.gal_vid_;
        gal_med_ = kitas.gal_med_;
    }
    return *this;
}

Studentas& Studentas::operator=(Studentas&& kitas) noexcept {
    if (this != &kitas) {
        vardas_ = std::move(kitas.vardas_);
        pavarde_ = std::move(kitas.pavarde_);
        paz_ = std::move(kitas.paz_);
        egz_ = kitas.egz_;
        gal_vid_ = kitas.gal_vid_;
        gal_med_ = kitas.gal_med_;

        kitas.egz_ = 0;
        kitas.gal_vid_ = 0.0;
        kitas.gal_med_ = 0.0;
    }
    return *this;
}

Studentas::~Studentas() {
    paz_.clear();
    egz_ = 0;
    gal_vid_ = 0.0;
    gal_med_ = 0.0;
}

const std::vector<int>& Studentas::getPaz() const { return paz_; }
int Studentas::getEgz() const { return egz_; }
double Studentas::getGalVid() const { return gal_vid_; }
double Studentas::getGalMed() const { return gal_med_; }

void Studentas::setPaz(const std::vector<int>& paz) { paz_ = paz; }
void Studentas::addPazymys(int pazymys) { paz_.push_back(pazymys); }
void Studentas::setEgz(int egz) { egz_ = egz; }

double mediana(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;

    std::vector<int> tmp = paz;
    std::sort(tmp.begin(), tmp.end());

    int n = (int)tmp.size();
    if (n % 2 == 1) return (double)tmp[n / 2];
    return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
}

void Studentas::skaiciuotiGalutinius() {
    double vid = 0.0;

    if (!paz_.empty()) {
        long long suma = 0;
        for (int x : paz_) suma += x;
        vid = (double)suma / paz_.size();
    }

    double med = mediana(paz_);

    gal_vid_ = vid * 0.4 + egz_ * 0.6;
    gal_med_ = med * 0.4 + egz_ * 0.6;
}

void Studentas::spausdintiInformacija() const {
    std::cout << vardas_ << " " << pavarde_
              << " Galutinis (vid): " << gal_vid_
              << " Galutinis (med): " << gal_med_
              << std::endl;
}

std::istream& operator>>(std::istream& in, Studentas& s) {
    std::string eilute;
    if (!std::getline(in >> std::ws, eilute)) return in;

    std::istringstream iss(eilute);
    std::string vardas, pavarde;

    if (!(iss >> vardas >> pavarde)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector<int> skaiciai;
    int x;
    while (iss >> x) skaiciai.push_back(x);

    if (!iss.eof() || skaiciai.size() < 2) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (int paz : skaiciai) {
        if (paz < 1 || paz > 10) {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    s.vardas_ = vardas;
    s.pavarde_ = pavarde;
    s.egz_ = skaiciai.back();
    skaiciai.pop_back();
    s.paz_ = skaiciai;

    s.skaiciuotiGalutinius();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << std::left << std::setw(15) << s.vardas_
        << std::setw(20) << s.pavarde_
        << std::setw(15) << std::fixed << std::setprecision(2) << s.gal_vid_
        << std::setw(15) << s.gal_med_;
    return out;
}

void skaiciuoti(Studentas& a) {
    a.skaiciuotiGalutinius();
}

int atsitiktinis_pazymys() {
    return std::rand() % 10 + 1;
}

double galutinis_pagal(const Studentas& a, char vm) {
    if (vm == 'M' || vm == 'm') return a.getGalMed();
    return a.getGalVid();
}