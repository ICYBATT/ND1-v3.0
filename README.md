# ND1 – Studentų duomenų apdorojimo sistema (v1.2)

## Projekto aprašymas

Programa skirta studentų duomenų apdorojimui. Ji leidžia:

* įvesti studentų duomenis (rankiniu būdu, automatiškai, iš failo),
* apskaičiuoti galutinį balą pagal vidurkį arba medianą,
* rikiuoti studentus,
* suskirstyti studentus į vargšiukus ir kietiakus,
* išvesti rezultatus į ekraną arba į failus,
* atlikti programos spartos tyrimus.

Versijoje v1.2 papildomai realizuota:

* pilna Rule of Five implementacija,
* perdengti įvesties ir išvesties operatoriai,
* visų metodų testavimas.

---

## Rule of Five realizacija

Klasėje `Studentas` realizuoti šie metodai:

| Metodas          | Aprašymas                 |
| ---------------- | ------------------------- |
| Copy constructor | Sukuria objekto kopiją    |
| Move constructor | Perkelia objekto duomenis |
| Copy assignment  | Priskiria kopijuojant     |
| Move assignment  | Priskiria perkeliant      |
| Destructor       | Atlaisvina resursus       |

Papildomai:

* numatytasis konstruktorius
* parametrinis konstruktorius

---

## Perdengti operatoriai

### operator>>

Naudojamas studento įvedimui:

```cpp
std::cin >> studentas;
```

Įvedimo formatas:

```
Vardas Pavarde ND1 ND2 ND3 ... Egzaminas
```

---

### operator<<

Naudojamas studento išvedimui:

```cpp
std::cout << studentas;
```

Išvedami:

* vardas
* pavardė
* galutinis balas (vidurkis)
* galutinis balas (mediana)

---

## Testavimas

Sukurta funkcija:

```
vykdyti_v12_testus()
```

Tikrinami:

* visi konstruktoriai
* copy ir move operatoriai
* įvesties/išvesties operatoriai
* destruktorius

### Testų rezultatas

<img width="807" height="423" alt="image" src="https://github.com/user-attachments/assets/f790e51b-2618-4a75-99e0-0d5f3852acd5" />


---

## Duomenų įvedimas

Programa palaiko šiuos įvedimo būdus:

| Būdas              | Aprašymas                       |
| ------------------ | ------------------------------- |
| Rankinis           | Vartotojas įveda visus duomenis |
| Pusiau automatinis | Pažymiai generuojami            |
| Automatinis        | Viskas generuojama              |
| Iš failo           | Duomenys skaitomi iš failo      |

---

## Duomenų išvedimas

| Būdas    | Aprašymas                       |
| -------- | ------------------------------- |
| Į ekraną | Naudojamas `std::cout`          |
| Į failą  | Sukuriami failai su rezultatais |

Sukuriami failai:

* vargsiukai.txt
* kietiakai.txt

---

## Įvesties ir išvesties pavyzdys

### Įvedimas

<img width="581" height="337" alt="image" src="https://github.com/user-attachments/assets/da616504-13ee-41a2-9982-9ba89f5e470e" />


---

### Išvedimas

<img width="882" height="121" alt="image" src="https://github.com/user-attachments/assets/6ce6acd1-98db-4520-8787-fe0786d43e89" />


---

## Studentų skirstymas

Studentai skirstomi:

* < 5 → vargšiukai
* ≥ 5 → kietiakai

---

## Programos paleidimas

1. Paleisti programą
2. Pasirinkti:

```
(V)idurkis arba (M)ediana
```

3. Naudotis meniu

---

## Išvada

Programa atitinka visus užduoties reikalavimus:

* realizuota pilna Studentas klasė
* įgyvendinti visi Rule of Five metodai
* realizuoti įvesties/išvesties operatoriai
* visi metodai patikrinti testais
* programa veikia stabiliai
