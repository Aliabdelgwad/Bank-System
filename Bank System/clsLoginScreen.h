#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
class clsLoginScreen:protected clsScreen
{
private:
    static bool _Login()
    {
        string UserName, Password;
        bool LoginFailed = false;
        short Trial = 3;
        do
        {
            if (LoginFailed)
            {
                Trial--;
                cout << "\nInvalid UserName/Password! ";
                cout << "\nYou have " << Trial << " Trials to login\n\n";
            }
            if (Trial==0)
            {
                cout << "\n\nYour are Locked after 3 faild trials  ";
                return false;
            }
            cout << "Enter User Name : ";
            UserName = clsInputValidate::ReadString();
            cout << "\nEnter Password : ";
            Password = clsInputValidate::ReadString();
            
            CurrentUser = clsUser::Find(UserName, Password);
            LoginFailed = (CurrentUser.IsEmpty());
        } while (LoginFailed);
        CurrentUser.RegisterLogIn();
            clsMainScreen::ShowMainMenue();
            return true;
        
    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t\tLogin Screen");
        return _Login();
    }
};

