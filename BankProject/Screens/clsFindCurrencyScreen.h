#pragma once 
#include <iostream>
#include "../Logic/clsCurrency.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
    private:
        static void _PrintCurrency(clsCurrency Currency)
        {
            cout<<"\n Currency Card:";
            cout<<"\n_____________________________\n";
            cout<<"\nCountry    : "<<Currency.Country();
            cout<<"\nCode       : "<<Currency.CurrencyCode();
            cout<<"\nName       : "<<Currency.CurrencyName();
            cout<<"\nRate(1$) = : "<<Currency.Rate();
            cout<<"\n_____________________________\n"<<endl;
        }

        static void _ShowResults(clsCurrency Currency)
        {
            if (!Currency.IsEmpty())
            {
                cout << "\nCurrency Found :-)\n";
                _PrintCurrency(Currency);
            }
            else
            {
                cout << "\nCurrency Was not Found :-(\n";
            }
        }

    public:
        static void ShowFindCurrencyScreen()
        {
            _DrawScreenHeader("\t Find Currency Screen");
        
            cout<<"\nFind By: [1] Code or [2] Country: ";
            short Answer = 1;
            cin>>Answer;
            
            if (Answer == 1)
            {
                string CurrencyCode;
                cout << "\nPlease Enter Currency Code: ";
                CurrencyCode = clsInputValidate::ReadString();
                clsCurrency Currency = clsCurrency::FindCurrencyByCode(CurrencyCode);
                _ShowResults(Currency);
            }
            else
            {
                string Country;
                cout << "\nPlease Enter Country Name: ";
                Country = clsInputValidate::ReadString();
                clsCurrency Currency = clsCurrency::FindCurrencyByCountry(Country);
                _ShowResults(Currency);
            }
        }
};
