#include <catch2/catch_test_macros.hpp>
#include "../Vector.h"
#include "../studentas.h"

#include <vector>
#include <utility>

TEST_CASE("Vector gali saugoti Studentas objektus", "[Vector][Studentas]") {
    Vector<Studentas> studentai;

    Studentas s1("Jonas", "Jonaitis", std::vector<int>{8, 9, 10}, 9);
    Studentas s2("Petras", "Petraitis", std::vector<int>{6, 7, 8}, 8);

    studentai.push_back(s1);
    studentai.push_back(s2);

    REQUIRE(studentai.size() == 2);
    REQUIRE(studentai[0].getVardas() == "Jonas");
    REQUIRE(studentai[0].getPavarde() == "Jonaitis");
    REQUIRE(studentai[1].getVardas() == "Petras");
    REQUIRE(studentai[1].getPavarde() == "Petraitis");
}

TEST_CASE("Vector<Studentas> kopijavimas sukuria nepriklausoma kopija", "[Vector][Studentas]") {
    Vector<Studentas> pirmas;

    pirmas.push_back(Studentas("Ona", "Onaite", std::vector<int>{10, 9, 8}, 10));
    pirmas.push_back(Studentas("Ieva", "Ievaite", std::vector<int>{7, 8, 9}, 8));

    Vector<Studentas> antras = pirmas;

    REQUIRE(antras.size() == 2);
    REQUIRE(antras[0].getVardas() == "Ona");
    REQUIRE(antras[1].getVardas() == "Ieva");

    antras[0].setVardas("Pakeista");

    REQUIRE(pirmas[0].getVardas() == "Ona");
    REQUIRE(antras[0].getVardas() == "Pakeista");
}

TEST_CASE("Vector<Studentas> erase pasalina studenta", "[Vector][Studentas]") {
    Vector<Studentas> studentai;

    studentai.push_back(Studentas("A", "A", std::vector<int>{5, 6, 7}, 7));
    studentai.push_back(Studentas("B", "B", std::vector<int>{8, 8, 8}, 8));
    studentai.push_back(Studentas("C", "C", std::vector<int>{9, 9, 9}, 9));

    studentai.erase(studentai.begin() + 1);

    REQUIRE(studentai.size() == 2);
    REQUIRE(studentai[0].getVardas() == "A");
    REQUIRE(studentai[1].getVardas() == "C");
}

TEST_CASE("Vector<Studentas> insert iterpia studenta i viduri", "[Vector][Studentas]") {
    Vector<Studentas> studentai;

    studentai.push_back(Studentas("A", "A", std::vector<int>{5, 5, 5}, 5));
    studentai.push_back(Studentas("C", "C", std::vector<int>{9, 9, 9}, 9));

    Studentas naujas("B", "B", std::vector<int>{7, 7, 7}, 7);
    studentai.insert(studentai.begin() + 1, naujas);

    REQUIRE(studentai.size() == 3);
    REQUIRE(studentai[0].getVardas() == "A");
    REQUIRE(studentai[1].getVardas() == "B");
    REQUIRE(studentai[2].getVardas() == "C");
}

TEST_CASE("Vector<Studentas> reserve nekeicia esamu studentu", "[Vector][Studentas]") {
    Vector<Studentas> studentai;

    studentai.push_back(Studentas("Jonas", "Jonaitis", std::vector<int>{8, 9, 10}, 9));

    studentai.reserve(50);

    REQUIRE(studentai.size() == 1);
    REQUIRE(studentai.capacity() >= 50);
    REQUIRE(studentai[0].getVardas() == "Jonas");
    REQUIRE(studentai[0].getPavarde() == "Jonaitis");
}

TEST_CASE("Vector<Studentas> resize padidina konteineri", "[Vector][Studentas]") {
    Vector<Studentas> studentai;

    studentai.push_back(Studentas("Jonas", "Jonaitis", std::vector<int>{8, 9}, 9));

    studentai.resize(3);

    REQUIRE(studentai.size() == 3);
    REQUIRE(studentai[0].getVardas() == "Jonas");
}