#include <iostream>
#include "illness.h"
#include "hcp.h"
#include "patient.h"
#include "hospital.h"

#include<vector>
#include<stdexcept>
#include<memory>
#include<algorithm>
#include <experimental/iterator>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::runtime_error;
using std::shared_ptr;
using std::weak_ptr;
using std::string;

#include "tasks.h"

int main(){

// Test Medical_Specialty
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    std::copy(meds.begin(), meds.end(), std::experimental::make_ostream_joiner(std::cerr, "\n")); 
    std::copy(meds.begin(), meds.end(), std::experimental::make_ostream_joiner(std::cout, "\n")); 
    cout << endl;
  }
 
// Test Illness
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};

    // Check Ctor:
    try{
      Illness{meds[0],""};
    } catch(runtime_error& e){
      cout << "No name detected" << endl;
    }
    {
      const Illness x{meds[0],"ABC"};
      cout << x.get_name() << ", " << x.get_specialty() << endl;
    }
    const vector<string> names{"A","A","a","AA","CCC","D"};
    vector<Illness> ills;
    for(const auto& n : names)
      for(const auto& m : meds)
        ills.push_back(Illness{m,n});
    for(const auto& n : names)
      for(const auto& m : meds)
        ills.push_back(Illness{m,n});
    const set<Illness> x{ills.begin(),ills.end()};
    std::copy(x.begin(), x.end(), std::experimental::make_ostream_joiner(std::cerr, "\n")); 
    std::copy(x.begin(), x.end(), std::experimental::make_ostream_joiner(std::cout, "\n")); 
    cout << endl;
    cout << (Illness{meds[0],"A"} == Illness{meds[0],"A"});
    cout << (Illness{meds[1],"A"} == Illness{meds[0],"A"});
    cout << (Illness{meds[0],"A"} == Illness{meds[0],"B"});
    cout << endl;
  }

