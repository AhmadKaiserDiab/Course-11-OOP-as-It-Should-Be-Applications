#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "../Logic/clsCurrency.h"
using namespace std;

class clsCurrecnciesListScreen : protected clsScreen
{
    private:
        static void _PrintCurrencyRecordLine(clsCurrency Currency)
        {
            cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
            cout << "| " << setw(8) << left << Currency.CurrencyCode();
            cout << "| " << setw(45) << left << Currency.CurrencyName();
            cout << "| " << setw(15) << left << Currency.Rate();
        }
    
    public:
        static void ShowCurrecnciesListScreen()
        {
            vector <clsCurrency> vCurrencies = clsCurrency :: GetCurrenciesList(); 
            string Title = "\t  Currencies List Screen";
            string SubTitle = "\t    ("+ to_string(vCurrencies.size()) + ") Currency.";
            _DrawScreenHeader(Title , SubTitle);
        
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;
            cout <<  setw(8) << left << "" << "| " << left << setw(30) << "Country Name";
            cout << "| " << left << setw(15) << "Currency Code";
            cout << "| " << left << setw(45) << "Currency Name";
            cout << "| " << left << setw(15) << "Rate";
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            if(vCurrencies.size() == 0)
            {
                cout<<"\t\t\t\tNo Currencies Available in The System!.\n";
            }
            else
            {
                for (clsCurrency & Currency : vCurrencies)
                {
                    _PrintCurrencyRecordLine(Currency);
                    cout<<endl;
                }
                
            }
        }
};

