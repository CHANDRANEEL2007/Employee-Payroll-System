#include "Attendance.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

Attendance::Attendance()
{
    workingDays = 0;
    daysPresent = 0;
    paidLeaves = 0;
    unpaidLeaves = 0;
    overtimeHours = 0.0;
}

Attendance::Attendance(string id, int work, int present, int paid, int unpaid, double overtime)
{
    employeeID = id;
    workingDays = work;
    daysPresent = present;
    paidLeaves = paid;
    unpaidLeaves = unpaid;
    overtimeHours = overtime;
}

AttendanceManager::AttendanceManager()
{
    ATTENDANCE_FILE = "data/attendance.txt";
    loadAttendance();
}

void AttendanceManager::loadAttendance()
{
    attendanceRecords.clear();
    ifstream fin(ATTENDANCE_FILE.c_str());

    if (!fin)
    {
        ofstream createFile(ATTENDANCE_FILE.c_str());
        createFile.close();
        return;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.empty()) continue;

        Attendance record;
        string dummy;
        stringstream ss(line);

        // Parsing format: ID: 1 | Work Days: 30 | Present: 28 | Paid Leave: 1 | Unpaid Leave: 1 | Overtime: 2
        ss >> dummy >> record.employeeID; // "ID:" and value
        ss >> dummy >> dummy >> dummy >> record.workingDays; // " |", "Work", "Days:", value
        ss >> dummy >> dummy >> record.daysPresent; // " |", "Present:", value
        ss >> dummy >> dummy >> dummy >> record.paidLeaves; // " |", "Paid", "Leave:", value
        ss >> dummy >> dummy >> dummy >> record.unpaidLeaves; // " |", "Unpaid", "Leave:", value
        ss >> dummy >> dummy >> record.overtimeHours; // " |", "Overtime:", value

        if (!record.employeeID.empty()) {
            attendanceRecords.push_back(record);
        }
    }
    fin.close();
}

void AttendanceManager::saveAttendance()
{
    ofstream fout(ATTENDANCE_FILE.c_str());
    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
        Attendance &r = attendanceRecords[i];
        fout << "ID: " << r.employeeID 
             << " | Work Days: " << r.workingDays 
             << " | Present: " << r.daysPresent 
             << " | Paid Leave: " << r.paidLeaves 
             << " | Unpaid Leave: " << r.unpaidLeaves 
             << " | Overtime: " << r.overtimeHours << endl;
    }
    fout.close();
}

int AttendanceManager::findAttendanceIndex(const string &employeeID)
{
    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
        if (attendanceRecords[i].employeeID == employeeID)
            return (int)i;
    }
    return -1;
}

void AttendanceManager::recordAttendance()
{
    Attendance record;
    cout << "\n========== RECORD ATTENDANCE ==========\n";
    cout << "Employee ID: "; cin >> record.employeeID;
    cout << "Working Days: "; cin >> record.workingDays;
    cout << "Days Present: "; cin >> record.daysPresent;
    cout << "Paid Leaves: "; cin >> record.paidLeaves;
    cout << "Unpaid Leaves: "; cin >> record.unpaidLeaves;
    cout << "Overtime Hours: "; cin >> record.overtimeHours;

    if (record.workingDays <= 0)
    {
        cout << "\nError: Working days must be greater than zero.\n";
        return;
    }

    if (record.daysPresent < 0 || record.paidLeaves < 0 || record.unpaidLeaves < 0 || record.overtimeHours < 0)
    {
        cout << "\nError: Negative values are not allowed.\n";
        return;
    }

    if (record.daysPresent + record.paidLeaves + record.unpaidLeaves > record.workingDays)
    {
        cout << "\nError: Attendance exceeds total working days.\n";
        return;
    }

    int index = findAttendanceIndex(record.employeeID);
    if (index != -1)
    {
        attendanceRecords[index] = record;
        cout << "\nAttendance updated successfully.\n";
    }
    else
    {
        attendanceRecords.push_back(record);
        cout << "\nAttendance recorded successfully.\n";
    }
    saveAttendance();
}

void AttendanceManager::viewAttendance()
{
    if (attendanceRecords.empty())
    {
        cout << "\nNo attendance records found.\n";
        return;
    }

    cout << "\n================ ATTENDANCE RECORDS ================\n\n";
    cout << left << setw(12) << "Emp ID" << setw(10) << "Work" << setw(10) << "Present"
         << setw(10) << "Paid" << setw(10) << "Unpaid" << setw(12) << "Overtime" << endl;
    cout << "--------------------------------------------------------------\n";

    for (size_t i = 0; i < attendanceRecords.size(); i++)
    {
        Attendance &r = attendanceRecords[i];
        cout << left << setw(12) << r.employeeID << setw(10) << r.workingDays << setw(10) << r.daysPresent
             << setw(10) << r.paidLeaves << setw(10) << r.unpaidLeaves << setw(12) << r.overtimeHours << endl;
    }
}

Attendance* AttendanceManager::getAttendanceByEmployeeID(const string &employeeID)
{
    int index = findAttendanceIndex(employeeID);
    if (index == -1) return NULL;
    return &attendanceRecords[index];
}
