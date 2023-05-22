#ifndef TASKS_H
#define TASKS_H
#include<iostream>
#include<memory>
#include<vector>
#include<experimental/iterator>
#include<iterator>
#include<algorithm>
#include<numeric>
#include<cstdlib>
#include<set>

const std::set<Medical_Specialty> all_topics{Medical_Specialty::Cardiology,Medical_Specialty::Dermatology,Medical_Specialty::Endocrinology,Medical_Specialty::Gynecology,Medical_Specialty::Neurology,Medical_Specialty::Oncology,Medical_Specialty::Pathology,Medical_Specialty::Pediatrics,Medical_Specialty::Pulmonology,Medical_Specialty::Urology};

class Super_Task
{
public:
	Super_Task(const std::vector<std::shared_ptr<Patient>>&);  
  std::vector<std::shared_ptr<Patient>> screening(const std::vector<Medical_Specialty>&) const;
private:
  std::vector<std::weak_ptr<Patient>> patients;
};


Super_Task::Super_Task(const std::vector<std::shared_ptr<Patient>>& patients):
	patients(patients.begin(), patients.end())
  {
  }

std::vector<std::shared_ptr<Patient>> Super_Task::screening(const std::vector<Medical_Specialty>& meds) const
{
  std::vector<std::shared_ptr<Patient>> res;
  
  for (const auto& patient : patients)
  {
    
    if (auto patient_shared = patient.lock())
    {
      bool has_illness {false};
      for (const auto& illness : patient_shared->get_illnesses())
      {
        if (std::find(meds.begin(), meds.end(), illness.get_specialty()) != meds.end()) {
          has_illness = true;
          break;
        }
      }
      if (!has_illness)
        res.push_back(patient_shared);
    }
  }
  return res;
}

std::vector<std::shared_ptr<Health_Care_Provider>> task4(const std::vector<std::shared_ptr<Health_Care_Provider>>& v)
{
  std::vector<std::shared_ptr<Health_Care_Provider>> result;

  // Find maximum wealth value among all HealthCareProvider objects in v
  unsigned max_wealth = 0;
  for (const auto& hcp : v) {
    max_wealth = std::max(max_wealth, hcp->get_wealth());
  }

  // Get the intersection of topics from all HealthCareProvider objects in v
  std::set<Medical_Specialty> commonTopics;
  if (!v.empty()) {
    commonTopics = v.front()->get_topics();
    for (const auto& hcp : v) {
      std::set<Medical_Specialty> hcpTopics = hcp->get_topics();
      std::set<Medical_Specialty> intersection;
      std::set_intersection(commonTopics.begin(), commonTopics.end(), hcpTopics.begin(),
                            hcpTopics.end(), std::inserter(intersection, intersection.begin()));
      commonTopics = intersection;
    }
  }

  // Create Teaching_Health_Care_Provider objects with the calculated attribute values
  for (const auto& hcp : v) {
    std::shared_ptr<Teaching_Health_Care_Provider> teachingProvider =
      std::make_shared<Teaching_Health_Care_Provider>(5, hcp->get_name(), commonTopics, max_wealth);
    result.push_back(teachingProvider);
  }

  return result;
}
#endif
