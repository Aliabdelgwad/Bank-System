#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;
class clsCurrency
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;
    enMode _Mode;

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector<string> vCurrency = clsString::Split(Line,Seperator);
        return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
    }
    string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string Line;
        Line += Currency.Country() + Seperator;
        Line += Currency.CurrencyCode() + Seperator;
        Line += Currency.CurrencyName() + Seperator;
        Line += to_string(Currency.Rate()) ;
        return Line;
    }
    void _Update()
    {
        vector<clsCurrency> vCurrency = _LoadCurrencyDataFromFile();
        for (clsCurrency& i : vCurrency)
        {
            if (i.CurrencyCode()==CurrencyCode())
            {
                i = *this;
                break;
            }
        }
        SaveCurrencyDataToFile(vCurrency);
    }

    static vector<clsCurrency> _LoadCurrencyDataFromFile()
    {
        fstream MyFile;
        vector<clsCurrency> vCurrency;
        MyFile.open("Currencies.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile,Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                vCurrency.push_back(Currency);
            }
            MyFile.close();
        }
        return vCurrency;
    }
    void SaveCurrencyDataToFile(vector<clsCurrency> vCurrency)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);
        if (MyFile.is_open())
        {
            string Line;
            for (clsCurrency& i : vCurrency)
            {
                Line = _ConvertCurrencyObjectToLine(i);
                MyFile << Line << endl;
            }
            MyFile.close();
        }

    }
    static clsCurrency _GetEmptyCurrencyObject() 
    {

        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }
public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string Country()
    {
        return _Country;
    }
    string CurrencyCode()
    {
        return _CurrencyCode;
    }
    string CurrencyName()
    {
        return _CurrencyName;
    }

    //property Set , Get
    float Rate()
    {
        return _Rate;
    }
    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();
    }
    static clsCurrency FindByCountry(string Country)
    {
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == clsString::UpperAllString(Country))
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();

        }

        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = FindByCode(CurrencyCode);
        return (!Currency.IsEmpty());
    }
    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencyDataFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());

    }
};


