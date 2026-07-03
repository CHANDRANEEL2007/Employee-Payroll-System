#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Employee
{
    string employeeID;
    string name;
    int age;
    string gender;
    string department;
    string designation;
    string joiningDate;
    string phone;
    string email;

    double basicSalary;
    double hra;
    double da;
    double bonus;
    double overtimeRate;
    double pf;
    double tax;
    double insurance;
};

class EmployeeManager
{
private:
    vector<Employee> employees;

    bool employeeExists(const string &id);
    void loadEmployees();
    void saveEmployees();

public:
    EmployeeManager();

    void addEmployee();
    void viewEmployees();
    void searchEmployee();
    void updateEmployee();
    void deleteEmployee();

    void departmentWiseListing();
    void searchByDepartment();
    void searchByDesignation();

    void salaryIncrement();

    Employee* getEmployeeByID(const string &id);
};

#endif
