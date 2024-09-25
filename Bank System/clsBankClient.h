#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>
using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;
    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        stTrnsferLogRecord LoginRegister;
        LoginRegister.DateTime = vUserData[0];
        LoginRegister.SourceAccountNumber = vUserData[1];
        LoginRegister.DestinationAccountNumber = vUserData[2];
        LoginRegister.Amount = stoi(vUserData[3]);
        LoginRegister.SourceAccountBalance = stoi(vUserData[4]);
        LoginRegister.DestinationAccountBalance = stoi(vUserData[5]);
        LoginRegister.UserName = vUserData[6];
        return LoginRegister;
    }



    string _PrepareTransferLoginRecord(double Amount,clsBankClient DestinationClient,string Seperator = "#//#")
    {

        string Line = "";
        Line += clsDate::GetSystemDateTimeString() + Seperator;
        Line += _AccountNumber + Seperator;
        Line += DestinationClient._AccountNumber + Seperator;
        Line += to_string(Amount) + Seperator;
        Line += to_string(_AccountBalance) + Seperator;
        Line += to_string(DestinationClient._AccountBalance) + Seperator;
        Line += CurrentUser.UserName;
        return Line;
    }
    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient)
    {
        fstream MyFile;
        string DataLine = _PrepareTransferLoginRecord(Amount, DestinationClient);
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }
    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5],3), stof(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += clsUtil::EncryptText(Client.PinCode,3) + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }
    
    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C._MarkForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double SourceAccountBalance;
        double DestinationAccountBalance;
        string UserName;
    };

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists =2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {
            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::AddNewMode:
        {
            if (IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }


        }


        }



    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient GetAddNewClient(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& i : vClients)
        {
            if (i.AccountNumber()==AccountNumber())
            {
                i._MarkForDelete = true;
                break;
            }
        }
        _SaveCleintsDataToFile(vClients);
        *this = _GetEmptyClientObject();
        return true;

    }
    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalance()
    {
        vector <clsBankClient> vClient = GetClientsList();
        double TotalBalance = 0;
        for (clsBankClient& i : vClient)
        {
            TotalBalance += i.AccountBalance;
        }
        return TotalBalance;
    }

     void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }
     bool Withdraw(double Amount)
     {
         if (Amount> _AccountBalance)
         {
             return false;
         }
         else
         {
             _AccountBalance -= Amount;
             Save();
         }
         
     }

     bool Transfer(double Amount, clsBankClient &DestinationClient)
     {
         if (Amount>AccountBalance)
         {
             return false;
         }
         else
         {
             Withdraw(Amount);
             DestinationClient.Deposit(Amount);
             _RegisterTransferLog(Amount, DestinationClient);
             return true;
         }
     }

     static vector<stTrnsferLogRecord > GetTransfersLogList()
     {
         vector <stTrnsferLogRecord> vTransferLog;

         fstream MyFile;
         MyFile.open("TransferLog.txt", ios::in);//read Mode

         if (MyFile.is_open())
         {

             string Line;


             while (getline(MyFile, Line))
             {

                 stTrnsferLogRecord TransferRecord = _ConvertTransferLogLineToRecord(Line);

                 vTransferLog.push_back(TransferRecord);
             }

             MyFile.close();

         }

         return vTransferLog;
     }
};

