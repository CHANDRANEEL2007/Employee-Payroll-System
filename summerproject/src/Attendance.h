#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Attendance
{
public:
    string employeeID;
    int workingDays;
    int daysPresent;
    int paidLeaves;
    int unpaidLeaves;
    double overtimeHours;

public:
    Attendance();
    Attendance(string id, int work, int present, int paid, int unpaid, double overtime);
};

class AttendanceManager
{
private:
    vector<Attendance> attendanceRecords;
    string ATTENDANCE_FILE;

    void loadAttendance();
    void saveAttendance();
    int findAttendanceIndex(const string &employeeID);

public:
    AttendanceManager();
    void recordAttendance();
    void viewAttendance();
    Attendance* getAttendanceByEmployeeID(const string &employeeID);
};

#endif
