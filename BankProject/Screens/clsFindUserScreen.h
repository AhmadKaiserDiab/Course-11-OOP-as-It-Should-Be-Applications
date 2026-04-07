#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Logic/clsUser.h"
#include "../Logic/clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
{
    private :
        static void _PrintUser(clsUser User)
        {
            cout<<"\nUser Card:";
            cout<<"\n_______________________________________";
            cout<<"\nFirst Name    : " <<User.FirstName();
            cout<<"\nLast Name     : " <<User.LastName();
            cout<<"\nFull Name     : " <<User.FullName();
            cout<<"\nEmail         : " <<User.Email();
            cout<<"\nPhone         : " <<User.Phone();
            cout<<"\nUsername      : " <<User.GetUsername();
            cout<<"\nPasword       : " <<User.GetPassword();
            cout<<"\nPermissions   : " <<User.GetPermissions();
            cout<<"\n_______________________________________"<<endl;
        }

    public:
        static void ShowFindUserScreen()
        {
            _DrawScreenHeader("\tFind User Screen");

            string Username;
            cout << "\nPlease Enter Username: ";
            Username = clsInputValidate::ReadString();
            
            while (!clsUser::IsUserExist(Username))
            {
                cout << "\nUsername is not found, choose another one: ";
                Username = clsInputValidate::ReadString();
            }
            
            clsUser User = clsUser::Find(Username);

            if (!User.IsEmpty())
            {
                cout << "\nUser Found :-)\n";
            }
            else
            {
                cout << "\nUser Was not Found :-(\n";
            }
            _PrintUser(User);
        }

};

