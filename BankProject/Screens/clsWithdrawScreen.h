#pragma once
#include <iostream>
#include <iomanip>
#include "../Logic/clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
{
    private:
        static void _PrintClient(clsBankClient Client)
        {
            cout << "\nClient Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << Client.FirstName();
            cout << "\nLastName    : " << Client.LastName();
            cout << "\nFull Name   : " << Client.FullName();
            cout << "\nEmail       : " << Client.Email();
            cout << "\nPhone       : " << Client.Phone();
            cout << "\nAcc. Number : " << Client.AccountNumber();
            cout << "\nPassword    : " << Client.GetPinCode();
            cout << "\nBalance     : " << Client.GetAccountBalance();
            cout << "\n___________________\n";
        }

        static string _ReadAccountNumber()
        {
            string AccountNumber = "";
            cout << "\nPlease enter Account Number: ";
            cin >> AccountNumber;
            return AccountNumber;
        }

    public:
        static void ShowWithdrawScreen()
        {
            _DrawScreenHeader("\t   Withdraw Screen");
        
            string AccountNumber = _ReadAccountNumber();
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
                AccountNumber = _ReadAccountNumber();
            }

            clsBankClient Client = clsBankClient::Find(AccountNumber);
            _PrintClient(Client);

            double Amount = 0;
            cout << "\nPlease enter Withdraw amount? ";
            Amount = clsInputValidate::ReadNumber <double> ();

            cout << "\nAre you sure you want to perform this transaction? ";
            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                if( Client.Withdraw(Amount))
                { 
                    cout << "\nAmount Withdrew Successfully.\n";
                    cout << "\nNew Balance Is: " << Client.GetAccountBalance();
                }
                else
                {
                    cout << "\nCannot withdraw, Insuffecient Balance!\n";
                    cout << "\nAmout to withdraw is: " << Amount;
                    cout << "\nYour Balance is: " << Client.GetAccountBalance();
                    
                }
            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }
        }
};
