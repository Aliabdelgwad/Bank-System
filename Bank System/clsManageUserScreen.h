#pragma once
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUserScreen :protected clsScreen
{
private:
    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };
    static int  _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }
    static void _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowManageUsersMenue();
    }
    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();

    }
    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowUpdateUserScreen();
    }
    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersOptions)
    {
        switch (ManageUsersOptions)
        {
        case clsManageUserScreen::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUserScreen::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUserScreen::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUserScreen::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUserScreen::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        case clsManageUserScreen::eMainMenue:
            break;
        default:
            break;
        }
    }
public:


    static void ShowManageUsersMenue()
    {

        system("cls");
        if (!CheckAccessRight(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
    }


};

