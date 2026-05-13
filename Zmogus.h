#pragma once
#include <string>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus();
    Zmogus(const std::string& vardas, const std::string& pavarde);

    virtual ~Zmogus() = 0;

    virtual void spausdintiInformacija() const = 0;

    const std::string& getVardas() const;
    const std::string& getPavarde() const;

    void setVardas(const std::string& vardas);
    void setPavarde(const std::string& pavarde);
};

inline Zmogus::Zmogus() : vardas_(""), pavarde_("") {}

inline Zmogus::Zmogus(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {}

inline Zmogus::~Zmogus() {}

inline const std::string& Zmogus::getVardas() const { return vardas_; }
inline const std::string& Zmogus::getPavarde() const { return pavarde_; }

inline void Zmogus::setVardas(const std::string& vardas) { vardas_ = vardas; }
inline void Zmogus::setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }