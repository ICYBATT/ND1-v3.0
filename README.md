# ND1 v3.0

## Projekto aprasymas

Tai C++ programa, skirta studentu duomenu apdorojimui, rusiavimui, skirstymui ir spartos tyrimams.

Programa leidzia:

* ivesti studentus rankiniu budu
* generuoti pazymius
* pilnai generuoti studentu duomenis
* nuskaityti duomenis is failo
* apskaiciuoti galutini bala pagal vidurki arba mediana
* rikiuoti studentus
* suskirstyti studentus i vargsiukus ir kietiakus
* isvesti rezultatus i ekrana arba failus
* atlikti programos spartos tyrimus
* testuoti Studentas klase
* testuoti nuosava Vector konteineri

---

## v3.0 versijos tikslas

v3.0 versijoje sukurtas nuosavas sabloninis `Vector` konteineris, kuris funkcionalumu imituoja `std::vector`.

Pagrindinis tikslas buvo sukurti konteineri, kuris padengtu ne maziau kaip 80% `std::vector` funkcionalumo ir veiktu su ankstesne studentu apdorojimo programa.

---

## Realizuotas Vector funkcionalumas

Nuosavas `Vector` konteineris palaiko:

* tuscia konstruktoriu
* konstruktoriu su dydziu
* konstruktoriu su dydziu ir pradine reiksme
* initializer list konstruktoriu
* konstruktoriu is iteratoriu intervalo
* kopijavimo konstruktoriu
* perkelimo konstruktoriu
* kopijavimo priskyrimo operatoriu
* perkelimo priskyrimo operatoriu
* initializer list priskyrima
* destruktoriu
* `size`
* `capacity`
* `max_size`
* `empty`
* `reserve`
* `resize`
* `shrink_to_fit`
* `data`
* `operator[]`
* `at`
* `front`
* `back`
* `begin`
* `end`
* `cbegin`
* `cend`
* `rbegin`
* `rend`
* `crbegin`
* `crend`
* `clear`
* `push_back`
* `emplace_back`
* `pop_back`
* `assign`
* `insert`
* `erase`
* `swap`
* palyginimo operatorius `==`, `!=`, `<`, `<=`, `>`, `>=`

---

## Vector panaudojimas su Studentas klase

Nuosavas `Vector` konteineris testuotas ne tik su paprastais duomenu tipais, bet ir su `Studentas` objektais.

Buvo patikrinta, kad `Vector<Studentas>`:

* gali saugoti studentu objektus
* gali kopijuoti studentu konteineri
* gali iterpti studentus i konteineri
* gali pasalinti studentus is konteinerio
* gali naudoti `reserve` ir `resize`
* islaiko duomenis po konteinerio dydzio ir talpos keitimo

---

## Testavimas

Projektas testuotas naudojant Catch2 testavimo biblioteka.

Testai tikrina:

* `Vector` tuscia konstruktoriu
* `push_back` veikima
* `at` metodo ribu tikrinima
* `front` ir `back` metodus
* `reserve` metoda
* `resize` metoda
* `pop_back` ir `clear`
* kopijavimo konstruktoriu
* kopijavimo priskyrimo operatoriu
* `insert` metoda
* `erase` metoda
* palyginimo operatorius
* iteratoriu veikima
* `Vector<Studentas>` veikima

Testai paleidziami komandomis:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Gautas testu rezultatas:

```text
100% tests passed, 0 tests failed out of 19
```

---

## Spartos analize: std::vector ir Vector push_back

v3.0 versijoje atlikta `std::vector` ir nuosavo `Vector` konteinerio spartos analize.

Analizuojamas `push_back` metodo veikimas ir perskirstymu skaicius.

Spartos analize paleidziama komanda:

```bash
.\build\Debug\VectorBenchmark.exe
```

Gauti rezultatai:

```text
std::vector vs Vector push_back spartos analize

Elementai      std::vector (s)   Vector (s)     std perskirstymai   Vector perskirstymai
----------------------------------------------------------------------------------------
10000          0.000381          0.000121       24                  15
100000         0.003232          0.000975       30                  18
1000000        0.032728          0.008760       35                  21
10000000       0.329964          0.107437       41                  25
100000000      3.496746          0.976576       47                  28
```

