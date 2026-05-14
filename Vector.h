#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <limits>

/*
    Nuosavas Vector konteineris.
    v3.0 darbo dalis.

    Si klase kuriama taip, kad funkcionalumu butu panasi i std::vector.
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
    Vector()
        : duomenys_(nullptr), dydis_(0), talpa_(0) {}

    explicit Vector(size_type kiekis)
        : duomenys_(nullptr), dydis_(kiekis), talpa_(kiekis) {
        if (kiekis > 0) {
            duomenys_ = new T[kiekis];
        }
    }

    Vector(size_type kiekis, const T& reiksme)
        : duomenys_(nullptr), dydis_(kiekis), talpa_(kiekis) {
        if (kiekis > 0) {
            duomenys_ = new T[kiekis];
            for (size_type i = 0; i < kiekis; ++i) {
                duomenys_[i] = reiksme;
            }
        }
    }

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

    template <typename InputIterator>
    Vector(InputIterator pirmas, InputIterator paskutinis)
        : duomenys_(nullptr), dydis_(0), talpa_(0) {
        for (InputIterator it = pirmas; it != paskutinis; ++it) {
            push_back(*it);
        }
    }

    Vector(const Vector& kitas)
        : duomenys_(nullptr), dydis_(kitas.dydis_), talpa_(kitas.talpa_) {
        if (talpa_ > 0) {
            duomenys_ = new T[talpa_];
            for (size_type i = 0; i < dydis_; ++i) {
                duomenys_[i] = kitas.duomenys_[i];
            }
        }
    }

    Vector(Vector&& kitas) noexcept
        : duomenys_(kitas.duomenys_), dydis_(kitas.dydis_), talpa_(kitas.talpa_) {
        kitas.duomenys_ = nullptr;
        kitas.dydis_ = 0;
        kitas.talpa_ = 0;
    }

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

    Vector& operator=(std::initializer_list<T> sarasas) {
        Vector laikinas(sarasas);
        swap(laikinas);
        return *this;
    }

    ~Vector() {
        delete[] duomenys_;
    }

    void swap(Vector& kitas) noexcept {
        std::swap(duomenys_, kitas.duomenys_);
        std::swap(dydis_, kitas.dydis_);
        std::swap(talpa_, kitas.talpa_);
    }

    size_type size() const {
        return dydis_;
    }

    size_type capacity() const {
        return talpa_;
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    bool empty() const {
        return dydis_ == 0;
    }

    void reserve(size_type nauja_talpa) {
        if (nauja_talpa > max_size()) {
            throw std::length_error("Vector reserve virsija max_size");
        }

        if (nauja_talpa > talpa_) {
            perkelti_i_nauja_talpa(nauja_talpa);
        }
    }

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

    void shrink_to_fit() {
        if (dydis_ < talpa_) {
            perkelti_i_nauja_talpa(dydis_);
        }
    }

    pointer data() {
        return duomenys_;
    }

    const_pointer data() const {
        return duomenys_;
    }

    reference operator[](size_type indeksas) {
        return duomenys_[indeksas];
    }

    const_reference operator[](size_type indeksas) const {
        return duomenys_[indeksas];
    }

    reference at(size_type indeksas) {
        if (indeksas >= dydis_) {
            throw std::out_of_range("Vector indeksas uz ribu");
        }
        return duomenys_[indeksas];
    }

    const_reference at(size_type indeksas) const {
        if (indeksas >= dydis_) {
            throw std::out_of_range("Vector indeksas uz ribu");
        }
        return duomenys_[indeksas];
    }

    reference front() {
        return duomenys_[0];
    }

    const_reference front() const {
        return duomenys_[0];
    }

    reference back() {
        return duomenys_[dydis_ - 1];
    }

    const_reference back() const {
        return duomenys_[dydis_ - 1];
    }

    iterator begin() {
        return duomenys_;
    }

    const_iterator begin() const {
        return duomenys_;
    }

    const_iterator cbegin() const {
        return duomenys_;
    }

    iterator end() {
        return duomenys_ + dydis_;
    }

    const_iterator end() const {
        return duomenys_ + dydis_;
    }

    const_iterator cend() const {
        return duomenys_ + dydis_;
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }

    void clear() {
        dydis_ = 0;
    }

    void push_back(const T& reiksme) {
        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        duomenys_[dydis_] = reiksme;
        ++dydis_;
    }

    void push_back(T&& reiksme) {
        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            reserve(nauja_talpa);
        }

        duomenys_[dydis_] = std::move(reiksme);
        ++dydis_;
    }

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

    void pop_back() {
        if (dydis_ > 0) {
            --dydis_;
        }
    }

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

    template <typename InputIterator>
    void assign(InputIterator pirmas, InputIterator paskutinis) {
        clear();

        for (InputIterator it = pirmas; it != paskutinis; ++it) {
            push_back(*it);
        }
    }

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
};