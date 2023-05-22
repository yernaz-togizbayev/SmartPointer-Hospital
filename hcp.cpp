#include<iostream>
#include<stdexcept>
#include<map>
#include<vector>
#include<memory>
#include<algorithm>
#include "hcp.h"
#include "illness.h"
#include "patient.h"

Health_Care_Provider::Health_Care_Provider(std::string n, const std::set<Medical_Specialty>& topics, unsigned wealth) :
    name {n},
    topics {topics},
    wealth {wealth}
    {
        if (name.empty())
            throw std::runtime_error("name must not be empty");
    }

std::string Health_Care_Provider::get_name() const { return name; }

void Health_Care_Provider::increase_wealth(unsigned x) { wealth += x; }

unsigned Health_Care_Provider::get_wealth() const { return wealth; }

const std::set<Medical_Specialty> Health_Care_Provider::get_topics() const { return topics; }

bool Health_Care_Provider::pay_license(unsigned x)
{
    if (static_cast<int>(wealth - x) >= 0)
    {
        wealth -= x;
        return true;
    }
    return false;
}

void Health_Care_Provider::receive_license(Medical_Specialty x) { topics.insert(x); }

bool Health_Care_Provider::eligible_for(Medical_Specialty m)
{
  if (topics.find(m) != topics.end())
    return true;
  return false;
}

std::ostream& operator<< (std::ostream& o, const Health_Care_Provider& h)
{
    o << '[' << h.get_name() << ", {";
    bool first {true};
    for (const auto& topic : h.topics)
    {
        if (first) first = false;
        else o << ", ";
        o << topic;
    }
    o << "}, " << h.wealth << " moneyz, " << h.hcp_type() << ']';
    return o;
}


Teaching_Health_Care_Provider::Teaching_Health_Care_Provider(unsigned fee, std::string n, const std::set<Medical_Specialty>& topics, unsigned wealth) :
    Health_Care_Provider(n, topics, wealth), fee {fee}
    {
      if (n.empty())
        throw std::runtime_error("name must not be empty");
    }

unsigned Teaching_Health_Care_Provider::perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m)
{
  if (this->eligible_for(m) && p->requires_treatment_in(m) && p->pay_procedure(x))
  {
    increase_wealth(x);
    return p->cure(m);
  }
  return 0;
}

std::string Teaching_Health_Care_Provider::hcp_type() const { return "Teacher"; }

bool Teaching_Health_Care_Provider::teach(Medical_Specialty m, std::shared_ptr<Health_Care_Provider> target)
{
  if (target.get() == this || target->eligible_for(m) || !this->eligible_for(m))
    return false;
  
  if (target->pay_license(fee))
  {
    this->increase_wealth(fee);
  	target->receive_license(m);
    return true;
  }
  
  return false;
}

Smart_Health_Care_Provider::Smart_Health_Care_Provider(unsigned fee, std::string n, const std::set<Medical_Specialty>& topics, unsigned wealth) :
    Health_Care_Provider(n, topics, wealth), fee {fee}
    {
        if (n.empty())
            throw std::runtime_error("name must not be empty");
    }

unsigned Smart_Health_Care_Provider::perform_procedure(unsigned x, std::shared_ptr<Patient> p, Medical_Specialty m) { return 0; }

std::string Smart_Health_Care_Provider::hcp_type() const { return "Smart"; }

unsigned Smart_Health_Care_Provider::get_fee() const { return fee; }

void Smart_Health_Care_Provider::receive_license(Medical_Specialty m)
{
  this->increase_wealth(fee);
  Health_Care_Provider::receive_license(m);
}

Semi_Smart_HCP::Semi_Smart_HCP(unsigned fee, std::string n, const std::set<Medical_Specialty>& topics, unsigned wealth):
	Smart_Health_Care_Provider(fee, n, topics, wealth)
  {
    if (n.empty())
      throw std::runtime_error("name must not be empty");
  }

void Semi_Smart_HCP::receive_license(Medical_Specialty m)
{
  if ((counter++)%2 == 0)
    Smart_Health_Care_Provider::receive_license(m);
  
}
