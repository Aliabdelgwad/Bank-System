#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferScreen :protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";        
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cin >> AccountNumber;
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }
        return AccountNumber;
    }
    static double _ReadAmount(clsBankClient SourceClient)
    {
        cout << "\nPlease enter Transfer amount? ";
        double Amount = clsInputValidate::ReadDblNumber();

        while (SourceClient.AccountBalance < Amount)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t Transfer Screen");

        cout << "\nPlease Enter Account Number to Transfer From: ";
        string AccountNumber = _ReadAccountNumber();
        clsBankClient SourceClient = clsBankClient::Find(AccountNumber);;
        _PrintClient(SourceClient);

        cout << "\nPlease Enter Account Number to Transfer To: ";
        AccountNumber = _ReadAccountNumber();
        clsBankClient DestinationClient = clsBankClient::Find(AccountNumber);
        _PrintClient(DestinationClient);

        double Amount = _ReadAmount(SourceClient);
        cout << "\nAre you sure you want to perform this operation? y/n?";
        char Answer = 'n';
        cin >> Answer;
        
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient))
            {
                cout << "\nTransfer done Successfully.\n";
                
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
            
        }
        else
        {
            cout << "\nOperation was cancelled.\n\n\n";
           
        }
        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);

    }
};

