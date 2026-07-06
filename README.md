The structure of the project looks like:
```text
summerproject/
│
├── src/
│   ├── main.cpp
│   ├── Employee.cpp
│   ├── Employee.h
│   ├── Attendance.cpp
│   ├── Attendance.h
│   ├── LeaveManager.cpp
│   ├── LeaveManager.h
│   ├── Payroll.cpp
│   ├── Payroll.h
│   ├── Login.cpp
│   ├── Login.h
│   ├── PayrollHistory.cpp
│   ├── PayrollHistory.h
│   └── Utilities.h
│
└── data/
    ├── employees.txt
    ├── attendance.txt
    ├── leaves.txt
    ├── payroll.txt
    └── payroll_history.txt
```



The console application can perform operations such as :

1. Secure Admin Login
2. Add Employee
3. View All Employees
4. Search Employee
5. Update Employee Details
6. Delete Employee
7. Record Employee Attendance
8. Manage Employee Leaves
9. Process Monthly Payroll
10. Generate Employee Payslip
11. View Payroll History
12. Display Department-wise Employee List
13. Search Employees by Department
14. Search Employees by Designation
15. Apply Salary Increment
16. Exit System

This project can easily be run on CMD.
Steps:
1.Go to the folder and open the terminal.
2.Compile it using the command :
g++ -o EmployeePayrollSystem.exe main.cpp src/Employee.cpp src/Attendance.cpp src/LeaveManager.cpp src/Payroll.cpp src/Login.cpp src/PayrollHistory.cpp -static-libgcc -g3
3.Finally run the command:
.\EmployeePayrollSystem.exe


Here in this project the login credentials are:
Username: admin
Password: admin123



This project includes an interactive browser-based demo of the Employee Payroll System.
The link for the demo is as follows:



https://chandraneel2007.github.io/Employee-Payroll-System/
