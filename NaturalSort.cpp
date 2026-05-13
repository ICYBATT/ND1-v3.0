#include "NaturalSort.h"

static bool ar_skaitmuo(char c) {
    return c >= '0' && c <= '9';
}

static int skaicius_gale(const std::string& s) {
    int i = (int)s.size() - 1;
    if (i < 0) return -1;
    if (!ar_skaitmuo(s[i])) return -1;

    int daugiklis = 1;
    int sk = 0;

    while (i >= 0 && ar_skaitmuo(s[i])) {
        sk += (s[i] - '0') * daugiklis;
        daugiklis *= 10;
        i--;
    }
    return sk;
}

static std::string tekstas_be_galo_skaiciaus(const std::string& s) {
    int i = (int)s.size() - 1;
    if (i < 0) return s;
    if (!ar_skaitmuo(s[i])) return s;

    while (i >= 0 && ar_skaitmuo(s[i])) i--;
    return s.substr(0, i + 1);
}

bool palyginti_nat(const std::string& a, const std::string& b) {
    std::string ta = tekstas_be_galo_skaiciaus(a);
    std::string tb = tekstas_be_galo_skaiciaus(b);

    if (ta != tb) return ta < tb;

    int na = skaicius_gale(a);
    int nb = skaicius_gale(b);

    if (na != -1 && nb != -1) return na < nb;

    return a < b;
}

bool compareByName(const Studentas& a, const Studentas& b) {
    if (a.getVardas() != b.getVardas()) return palyginti_nat(a.getVardas(), b.getVardas());
    return palyginti_nat(a.getPavarde(), b.getPavarde());
}

bool compareBySurname(const Studentas& a, const Studentas& b) {
    if (a.getPavarde() != b.getPavarde()) return palyginti_nat(a.getPavarde(), b.getPavarde());
    return palyginti_nat(a.getVardas(), b.getVardas());
}

bool compareByAvg(const Studentas& a, const Studentas& b) {
    if (a.getGalVid() != b.getGalVid()) return a.getGalVid() < b.getGalVid();
    if (a.getPavarde() != b.getPavarde()) return palyginti_nat(a.getPavarde(), b.getPavarde());
    return palyginti_nat(a.getVardas(), b.getVardas());
}

bool compareByMed(const Studentas& a, const Studentas& b) {
    if (a.getGalMed() != b.getGalMed()) return a.getGalMed() < b.getGalMed();
    if (a.getPavarde() != b.getPavarde()) return palyginti_nat(a.getPavarde(), b.getPavarde());
    return palyginti_nat(a.getVardas(), b.getVardas());
}