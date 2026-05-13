#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <utility>

#include "studentas.h"
#include "Input.h"
#include "Menu.h"
#include "FileIO.h"
#include "Output.h"
#include "NaturalSort.h"
#include "Generator.h"
#include "Tyrimas.h"
#include "KonteineriuStrategijos.h"

using std::vector;
using std::list;
using std::deque;
using std::string;
using std::cout;
using std::endl;

struct TyrimoRezultatas {
    string failas;
    size_t studentu_kiekis = 0;
    int praleista = 0;
    double skaitymas = 0.0;
    double skirstymas = 0.0;
    double isvedimas = 0.0;
    double visas = 0.0;
};

static bool beveik_lygu(double a, double b) {
    return std::fabs(a - b) < 1e-6;
}

static void vykdyti_v12_testus() {
    using std::istringstream;
    using std::ostringstream;

    int is_viso = 0;
    int praejo = 0;

    auto testas = [&](bool salyga, const string& pavadinimas) {
        is_viso++;
        if (salyga) {
            praejo++;
            cout << "[OK] " << pavadinimas << "\n";
        }
        else {
            cout << "[FAIL] " << pavadinimas << "\n";
        }
    };

    cout << "\n========== V1.5 TESTAI ==========\n";

    cout << "\nAbstrakcios klases patikra:\n";
    cout << "Zmogus objekto sukurti negalima, nes klase turi pure virtual metoda.\n";
    cout << "Pavyzdys, kuris nesikompiliuotu: Zmogus z;\n";

    Studentas s1;
    testas(
        s1.getVardas().empty() &&
        s1.getPavarde().empty() &&
        s1.getPaz().empty() &&
        s1.getEgz() == 0 &&
        beveik_lygu(s1.getGalVid(), 0.0) &&
        beveik_lygu(s1.getGalMed(), 0.0),
        "Default konstruktorius"
    );

    Studentas s2("Jonas", "Jonaitis", { 8, 9, 10 }, 9);
    testas(
        s2.getVardas() == "Jonas" &&
        s2.getPavarde() == "Jonaitis" &&
        s2.getPaz().size() == 3 &&
        s2.getEgz() == 9,
        "Parametrinis konstruktorius"
    );

    Studentas s3(s2);
    testas(
        s3.getVardas() == s2.getVardas() &&
        s3.getPavarde() == s2.getPavarde() &&
        s3.getPaz() == s2.getPaz() &&
        s3.getEgz() == s2.getEgz() &&
        beveik_lygu(s3.getGalVid(), s2.getGalVid()) &&
        beveik_lygu(s3.getGalMed(), s2.getGalMed()),
        "Copy konstruktorius"
    );

    Studentas s4;
    s4 = s2;
    testas(
        s4.getVardas() == s2.getVardas() &&
        s4.getPavarde() == s2.getPavarde() &&
        s4.getPaz() == s2.getPaz() &&
        s4.getEgz() == s2.getEgz(),
        "Copy assignment"
    );

    Studentas laikinas1("Petras", "Petraitis", { 7, 8, 9 }, 10);
    Studentas s5(std::move(laikinas1));
    testas(
        s5.getVardas() == "Petras" &&
        s5.getPavarde() == "Petraitis" &&
        s5.getPaz().size() == 3 &&
        s5.getEgz() == 10,
        "Move konstruktorius"
    );

    Studentas laikinas2("Ona", "Onaite", { 6, 7, 8 }, 9);
    Studentas s6;
    s6 = std::move(laikinas2);
    testas(
        s6.getVardas() == "Ona" &&
        s6.getPavarde() == "Onaite" &&
        s6.getPaz().size() == 3 &&
        s6.getEgz() == 9,
        "Move assignment"
    );

    ostringstream out;
    out << s2;
    testas(!out.str().empty(), "operator<<");

    istringstream in("Mantas Mantaitis 8 9 10 9\n");
    Studentas s7;
    in >> s7;
    testas(
        s7.getVardas() == "Mantas" &&
        s7.getPavarde() == "Mantaitis" &&
        s7.getPaz().size() == 3 &&
        s7.getEgz() == 9,
        "operator>>"
    );

    Zmogus* z = new Studentas("Test", "Studentas", { 10, 9, 8 }, 10);
    testas(
        z->getVardas() == "Test" &&
        z->getPavarde() == "Studentas",
        "Studentas naudojamas per Zmogus rodykle"
    );
    delete z;

    {
        Studentas scope_test("Scope", "Test", { 10, 10, 10 }, 10);
        testas(scope_test.getVardas() == "Scope", "Objektas destruktoriaus testui sukurtas");
    }

    testas(true, "Destruktorius pasiektas iseinant is scope");

    cout << "\nPraejo " << praejo << " is " << is_viso << " testu.\n";
    cout << "=================================\n";
}

