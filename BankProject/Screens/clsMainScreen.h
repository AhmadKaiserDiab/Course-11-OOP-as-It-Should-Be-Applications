#pragma once
#include <iostream>
#include <iomanip>
#include "../Global.h"
#include "../Logic/clsInputValidate.h"
#include "clsLoginScreen.h"
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionMenuScreen.h"
#include "clsManageUsersMenuScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMenuScreen.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
    private:
        enum enMainMenuOptions
        {
            eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
            eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
            eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
        };

        static short _ReadMainMenuOption()
        {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 10]? ";
            short Choice = clsInputValidate::ReadNumberBetween <short> (1,10,"Enter Number between 1 to 9 ? ");
            return Choice;
        }

        static void _GoBackToMainMenu()
        {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Main Menu...\n";
            system("pause>0");
            ShowMainMenu();
        }

        static void _ShowAllClientsScreen()
        {
            clsClientsListScreen :: ShowClientsList();
        }

        static void _ShowAddNewClientsScreen()
        {
            clsAddNewClientScreen :: ShowAddNewClientScreen();
        }

        static void _ShowDeleteClientScreen()
        {
            clsDeleteClientScreen :: ShowDeleteClientScreen();
        }

        static void _ShowUpdateClientScreen()
        {
            clsUpdateClientScreen :: ShowUpdateClientScreen() ;
        }

        static void _ShowFindClientScreen()
        {
            clsFindClientScreen :: ShowFindClientScreen();
        }

        static void _ShowTransactionsMenu()
        {
            clsTransactionsMenuScreen :: ShowTransactionsMenu();
        }

        static void _ShowManageUsersMenu()
        {
            clsManageUsersMenuScreen :: ShowManageUsersMenu();
        }

        static void _ShowLoginRegisterScreen()
        {
            clsLoginRegisterScreen :: ShowLoginRegisterScreen();
        }

        static void _ShowCurrencyExchangeMenuScreen()
        {
            clsCurrencyExchangeMenuScreen :: ShowCurrencyExchangeMenuScreen();
        }

        static void _ShowEndScreen()
            {
                cout << "\nEnd Screen Will be here...\n";
            }

        static void _Logout()
        {
            CurrentUser = clsUser :: Find("","");
        } 

        static void ShowAccessDeniedScreen()
        {
            cout<<"\t\t\t\t\t______________________________________";
            cout<<"\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";  
            cout<<"\n\t\t\t\t\t______________________________________\n\n";
        }

        static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
        {
            switch (MainMenuOption)
            {
                case enMainMenuOptions::eListClients:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pListClients))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowAllClientsScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eAddNewClient:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pAddNewClient))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowAddNewClientsScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eDeleteClient:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pDeleteClient))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowDeleteClientScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eUpdateClient:
                {    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pUpdateClient))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowUpdateClientScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eFindClient:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pFindClient))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowFindClientScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eShowTransactionsMenu:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pTransactions))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowTransactionsMenu();
                    }
                    _GoBackToMainMenu(); 
                    break;
                }
                case enMainMenuOptions::eManageUsers:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pManageUsers))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowManageUsersMenu();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eLoginRegister:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pShowLogInRegister))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowLoginRegisterScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eCurrencyExchange:
                {
                    system("cls");
                    if(!CurrentUser.CheckAccessPermission(clsUser :: enPermissions :: pCurrencyExchange))
                    {
                        ShowAccessDeniedScreen();
                    }
                    else
                    {
                        _ShowCurrencyExchangeMenuScreen();
                    }
                    _GoBackToMainMenu();
                    break;
                }
                case enMainMenuOptions::eExit:
                {
                    system("cls");
                    _Logout();
                    break;
                }
            }
        }

	public:
        static void ShowMainMenu()
        { 
            system("cls");
            _DrawScreenHeader("\t\tMain Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Login Register.\n";
            cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
            cout << setw(37) << left << "" << "\t[10] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
        }
};

