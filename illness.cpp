#include "illness.h"
#include<vector>
#include<string>
#include<iostream>

Illness::Illness(Medical_Specialty med, const std::string& name) : med {med}, name{name}
{
    if (name.empty())
        throw std::runtime_error("name must not be empty");
}

Medical_Specialty Illness::get_specialty() const { return med; }

std::string Illness::get_name() const { return name; }

bool Illness::operator== (const Illness& other) const
{
    return this->name == other.name && this->med == other.med;
}

bool Illness::operator< (const Illness& other) const
{
  if (this->get_specialty() < other.get_specialty())
    return true;
  else if (this->get_specialty() > other.get_specialty())
    return false;
  else
    return this->name < other.name;
}

std::ostream& operator<< (std::ostream& o, const Illness& ill)
{
    return o << '[' << ill.get_specialty() << ", " << ill.name << ']';
}