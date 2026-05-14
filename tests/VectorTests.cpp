#include <catch2/catch_test_macros.hpp>
#include "../Vector.h"

TEST_CASE("Vector tuscias konstruktorius veikia teisingai", "[Vector]") {
    Vector<int> v;

    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty() == true);
}

TEST_CASE("Vector push_back prideda elementus", "[Vector]") {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);
    REQUIRE(v[2] == 30);
    REQUIRE(v.empty() == false);
}

TEST_CASE("Vector at metodas tikrina ribas", "[Vector]") {
    Vector<int> v = {1, 2, 3};

    REQUIRE(v.at(0) == 1);
    REQUIRE(v.at(1) == 2);
    REQUIRE(v.at(2) == 3);

    REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
}

TEST_CASE("Vector front ir back grazina pirmą ir paskutinį elementą", "[Vector]") {
    Vector<int> v = {5, 10, 15};

    REQUIRE(v.front() == 5);
    REQUIRE(v.back() == 15);
}

TEST_CASE("Vector reserve padidina capacity bet nekeicia size", "[Vector]") {
    Vector<int> v = {1, 2, 3};

    v.reserve(20);

    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() >= 20);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("Vector resize padidina ir sumazina dydi", "[Vector]") {
    Vector<int> v = {1, 2, 3};

    v.resize(5, 9);

    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 9);
    REQUIRE(v[4] == 9);

    v.resize(2);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
}

TEST_CASE("Vector pop_back ir clear veikia teisingai", "[Vector]") {
    Vector<int> v = {1, 2, 3};

    v.pop_back();

    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 2);

    v.clear();

    REQUIRE(v.size() == 0);
    REQUIRE(v.empty() == true);
}

TEST_CASE("Vector kopijavimo konstruktorius sukuria nepriklausoma kopija", "[Vector]") {
    Vector<int> pirmas = {1, 2, 3};
    Vector<int> antras(pirmas);

    antras[0] = 100;

    REQUIRE(pirmas[0] == 1);
    REQUIRE(antras[0] == 100);
    REQUIRE(antras.size() == 3);
}

TEST_CASE("Vector kopijavimo priskyrimas veikia teisingai", "[Vector]") {
    Vector<int> pirmas = {1, 2, 3};
    Vector<int> antras;

    antras = pirmas;
    antras[1] = 200;

    REQUIRE(pirmas[1] == 2);
    REQUIRE(antras[1] == 200);
    REQUIRE(antras.size() == 3);
}

TEST_CASE("Vector insert iterpia elementus", "[Vector]") {
    Vector<int> v = {1, 2, 4};

    v.insert(v.begin() + 2, 3);

    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
}

TEST_CASE("Vector erase pasalina elementa", "[Vector]") {
    Vector<int> v = {1, 2, 3, 4};

    v.erase(v.begin() + 1);

    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
    REQUIRE(v[2] == 4);
}

TEST_CASE("Vector palyginimo operatoriai veikia teisingai", "[Vector]") {
    Vector<int> a = {1, 2, 3};
    Vector<int> b = {1, 2, 3};
    Vector<int> c = {1, 2, 4};

    REQUIRE(a == b);
    REQUIRE(a != c);
    REQUIRE(a < c);
    REQUIRE(c > a);
    REQUIRE(a <= b);
    REQUIRE(a >= b);
}

TEST_CASE("Vector iteratoriai leidzia pereiti per elementus", "[Vector]") {
    Vector<int> v = {1, 2, 3, 4};

    int suma = 0;

    for (auto it = v.begin(); it != v.end(); ++it) {
        suma += *it;
    }

    REQUIRE(suma == 10);
}