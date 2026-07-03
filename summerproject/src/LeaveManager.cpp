#include "LeaveManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

static const string LEAVE_FILE = "data/leaves.txt";

LeaveManager::LeaveManager()
{
    loadLeaves();
}

void LeaveManager::loadLeaves()
{
    leaveRecords.clear();
    ifstream fin(LEAVE_FILE.c_str());

    if (!fin)
    {
        ofstream createFile(LEAVE_FILE.c_str());
        createFile.close();
        return;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;

        LeaveRecord record;
        string dummy;
        stringstream ss(line);

        // Parsing format: ID: 1 | Paid Leave: 5 | Casual Leave: 2 | Sick Leave: 1 | Unpaid Leave: 0
        ss >> dummy >> record.employeeID;
        ss >> dummy >> dummy >> dummy >> record.paidLeave;
        ss >> dummy >> dummy >> dummy >> record.casualLeave;
        ss >> dummy >> dummy >> dummy >> record.sickLeave;
        ss >> dummy >> dummy >> dummy >> record.unpaidLeave;

        if (!record.employeeID.empty()) {
            leaveRecords.push_back(record);
        }
    }
    fin.close();
}

void LeaveManager::saveLeaves()
{
    ofstream fout(LEAVE_FILE.c_str());
    for (size_t i = 0; i < leaveRecords.size(); i++)
    {
        LeaveRecord &r = leaveRecords[i];
        fout << "ID: " << r.employeeID 
             << " | Paid Leave: " << r.paidLeave 
             << " | Casual Leave: " << r.casualLeave 
             << " | Sick Leave: " << r.sickLeave 
             << " | Unpaid Leave: " << r.unpaidLeave << endl;
    }
    fout.close();
}

int LeaveManager::findLeaveIndex(const string &employeeID)
{
    for (size_t i = 0; i < leaveRecords.size(); i++)
    {
        if (leaveRecords[i].employeeID == employeeID)
            return (int)i;
    }
    return -1;
}

void LeaveManager::manageLeaves()
{
    LeaveRecord record;
    cout << "\n========== MANAGE LEAVES ==========\n";
    cout << "Employee ID: "; cin >> record.employeeID;
    cout << "Paid Leave: "; cin >> record.paidLeave;
    cout << "Casual Leave: "; cin >> record.casualLeave;
    cout << "Sick Leave: "; cin >> record.sickLeave;
    cout << "Unpaid Leave: "; cin >> record.unpaidLeave;

    if (record.paidLeave < 0 || record.casualLeave < 0 || record.sickLeave < 0 || record.unpaidLeave < 0)
    {
        cout << "\nError: Leave values cannot be negative.\n";
        return;
    }

    int index = findLeaveIndex(record.employeeID);
    if (index != -1)
    {
        leaveRecords[index] = record;
        cout << "\nLeave record updated successfully.\n";
    }
    else
    {
        leaveRecords.push_back(record);
        cout << "\nLeave record added successfully.\n";
    }
    saveLeaves();
}

void LeaveManager::viewLeaves()
{
    if (leaveRecords.empty())
    {
        cout << "\nNo leave records found.\n";
        return;
    }

    cout << "\n================ LEAVE RECORDS ================\n\n";
    cout << left << setw(12) << "Emp ID" << setw(10) << "Paid" << setw(10) << "Casual"
         << setw(10) << "Sick" << setw(10) << "Unpaid" << endl;
    cout << "------------------------------------------------------\n";

    for (size_t i = 0; i < leaveRecords.size(); i++)
    {
        LeaveRecord &r = leaveRecords[i];
        cout << left << setw(12) << r.employeeID << setw(10) << r.paidLeave << setw(10) << r.casualLeave
             << setw(10) << r.sickLeave << setw(10) << r.unpaidLeave << endl;
    }
}

LeaveRecord* LeaveManager::getLeaveRecord(const string &employeeID)
{
    int index = findLeaveIndex(employeeID);
    if (index == -1) return NULL;
    return &leaveRecords[index];
}
