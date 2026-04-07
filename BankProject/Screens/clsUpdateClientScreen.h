#pragma once
#include <iostream>
#include <iomanip>
#include "../Logic/clsBankClient.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

        static void _ReadClientInfo(clsBankClient & Client)
        {
            cout<<"\nEnter First Name: ";
            Client.SetFirstName(clsInputValidate :: ReadString());

            cout<<"\nEnter Last Name: ";
            Client.SetLastName(clsInputValidate :: ReadString());

            cout<<"\nEnter Email: ";
            Client.SetEmail(clsInputValidate :: ReadString());

            cout<<"\nEnter Phone: ";
            Client.SetPhone(clsInputValidate :: ReadString());
            
            cout<<"\nEnter PinCode: ";
            Client.SetPinCode(clsInputValidate :: ReadString());

            cout<<"\nEnter Account Balance: ";
            Client.SetAccountBalance(clsInputValidate :: ReadNumber <double> ());
        }

    public:
        static void ShowUpdateClientScreen()
        {
            _DrawScreenHeader("\tUpdate Client Screen");

            string AccountNumber = "";
            cout << "\nPlease Enter client Account Number: ";
            AccountNumber = clsInputValidate::ReadString();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }
            clsBankClient Client = clsBankClient::Find(AccountNumber);
            _PrintClient(Client);

            cout << "\nAre you sure you want to update this client y/n? ";
            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {
                cout << "\n\nUpdate Client Info:";
                cout << "\n____________________\n";

                _ReadClientInfo(Client);

                clsBankClient::enSaveResults SaveResult;
                SaveResult = Client.Save();

                switch (SaveResult)
                {
                    case  clsBankClient::enSaveResults::svSucceeded:
                    {
                        cout << "\nAccount Updated Successfully :-)\n";
                    
                        _PrintClient(Client);
                        break;
                    }
                    case clsBankClient::enSaveResults::svFaildEmptyObject:
                    {
                        cout << "\nError account was not saved because it's Empty";
                        break;
                    }
                }
            }
        }

};
