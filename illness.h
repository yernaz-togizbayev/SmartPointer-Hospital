#ifndef ILLNESS_H
#define ILLNESS_H

#include<iostream>
#include<stdexcept>
#include<string>

enum class Medical_Specialty
{
    Cardiology,
    Dermatology,
    Endocrinology,
    Gynecology,
    Neurology,
    Oncology,
    Pathology,
    Pediatrics,
    Pulmonology,
    Urology
};

inline std::ostream& operator<<(std::ostream& o, Medical_Specialty m)
{
    switch (m)
    {
        case Medical_Specialty::Cardiology: o << "Cardiology"; break;
        case Medical_Specialty::Dermatology: o << "Dermatology"; break;
        case Medical_Specialty::Endocrinology: o << "Endocrinology"; break;
        case Medical_Specialty::Gynecology: o << "Gynecology"; break;
        case Medical_Specialty::Neurology: o << "Neurology"; break;
        case Medical_Specialty::Oncology: o << "Oncology"; break;
        case Medical_Specialty::Pathology: o << "Pathology"; break;
        case Medical_Specialty::Pediatrics: o << "Pediatrics"; break;
        case Medical_Specialty::Pulmonology: o << "Pulmonology"; break;
        case Medical_Specialty::Urology: o << "Urology"; break;
    }
    return o;
}


class Illness
{
public:
    Illness(Medical_Specialty, const std::string&);
    Medical_Specialty get_specialty() const;
    std::string get_name() const;
    friend std::ostream& operator<< (std::ostream&, const Illness&);
    bool operator==(const Illness&) const;
    bool operator< (const Illness&) const;

private:
    Medical_Specialty med;
    std::string name;
};

#endif
