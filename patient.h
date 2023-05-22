#ifndef PATIENT_H
#define PATIENT_H

#include<iostream>
#include<stdexcept>
#include<set>
#include "illness.h"

enum class Medical_Specialty;
class Illness;

class Patient
{
public:
    Patient(std::string, int, const std::set<Illness>&, unsigned = 200);
    std::string get_name() const;
  	std::set<Illness> get_illnesses() const;
    void increase_wealth(unsigned);
    bool pay_procedure(unsigned);
    void catch_disease(const Illness&);
    bool requires_treatment_in(Medical_Specialty) const;
    unsigned cure(Medical_Specialty);
    bool operator== (const Patient&) const;
    bool healthy() const;
    friend std::ostream& operator<< (std::ostream&, const Patient&);

private:
    std::string name;
    int age;
    std::set<Illness> illnesses;
    unsigned wealth;
};

#endif
