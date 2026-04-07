#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
using namespace std;

const string FileName = "./DataFiles/Currencies.txt";

class clsCurrency
{
    private:
        enum enMode {EmptyMode = 0 , UpdateMode = 1};
        enMode _Mode;
        string _Country;
        string _CurrencyCode;
        string _CurrencyName;
        float _Rate;

        static vector <clsCurrency> _LoadCurrenciesDateFromFile()
        {
            vector <clsCurrency> _vCurrencies;
            fstream MyFile;
            MyFile.open(FileName, ios :: in);
            if(MyFile.is_open())
            {
                string Line;
                while(getline(MyFile,Line))
                {
                    _vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
                }
                MyFile.close();
            }
            return _vCurrencies;
        }

        static void _SaveCurrencnciesDataToFile(vector <clsCurrency> _vCurrencies)
        {
            fstream MyFile;
            MyFile.open(FileName , ios::out);
            if(MyFile.is_open())
            {
                for(clsCurrency & Currency : _vCurrencies)
                {
                    MyFile<<_ConvertCurrencyObjectToLine(Currency)<<endl;
                }
                MyFile.close();
            }
        }

        static string _ConvertCurrencyObjectToLine(clsCurrency Currency,string Seperator = "#//#")
        {
            string stCurrencyRecord = "";
            stCurrencyRecord = stCurrencyRecord + Currency.Country() + Seperator;
            stCurrencyRecord = stCurrencyRecord + Currency.CurrencyCode() + Seperator;
            stCurrencyRecord = stCurrencyRecord + Currency.CurrencyName() + Seperator;
            stCurrencyRecord = stCurrencyRecord + to_string(Currency.Rate());
            
            return stCurrencyRecord;
        }

        static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#")
        {
            vector<string> vCurrencyData;
            vCurrencyData = clsString::Split(Line, Seperator);
            return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
                stod(vCurrencyData[3]));
        }

        static clsCurrency _GetEmptyCurrencyObject()
        {
            return clsCurrency (enMode :: EmptyMode , "","","",0);
        }

        void _Update()
        {
            vector <clsCurrency> _vCurrencies = _LoadCurrenciesDateFromFile();
            for(clsCurrency & Currency :_vCurrencies)
            {
                if(Currency.CurrencyCode() == CurrencyCode() )
                {
                    Currency = *this;
                    break;
                }
            }
            _SaveCurrencnciesDataToFile(_vCurrencies);
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

        float Rate()
        {
            return _Rate; 
        }

        void UpdateRate(float NewRate)
        {
            _Rate = NewRate;
            _Update();
        }

        static bool IsCurrencyExist(string CurrencyCode)
        {
            clsCurrency Currency = FindCurrencyByCode(CurrencyCode);
            return !(Currency.IsEmpty());
        }

        static clsCurrency FindCurrencyByCode(string CurrencyCode)
        {
            vector <clsCurrency> _vCurrencies = _LoadCurrenciesDateFromFile();
            CurrencyCode = clsString :: UpperAllString(CurrencyCode);
            for(clsCurrency Currency : _vCurrencies)
            {
                if(Currency.CurrencyCode() == CurrencyCode)
                {
                    return Currency;
                }
            }
            return _GetEmptyCurrencyObject();
        }

        static clsCurrency FindCurrencyByCountry(string Country)
            {
                vector <clsCurrency> _vCurrencies = _LoadCurrenciesDateFromFile();
                Country = clsString :: UpperFirstLetterOfEachWord(Country);
                for(clsCurrency Currency : _vCurrencies)
                {
                    if(Currency.Country() == Country)
                    {
                        return Currency;
                    }
                }
                return _GetEmptyCurrencyObject();
            }

        static vector<clsCurrency> GetCurrenciesList()
        {
            return _LoadCurrenciesDateFromFile();
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
