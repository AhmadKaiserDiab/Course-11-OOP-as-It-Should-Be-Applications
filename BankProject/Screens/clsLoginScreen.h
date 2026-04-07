#pragma once
#include <iostream>
#include <fstream>
#include "../Global.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
    private:
        static bool _Login()
        {
            bool LoginFailed = false;
            short FailedLoginCount = 0;
            string Username,Password;
            
            do
            {
                cout<<"Enter Username:  ";
                cin>>Username;
                cout<<"Enter Passsword: ";
                cin>>Password;
                
                CurrentUser = clsUser :: Find(Username,Password);
                LoginFailed = CurrentUser.IsEmpty();
                if (LoginFailed)
                {
                    FailedLoginCount++;
                    cout<<"\n Inavalid Username/Passsword:\n\n";
                    cout<<"\n You Have "<<(3 -FailedLoginCount)
                        <<" Trials To Login.\n\n";
                }
                if (FailedLoginCount == 3)
                {
                    cout<<"\n You Are Locked After 3 Failed Trials To Login.\n\n";
                    return false;
                }
            } while (LoginFailed);
            CurrentUser.RegisterLogIn();
            clsMainScreen :: ShowMainMenu();
            return true;
        }

    public:
        static bool ShowLoginScreen()
        {
            system("cls");
            _DrawScreenHeader("\t    Login Screen");
            return _Login();
        }
};
