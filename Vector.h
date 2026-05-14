#pragma once

/**
 * @file Vector.h
 * @brief Nuosavo sabloninio Vector konteinerio realizacija.
 *
 * Siame faile aprasyta nuosava Vector klase, kuri imituoja pagrindini
 * std::vector funkcionaluma. Konteineris palaiko dinamini masyva,
 * iteratorius, elementu pridejima, salinima, kopijavima, perkelima,
 * capacity valdyma ir palyginimo operatorius.
 */

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <limits>

/**
 * @class Vector
 * @brief Sabloninis dinaminio masyvo konteineris.
 *
 * Vector klase saugo elementus vientisoje dinamiskai paskirtoje atmintyje.
 * Kai konteineryje nebelieka vietos naujam elementui, talpa yra padidinama.
 * Klase realizuoja didele dali std::vector funkcionalumo.
 *
 * @tparam T Konteineryje saugomu elementu tipas.
 */
template <typename T>
class Vector {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    T* duomenys_;
    size_type dydis_;
    size_type talpa_;

    /**
     * @brief Perkelia elementus i nauja atminties bloka.
     *
     * Sukuriamas naujas masyvas su nurodyta talpa, i ji perkeliami seni
     * elementai, o sena atmintis atlaisvinama.
     *
     * @param nauja_talpa Nauja konteinerio talpa.
     */
    void perkelti_i_nauja_talpa(size_type nauja_talpa) {
        T* nauji_duomenys = nullptr;

        if (nauja_talpa > 0) {
            nauji_duomenys = new T[nauja_talpa];

            size_type kiek_kopijuoti = (dydis_ < nauja_talpa) ? dydis_ : nauja_talpa;
            for (size_type i = 0; i < kiek_kopijuoti; ++i) {
                nauji_duomenys[i] = std::move(duomenys_[i]);
            }

            dydis_ = kiek_kopijuoti;
        } else {
            dydis_ = 0;
        }

        delete[] duomenys_;
        duomenys_ = nauji_duomenys;
        talpa_ = nauja_talpa;
    }

public:
    /**
     * @brief Sukuria tuscia Vector konteineri.
     */
    Vector()
        : duomenys_(nullptr), dydis_(0), talpa_(0) {}

    /**
     * @brief Sukuria Vector konteineri su nurodytu elementu kiekiu.
     *
     * @param kiekis Elementu kiekis.
     */
    explicit Vector(size_type kiekis)
        : duomenys_(nullptr), dydis_(kiekis), talpa_(kiekis) {
        if (kiekis > 0) {
            duomenys_ = new T[kiekis];
        }
    }

    /**
     * @brief Sukuria Vector konteineri ir uzpildo ji nurodyta reiksme.
     *
     * @param kiekis Elementu kiekis.
     * @param reiksme Reiksme, kuria uzpildomas konteineris.
     */
    Vector(size_type kiekis, const T& reiksme)
        : duomenys_(nullptr), dydis_(kiekis), talpa_(kiekis) {
        if (kiekis > 0) {
            duomenys_ = new T[kiekis];
            for (size_type i = 0; i < kiekis; ++i) {
                duomenys_[i] = reiksme;
            }
        }
    }

    /**
     * @brief Sukuria Vector konteineri is initializer_list saraso.
     *
     * @param sarasas Pradinis elementu sarasas.
     */
    Vector(std::initializer_list<T> sarasas)
        : duomenys_(nullptr), dydis_(sarasas.size()), talpa_(sarasas.size()) {
        if (talpa_ > 0) {
            duomenys_ = new T[talpa_];
            size_type i = 0;
            for (const auto& elementas : sarasas) {
                duomenys_[i++] = elementas;
            }
        }
    }

    /**
     * @brief Sukuria Vector konteineri is iteratoriu intervalo.
     *
     * @param pirmas Pirmas intervalo iteratorius.
     * @param paskutinis Iteratorius uz paskutinio intervalo elemento.
     */
    template <typename InputIterator>
    Vector(InputIterator pirmas, InputIterator paskutinis)
        : duomenys_(nullptr), dydis_(0), talpa_(0) {
        for (InputIterator it = pirmas; it != paskutinis; ++it) {
            push_back(*it);
        }
    }

