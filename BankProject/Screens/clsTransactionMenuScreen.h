#pragma once
#include <iostream>
#include <iomanip>
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;

class clsTransactionsMenuScreen : protected clsScreen
{
    private:
        enum enTransactionMenuOptions
        {
            eDeposit = 1,
            eWithDraw = 2,
            eTotalBalances = 3,
            eTransfer = 4,
            eTransferLog = 5,
            eMainMenu = 6
        };

        static short _ReadTransactionMenuOption()
        {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 6]? ";
            short Choice = clsInputValidate::ReadNumberBetween  <short> (1,6,"Enter Number between 1 to 4 ? ");
            return Choice;
        }

        static void _GoBackToTransactionMenu()
        {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Main Menu...\n";
            system("pause>0");
            ShowTransactionsMenu();
        }

        static void _ShowDepositScreen()
        {
            clsDepositScreen :: ShowDepositScreen();
        }

        static void _ShowWithdrawScreen()
        {
            clsWithdrawScreen :: ShowWithdrawScreen();
        }

        static void _ShowTotalBalancesScreen()
        {
            clsTotalBalancesScreen :: ShowTotalBalances();
        }

        static void _ShowTransferScreen()
        {
            clsTransferScreen :: ShowTransferScreen();
        }

        static void _ShowTransferLogScreen()
        {
            clsTransferLogScreen :: ShowTransferLogScreen();
        }

        static void _PerfromTransactionMenuOption(enTransactionMenuOptions TransactionMenuOption)
        {
            switch (TransactionMenuOption)
            {
                case enTransactionMenuOptions::eDeposit:
                {
                    system("cls");
                    _ShowDepositScreen();
                    _GoBackToTransactionMenu();
                    break;
                }
                case enTransactionMenuOptions:: eWithDraw :
                {
                    system("cls");
                    _ShowWithdrawScreen();
                    _GoBackToTransactionMenu();
                    break;
                }
                case enTransactionMenuOptions::eTotalBalances:
                {
                    system("cls");
                    _ShowTotalBalancesScreen();
                    _GoBackToTransactionMenu();
                    break;
                }
                case enTransactionMenuOptions::eTransfer:
                {
                    system("cls");
                    _ShowTransferScreen();
                    _GoBackToTransactionMenu();
                    break;
                }
                case enTransactionMenuOptions::eTransferLog:
                {
                    system("cls");
                    _ShowTransferLogScreen();
                    _GoBackToTransactionMenu();
                    break;
                }
                case enTransactionMenuOptions:: eMainMenu:
                {    
                    break;
                }
            }
        }

	public:
        static void ShowTransactionsMenu()
        { 
            system("cls");
            _DrawScreenHeader("\t\tTransaction Screen");
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tTransaction Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Deposit.\n";
            cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
            cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
            cout << setw(37) << left << "" << "\t[4] Transfer.\n";
            cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            _PerfromTransactionMenuOption((enTransactionMenuOptions)_ReadTransactionMenuOption());
        }
};