static void rikiuoti(vector<Studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Grupe tuscia - nera ka rikiuoti.\n";
        return;
    }

    cout << "\nRikiuoti studentus pagal:\n";
    cout << "1 - Varda\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutini (Vid.)\n";
    cout << "4 - Galutini (Med.)\n";

    int r = ivesti_skaiciu("Pasirinkimas: ", 1, 4);

    if (r == 1) std::sort(grupe.begin(), grupe.end(), compareByName);
    else if (r == 2) std::sort(grupe.begin(), grupe.end(), compareBySurname);
    else if (r == 3) std::sort(grupe.begin(), grupe.end(), compareByAvg);
    else std::sort(grupe.begin(), grupe.end(), compareByMed);
}

static void skirstyti_studentus(
    const vector<Studentas>& visi,
    vector<Studentas>& vargsiukai,
    vector<Studentas>& kietiakai,
    char vm
) {
    vargsiukai.clear();
    kietiakai.clear();

    for (const auto& s : visi) {
        if (galutinis_pagal(s, vm) < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}

static void issaugoti_suskirstytus(
    const vector<Studentas>& vargsiukai,
    const vector<Studentas>& kietiakai,
    char vm
) {
    isvesti_i_faila(vargsiukai, "vargsiukai.txt", vm);
    isvesti_i_faila(kietiakai, "kietiakai.txt", vm);

    cout << "Sukurti failai:\n";
    cout << " - vargsiukai.txt\n";
    cout << " - kietiakai.txt\n";
}

static TyrimoRezultatas atlikti_tyrima(const string& failas, char vm) {
    TyrimoRezultatas rez;
    rez.failas = failas;

    vector<Studentas> visi;
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakai;

    auto visas_start = std::chrono::high_resolution_clock::now();

    auto t1 = std::chrono::high_resolution_clock::now();
    bool ok = nuskaityti_is_failo(failas, visi, rez.praleista);
    auto t2 = std::chrono::high_resolution_clock::now();

    if (!ok) return rez;

    auto t3 = std::chrono::high_resolution_clock::now();
    skirstyti_studentus(visi, vargsiukai, kietiakai, vm);
    auto t4 = std::chrono::high_resolution_clock::now();

    auto t5 = std::chrono::high_resolution_clock::now();
    string prefix = failas;
    size_t taskas = prefix.find_last_of('.');
    if (taskas != string::npos) prefix = prefix.substr(0, taskas);

    isvesti_i_faila(vargsiukai, prefix + "_vargsiukai.txt", vm);
    isvesti_i_faila(kietiakai, prefix + "_kietiakai.txt", vm);
    auto t6 = std::chrono::high_resolution_clock::now();

    auto visas_end = std::chrono::high_resolution_clock::now();

    rez.studentu_kiekis = visi.size();
    rez.skaitymas = std::chrono::duration<double>(t2 - t1).count();
    rez.skirstymas = std::chrono::duration<double>(t4 - t3).count();
    rez.isvedimas = std::chrono::duration<double>(t6 - t5).count();
    rez.visas = std::chrono::duration<double>(visas_end - visas_start).count();

    return rez;
}

static void spausdinti_tyrimo_rezultata(const TyrimoRezultatas& r) {
    cout << "\nFailas: " << r.failas << "\n";
    cout << "Studentu kiekis: " << r.studentu_kiekis << "\n";
    cout << "Praleista eiluciu: " << r.praleista << "\n";
    cout << std::fixed << std::setprecision(6);
    cout << "Nuskaitymas: " << r.skaitymas << " s\n";
    cout << "Skirstymas:  " << r.skirstymas << " s\n";
    cout << "Isvedimas:   " << r.isvedimas << " s\n";
    cout << "Visas laikas:" << r.visas << " s\n";
}

static void spausdinti_lentele(const vector<TyrimoRezultatas>& visi) {
    cout << "\n================= TYRIMO LENTELE =================\n";
    cout << std::left
         << std::setw(22) << "Failas"
         << std::setw(12) << "Studentai"
         << std::setw(14) << "Skaitymas"
         << std::setw(14) << "Skirstymas"
         << std::setw(14) << "Isvedimas"
         << std::setw(14) << "Viso"
         << "\n";

    cout << string(90, '-') << "\n";

    cout << std::fixed << std::setprecision(6);

    for (const auto& r : visi) {
        cout << std::left
             << std::setw(22) << r.failas
             << std::setw(12) << r.studentu_kiekis
             << std::setw(14) << r.skaitymas
             << std::setw(14) << r.skirstymas
             << std::setw(14) << r.isvedimas
             << std::setw(14) << r.visas
             << "\n";
    }
}

static int pasirinkti_rikiavimo_buda_v1() {
    cout << "\nRikiuoti studentus pagal:\n";
    cout << "1 - Varda\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutini (Vid.)\n";
    cout << "4 - Galutini (Med.)\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 4);
}

static int pasirinkti_konteineri_v1() {
    cout << "\nPasirinkite konteinerio tipa:\n";
    cout << "1 - vector\n";
    cout << "2 - list\n";
    cout << "3 - deque\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 3);
}

static int pasirinkti_strategija_v1() {
    cout << "\nPasirinkite skirstymo strategija:\n";
    cout << "1 - du nauji konteineriai (vargsiukai ir kietiakai)\n";
    cout << "2 - vienas naujas konteineris (vargsiukai), salinant is bendro\n";
    cout << "3 - optimizuota strategija su partition\n";
    return ivesti_skaiciu("Pasirinkimas: ", 1, 3);
}

template <typename Container>
static TyrimoRezultatasV1 atlikti_v1_tyrima_sablonas(
    const string& failas,
    char vm,
    int konteinerio_tipas,
    int strategija,
    int rikiavimo_budas
) {
    TyrimoRezultatasV1 rez;
    rez.failas = failas;
    rez.konteineris = konteinerio_pavadinimas(konteinerio_tipas);
    rez.strategija = strategija;

    Container studentai;
    Container vargsiukai;
    Container kietiakai;

    auto visas_start = std::chrono::high_resolution_clock::now();

    auto t1 = std::chrono::high_resolution_clock::now();
    bool ok = nuskaityti_i_konteineri(failas, studentai, rez.praleista);
    auto t2 = std::chrono::high_resolution_clock::now();

    if (!ok) {
        return rez;
    }

    rez.studentu_kiekis = studentai.size();

    auto t3 = std::chrono::high_resolution_clock::now();
    rikiuoti_konteineri(studentai, rikiavimo_budas);
    auto t4 = std::chrono::high_resolution_clock::now();

    auto t5 = std::chrono::high_resolution_clock::now();

    if (strategija == 1) {
        skirstyti_strategija1(studentai, vargsiukai, kietiakai, vm);
    }
    else if (strategija == 2) {
        skirstyti_strategija2(studentai, vargsiukai, vm);
        kietiakai = studentai;
    }
    else {
        skirstyti_strategija3(studentai, vargsiukai, kietiakai, vm);
    }

    auto t6 = std::chrono::high_resolution_clock::now();
    auto visas_end = std::chrono::high_resolution_clock::now();

    rez.nuskaitymas = std::chrono::duration<double>(t2 - t1).count();
    rez.rikiavimas = std::chrono::duration<double>(t4 - t3).count();
    rez.skirstymas = std::chrono::duration<double>(t6 - t5).count();
    rez.visas = std::chrono::duration<double>(visas_end - visas_start).count();

    cout << "\nVargsiuku: " << vargsiukai.size() << "\n";
    cout << "Kietiaku: " << kietiakai.size() << "\n";

    return rez;
}

static TyrimoRezultatasV1 atlikti_v1_tyrima(
    const string& failas,
    char vm,
    int konteinerio_tipas,
    int strategija,
    int rikiavimo_budas
) {
    const int KARTAI = 5;

    double sum_nuskaitymas = 0;
    double sum_rikiavimas = 0;
    double sum_skirstymas = 0;
    double sum_visas = 0;

    TyrimoRezultatasV1 paskutinis;

    for (int i = 0; i < KARTAI; i++) {

        TyrimoRezultatasV1 r;

        if (konteinerio_tipas == KONTEINERIS_VECTOR) {
            r = atlikti_v1_tyrima_sablonas<vector<Studentas>>(failas, vm, konteinerio_tipas, strategija, rikiavimo_budas);
        }
        else if (konteinerio_tipas == KONTEINERIS_LIST) {
            r = atlikti_v1_tyrima_sablonas<list<Studentas>>(failas, vm, konteinerio_tipas, strategija, rikiavimo_budas);
        }
        else {
            r = atlikti_v1_tyrima_sablonas<deque<Studentas>>(failas, vm, konteinerio_tipas, strategija, rikiavimo_budas);
        }

        sum_nuskaitymas += r.nuskaitymas;
        sum_rikiavimas += r.rikiavimas;
        sum_skirstymas += r.skirstymas;
        sum_visas += r.visas;

        paskutinis = r;
    }

    paskutinis.nuskaitymas = sum_nuskaitymas / KARTAI;
    paskutinis.rikiavimas = sum_rikiavimas / KARTAI;
    paskutinis.skirstymas = sum_skirstymas / KARTAI;
    paskutinis.visas = sum_visas / KARTAI;

    return paskutinis;
}

static void vykdyti_v1_vieno_failo_tyrima(char vm) {
    string fname;
    cout << "Iveskite failo pavadinima tyrimui: ";
    std::cin >> fname;

    int konteineris = pasirinkti_konteineri_v1();
    int strategija = pasirinkti_strategija_v1();
    int rikiavimas = pasirinkti_rikiavimo_buda_v1();

    TyrimoRezultatasV1 r = atlikti_v1_tyrima(fname, vm, konteineris, strategija, rikiavimas);
    spausdinti_v1_rezultata(r);
}

static void vykdyti_v1_visu_failu_tyrima(char vm) {
    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt",
        "studentai10000000.txt"
    };

    int konteineris = pasirinkti_konteineri_v1();
    int strategija = pasirinkti_strategija_v1();
    int rikiavimas = pasirinkti_rikiavimo_buda_v1();

    vector<TyrimoRezultatasV1> rezultatai;

    for (const auto& f : failai) {
        cout << "\nVykdomas V1.0 tyrimas su: " << f << "\n";
        TyrimoRezultatasV1 r = atlikti_v1_tyrima(f, vm, konteineris, strategija, rikiavimas);
        rezultatai.push_back(r);
        spausdinti_v1_rezultata(r);
    }

    spausdinti_v1_lentele(rezultatai);
}

int main() {
    std::srand((unsigned)std::time(nullptr));

    try {
        char pasirinktasVM = ivesti_vm();

        vector<Studentas> grupe;

        while (true) {
            int p = meniu();
            if (p == 13) break;

            if (p == 1) {
                int m = ivesti_kieki("Kiek studentu? ");
                int n = ivesti_kieki("Kiek pazymiu kiekvienam? ");

                for (int i = 0; i < m; i++) {
                    Studentas A;
                    string vardas, pavarde;

                    cout << "Ivesk varda ir pavarde: ";
                    std::cin >> vardas >> pavarde;

                    A.setVardas(vardas);
                    A.setPavarde(pavarde);

                    for (int j = 0; j < n; j++) {
                        int x = ivesti_skaiciu("Pazymys (1-10): ", 1, 10);
                        A.addPazymys(x);
                    }

                    A.setEgz(ivesti_skaiciu("Egzamino pazymys (1-10): ", 1, 10));
                    skaiciuoti(A);
                    grupe.push_back(A);
                }

                cout << "Uzbaigta. Is viso studentu: " << grupe.size() << endl;
            }

            else if (p == 2) {
                int m = ivesti_kieki("Kiek studentu? ");
                int n = ivesti_kieki("Kiek pazymiu generuoti kiekvienam? ");

                for (int i = 0; i < m; i++) {
                    Studentas A;
                    string vardas, pavarde;

                    cout << "Ivesk varda ir pavarde: ";
                    std::cin >> vardas >> pavarde;

                    A.setVardas(vardas);
                    A.setPavarde(pavarde);

                    for (int j = 0; j < n; j++) {
                        A.addPazymys(atsitiktinis_pazymys());
                    }

                    A.setEgz(atsitiktinis_pazymys());
                    skaiciuoti(A);
                    grupe.push_back(A);
                }

                cout << "Sugeneruoti ir prideti " << m << " studentai.\n";
                cout << "Sugeneruota studentu: " << grupe.size() << endl;
            }

            else if (p == 3) {
                int m = std::rand() % 5 + 3;
                int n = std::rand() % 5 + 3;

                vector<string> vardai = { "Jonas", "Ona", "Ieva", "Mantas", "Egle", "Tomas", "Ruta", "Paulius", "Greta", "Lukas" };
                vector<string> pavardes = { "Kazlauskas", "Petrauskas", "Jankauskas", "Vaitkus", "Zukauskas",
                                           "Stankevicius", "Pocius", "Noreika", "Mikulenas", "Sabonis" };

                for (int i = 0; i < m; i++) {
                    Studentas A;
                    A.setVardas(vardai[std::rand() % (int)vardai.size()]);
                    A.setPavarde(pavardes[std::rand() % (int)pavardes.size()]);

                    for (int j = 0; j < n; j++) {
                        A.addPazymys(atsitiktinis_pazymys());
                    }

                    A.setEgz(atsitiktinis_pazymys());
                    skaiciuoti(A);
                    grupe.push_back(A);
                }

                cout << "Programa sugeneravo " << m << " studentu ir po " << n << " ND kiekvienam.\n";
                cout << "Sugeneruota studentu: " << grupe.size() << endl;
            }

            else if (p == 4) {
                cout << "Iveskite failo pavadinima: ";
                string fname;
                std::cin >> fname;

                int praleista = 0;

                auto start = std::chrono::high_resolution_clock::now();
                bool ok = nuskaityti_is_failo(fname, grupe, praleista);
                auto end = std::chrono::high_resolution_clock::now();

                if (!ok) {
                    cout << "Skaitymas nepavyko.\n";
                }
                else {
                    std::chrono::duration<double> diff = end - start;
                    cout << "Studentu: " << grupe.size() << endl;
                    cout << "Laikas: " << diff.count() << " s\n";
                    if (praleista > 0) cout << "Praleista eiluciu: " << praleista << endl;

                    cout << "\nAr norite dabar rikiuoti ir isvesti?\n";
                    cout << "1 - Taip\n";
                    cout << "2 - Ne\n";

                    int ats = ivesti_skaiciu("Pasirinkimas: ", 1, 2);

                    if (ats == 1) {
                        rikiuoti(grupe);
                        isvedimo_pasirinkimas(grupe, pasirinktasVM);
                    }
                }
            }

            else if (p == 5) {
                if (grupe.empty()) {
                    cout << "Grupe tuscia.\n";
                }
                else {
                    vector<Studentas> vargsiukai;
                    vector<Studentas> kietiakai;

                    skirstyti_studentus(grupe, vargsiukai, kietiakai, pasirinktasVM);

                    cout << "Vargsiuku: " << vargsiukai.size() << "\n";
                    cout << "Kietiaku: " << kietiakai.size() << "\n";

                    issaugoti_suskirstytus(vargsiukai, kietiakai, pasirinktasVM);
                }
            }

            else if (p == 6) {
                if (grupe.empty()) {
                    cout << "Grupe tuscia.\n";
                }
                else {
                    rikiuoti(grupe);
                    isvedimo_pasirinkimas(grupe, pasirinktasVM);
                }
            }

            else if (p == 7) {
                generuoti_visus_testinius_failus();
                cout << "Sugeneruoti failai:\n";
                cout << " - studentai1000.txt\n";
                cout << " - studentai10000.txt\n";
                cout << " - studentai100000.txt\n";
                cout << " - studentai1000000.txt\n";
                cout << " - studentai10000000.txt\n";
            }

            else if (p == 8) {
                string fname;
                cout << "Iveskite failo pavadinima tyrimui: ";
                std::cin >> fname;

                TyrimoRezultatas r = atlikti_tyrima(fname, pasirinktasVM);
                spausdinti_tyrimo_rezultata(r);
            }

            else if (p == 9) {
                vector<string> failai = {
                    "studentai1000.txt",
                    "studentai10000.txt",
                    "studentai100000.txt",
                    "studentai1000000.txt",
                    "studentai10000000.txt"
                };

                vector<TyrimoRezultatas> rezultatai;

                for (const auto& f : failai) {
                    cout << "\nVykdomas tyrimas su: " << f << "\n";
                    TyrimoRezultatas r = atlikti_tyrima(f, pasirinktasVM);
                    rezultatai.push_back(r);
                    spausdinti_tyrimo_rezultata(r);
                }

                spausdinti_lentele(rezultatai);
            }

            else if (p == 10) {
                vykdyti_v1_vieno_failo_tyrima(pasirinktasVM);
            }

            else if (p == 11) {
                vykdyti_v1_visu_failu_tyrima(pasirinktasVM);
            }

            else if (p == 12) {
                vykdyti_v12_testus();
            }
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "Ivyko kritine klaida: " << e.what() << "\n";
        return 1;
    }
}