    /**
     * @brief Kopijavimo konstruktorius.
     *
     * Sukuria nepriklausoma kito Vector objekto kopija.
     *
     * @param kitas Kopijuojamas Vector objektas.
     */
    Vector(const Vector& kitas)
        : duomenys_(nullptr), dydis_(kitas.dydis_), talpa_(kitas.talpa_) {
        if (talpa_ > 0) {
            duomenys_ = new T[talpa_];
            for (size_type i = 0; i < dydis_; ++i) {
                duomenys_[i] = kitas.duomenys_[i];
            }
        }
    }

    /**
     * @brief Perkelimo konstruktorius.
     *
     * Perima kito Vector objekto atminties valdyma.
     *
     * @param kitas Perkeliamas Vector objektas.
     */
    Vector(Vector&& kitas) noexcept
        : duomenys_(kitas.duomenys_), dydis_(kitas.dydis_), talpa_(kitas.talpa_) {
        kitas.duomenys_ = nullptr;
        kitas.dydis_ = 0;
        kitas.talpa_ = 0;
    }

    /**
     * @brief Kopijavimo priskyrimo operatorius.
     *
     * @param kitas Kopijuojamas Vector objektas.
     * @return Nuoroda i si Vector objekta.
     */
    Vector& operator=(const Vector& kitas) {
        if (this != &kitas) {
            T* nauji_duomenys = nullptr;

            if (kitas.talpa_ > 0) {
                nauji_duomenys = new T[kitas.talpa_];
                for (size_type i = 0; i < kitas.dydis_; ++i) {
                    nauji_duomenys[i] = kitas.duomenys_[i];
                }
            }

            delete[] duomenys_;
            duomenys_ = nauji_duomenys;
            dydis_ = kitas.dydis_;
            talpa_ = kitas.talpa_;
        }

        return *this;
    }

    /**
     * @brief Perkelimo priskyrimo operatorius.
     *
     * @param kitas Perkeliamas Vector objektas.
     * @return Nuoroda i si Vector objekta.
     */
    Vector& operator=(Vector&& kitas) noexcept {
        if (this != &kitas) {
            delete[] duomenys_;

            duomenys_ = kitas.duomenys_;
            dydis_ = kitas.dydis_;
            talpa_ = kitas.talpa_;

            kitas.duomenys_ = nullptr;
            kitas.dydis_ = 0;
            kitas.talpa_ = 0;
        }

        return *this;
    }

    /**
     * @brief Priskiria initializer_list sarasa Vector konteineriui.
     *
     * @param sarasas Naujas elementu sarasas.
     * @return Nuoroda i si Vector objekta.
     */
    Vector& operator=(std::initializer_list<T> sarasas) {
        Vector laikinas(sarasas);
        swap(laikinas);
        return *this;
    }

    /**
     * @brief Atlaisvina Vector naudojama atminti.
     */
    ~Vector() {
        delete[] duomenys_;
    }

    /**
     * @brief Sukeicia dvieju Vector objektu duomenis.
     *
     * @param kitas Kitas Vector objektas.
     */
    void swap(Vector& kitas) noexcept {
        std::swap(duomenys_, kitas.duomenys_);
        std::swap(dydis_, kitas.dydis_);
        std::swap(talpa_, kitas.talpa_);
    }

    /**
     * @brief Grazina konteinerio elementu kieki.
     *
     * @return Elementu skaicius.
     */
    size_type size() const {
        return dydis_;
    }

    /**
     * @brief Grazina konteinerio talpa.
     *
     * @return Talpos reiksme.
     */
    size_type capacity() const {
        return talpa_;
    }

    /**
     * @brief Grazina maksimalu galima konteinerio dydi.
     *
     * @return Maksimalus dydis.
     */
    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    /**
     * @brief Patikrina, ar konteineris tuscias.
     *
     * @return true, jeigu konteineris tuscias, kitu atveju false.
     */
    bool empty() const {
        return dydis_ == 0;
    }

    /**
     * @brief Padidina konteinerio talpa.
     *
     * Jeigu nauja talpa yra didesne uz dabartine, paskiriama nauja atmintis
     * ir esami elementai perkeliami i nauja vieta.
     *
     * @param nauja_talpa Nauja konteinerio talpa.
     */
    void reserve(size_type nauja_talpa) {
        if (nauja_talpa > max_size()) {
            throw std::length_error("Vector reserve virsija max_size");
        }

        if (nauja_talpa > talpa_) {
            perkelti_i_nauja_talpa(nauja_talpa);
        }
    }

