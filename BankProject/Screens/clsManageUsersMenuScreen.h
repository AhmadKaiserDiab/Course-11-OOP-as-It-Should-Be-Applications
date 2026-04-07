#pragma once
#include <iostream>
#include <iomanip>
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersMenuScreen : protected clsScreen
{
    private:
        enum enManageUsersMenuOptions
        {
            eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
            eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
        };

        static short _ReadManageUsersMenuOption()
        {
            cout <<setw(37) << left << ""<< "Choose what do you want to do? [1 to 6]? ";
            short Choice = clsInputValidate::ReadNumberBetween <short> (1,6,"Enter Number between 1 to 8 ? ");
            return Choice;
        }

        static void _GoBackToManageUsersMenu()
        {
            cout << setw(37) << left << ""<<"\n\tPress any key to go back to Manage Users Menu...\n";
            system("pause>0");
            ShowManageUsersMenu();
        }

        static void _ShowAllUsersScreen()
        {
            clsUsersListScreen :: ShowUsersList();
        }

        static void _ShowAddNewUserScreen()
        {
            clsAddNewUserScreen :: ShowAddNewUserScreen();
        }

        static void _ShowDeleteUserScreen()
        {
            clsDeleteUserScreen :: ShowDeleteUserScreen();
        }

        static void _ShowUpdateUserScreen()
        {
            clsUpdateUserScreen :: ShowUpdateUserScreen() ;
        }

        static void _ShowFindUserScreen()
        {
            clsFindUserScreen :: ShowFindUserScreen();
        }

        static void _PerfromManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
        {
            switch (ManageUsersMenuOption)
            {
                case enManageUsersMenuOptions::eListUsers:
                {
                    system("cls");
                    _ShowAllUsersScreen();
                    _GoBackToManageUsersMenu();
                    break;
                }
                case enManageUsersMenuOptions::eAddNewUser:
                {
                    system("cls");
                    _ShowAddNewUserScreen();
                    _GoBackToManageUsersMenu();
                    break;
                }
                case enManageUsersMenuOptions::eDeleteUser:
                {
                    system("cls");
                    _ShowDeleteUserScreen();
                    _GoBackToManageUsersMenu();
                    break;
                }
                case enManageUsersMenuOptions::eUpdateUser:
                {    system("cls");
                    _ShowUpdateUserScreen();
                    _GoBackToManageUsersMenu();
                    break;
                }
                case enManageUsersMenuOptions::eFindUser:
                {
                    system("cls");
                    _ShowFindUserScreen();
                    _GoBackToManageUsersMenu();
                    break;
                }
                case enManageUsersMenuOptions:: eMainMenu:
                {    
                    break;
                }
            }
        }

	public:
        static void ShowManageUsersMenu()
        { 
            system("cls");
            _DrawScreenHeader("\t\tManage Users Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tManage Users Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show User List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New User.\n";
            cout << setw(37) << left << "" << "\t[3] Delete User.\n";
            cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find User.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
        }
};

