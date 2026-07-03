#include "Employee.h"
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

static const string EMPLOYEE_FILE = "data/employees.txt";

EmployeeManager::EmployeeManager()
{
    loadEmployees();
}

bool EmployeeManager::employeeExists(const string &id)
{
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].employeeID == id)
            return true;
    }
    return false;
}

void EmployeeManager::loadEmployees()
{
    employees.clear();
    ifstream fin(EMPLOYEE_FILE.c_str());

    if (!fin)
    {
        ofstream createFile(EMPLOYEE_FILE.c_str());
        createFile.close();
        return;
    }

    string line;
    Employee emp;
    while (getline(fin, line))
    {
        if (line.empty() || line.find("===") != string::npos) continue;

        stringstream ss(line);
        string key, dummy;
        
        ss >> key;
        if (key == "ID:") {
            ss >> emp.employeeID;
        } else if (key == "Name:") {
            ss.ignore(); getline(ss, emp.name);
        } else if (key == "Age:") {
            ss >> emp.age;
        } else if (key == "Gender:") {
            ss >> emp.gender;
        } else if (key == "Dept:") {
            ss.ignore(); getline(ss, emp.department);
        } else if (key == "Desig:") {
            ss.ignore(); getline(ss, emp.designation);
        } else if (key == "JoinDate:") {
            ss >> emp.joiningDate;
        } else if (key == "Phone:") {
            ss >> emp.phone;
        } else if (key == "Email:") {
            ss >> emp.email;
        } else if (key == "Salary:") {
            ss >> emp.basicSalary;
        } else if (key == "HRA:") {
            ss >> emp.hra;
        } else if (key == "DA:") {
            ss >> emp.da;
        } else if (key == "Bonus:") {
            ss >> emp.bonus;
        } else if (key == "OTRate:") {
            ss >> emp.overtimeRate;
        } else if (key == "PF:") {
            ss >> emp.pf;
        } else if (key == "Tax:") {
            ss >> emp.tax;
        } else if (key == "Insurance:") {
            ss >> emp.insurance;
            employees.push_back(emp); // End of employee record block reached
        }
    }
    fin.close();
}

void EmployeeManager::saveEmployees()
{
    ofstream fout(EMPLOYEE_FILE.c_str());
    for (size_t i = 0; i < employees.size(); i++)
    {
        Employee &e = employees[i];
        fout << "========================================\n";
        fout << "ID: " << e.employeeID << "\n";
        fout << "Name: " << e.name << "\n";
        fout << "Age: " << e.age << "\n";
        fout << "Gender: " << e.gender << "\n";
        fout << "Dept: " << e.department << "\n";
        fout << "Desig: " << e.designation << "\n";
        fout << "JoinDate: " << e.joiningDate << "\n";
        fout << "Phone: " << e.phone << "\n";
        fout << "Email: " << e.email << "\n";
        fout << "Salary: " << e.basicSalary << "\n";
        fout << "HRA: " << e.hra << "\n";
        fout << "DA: " << e.da << "\n";
        fout << "Bonus: " << e.bonus << "\n";
        fout << "OTRate: " << e.overtimeRate << "\n";
        fout << "PF: " << e.pf << "\n";
        fout << "Tax: " << e.tax << "\n";
        fout << "Insurance: " << e.insurance << "\n";
    }
    fout.close();
}

void EmployeeManager::addEmployee()
{
    Employee emp;
    cout << "\n========== ADD EMPLOYEE ==========\n";
    cout << "Employee ID : "; cin >> emp.employeeID;

    if (employeeExists(emp.employeeID))
    {
        cout << "\nError: Employee ID already exists.\n";
        return;
    }
    cin.ignore();

    cout << "Name : "; getline(cin, emp.name);
    cout << "Age : "; cin >> emp.age;

    if (emp.age <= 0)
    {
        cout << "Invalid age.\n";
        return;
    }
    cin.ignore();

    cout << "Gender : "; getline(cin, emp.gender);
    cout << "Department : "; getline(cin, emp.department);
    cout << "Designation : "; getline(cin, emp.designation);
    cout << "Date of Joining : "; getline(cin, emp.joiningDate);
    cout << "Phone Number : "; getline(cin, emp.phone);
    cout << "Email Address : "; getline(cin, emp.email);

    cout << "Basic Salary : "; cin >> emp.basicSalary;
    cout << "HRA : "; cin >> emp.hra;
    cout << "DA : "; cin >> emp.da;
    cout << "Bonus : "; cin >> emp.bonus;
    cout << "Overtime Rate : "; cin >> emp.overtimeRate;
    cout << "PF : "; cin >> emp.pf;
    cout << "Tax : "; cin >> emp.tax;
    cout << "Insurance : "; cin >> emp.insurance;

    if (emp.basicSalary < 0 || emp.hra < 0 || emp.da < 0 ||
        emp.bonus < 0 || emp.overtimeRate < 0 ||
        emp.pf < 0 || emp.tax < 0 || emp.insurance < 0)
    {
        cout << "\nSalary values cannot be negative.\n";
        return;
    }

    employees.push_back(emp);
    saveEmployees();
    cout << "\nEmployee added successfully.\n";
}

