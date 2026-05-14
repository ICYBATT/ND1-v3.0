#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

/*
    Nuosavas Vector konteineris.
    v3.0 darbo dalis.

    Si klase bus pleciama taip, kad funkcionalumu butu panasi i std::vector.
*/

template <typename T>
class Vector {
private:
    T* duomenys_;
    std::size_t dydis_;
    std::size_t talpa_;

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

    // Tuscias konstruktorius
    Vector()
        : duomenys_(nullptr), dydis_(0), talpa_(0) {}

    // Sukuria Vector su n tusciu elementu
    explicit Vector(size_type kiekis)
        : duomenys_(nullptr), dydis_(kiekis), talpa_(kiekis) {
        if (kiekis > 0) {
            duomenys_ = new T[kiekis];
        }
    }

    // Sukuria Vector su n vienodu elementu
    Vector(size_type kiekis, const T& reiksme)
        : duomenys_(nullptr), dydis_(kiekis), talpa_(kiekis) {
        if (kiekis > 0) {
            duomenys_ = new T[kiekis];
            for (size_type i = 0; i < kiekis; ++i) {
                duomenys_[i] = reiksme;
            }
        }
    }

    // Sukuria Vector is initializer_list, pvz. Vector<int> v = {1, 2, 3}
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

    // Sukuria Vector is iteratoriu intervalo
    template <typename InputIterator>
    Vector(InputIterator pirmas, InputIterator paskutinis)
        : duomenys_(nullptr), dydis_(0), talpa_(0) {
        for (InputIterator it = pirmas; it != paskutinis; ++it) {
            push_back(*it);
        }
    }

    // Destruktorius
    ~Vector() {
        delete[] duomenys_;
    }

    size_type size() const {
        return dydis_;
    }

    size_type capacity() const {
        return talpa_;
    }

    bool empty() const {
        return dydis_ == 0;
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

    iterator end() {
        return duomenys_ + dydis_;
    }

    const_iterator end() const {
        return duomenys_ + dydis_;
    }

    void push_back(const T& reiksme) {
        if (dydis_ == talpa_) {
            size_type nauja_talpa = (talpa_ == 0) ? 1 : talpa_ * 2;
            T* nauji_duomenys = new T[nauja_talpa];

            for (size_type i = 0; i < dydis_; ++i) {
                nauji_duomenys[i] = duomenys_[i];
            }

            delete[] duomenys_;
            duomenys_ = nauji_duomenys;
            talpa_ = nauja_talpa;
        }

        duomenys_[dydis_] = reiksme;
        ++dydis_;
    }
};