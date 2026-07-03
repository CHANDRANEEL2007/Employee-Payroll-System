#include "Login.h"
#include <conio.h>

using namespace std;

Login::Login()
{
    username = "admin";
    password = "admin123";
}

string Login::getHiddenPassword()
{
    string pass = "";
    char ch;

    while(true)
    {
        ch = getch();
        if(ch == 13) // Enter key
        {
            break;
        }
        else if(ch == 8) // Backspace key
        {
            if(pass.length() > 0)
            {
                pass.erase(pass.length()-1);
                cout << "\b \b";
            }
        }
        else
        {
            pass += ch;
            cout << "*";
        }
    }
    return pass;
}

bool Login::authenticate()
{
    int attempts = 0;
    while(attempts < 3)
    {
        string user;
        cout << "\n====================================\n";
        cout << "     EMPLOYEE PAYROLL SYSTEM LOGIN\n";
        cout << "====================================\n";
        cout << "Username : "; cin >> user;
        cout << "Password : "; string pass = getHiddenPassword();
        cout << endl;

        if(user == username && pass == password)
        {
            cout << "\nLogin successful.\n";
            return true;
        }

        attempts++;
        cout << "\nInvalid username or password.\n";
        cout << "Attempts remaining : " << 3 - attempts << endl;
    }

    cout << "\nMaximum login attempts exceeded.\nSystem terminated.\n";
    return false;
}