void EmployeeManager::viewEmployees()
{
    if (employees.empty())
    {
        cout << "\nNo employee records found.\n";
        return;
    }
    cout << "\n================ EMPLOYEE LIST ================\n\n";
    for (size_t i = 0; i < employees.size(); i++)
    {
        Employee &e = employees[i];
        cout << "Employee ID : " << e.employeeID << endl;
        cout << "Name        : " << e.name << endl;
        cout << "Department  : " << e.department << endl;
        cout << "Designation : " << e.designation << endl;
        cout << "Salary      : " << e.basicSalary << endl;
        cout << "-------------------------------------------\n";
    }
}

void EmployeeManager::searchEmployee()
{
    string id;
    cout << "\nEnter Employee ID : "; cin >> id;
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].employeeID == id)
        {
            Employee &e = employees[i];
            cout << "\nEmployee Found\n";
            cout << "Name : " << e.name << endl;
            cout << "Department : " << e.department << endl;
            cout << "Designation : " << e.designation << endl;
            cout << "Salary : " << e.basicSalary << endl;
            return;
        }
    }
    cout << "\nEmployee not found.\n";
}

void EmployeeManager::updateEmployee()
{
    string id;
    cout << "\nEnter Employee ID : "; cin >> id;
    cin.ignore();
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].employeeID == id)
        {
            Employee &e = employees[i];
            cout << "New Name : "; getline(cin, e.name);
            cout << "New Department : "; getline(cin, e.department);
            cout << "New Designation : "; getline(cin, e.designation);
            saveEmployees();
            cout << "\nEmployee updated successfully.\n";
            return;
        }
    }
    cout << "\nEmployee not found.\n";
}

void EmployeeManager::deleteEmployee()
{
    string id;
    cout << "\nEnter Employee ID : "; cin >> id;
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].employeeID == id)
        {
            employees.erase(employees.begin() + i);
            saveEmployees();
            cout << "\nEmployee deleted successfully.\n";
            return;
        }
    }
    cout << "\nEmployee not found.\n";
}

void EmployeeManager::departmentWiseListing()
{
    viewEmployees();
}

void EmployeeManager::searchByDepartment()
{
    string dept;
    cin.ignore();
    cout << "\nDepartment : "; getline(cin, dept);
    bool found = false;
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].department == dept)
        {
            cout << employees[i].employeeID << " - " << employees[i].name << endl;
            found = true;
        }
    }
    if (!found) cout << "No employees found.\n";
}

void EmployeeManager::searchByDesignation()
{
    string des;
    cin.ignore();
    cout << "\nDesignation : "; getline(cin, des);
    bool found = false;
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].designation == des)
        {
            cout << employees[i].employeeID << " - " << employees[i].name << endl;
            found = true;
        }
    }
    if (!found) cout << "No employees found.\n";
}

void EmployeeManager::salaryIncrement()
{
    string id;
    cout << "\nEmployee ID : "; cin >> id;
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].employeeID == id)
        {
            double percent;
            cout << "Increment Percentage : "; cin >> percent;
            if (percent < 0)
            {
                cout << "Invalid percentage.\n";
                return;
            }
            cout << "\nCurrent Salary : " << employees[i].basicSalary << endl;
            employees[i].basicSalary += employees[i].basicSalary * percent / 100.0;
            cout << "New Salary : " << employees[i].basicSalary << endl;
            saveEmployees();
            cout << "\nSalary updated successfully.\n";
            return;
        }
    }
    cout << "\nEmployee not found.\n";
}

Employee* EmployeeManager::getEmployeeByID(const string &id)
{
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].employeeID == id)
            return &employees[i];
    }
    return NULL;
}
