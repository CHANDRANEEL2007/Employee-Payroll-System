#include <iostream>

#include "Login.h"
#include "Employee.h"
#include "Attendance.h"
#include "LeaveManager.h"
#include "Payroll.h"
#include "PayrollHistory.h"

using namespace std;

void displayDashboard()
{
    cout << "\n=================================================\n";
    cout << "        EMPLOYEE PAYROLL MANAGEMENT SYSTEM        \n";
    cout << "=================================================\n";

    cout << "1. Add Employee\n";
    cout << "2. View All Employees\n";
    cout << "3. Search Employee\n";
    cout << "4. Update Employee\n";
    cout << "5. Delete Employee\n";
    cout << "6. Record Attendance\n";
    cout << "7. Manage Leaves\n";
    cout << "8. Process Monthly Payroll\n";
    cout << "9. View Generated Payslips\n";
    cout << "10. View Payroll History\n";
    cout << "11. Department-wise Employee Listing\n";
    cout << "12. Search by Department\n";
    cout << "13. Search by Designation\n";
    cout << "14. Salary Increment\n";
    cout << "15. Exit\n";

    cout << "=================================================\n";
}

int main()
{
    Login login;

    if(!login.authenticate())
    {
        return 0;
    }

    EmployeeManager employeeManager;
    AttendanceManager attendanceManager;
    LeaveManager leaveManager;
    PayrollHistory history;
    Payroll payroll;

    int choice;

    do
    {
        displayDashboard();

        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                employeeManager.addEmployee();
                break;

            case 2:
                employeeManager.viewEmployees();
                break;

            case 3:
                employeeManager.searchEmployee();
                break;

            case 4:
                employeeManager.updateEmployee();
                break;

            case 5:
                employeeManager.deleteEmployee();
                break;

            case 6:
                attendanceManager.recordAttendance();
                break;

            case 7:
                leaveManager.manageLeaves();
                break;

            case 8:
                payroll.processMonthlyPayroll(
                    employeeManager,
                    attendanceManager,
                    history
                );
                break;

            case 9:
                payroll.viewPayroll();
                break;

            case 10:
                history.viewHistory();
                break;

            case 11:
                employeeManager.departmentWiseListing();
                break;

            case 12:
                employeeManager.searchByDepartment();
                break;

            case 13:
                employeeManager.searchByDesignation();
                break;

            case 14:
                employeeManager.salaryIncrement();
                break;

            case 15:
                cout << "\nThank you for using Payroll System.\n";
                break;

            default:
                cout << "\nInvalid menu choice.\n";
        }

    } while(choice != 15);

    return 0;
}
