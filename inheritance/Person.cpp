#include "Person.h"

#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;

/*
I've included stringstreams to be used as I was testing if the code would run differently
while bug testing for errors. I have left its use in Customer::toString().

Note: Most of the comments I have made are done in the Person.h file.
*/

Person::Person(const char* name){
	name_ = name;
}

Person::Person(const std::string& name) : name_(name){
}

Person::~Person(){
}

std::string Person::name() const{
	return name_;
}

std::ostream& operator<<(std::ostream& o, const Person& p){
	o << p.toString() << "\n";
	return o;
}

Customer::Customer(const char* name, unsigned int customerId) : Person(name), id_(customerId){
}

Customer::Customer(const std::string& name, unsigned int customerId) : Person(name), id_(customerId){
}

Customer::~Customer(){
}

void Customer::addOrder(unsigned int order){
	orders_.resize(orders_.size()+1);
	orders_[orders_.size()-1] = order;
}

unsigned int Customer::getOrder(unsigned int i){
	if(i >= orders_.size()) return 0;
	return orders_[i];
}

unsigned int Customer::id() const{
	return id_;
}

std::string Customer::type() const {
	return "Customer";
}

std::string Customer::toString() const{
	stringstream customer;
	uint c(0);
	customer << "[" << this->name() << ", " << to_string(this->id());
	while(c < orders_.size()) {
		if(c < orders_.size()) customer << ", ";
		customer << this->orders_[c];
		c++;
	}
	customer << "]";
	return customer.str();
}

Employee::Employee(const char* name, double salary) : Person(name), income(salary){
}

Employee::Employee(const std::string& name, double salary) : Person(name), income(salary){
}

Employee::~Employee(){
}

void Employee::increaseSalaryBy(double amount){
	income += amount;
}

double Employee::salary()const{
	return income;
}


Manager::Manager(const char* name, double salary) : Employee(name, salary){
}

Manager::Manager(const std::string& name, double salary) : Employee(name, salary){
}

Manager::~Manager(){
}

std::string Manager::type() const {
	return "Manager";
}

std::string Manager::toString() const{
	return "["+this->name()+", earns: "+to_string(this->salary())+"]";
}

Consultant::Consultant(const char* name, double salary) : Employee(name, salary){
}

Consultant::Consultant(const std::string& name, double salary) : Employee(name, salary){
}

Consultant::~Consultant(){
}

void Consultant::setManager(Manager* manager){
	this->manager = manager;
}

std::string Consultant::getManagerName() const{
	if(manager == nullptr) return "";
	return manager->name();
}

std::string Consultant::type() const {
	return "Consultant";
}

std::string Consultant::toString() const{
	string consultant = "";
	consultant = "["+this->name()+", earns: "+to_string(this->salary());
	if(this->getManagerName() != "") consultant+=", Manager: "+this->getManagerName();
	return consultant+"]";
}
