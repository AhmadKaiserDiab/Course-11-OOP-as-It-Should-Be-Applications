
#pragma once 
#include <iostream>
#include "../Logic/clsBankClient.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
    private:
        static void _PrintClient(clsBankClient Client)
        {
            cout << "\nClient Card:";
            cout << "\n_____________________________";
            cout << "\nFull Name   : " << Client.FullName();
            cout << "\nAcc. Number : " << Client.AccountNumber();
            cout << "\nBalance     : " << Client.GetAccountBalance();
            cout << "\n_____________________________\n";
        }

        static string _ReadAccountNumber()
        {
            string AccountNumber = "";
            // cout << "\nPlease enter Account Number: ";
            cin >>AccountNumber;
            return AccountNumber;
        }

    public:
        static void ShowTransferScreen()
        {
            _DrawScreenHeader("\t  Transfer Screen");
            
            cout<<"\n\n Please Enter Account Number To Transfer From: ";
            string SourceAccountNumber = _ReadAccountNumber();

            while(!clsBankClient::IsClientExist(SourceAccountNumber))
            {
                cout<<"\nAccount Number Not Found, Enter Another Account Number: ";
                SourceAccountNumber = _ReadAccountNumber();
            }
            clsBankClient SourceClient = clsBankClient :: Find(SourceAccountNumber);
            _PrintClient(SourceClient);
            
            cout<<"\n\n Please Enter Account Number To Transfer To: ";
            string DestinationAccountNumber = _ReadAccountNumber();
            while(!clsBankClient::IsClientExist(DestinationAccountNumber) || DestinationAccountNumber == SourceAccountNumber)
            {
                cout<<"\nAccount Number Not Found, Enter Another Account Number: ";
                DestinationAccountNumber = _ReadAccountNumber();
            }
            clsBankClient DestinationClient = clsBankClient :: Find(DestinationAccountNumber);
            _PrintClient(DestinationClient);
            
            double TransferAmount = 0;
            cout<<"\n\nEnter Transfer Amount: ";
            TransferAmount = clsInputValidate::ReadNumber <double> ();
            
            while(TransferAmount > SourceClient.GetAccountBalance())
            {
                cout<<"\nAmount Exceed The Avaliable Balance, Enter Another Amount: ";
                TransferAmount = clsInputValidate::ReadNumber <double> ();
            }
            
            cout << "\nAre you sure you Want to Perform This Transaction?Y/N  ";
            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                if(SourceClient.Transfer(DestinationClient,TransferAmount))
                { 
                    cout<<"\n Transfer Done Successfully."<<endl;
                }
                else
                {
                    cout << "\nElse Transfer Failed.\n";
                }
            }
            _PrintClient(SourceClient);
            _PrintClient(DestinationClient);
        }


};