// Test Patient
  {
  //Patient(const std::string&,int,const std::set<Illness>&,unsigned=200);
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    const vector<string> names{"Hera","Aphrodite","Koarl","Franz"};
    Illness i1{meds[1],"A"};
    Illness i2{meds[1],"AB"};
    Illness i3{meds[0],"A"};
    // Patient Ctor
    try{
      Patient{"",1,{i1}};
    } catch(runtime_error& e){
      cout << "Patient no name" << endl;
    }
    try{
      Patient{"A",1,std::set<Illness>{}};
    } catch(runtime_error& e){
      cout << "Patient no illness at start" << endl;
    }
    try{
      Patient{"A",-1,std::set<Illness>{i1}};
    } catch(runtime_error& e){
      cout << "Patient negative age" << endl;
    }
    Patient p{"Hera",69,{i1,i2},0};
    Patient p2{"Hera",69,{i1,i2},0};
    cout << p << endl;
    cout << "equals: " << (p==p2) << endl;
    cout << p.get_name() << endl;
    cout << "Pay 0: " << p.pay_procedure(0) << endl;
    cout << "Pay 1: " << p.pay_procedure(1) << endl;
    p.increase_wealth(1);
    cout << "equals: " << (p==p2) << endl;
    cout << "Pay 1: " << p.pay_procedure(1) << endl;
    cout << "Pay 1: " << p.pay_procedure(1) << endl;
    cout << "Healthy: " << p.healthy() << endl;
    p.catch_disease(i1);
    cout << "equals: " << (p==p2) << endl;
    cout << p << endl;
    cout << "Require in " << p.requires_treatment_in(meds[0]) << endl;
    cout << "Require in " << p.requires_treatment_in(meds[1]) << endl;
    p.catch_disease(i2);
    p.catch_disease(i3);
    cout << "Cure: " << p.cure(meds[1]) << endl;
    cout << "Healthy: " << p.healthy() << endl;
    cout << "Require in " << p.requires_treatment_in(meds[1]) << endl;
    p.catch_disease(i1);
    cout << "Require in " << p.requires_treatment_in(meds[1]) << endl;
    cout << "Cure: " << p.cure(meds[1]) << endl;
    cout << "Cure: " << p.cure(meds[1]) << endl;
    cout << p << endl;
  }
  //Test HCP
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    const vector<string> names{"Hera","Aphrodite","Koarl","Franz"};

    //Teaching_Health_Care_Provider(unsigned fee,const std::string&,const std::set<Medical_Specialty>&,unsigned=500);
    try{
      Teaching_Health_Care_Provider(20,"",std::set<Medical_Specialty>{});
    }catch(runtime_error&){
      cout << "HCP Ctor No Name" << endl; 
    }
    try{
      Smart_Health_Care_Provider(20,"",std::set<Medical_Specialty>{});
    }catch(runtime_error&){
      cout << "HCP Ctor No Name" << endl; 
    }
    Teaching_Health_Care_Provider t1{100,"Teacher 1",std::set<Medical_Specialty>{},0};
    cout << t1 << endl;
    cout << "Eligible for " << t1.eligible_for(meds[0]) << endl;
    cout << "Pay 1 " << t1.pay_license(1) << endl;
    cout << "Pay 0 " << t1.pay_license(0) << endl;
    t1.increase_wealth(1);
    cout << "Pay 1 " << t1.pay_license(1) << endl;
    cout << "Pay 1 " << t1.pay_license(1) << endl;
    t1.receive_license(meds[0]);
    cout << "Eligible for " << t1.eligible_for(meds[0]) << endl;
    cout << t1 << endl;
    cout << t1.get_name() << endl;
    Illness i1{meds[1],"A"};
    Illness i2{meds[0],"AB"};
    Illness i3{meds[0],"A"};
    shared_ptr<Patient> sp{std::make_shared<Patient>("Hera",69,std::set<Illness>{i1,i2,i3},0)};
    cout << "Perform: " << t1.perform_procedure(200,sp,meds[2]) << endl;
    cout << t1 << endl;
    sp->increase_wealth(3000);
    cout << "Perform: " << t1.perform_procedure(200,sp,meds[2]) << endl;
    cout << t1 << endl;
    cout << "Perform: " << t1.perform_procedure(200,sp,meds[0]) << endl;
    cout << t1 << endl;
    cout << "Perform: " << t1.perform_procedure(200,sp,meds[0]) << endl;
    cout << t1 << endl;
    shared_ptr<Health_Care_Provider> s1{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 1",std::set<Medical_Specialty>{},0)};
    shared_ptr<Health_Care_Provider> t2{std::make_shared<Teaching_Health_Care_Provider>(100,"Teach 2",std::set<Medical_Specialty>{},30000)};
    cout << "Teach: " << t1.teach(meds[2],s1) << endl;
    cout << "Teach: " << t1.teach(meds[0],s1) << endl;
    s1->increase_wealth(2000);
    cout << "Teach: " << t1.teach(meds[2],s1) << endl;
    cout << "Teach: " << t1.teach(meds[0],s1) << endl;
    cout << "Teach: " << t1.teach(meds[0],s1) << endl;
    cout << t1 << endl;
    cout << *s1 << endl;
    cout << "Teach: " << t1.teach(meds[0],t2) << endl;
    cout << t1 << endl;
    cout << *t2 << endl;
  }
