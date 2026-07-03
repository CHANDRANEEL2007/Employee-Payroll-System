#ifndef PAYROLL_HISTORY_H
#define PAYROLL_HISTORY_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PayrollRecord
{
private:
    string employeeID;
    string employeeName;
    string payrollMonth;
    double grossSalary;
    double deduction;
    double netSalary;

public:
    PayrollRecord();
    PayrollRecord(string id, string name, string month, double gross, double deduct, double net);

    string getEmployeeID() const;
    string getEmployeeName() const;
    string getPayrollMonth() const;
    double getNetSalary() const;
};

class PayrollHistory
{
private:
    vector<PayrollRecord> records;
    string payrollHistoryFile;

    void saveHistory();
    void viewPayrollHistory();

public:
    PayrollHistory();
    void addHistory(PayrollRecord record);
    void viewHistory();
};

#endif
