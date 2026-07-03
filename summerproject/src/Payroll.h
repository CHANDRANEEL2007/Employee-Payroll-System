#ifndef PAYROLL_H
#define PAYROLL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Employee.h"
#include "Attendance.h"
#include "PayrollHistory.h"

using namespace std;

class Payroll
{
private:
    vector<string> payrollRecords;
    string PAYROLL_FILE;

    void savePayslip(string payslip);
    string getCurrentDate();

public:
    Payroll();

    void processMonthlyPayroll(
        EmployeeManager &employeeManager,
        AttendanceManager &attendanceManager,
        PayrollHistory &history
    );

    void generatePayslip(
        Employee &employee,
        Attendance &attendance,
        string month,
        PayrollHistory &history
    );

    void viewPayroll();
};

#endif
