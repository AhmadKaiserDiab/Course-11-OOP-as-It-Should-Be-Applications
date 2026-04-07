#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Logic/clsInputValidate.h"
using namespace std;

class clsUpdateRateScreen : protected clsScreen
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
            cout<<"\n_____________________________"<<endl;
        }

        static float _ReadRate()
        {
            cout << "\nEnter New Rate: ";
            float NewRate = 0;
            NewRate = clsInputValidate::ReadNumber  <float> ();
            return NewRate;
        }

    public:
        static void ShowUpdateRateScreen()
        {
            _DrawScreenHeader("\t Update Currency Screen ");
            
            cout<<"\nPlease Enter Currency Code: ";
            string CurrencyCode = clsInputValidate ::ReadString() ;
            
            while (!clsCurrency::IsCurrencyExist(CurrencyCode))
            {
                cout << "\nCurrency is not found, choose another one: ";
                CurrencyCode = clsInputValidate::ReadString();
            }
        
            clsCurrency Currency = clsCurrency :: FindCurrencyByCode(CurrencyCode);
            _PrintCurrency(Currency);
            
            cout<<"\nAre You Sure You Want To Update The Rate of This Currency? Y/N  ";
            char Answer = 'N';
            cin>>Answer;
            if(Answer == 'Y' || Answer == 'y')
            {
                cout << "\n\nUpdate Currency Rate:";
                cout << "\n____________________\n";
                
                Currency.UpdateRate( _ReadRate());

                cout << "\nCurrency Rate Updated Successfully :-)\n";
                _PrintCurrency(Currency);
            }
            else
            {
                cout<<"\nOperation Was Cancelled :-(";
            }

        }

};
