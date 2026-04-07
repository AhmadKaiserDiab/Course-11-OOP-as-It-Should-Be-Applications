#pragma once
#include <iostream>
#include "../Logic/clsCurrency.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrecnciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMenuScreen : protected clsScreen
{
    private:
        enum enCurrencyExchangeMenuOptions {
            eListCurrencies = 1,
            eFindCurrency = 2,
            eUpdateCurrencyRate = 3,
            eCurrecnyCalculator = 4,
            eMainMenu = 5,
        };

        static short _ReadenCurrencyExchangeMenuOptions()
        {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 5]: ";
            short Choice = clsInputValidate::ReadNumberBetween <short> (1,5,"Enter Number between 1 to 5 : ");
            return Choice;
        }

        static void _GoBackToCurrencyExchangeMenu()
        {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Currency Exchange Menu...\n";
            system("pause>0");
            ShowCurrencyExchangeMenuScreen();
        }

        static void _ShowListCurrenciesScreen()
        {
            clsCurrecnciesListScreen :: ShowCurrecnciesListScreen();
        }

        static void _ShowFindCurrencyScreen()
        {
            clsFindCurrencyScreen :: ShowFindCurrencyScreen();
        }

        static void _ShowUpdateRateScreen()
        {
            clsUpdateRateScreen :: ShowUpdateRateScreen();
        }

        static void _ShowCurrecnyCalculatorScreen()
        {
            clsCurrencyCalculatorScreen :: ShowCurrencyCalculatorScreen();
        }

        static void _PerfromenCurrencyExchangeMenuOptions(enCurrencyExchangeMenuOptions MainMenuOption)
        {
            switch (MainMenuOption)
            {
                case enCurrencyExchangeMenuOptions::eListCurrencies:
                {
                    system("cls");
                    _ShowListCurrenciesScreen();
                    _GoBackToCurrencyExchangeMenu();
                    break;
                }
                case enCurrencyExchangeMenuOptions::eFindCurrency:
                {
                    system("cls");
                    _ShowFindCurrencyScreen();
                    _GoBackToCurrencyExchangeMenu();
                    break;
                }
                case enCurrencyExchangeMenuOptions::eUpdateCurrencyRate:
                {
                    system("cls");
                    _ShowUpdateRateScreen();
                    _GoBackToCurrencyExchangeMenu();
                    break;
                }
                case enCurrencyExchangeMenuOptions::eCurrecnyCalculator:
                {    
                    system("cls");
                    _ShowCurrecnyCalculatorScreen();
                    _GoBackToCurrencyExchangeMenu(); 
                    break;
                }
                case enCurrencyExchangeMenuOptions::eMainMenu: {}
            }
        }
    
    public:
        static void ShowCurrencyExchangeMenuScreen()
        {
            system("cls");
            _DrawScreenHeader("\t Currency Exchange Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Currencies List.\n";
            cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
            cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
            cout << setw(37) << left << "" << "\t[4] Currency Exchange.\n";
            cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromenCurrencyExchangeMenuOptions((enCurrencyExchangeMenuOptions) _ReadenCurrencyExchangeMenuOptions());
        };

};
