#include <iostream>
#include <iomanip>
#include "../Logic/clsUser.h"
#include "../Logic/clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
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

        static void _ReadUserInfo(clsUser & User)
        {
            cout<<"\nEnter First Name: ";
            User.SetFirstName(clsInputValidate :: ReadString());

            cout<<"\nEnter Last Name: ";
            User.SetLastName(clsInputValidate :: ReadString());

            cout<<"\nEnter Email: ";
            User.SetEmail(clsInputValidate :: ReadString());

            cout<<"\nEnter Phone: ";
            User.SetPhone(clsInputValidate :: ReadString());
            
            cout<<"\nEnter Password: ";
            User.SetPassword(clsInputValidate :: ReadString());
            
            cout<<"\nEnter Permissions: ";
            User.SetPermissions(_ReadPermissionsToSet());
        }

        static short _ReadPermissionsToSet()
        {
            short Permissions = 0;
            char Confirm = 'N';

            cout << "\n Do You Want To Give Full Access? Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                return -1;
            }

            cout << "\n Do You Want To Give Access To:\n ";
            cout << "Show Client List: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pListClients;
            }

            cout << "\n Add New Client: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pAddNewClient;
            }

            cout << "\n Delete Client: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pDeleteClient;
            }

            cout << "\n Update Client: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pUpdateClient;
            }

            cout << "\n Find Client: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pFindClient;
            }

            cout << "\n Transactions: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pTransactions;
            }

            cout << "\n Manage Users Client: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pManageUsers;
            }

            cout << "\n Show Login Register: Y/N ? ";
            cin >> Confirm;
            if (Confirm == 'Y' || Confirm == 'y')
            {
                Permissions += clsUser :: enPermissions::pShowLogInRegister;
            }
            return Permissions;
        }

    public:
        static void ShowAddNewUserScreen()
        {
            _DrawScreenHeader("\t Add New User Screen");
            
            string Username = "";
            cout<<"\nPlease Enter Username: ";
            Username = clsInputValidate :: ReadString();
            while (clsUser :: IsUserExist(Username))
            {
                cout<<"\nUsername Is Already Used, Choose Another One: ";
                Username = clsInputValidate :: ReadString();
            }
        
            clsUser User = clsUser :: GetAddNewUserObject(Username);
            _ReadUserInfo(User);

            clsUser :: enSaveResults SaveResult;
            SaveResult = User.Save();

            switch (SaveResult)
            {
                case clsUser :: svSucceeded :
                {
                    cout << "\nUser Added Successfully:-) \n";
                    _PrintUser(User);
                    break;
                }

                case clsUser :: svFaildEmptyObject :
                {
                    cout << "\nError User was not Saved Because it's Empty"; 
                    break;
                }

                case clsUser :: enSaveResults :: svFaildUsernameExists:
                    {
                        cout << "\nUser Already Exist.\n";
                        break;
                    }
            }
        }

};
