#include<iostream>
#include<stdexcept>
#include<set>
#include<algorithm>
#include "patient.h"
#include "illness.h"

Patient::Patient(std::string name, int age, const std::set<Illness>& illnesses, unsigned wealth) :
    name {name},
    age {age},
    illnesses {illnesses},
    wealth {wealth}
    {
        if (name.empty())
            throw std::runtime_error("name must not be empty");
        
        if (age < 0)
            throw std::runtime_error("age cannot be less than 0");
      
      if (illnesses.empty())
        throw std::runtime_error("Patient must suffer from at least one Illness at the beginning");
    }

std::string Patient::get_name() const { return name; }

std::set<Illness> Patient::get_illnesses() const { return illnesses; }

void Patient::increase_wealth(unsigned x) { wealth += x; }

bool Patient::pay_procedure(unsigned x)
{
    if (static_cast<int>(wealth - x) >= 0)
    {
        wealth -= x;
        return true;
    }
    return false;
}

void Patient::catch_disease(const Illness& x) { illnesses.insert(x); }

bool Patient::requires_treatment_in(Medical_Specialty x) const
{
    for (const auto& illness : illnesses)
    {
        if (illness.get_specialty() == x)
            return true;
    }
    return false;
}

bool Patient::healthy() const
{
    if (illnesses.empty())
        return true;
    return false;
}

unsigned Patient::cure(Medical_Specialty x)
{
    unsigned removed{0};
    for (auto it{illnesses.begin()}; it != illnesses.end();)
    {
      if (it->get_specialty() == x)
      {
        it = illnesses.erase(it);
        ++removed;
      }
      else ++it;
    }
    return removed;
}

bool Patient::operator== (const Patient& other) const
{
    return  this->name == other.name &&
            this->age == other.age &&
            this->illnesses == other.illnesses &&
            this->wealth == other.wealth;
}

std::ostream& operator<< (std::ostream& o, const Patient& p)
{
    o << '[' << p.name << ", " << p.age << " years, {";
    bool first {true};
    for (const auto& illness : p.illnesses)
    {
        if (first) first = false;
        else o << ", ";
        o << illness;
    }

    o << "}, " << p.wealth << " moneyz]";
    return o;
}