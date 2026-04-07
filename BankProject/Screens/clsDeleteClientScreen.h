#pragma once
#include <iostream>
#include <iomanip>
#include "../Logic/clsBankClient.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
    private:

        static void _PrintClient(clsBankClient Client)
        {
            cout<<"\nClient Card:";
            cout<<"\n_______________________________________";
            cout<<"\nFirst Name    : " <<Client.FirstName();
            cout<<"\nLast Name     : " <<Client.LastName();
            cout<<"\nFull Name     : " <<Client.FullName();
            cout<<"\nEmail         : " <<Client.Email();
            cout<<"\nPhone         : " <<Client.Phone();
            cout<<"\nAccount Number: " <<Client.AccountNumber();
            cout<<"\nPinCode       : " <<Client.GetPinCode();
            cout<<"\nBalance       : " <<Client.GetAccountBalance();
            cout<<"\n_______________________________________"<<endl;
        }

    public:
        static void ShowDeleteClientScreen()
        {
            _DrawScreenHeader("\t Delete Client Screen");
            
            cout<<"\nEnter Account Number: ";
            string AccountNumber = clsInputValidate :: ReadString();
            
            while(!clsBankClient :: IsClientExist(AccountNumber))
            {
                cout << "\nAccount Number is not found, choose another one: ";
                string Username = clsInputValidate :: ReadString();
            }
            
            clsBankClient Client = clsBankClient :: Find(AccountNumber);
            _PrintClient(Client);
            
            cout<<"Are You Sure You Want To Delete This Client, Y/N? ";
            char Answer = 'n';
            cin >> Answer;
            
            if (Answer == 'y' || Answer == 'Y')
            {
                if (Client.Delete())
                {
                    cout << "\nClient Deleted Successfully :-)\n";
                    _PrintClient(Client);
                }
                else
                {
                    cout << "\nError Client Was not Deleted\n";
                }
            }
        }
};
