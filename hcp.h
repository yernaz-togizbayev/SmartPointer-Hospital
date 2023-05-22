#ifndef HCP_H
#define HCP_H

#include<iostream>
#include<stdexcept>
#include<set>
#include<vector>
#include<memory>

#include "illness.h"
#include "patient.h"
#include "hospital.h"

class Health_Care_Provider
{
public:
  Health_Care_Provider(std::string, const std::set<Medical_Specialty>&, unsigned=500);
  std::string get_name() const;
  virtual ~Health_Care_Provider() = default;
  void increase_wealth(unsigned);
  unsigned get_wealth() const;
  const std::set<Medical_Specialty> get_topics() const;
  virtual unsigned perform_procedure(unsigned, std::shared_ptr<Patient>, Medical_Specialty) = 0;
  virtual std::string hcp_type() const = 0;
  bool pay_license(unsigned);
  virtual void receive_license(Medical_Specialty);
  bool eligible_for(Medical_Specialty);
  friend std::ostream& operator<< (std::ostream&, const Health_Care_Provider&);

private:
  std::string name;
  std::set<Medical_Specialty> topics;
  unsigned wealth;
};


class Teaching_Health_Care_Provider : public Health_Care_Provider
{
public:
    Teaching_Health_Care_Provider(unsigned fee, std::string, const std::set<Medical_Specialty>&,unsigned = 500);
    unsigned perform_procedure(unsigned, std::shared_ptr<Patient>, Medical_Specialty) override;
    std::string hcp_type() const override;
    bool teach(Medical_Specialty, std::shared_ptr<Health_Care_Provider>);

private:
    unsigned fee;
};


class Smart_Health_Care_Provider : public Health_Care_Provider
{
public:
    Smart_Health_Care_Provider(unsigned, std::string, const std::set<Medical_Specialty>&, unsigned = 500);
    unsigned get_fee() const;
    unsigned perform_procedure(unsigned, std::shared_ptr<Patient>, Medical_Specialty) override;
    std::string hcp_type() const override;
    void receive_license(Medical_Specialty) override;

private:
    unsigned fee;
};

class Semi_Smart_HCP : public Smart_Health_Care_Provider
{
public:
	Semi_Smart_HCP(unsigned, std::string, const std::set<Medical_Specialty>&, unsigned = 500);
	void receive_license(Medical_Specialty) override;
private:
	unsigned counter { 1 };
	
};

#endif
