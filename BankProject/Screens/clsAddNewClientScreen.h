#include <iostream>
#include <iomanip>
#include "../Logic/clsBankClient.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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
            Client.SetAccountBalance(clsInputValidate :: ReadNumber <double> () );
        }

    public:
        static void ShowAddNewClientScreen()
        {
            _DrawScreenHeader("\t Add New Client Screen");
            
            string AccountNumber = "";
            cout<<"\nPlease Enter Account Number: ";
            AccountNumber = clsInputValidate :: ReadString();
            while (clsBankClient :: IsClientExist(AccountNumber))
            {
                cout<<"\nAccount Number Is Already Used, Choose Another One: ";
                AccountNumber = clsInputValidate :: ReadString();
            }
        
            clsBankClient Client = clsBankClient :: GetAddNewClientObject(AccountNumber);
            _ReadClientInfo(Client);

            clsBankClient :: enSaveResults SaveResult;
            SaveResult = Client.Save();

            switch (SaveResult)
            {
                case clsBankClient :: svSucceeded :
                {
                    cout << "\nAccount Added Successfully:-) \n";
                    _PrintClient(Client);
                    break;
                }

                case clsBankClient :: svFaildEmptyObject :
                {
                    cout << "\nError account was not saved because it's Empty"; 
                    break;
                }

                case clsBankClient :: enSaveResults :: svFaildAccountNumberExists:
                    {
                        cout << "\nAccount Already Exist.\n";
                        break;
                    }
            }
        }

};