Pagal gautus rezultatus matoma, kad nuosavas `Vector` konteineris `push_back` operacijoje veikia greitai ir turi maziau perskirstymu siame teste.

---

## Studentu apdorojimo spartos analize

Taip pat atlikta studentu apdorojimo spartos analize, kurioje lyginama:

* `std::vector<Studentas>`
* `Vector<Studentas>`

Analize paleidziama komanda:

```bash
.\build\Debug\StudentuBenchmark.exe
```

Gauti rezultatai:

```text
Studentu apdorojimo spartos analize
Lyginama std::vector<Studentas> ir Vector<Studentas>
Rikiavimas: pagal galutini vidurki
Strategija: 1

Failas                  std::vector (s)   Vector (s)        Studentai     Vargsiukai    Kietiakai
------------------------------------------------------------------------------------------------------
studentai100000.txt     6.542413          6.038738          100000        41330         58670
studentai1000000.txt    66.888411         63.802425         1000000       414570        585430
studentai10000000.txt   734.078845        708.021295        10000000      4150910       5849090
```

Pagal siuos rezultatus matoma, kad nuosavas `Vector<Studentas>` konteineris veikia panasiai kaip `std::vector<Studentas>` ir gali buti naudojamas studentu duomenu apdorojimui.

---

## Dokumentacija

Projektui sugeneruota Doxygen dokumentacija.

Dokumentacija generuojama komanda:

```bash
doxygen Doxyfile
```

Sugeneruota HTML dokumentacija yra aplanke:

```text
docs/html/index.html
```

Dokumentacijoje pateikiama informacija apie:

* `Vector` klase
* `Studentas` klase
* `Zmogus` abstrakcia klase
* klasiu metodus
* paveldimumo struktura

---

## Projekto paleidimas

Pirma karta projektas sukonfiguruojamas komanda:

```bash
cmake -S . -B build
```

Tada projektas sukompiliuojamas:

```bash
cmake --build build
```

Pagrindine programa paleidziama:

```bash
.\build\Debug\1UZD.exe
```

Testai paleidziami:

```bash
ctest --test-dir build --output-on-failure
```

Vector spartos analize paleidziama:

```bash
.\build\Debug\VectorBenchmark.exe
```

Studentu spartos analize paleidziama:

```bash
.\build\Debug\StudentuBenchmark.exe
```

---

## Naudoti failai

Pagrindiniai projekto failai:

* `main.cpp`
* `studentas.h`
* `studentas.cpp`
* `Zmogus.h`
* `Vector.h`
* `KonteineriuStrategijos.h`
* `FileIO.h`
* `FileIO.cpp`
* `Input.h`
* `Input.cpp`
* `Output.h`
* `Output.cpp`
* `Generator.h`
* `Generator.cpp`
* `Menu.h`
* `Menu.cpp`
* `NaturalSort.h`
* `NaturalSort.cpp`
* `Tyrimas.h`
* `Tyrimas.cpp`
* `VectorBenchmark.cpp`
* `StudentuBenchmark.cpp`
* `CMakeLists.txt`
* `Doxyfile`

Testu failai:

* `tests/VectorTests.cpp`
* `tests/StudentasVectorTests.cpp`

---

## Naudoti testavimo failai

Spartos tyrimams naudoti studentu duomenu failai:

* `studentai10000.txt`
* `studentai100000.txt`
* `studentai1000000.txt`
* `studentai10000000.txt`


---

## Kompiliavimo aplinka

Projektas kurtas ir testuotas su:

* Windows 11
* Visual Studio 2022
* MSVC kompiliatoriumi
* CMake
* C++17 standartu
* Catch2 testavimo biblioteka
* Doxygen dokumentacijos generavimui


---

## v3.0 rezultatas

v3.0 versijoje:

* sukurtas nuosavas `Vector` konteineris
* konteineris padengia didziaja dali `std::vector` funkcionalumo
* `Vector` veikia su `Studentas` klase
* parasyti Catch2 testai
* visi testai praeina sekmingai
* atlikta `std::vector` ir `Vector` spartos analize
* atlikta studentu apdorojimo su `Vector<Studentas>` spartos analize
* sugeneruota Doxygen dokumentacija
* projektas paruostas v3.0 release pateikimui
