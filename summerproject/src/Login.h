#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>

using namespace std;

class Login
{
private:
    string username;
    string password;
    string getHiddenPassword();

public:
    Login();
    bool authenticate();
};

#endif
