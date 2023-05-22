#include<iostream>
#include<stdexcept>
#include<map>
#include<vector>
#include<memory>
#include<algorithm>
#include "hcp.h"
#include "illness.h"
#include "patient.h"
#include "hospital.h"

Hospital::Hospital(std::string name) : name {name}
{
    if (name.empty())
        throw std::runtime_error("name cannot be empty");
}

bool Hospital::sign_hcp(std::shared_ptr<Health_Care_Provider> m)
{
  auto it = hcps.find(m->get_name());
  
  if (it == hcps.end())
  {
    hcps[m->get_name()] = m;
    return true;
  }
  
  return false;
}

bool Hospital::admit_patient(std::shared_ptr<Patient> m)
{
  auto it = patients.find(m->get_name());

  if (it == patients.end() || it->second.expired())
  {
    patients[m->get_name()] = m;
    return true;
  }
  
  return false;
}

bool Hospital::dismiss_hcp(std::string n)
{
    for (const auto& hcp : hcps)
    {
        if (hcp.first == n)
        {
            hcps.erase(hcp.first);
            return true;
        }
    }
    return false;
}

std::shared_ptr<Health_Care_Provider> Hospital::get_hcp(std::string n) const
{
    auto it = hcps.find(n);

    if (it == hcps.end())
        throw std::runtime_error("No hcp with name n could be found");
    
    return it->second;
}

std::shared_ptr<Patient> Hospital::get_patient(std::string n) const
{
    auto it = patients.find(n);

    if (it == patients.end() || it->second.expired())
        throw std::runtime_error("No patient with name n could be found");

    return std::shared_ptr(it->second);
}

bool  Hospital::dismiss_patient(std::string n)
{
    auto it = patients.find(n);
    if (it != patients.end() && !it->second.expired())
    {
        it = patients.erase(it);
        return true;
    }
    return false;
}

std::ostream& operator<< (std::ostream& o, const Hospital& p)
{
    o << '[' << p.name << ", hcps {";
    bool first1 {true};
    for (const auto& hcp : p.hcps)
    {
        if (first1) first1 = false;
        else o << ", ";
        o << *hcp.second;
    }
    o << "}, patients {";
    bool first2 {true};
    for (const auto& patient : p.patients)
    {
      auto shared_patient = patient.second.lock();
      if (shared_patient)
      {
        if (first2) first2 = false;
        else o << ", ";
        o << *shared_patient;
      }
    }
    o << "}]";
    return o;
}

Special_Hospital::Special_Hospital(const std::set<Medical_Specialty>& specialties, std::string name):
	Hospital(name), specialties{specialties}
{
  if (specialties.empty())
    throw std::runtime_error("specialties may not be empty");
}

bool Special_Hospital::admit_patient(std::shared_ptr<Patient> m)
{
  for (const auto& illness : m->get_illnesses())
  {
    auto found = std::find(specialties.begin(), specialties.end(), illness.get_specialty());
    if (found == specialties.end())
      return false;
  }
  return Hospital::admit_patient(m);
}