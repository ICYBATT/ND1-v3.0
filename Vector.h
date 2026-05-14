#pragma once

#include <cstddef>
#include <stdexcept>
#include <algorithm>

/*
    Nuosavas Vector konteineris.
    Pradine versija v3.0 darbui.

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
};