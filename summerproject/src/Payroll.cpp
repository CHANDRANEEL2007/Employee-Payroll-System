#include "Payroll.h"
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

Payroll::Payroll()
{
    PAYROLL_FILE = "data/payroll.txt";
}

string Payroll::getCurrentDate()
{
    time_t now = time(0);
    tm *current = localtime(&now);
    stringstream dateStream;
    if (current != NULL) {
        dateStream << current->tm_mday << "-" 
                   << (current->tm_mon + 1) << "-" 
                   << (current->tm_year + 1900);
    } else {
        dateStream << "02-07-2026";
    }
    return dateStream.str();
}

void Payroll::savePayslip(string payslip)
{
    ofstream fout(PAYROLL_FILE.c_str(), ios::app);
    if (fout) {
        fout << payslip << "\n\n";
        fout.close();
    }
}

void Payroll::processMonthlyPayroll(
        EmployeeManager &employeeManager,
        AttendanceManager &attendanceManager,
        PayrollHistory &history)
{
    string id;
    cout << "\n========== PROCESS PAYROLL ==========\n";
    cout << "Employee ID : "; cin >> id;

    Employee *employee = employeeManager.getEmployeeByID(id);
    if(employee == NULL)
    {
        cout << "\nEmployee not found.\n";
        return;
    }

    Attendance *attendance = attendanceManager.getAttendanceByEmployeeID(id);
    if(attendance == NULL)
    {
        cout << "\nAttendance record not found.\n";
        return;
    }

    string month;
    cout << "Payroll Month : "; cin >> month;

    generatePayslip(*employee, *attendance, month, history);
}

void Payroll::generatePayslip(
        Employee &employee,
        Attendance &attendance,
        string month,
        PayrollHistory &history)
{
    double perDaySalary = employee.basicSalary / (attendance.workingDays > 0 ? attendance.workingDays : 1);
    double absentDays = attendance.workingDays - attendance.daysPresent;
    if(absentDays < 0) absentDays = 0;

    double attendanceDeduction = absentDays * perDaySalary;
    double overtimePay = attendance.overtimeHours * employee.overtimeRate;

    double grossSalary = employee.basicSalary + employee.hra + employee.da + employee.bonus + overtimePay;
    double totalDeduction = attendanceDeduction + employee.pf + employee.tax + employee.insurance;
    double netSalary = grossSalary - totalDeduction;

    stringstream slip;
    slip << "\n====================================================\n"
         << "              EMPLOYEE PAYROLL SLIP                 \n"
         << "====================================================\n"
         << left
         << setw(25) << "Company Name"  << ": TECH SOLUTIONS\n"
         << setw(25) << "Employee ID"   << ": " << employee.employeeID << "\n"
         << setw(25) << "Employee Name" << ": " << employee.name << "\n"
         << setw(25) << "Department"    << ": " << employee.department << "\n"
         << setw(25) << "Designation"   << ": " << employee.designation << "\n"
         << setw(25) << "Payroll Month" << ": " << month << "\n"
         << setw(25) << "Current Date"  << ": " << getCurrentDate() << "\n"
         << "----------------------------------------------------\n"
         << setw(25) << "Basic Salary"  << ": " << employee.basicSalary << "\n"
         << setw(25) << "HRA"           << ": " << employee.hra << "\n"
         << setw(25) << "DA"            << ": " << employee.da << "\n"
         << setw(25) << "Bonus"         << ": " << employee.bonus << "\n"
         << setw(25) << "Overtime Pay"  << ": " << overtimePay << "\n"
         << setw(25) << "Gross Salary"   << ": " << grossSalary << "\n"
         << "----------------------------------------------------\n"
         << setw(25) << "Attendance Deduction" << ": " << attendanceDeduction << "\n"
         << setw(25) << "PF"            << ": " << employee.pf << "\n"
         << setw(25) << "Tax"           << ": " << employee.tax << "\n"
         << setw(25) << "Insurance"     << ": " << employee.insurance << "\n"
         << setw(25) << "Net Salary"     << ": " << netSalary << "\n"
         << "====================================================\n";

    savePayslip(slip.str());

    PayrollRecord record(employee.employeeID, employee.name, month, grossSalary, totalDeduction, netSalary);
    history.addHistory(record);

    cout << slip.str() << "\nPayslip generated successfully.\n";
}

void Payroll::viewPayroll()
{
    ifstream fin(PAYROLL_FILE.c_str());
    if(!fin)
    {
        cout << "\nNo payroll records available.\n";
        return;
    }

    string line;
    cout << "\n================ PAYROLL RECORDS ================\n";
    while(getline(fin, line))
    {
        cout << line << endl;
    }
    fin.close();
}
