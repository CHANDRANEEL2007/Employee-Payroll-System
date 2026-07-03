#ifndef LEAVEMANAGER_H
#define LEAVEMANAGER_H

#include <string>
#include <vector>

using namespace std;

struct LeaveRecord
{
    string employeeID;
    int paidLeave;
    int casualLeave;
    int sickLeave;
    int unpaidLeave;
};

class LeaveManager
{
private:
    vector<LeaveRecord> leaveRecords;

    void loadLeaves();
    void saveLeaves();
    int findLeaveIndex(const string &employeeID);

public:
    LeaveManager();
    void manageLeaves();
    void viewLeaves();
    LeaveRecord* getLeaveRecord(const string &employeeID);
};

#endif
