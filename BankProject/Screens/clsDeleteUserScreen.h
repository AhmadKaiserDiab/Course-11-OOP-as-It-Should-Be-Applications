#pragma once
#include <iostream>
#include <iomanip>
#include "../Logic/clsUser.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
    private:

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
        static void ShowDeleteUserScreen()
        {
            _DrawScreenHeader("\t Delete User Screen");
            
            cout<<"\nEnter Username: ";
            string Username = clsInputValidate :: ReadString();
            
            while(!clsUser :: IsUserExist(Username))
            {
                cout << "\nUsername is not found, choose another one: ";
                string Username = clsInputValidate :: ReadString();
            }
            
            clsUser User = clsUser :: Find(Username);
            _PrintUser(User);
            
            cout<<"Are You Sure You Want To Delete This User, Y/N? ";
            char Answer = 'n';
            cin >> Answer;
            
            if (Answer == 'y' || Answer == 'Y')
            {
                if (User.Delete())
                {
                    cout << "\nUser Deleted Successfully :-)\n";
                    _PrintUser(User);
                }
                else
                {
                    cout << "\nError User Was not Deleted\n";
                }
            }
        }
};