    /**
     * @brief Pakeicia konteinerio dydi.
     *
     * Jeigu naujas dydis yra didesnis, sukuriami papildomi numatytos
     * reiksmes elementai. Jeigu mazesnis, konteinerio dydis sumazinamas.
     *
     * @param naujas_dydis Naujas konteinerio dydis.
     */
    void resize(size_type naujas_dydis) {
        if (naujas_dydis > talpa_) {
            reserve(naujas_dydis);
        }

        if (naujas_dydis > dydis_) {
            for (size_type i = dydis_; i < naujas_dydis; ++i) {
                duomenys_[i] = T();
            }
        }

        dydis_ = naujas_dydis;
    }

    /**
     * @brief Pakeicia konteinerio dydi naudojant nurodyta reiksme.
     *
     * Jeigu konteineris padidinamas, nauji elementai uzpildomi perduota
     * reiksme.
     *
     * @param naujas_dydis Naujas konteinerio dydis.
     * @param reiksme Reiksme, kuria uzpildomi nauji elementai.
     */
    void resize(size_type naujas_dydis, const T& reiksme) {
        if (naujas_dydis > talpa_) {
            reserve(naujas_dydis);
        }

        if (naujas_dydis > dydis_) {
            for (size_type i = dydis_; i < naujas_dydis; ++i) {
                duomenys_[i] = reiksme;
            }
        }

        dydis_ = naujas_dydis;
    }

    /**
     * @brief Sumazina talpa iki dabartinio dydzio.
     */
    void shrink_to_fit() {
        if (dydis_ < talpa_) {
            perkelti_i_nauja_talpa(dydis_);
        }
    }

    /**
     * @brief Grazina rodykle i vidinius duomenis.
     *
     * @return Rodykle i pirma elementa.
     */
    pointer data() {
        return duomenys_;
    }

    /**
     * @brief Grazina konstantine rodykle i vidinius duomenis.
     *
     * @return Konstantine rodykle i pirma elementa.
     */
    const_pointer data() const {
        return duomenys_;
    }

    /**
     * @brief Grazina elementa pagal indeksa be ribu tikrinimo.
     *
     * @param indeksas Elemento indeksas.
     * @return Nuoroda i elementa.
     */
    reference operator[](size_type indeksas) {
        return duomenys_[indeksas];
    }

    /**
     * @brief Grazina konstantini elementa pagal indeksa be ribu tikrinimo.
     *
     * @param indeksas Elemento indeksas.
     * @return Konstantine nuoroda i elementa.
     */
    const_reference operator[](size_type indeksas) const {
        return duomenys_[indeksas];
    }

    /**
     * @brief Grazina elementa pagal indeksa su ribu tikrinimu.
     *
     * @param indeksas Elemento indeksas.
     * @return Nuoroda i elementa.
     * @throws std::out_of_range Jeigu indeksas yra uz konteinerio ribu.
     */
    reference at(size_type indeksas) {
        if (indeksas >= dydis_) {
            throw std::out_of_range("Vector indeksas uz ribu");
        }
        return duomenys_[indeksas];
    }

    /**
     * @brief Grazina konstantini elementa pagal indeksa su ribu tikrinimu.
     *
     * @param indeksas Elemento indeksas.
     * @return Konstantine nuoroda i elementa.
     * @throws std::out_of_range Jeigu indeksas yra uz konteinerio ribu.
     */
    const_reference at(size_type indeksas) const {
        if (indeksas >= dydis_) {
            throw std::out_of_range("Vector indeksas uz ribu");
        }
        return duomenys_[indeksas];
    }

    /**
     * @brief Grazina pirma konteinerio elementa.
     *
     * @return Nuoroda i pirma elementa.
     */
    reference front() {
        return duomenys_[0];
    }

    /**
     * @brief Grazina pirma konteinerio elementa konstantiniam objektui.
     *
     * @return Konstantine nuoroda i pirma elementa.
     */
    const_reference front() const {
        return duomenys_[0];
    }

    /**
     * @brief Grazina paskutini konteinerio elementa.
     *
     * @return Nuoroda i paskutini elementa.
     */
    reference back() {
        return duomenys_[dydis_ - 1];
    }

    /**
     * @brief Grazina paskutini konteinerio elementa konstantiniam objektui.
     *
     * @return Konstantine nuoroda i paskutini elementa.
     */
    const_reference back() const {
        return duomenys_[dydis_ - 1];
    }

    /**
     * @brief Grazina iteratoriu i pirma elementa.
     *
     * @return Iteratorius i pradzia.
     */
    iterator begin() {
        return duomenys_;
    }

