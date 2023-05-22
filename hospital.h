#ifndef HOSPITAL_H
#define HOSPITAL_H

#include<iostream>
#include<stdexcept>
#include<set>
#include<memory>
#include<map>

#include "hcp.h"
#include "illness.h"
#include "patient.h"

class Health_Care_Provider;

class Hospital
{
public:
  Hospital(std::string);
  virtual ~Hospital() = default;
  bool sign_hcp(std::shared_ptr<Health_Care_Provider>);
  virtual bool admit_patient(std::shared_ptr<Patient>);
  bool dismiss_hcp(std::string);
  std::shared_ptr<Health_Care_Provider> get_hcp(std::string) const;
  std::shared_ptr<Patient> get_patient(std::string) const;
  bool dismiss_patient(std::string);
  friend std::ostream& operator<< (std::ostream&, const Hospital&);

private:
  std::string name;
  std::map<std::string, std::shared_ptr<Health_Care_Provider>> hcps;
  std::map<std::string, std::weak_ptr<Patient>> patients;
};

class Special_Hospital : public Hospital
{
public:
	Special_Hospital(const std::set<Medical_Specialty>&, std::string);
	bool admit_patient(std::shared_ptr<Patient>) override;
private:
	std::set<Medical_Specialty> specialties;
};
#endif
