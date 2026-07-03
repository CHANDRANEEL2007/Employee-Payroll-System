#include "PayrollHistory.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

PayrollRecord::PayrollRecord() 
{
    grossSalary = 0.0;
    deduction = 0.0;
    netSalary = 0.0;
}

PayrollRecord::PayrollRecord(string id, string name, string month, double gross, double deduct, double net) 
{
    employeeID = id; 
    employeeName = name; 
    payrollMonth = month;
    grossSalary = gross; 
    deduction = deduct; 
    netSalary = net;
}

string PayrollRecord::getEmployeeID() const { return employeeID; }
string PayrollRecord::getEmployeeName() const { return employeeName; }
string PayrollRecord::getPayrollMonth() const { return payrollMonth; }
double PayrollRecord::getNetSalary() const { return netSalary; }

PayrollHistory::PayrollHistory()
{
    payrollHistoryFile = "data/payroll_history.txt";
    ifstream fin(payrollHistoryFile.c_str());
    if (!fin)
    {
        ofstream fout(payrollHistoryFile.c_str());
        fout.close();
    }
    else
    {
        fin.close();
    }
}

void PayrollHistory::addHistory(PayrollRecord record)
{
    records.push_back(record);
    saveHistory();
}

void PayrollHistory::viewHistory()
{
    viewPayrollHistory();
}

/*
    Updated File Storage Scheme: Highly human-readable text block labels
*/
void PayrollHistory::saveHistory()
{
    ofstream fout(payrollHistoryFile.c_str(), ios::app);
    if (!fout) return;

    for (size_t i = 0; i < records.size(); i++)
    {
        fout << "====================================================\n";
        fout << "HIST_ID      : " << records[i].getEmployeeID() << "\n";
        fout << "HIST_NAME    : " << records[i].getEmployeeName() << "\n";
        fout << "HIST_MONTH   : " << records[i].getPayrollMonth() << "\n";
        fout << "HIST_NETPAY  : " << records[i].getNetSalary() << "\n";
    }
    fout.close();
    records.clear(); 
}

void PayrollHistory::viewPayrollHistory()
{
    ifstream fin(payrollHistoryFile.c_str());
    if (!fin)
    {
        cout << "\nUnable to open payroll history file." << endl;
        return;
    }

    cout << "\n==============================================================" << endl;
    cout << "                  ARCHIVED PAYROLL HISTORY" << endl;
    cout << "==============================================================" << endl;

    string line;
    bool found = false;
    while (getline(fin, line))
    {
        cout << line << endl;
        found = true;
    }

    if (!found)
    {
        cout << "No payroll history available." << endl;
    }
    cout << "==============================================================" << endl;
    fin.close();
}