// Test Hospital
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    const vector<string> names{"Hera","Aphrodite","Koarl","Franz"};

    try{
      Hospital("");
    }catch(runtime_error&){
      cout << "Hospital Ctor No Name" << endl; 
    }
    
    shared_ptr<Health_Care_Provider> s1{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 1",std::set<Medical_Specialty>{meds[0],meds[6]},0)};
    shared_ptr<Health_Care_Provider> s2{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 2",std::set<Medical_Specialty>{meds[1],meds[2]},2000)};
    Hospital h{"Hospital"};
    Illness i1{meds[1],"A"};
    Illness i2{meds[0],"AB"};
    Illness i3{meds[0],"A"};
    cout << h << endl;
    cout << "Sign: " << h.sign_hcp(s1) << endl;
    cout << "Sign: " << h.sign_hcp(s1) << endl;
    cout << h << endl;
    cout << "Sign: " << h.sign_hcp(s2) << endl;
    cout << h << endl;
    cout << *h.get_hcp(s2->get_name()) << endl;
    cout << "Dismiss: " << h.dismiss_hcp(s2->get_name()) << endl;
    cout << h << endl;
    try{
      cout << h.get_hcp(s2->get_name()) << endl;
    } catch(runtime_error&){
      cout << "HCP not found" << endl;
    }
    cout << "Dismiss: " << h.dismiss_hcp(s2->get_name()) << endl;
    cout << h << endl;

    shared_ptr<Patient> p1{std::make_shared<Patient>("Hera",69,std::set<Illness>{i1,i2,i3},0)};
    shared_ptr<Patient> p2{std::make_shared<Patient>("Hera2",69,std::set<Illness>{i1,i2,i3},0)};
    shared_ptr<Patient> p3{std::make_shared<Patient>("Hera2",69,std::set<Illness>{i1,i2,i3},20)};
    cout << "Admit: " << h.admit_patient(p1) << endl;
    cout << "Admit: " << h.admit_patient(p1) << endl;
    cout << h << endl;
    cout << "Admit: " << h.admit_patient(p2) << endl;
    cout << "Admit: " << h.admit_patient(p3) << endl;
    cout << h << endl;
    p2 = nullptr;
    cout << h << endl;
    cout << "Admit: " << h.admit_patient(p3) << endl;
    cout << h << endl;
    cout << *h.get_patient("Hera2") << endl;
    p3 = nullptr;
    try{
      cout << h.get_patient("Hera2") << endl;
    } catch(runtime_error&){
      cout << "Patient not found" << endl;
    }
    cout << "Dismiss: " << h.dismiss_patient("Hera") << endl;
    cout << "Dismiss: " << h.dismiss_patient("Hera") << endl;
    cout << "Dismiss: " << h.dismiss_patient("Hera2") << endl;
    cout << h << endl;
  }

  // Task 1
  
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    Semi_Smart_HCP x{100,"Semi Smart 1",std::set<Medical_Specialty>{},0};
    Semi_Smart_HCP y{100,"Semi Smart 2",std::set<Medical_Specialty>{meds[0],meds[1]},10};
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    y.receive_license(meds[0]);
    x.receive_license(meds[0]);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    y.receive_license(meds[0]);
    x.receive_license(meds[0]);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    y.receive_license(meds[3]);
    x.receive_license(meds[3]);
    y.receive_license(meds[0]);
    x.receive_license(meds[0]);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    y.receive_license(meds[2]);
    x.receive_license(meds[2]);
    y.receive_license(meds[3]);
    x.receive_license(meds[3]);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
  }

  // Task 2
  
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    Special_Hospital sp{{meds[0],meds[1]},"1 and 2"};
    Illness i1{meds[0],"A"};
    Illness i2{meds[1],"AB"};
    Illness i3{meds[2],"A"};
    Illness i4{meds[3],"A"};
    shared_ptr<Patient> p1{std::make_shared<Patient>("Hera",69,std::set<Illness>{i1,i2},0)};
    shared_ptr<Patient> p2{std::make_shared<Patient>("Hera2",69,std::set<Illness>{i1,i2,i3},0)};
    shared_ptr<Patient> p3{std::make_shared<Patient>("Hera2",69,std::set<Illness>{i4,i3},0)};
    cout << sp << std::endl;
    cout << sp.admit_patient(p1) << std::endl;
    cout << sp.admit_patient(p1) << std::endl;
    cout << sp.admit_patient(p2) << std::endl;
    cout << sp.admit_patient(p2) << std::endl;
    cout << sp.admit_patient(p3) << std::endl;
    cout << sp.admit_patient(p3) << std::endl;
    {
      shared_ptr<Patient> p4{std::make_shared<Patient>("Hera4",69,std::set<Illness>{i1},0)};
      cout << sp.admit_patient(p4) << std::endl;
      cout << sp.admit_patient(p4) << std::endl;
    }
    {
      shared_ptr<Patient> p4{std::make_shared<Patient>("Hera4",69,std::set<Illness>{i1},0)};
      cout << sp.admit_patient(p4) << std::endl;
      cout << sp.admit_patient(p4) << std::endl;
    }
      cout << sp << std::endl;
  }
  
	std::cout << "end of Task2" << std::endl;
  // Task 3
  
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    Illness i1{meds[0],"A"};
    Illness i2{meds[1],"AB"};
    Illness i3{meds[2],"A"};
    Illness i4{meds[3],"A"};
    shared_ptr<Patient> p1{std::make_shared<Patient>("Hera",9,std::set<Illness>{i1,i2},10)};
    shared_ptr<Patient> p2{std::make_shared<Patient>("Hera2",69,std::set<Illness>{i1,i2,i3},220)};
    shared_ptr<Patient> p3{std::make_shared<Patient>("Hera2",69,std::set<Illness>{i4,i3},30)};
    shared_ptr<Patient> p4{std::make_shared<Patient>("Hera4",9,std::set<Illness>{i1,i3},1110)};
    vector<weak_ptr<Patient>> v1{p1,p2,p4};
    vector<weak_ptr<Patient>> v2{p1,p2,p3,p4};
    Super_Task st1{{p1,p2,p4}};
    Super_Task st2{{p1,p2,p3,p4}};
    p2.reset();
    std::cout<< "[";
    for(const auto& x : st1.screening({meds[4]}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st2.screening({meds[4]}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st1.screening({meds[0],meds[4]}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st2.screening({meds[4],meds[0]}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st1.screening({meds[1],meds[4]}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st2.screening({meds[4],meds[1]}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st1.screening({}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl << "[";
    for(const auto& x : st2.screening({}))
      std::cout << *x << ",";
    std::cout<< "]"<<std::endl;
  }
  
  // Task 4
  
  {
    const vector meds{Medical_Specialty::Cardiology, Medical_Specialty::Dermatology, Medical_Specialty::Endocrinology, Medical_Specialty::Gynecology, Medical_Specialty::Neurology, Medical_Specialty::Oncology, Medical_Specialty::Pathology, Medical_Specialty::Pediatrics, Medical_Specialty::Pulmonology, Medical_Specialty::Urology};
    shared_ptr<Health_Care_Provider> s1{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 1",std::set<Medical_Specialty>{meds[0],meds[6]},220)};
    shared_ptr<Health_Care_Provider> s2{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 2",std::set<Medical_Specialty>{meds[0],meds[3]},3210)};
    shared_ptr<Health_Care_Provider> s3{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 3",std::set<Medical_Specialty>{meds[2],meds[6],meds[3]},22)};
    shared_ptr<Health_Care_Provider> s4{std::make_shared<Smart_Health_Care_Provider>(100,"Smart 4",std::set<Medical_Specialty>{meds[3],meds[6],meds[5]},44)};
    
    std::cout << "[";
    for(const auto& x : task4({}))
      std::cout << *x << ",";
    std::cout << "]" << std::endl << "[";
    for(const auto& x : task4({s1,s2,s3,s4}))
      std::cout << *x << ",";
    std::cout << "]" << std::endl << "[";
    for(const auto& x : task4({s1,s2}))
      std::cout << *x << ",";
    std::cout << "]" << std::endl << "[";
    for(const auto& x : task4({s3,s4}))
      std::cout << *x << ",";
    std::cout << "]" << std::endl << "[";
    for(const auto& x : task4({s1,s4}))
      std::cout << *x << ",";
    std::cout << "]" << std::endl;
  }
  
}
