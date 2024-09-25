#pragma once
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionScreen:protected clsScreen
{
private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer = 4, 
        eTransferLog = 5, eShowMainMenue = 6
	};
    static int  _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }
    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalanceScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }
    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }
    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions)
    {
        switch (TransactionsMenueOptions)
        {
        case clsTransactionScreen::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        case clsTransactionScreen::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        case clsTransactionScreen::eShowTotalBalance:
            system("cls");
            _ShowTotalBalanceScreen();
            _GoBackToTransactionsMenue();
            break;
        case clsTransactionScreen::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        case clsTransactionScreen::eTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
            
        case clsTransactionScreen::eShowMainMenue:
            break;
        default:
            break;
        }
    }
public:
    static void ShowTransactionsMenue()
    {


        system("cls");
        if (!CheckAccessRight(clsUser::enPermissions::pTranactions))
        {
            return;
        }
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }
};