    /**
     * @brief Grazina konstantini iteratoriu i pirma elementa.
     *
     * @return Konstantinis iteratorius i pradzia.
     */
    const_iterator begin() const {
        return duomenys_;
    }

    /**
     * @brief Grazina konstantini iteratoriu i pirma elementa.
     *
     * @return Konstantinis iteratorius i pradzia.
     */
    const_iterator cbegin() const {
        return duomenys_;
    }

    /**
     * @brief Grazina iteratoriu uz paskutinio elemento.
     *
     * @return Iteratorius i pabaiga.
     */
    iterator end() {
        return duomenys_ + dydis_;
    }

    /**
     * @brief Grazina konstantini iteratoriu uz paskutinio elemento.
     *
     * @return Konstantinis iteratorius i pabaiga.
     */
    const_iterator end() const {
        return duomenys_ + dydis_;
    }

    /**
     * @brief Grazina konstantini iteratoriu uz paskutinio elemento.
     *
     * @return Konstantinis iteratorius i pabaiga.
     */
    const_iterator cend() const {
        return duomenys_ + dydis_;
    }

    /**
     * @brief Grazina atbulini iteratoriu i paskutini elementa.
     *
     * @return Atbulinis iteratorius i pradzia nuo galo.
     */
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    /**
     * @brief Grazina konstantini atbulini iteratoriu i paskutini elementa.
     *
     * @return Konstantinis atbulinis iteratorius.
     */
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Grazina konstantini atbulini iteratoriu i paskutini elementa.
     *
     * @return Konstantinis atbulinis iteratorius.
     */
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }

    /**
     * @brief Grazina atbulini iteratoriu uz pirmo elemento.
     *
     * @return Atbulinis iteratorius i pabaiga.
     */
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    /**
     * @brief Grazina konstantini atbulini iteratoriu uz pirmo elemento.
     *
     * @return Konstantinis atbulinis iteratorius i pabaiga.
     */
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Grazina konstantini atbulini iteratoriu uz pirmo elemento.
     *
     * @return Konstantinis atbulinis iteratorius i pabaiga.
     */
    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }

    /**
     * @brief Isvalo konteineri.
     *
     * Po isvalymo size() tampa 0, bet capacity() nesikeicia.
     */
    void clear() {
        dydis_ = 0;
    }

    /**
     * @brief Prideda elementa i konteinerio pabaiga.
     *
     * Jeigu konteinerio dydis pasiekia talpa, pries pridedant elementa
     * atliekamas atminties perskirstymas.
     *
     * @param reiksme Pridedama elemento reiksme.
     */
    void push_back(const T& reiksme) {
        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        duomenys_[dydis_] = reiksme;
        ++dydis_;
    }

    /**
     * @brief Prideda perkeliamą elementa i konteinerio pabaiga.
     *
     * Naudojama move semantika, todel objektas gali buti perkeltas
     * efektyviau negu kopijuojant.
     *
     * @param reiksme Perkeliama elemento reiksme.
     */
    void push_back(T&& reiksme) {
        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        duomenys_[dydis_] = std::move(reiksme);
        ++dydis_;
    }

    /**
     * @brief Sukuria elementa konteinerio pabaigoje.
     *
     * Elementas sukuriamas naudojant perduotus konstruktoriaus argumentus.
     *
     * @param args Argumentai elemento konstruktoriui.
     * @return Nuoroda i naujai prideta elementa.
     */
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        duomenys_[dydis_] = T(std::forward<Args>(args)...);
        ++dydis_;

        return back();
    }

    /**
     * @brief Pasalina paskutini konteinerio elementa.
     */
    void pop_back() {
        if (dydis_ > 0) {
            --dydis_;
        }
    }

    /**
     * @brief Priskiria konteineriui nurodyta kieki vienodu reiksmiu.
     *
     * @param kiekis Elementu kiekis.
     * @param reiksme Reiksme, kuria uzpildomas konteineris.
     */
    void assign(size_type kiekis, const T& reiksme) {
        clear();

        if (kiekis > talpa_) {
            reserve(kiekis);
        }

        for (size_type i = 0; i < kiekis; ++i) {
            duomenys_[i] = reiksme;
        }

        dydis_ = kiekis;
    }

    /**
     * @brief Priskiria konteineriui elementus is iteratoriu intervalo.
     *
     * @param pirmas Pirmas intervalo iteratorius.
     * @param paskutinis Iteratorius uz paskutinio intervalo elemento.
     */
    template <typename InputIterator>
    void assign(InputIterator pirmas, InputIterator paskutinis) {
        clear();

        for (InputIterator it = pirmas; it != paskutinis; ++it) {
            push_back(*it);
        }
    }

    /**
     * @brief Priskiria konteineriui initializer_list sarasa.
     *
     * @param sarasas Naujas elementu sarasas.
     */
    void assign(std::initializer_list<T> sarasas) {
        clear();

        if (sarasas.size() > talpa_) {
            reserve(sarasas.size());
        }

        size_type i = 0;
        for (const auto& elementas : sarasas) {
            duomenys_[i++] = elementas;
        }

        dydis_ = sarasas.size();
    }

    /**
     * @brief Iterpia elementa i nurodyta pozicija.
     *
     * Visi po iterpimo vietos esantys elementai paslenkami i desine.
     *
     * @param pozicija Iteratorius i vieta, kur turi buti iterptas elementas.
     * @param reiksme Iterpiama elemento reiksme.
     * @return Iteratorius i iterpta elementa.
     */
    iterator insert(const_iterator pozicija, const T& reiksme) {
        size_type indeksas = pozicija - cbegin();

        if (indeksas > dydis_) {
            throw std::out_of_range("Vector insert pozicija uz ribu");
        }

        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        for (size_type i = dydis_; i > indeksas; --i) {
            duomenys_[i] = std::move(duomenys_[i - 1]);
        }

        duomenys_[indeksas] = reiksme;
        ++dydis_;

        return begin() + indeksas;
    }

    /**
     * @brief Iterpia perkeliama elementa i nurodyta pozicija.
     *
     * @param pozicija Iteratorius i vieta, kur turi buti iterptas elementas.
     * @param reiksme Perkeliama elemento reiksme.
     * @return Iteratorius i iterpta elementa.
     */
    iterator insert(const_iterator pozicija, T&& reiksme) {
        size_type indeksas = pozicija - cbegin();

        if (indeksas > dydis_) {
            throw std::out_of_range("Vector insert pozicija uz ribu");
        }

        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        for (size_type i = dydis_; i > indeksas; --i) {
            duomenys_[i] = std::move(duomenys_[i - 1]);
        }

        duomenys_[indeksas] = std::move(reiksme);
        ++dydis_;

        return begin() + indeksas;
    }

    /**
     * @brief Iterpia kelis vienodus elementus i nurodyta pozicija.
     *
     * @param pozicija Iteratorius i iterpimo vieta.
     * @param kiekis Iterpiamu elementu kiekis.
     * @param reiksme Iterpiama reiksme.
     * @return Iteratorius i pirma iterpta elementa.
     */
    iterator insert(const_iterator pozicija, size_type kiekis, const T& reiksme) {
        size_type indeksas = pozicija - cbegin();

        if (indeksas > dydis_) {
            throw std::out_of_range("Vector insert pozicija uz ribu");
        }

        if (kiekis == 0) {
            return begin() + indeksas;
        }

        if (dydis_ + kiekis > talpa_) {
            size_type nauja_talpa = talpa_;
            if (nauja_talpa == 0) {
                nauja_talpa = 1;
            }

            while (nauja_talpa < dydis_ + kiekis) {
                nauja_talpa *= 2;
            }

            reserve(nauja_talpa);
        }

        for (size_type i = dydis_; i > indeksas; --i) {
            duomenys_[i + kiekis - 1] = std::move(duomenys_[i - 1]);
        }

        for (size_type i = 0; i < kiekis; ++i) {
            duomenys_[indeksas + i] = reiksme;
        }

        dydis_ += kiekis;

        return begin() + indeksas;
    }

    /**
     * @brief Iterpia initializer_list sarasa i nurodyta pozicija.
     *
     * @param pozicija Iteratorius i iterpimo vieta.
     * @param sarasas Iterpiamu elementu sarasas.
     * @return Iteratorius i pirma iterpta elementa.
     */
    iterator insert(const_iterator pozicija, std::initializer_list<T> sarasas) {
        size_type indeksas = pozicija - cbegin();
        size_type kiekis = sarasas.size();

        if (indeksas > dydis_) {
            throw std::out_of_range("Vector insert pozicija uz ribu");
        }

        if (kiekis == 0) {
            return begin() + indeksas;
        }

        if (dydis_ + kiekis > talpa_) {
            size_type nauja_talpa = talpa_;
            if (nauja_talpa == 0) {
                nauja_talpa = 1;
            }

            while (nauja_talpa < dydis_ + kiekis) {
                nauja_talpa *= 2;
            }

            reserve(nauja_talpa);
        }

        for (size_type i = dydis_; i > indeksas; --i) {
            duomenys_[i + kiekis - 1] = std::move(duomenys_[i - 1]);
        }

        size_type i = 0;
        for (const auto& elementas : sarasas) {
            duomenys_[indeksas + i] = elementas;
            ++i;
        }

        dydis_ += kiekis;

        return begin() + indeksas;
    }

    /**
     * @brief Pasalina viena elementa is konteinerio.
     *
     * Pasalinus elementa, po jo buve elementai paslenkami i kaire.
     *
     * @param pozicija Iteratorius i salinama elementa.
     * @return Iteratorius i elementa, kuris yra po pasalinto elemento.
     */
    iterator erase(const_iterator pozicija) {
        size_type indeksas = pozicija - cbegin();

        if (indeksas >= dydis_) {
            throw std::out_of_range("Vector erase pozicija uz ribu");
        }

        for (size_type i = indeksas; i + 1 < dydis_; ++i) {
            duomenys_[i] = std::move(duomenys_[i + 1]);
        }

        --dydis_;

        return begin() + indeksas;
    }

    /**
     * @brief Pasalina elementu intervala is konteinerio.
     *
     * @param pirmas Pirmas salinamo intervalo iteratorius.
     * @param paskutinis Iteratorius uz paskutinio salinamo elemento.
     * @return Iteratorius i elementa, kuris yra po pasalinto intervalo.
     */
    iterator erase(const_iterator pirmas, const_iterator paskutinis) {
        size_type pradzia = pirmas - cbegin();
        size_type pabaiga = paskutinis - cbegin();

        if (pradzia > pabaiga || pabaiga > dydis_) {
            throw std::out_of_range("Vector erase intervalas uz ribu");
        }

        size_type kiekis = pabaiga - pradzia;

        for (size_type i = pradzia; i + kiekis < dydis_; ++i) {
            duomenys_[i] = std::move(duomenys_[i + kiekis]);
        }

        dydis_ -= kiekis;

        return begin() + pradzia;
    }

    /**
     * @brief Patikrina, ar du Vector objektai yra lygus.
     *
     * @param kitas Kitas Vector objektas.
     * @return true, jeigu elementai sutampa.
     */
    bool operator==(const Vector& kitas) const {
        if (dydis_ != kitas.dydis_) {
            return false;
        }

        for (size_type i = 0; i < dydis_; ++i) {
            if (!(duomenys_[i] == kitas.duomenys_[i])) {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Patikrina, ar du Vector objektai yra nelygus.
     *
     * @param kitas Kitas Vector objektas.
     * @return true, jeigu objektai nelygus.
     */
    bool operator!=(const Vector& kitas) const {
        return !(*this == kitas);
    }

    /**
     * @brief Leksikografiskai palygina du Vector objektus.
     *
     * @param kitas Kitas Vector objektas.
     * @return true, jeigu sis Vector yra mazesnis.
     */
    bool operator<(const Vector& kitas) const {
        size_type mazesnis_dydis = (dydis_ < kitas.dydis_) ? dydis_ : kitas.dydis_;

        for (size_type i = 0; i < mazesnis_dydis; ++i) {
            if (duomenys_[i] < kitas.duomenys_[i]) {
                return true;
            }

            if (kitas.duomenys_[i] < duomenys_[i]) {
                return false;
            }
        }

        return dydis_ < kitas.dydis_;
    }

    /**
     * @brief Patikrina, ar sis Vector yra mazesnis arba lygus kitam.
     *
     * @param kitas Kitas Vector objektas.
     * @return true, jeigu sis Vector yra mazesnis arba lygus.
     */
    bool operator<=(const Vector& kitas) const {
        return !(kitas < *this);
    }

    /**
     * @brief Patikrina, ar sis Vector yra didesnis uz kita.
     *
     * @param kitas Kitas Vector objektas.
     * @return true, jeigu sis Vector yra didesnis.
     */
    bool operator>(const Vector& kitas) const {
        return kitas < *this;
    }

    /**
     * @brief Patikrina, ar sis Vector yra didesnis arba lygus kitam.
     *
     * @param kitas Kitas Vector objektas.
     * @return true, jeigu sis Vector yra didesnis arba lygus.
     */
    bool operator>=(const Vector& kitas) const {
        return !(*this < kitas);
    }
};