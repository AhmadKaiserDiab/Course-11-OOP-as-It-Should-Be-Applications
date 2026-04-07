#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsDate.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtility.h"

using namespace std;

const string UsersFile = "./DataFiles/Users.txt";
const string LogFile = "./DataFiles/LoginRegister.txt";

class clsUser : public clsPerson
{
    private:
        enum enMode
        { EmptyMode = 0,UpdateMode = 1,AddNewMode = 2 };

        enMode _Mode;
        string _Username;
        string _Password;
        short _Permissions;
        bool _MarkedForDelete = false;

    public:
        struct stLoginRegisterRecord;

    private:
        static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
        {
            stLoginRegisterRecord LoginRegisterRecord;
    
            vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
            LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
            LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
            LoginRegisterRecord.Password = clsUtility:: DecryptText(LoginRegisterDataLine[2]);
            LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
    
            return LoginRegisterRecord;
    
        }

        string _PrepareLogInrecord(string Seperator = "#//#")
        {
            string strUserRecord = "";
            strUserRecord += clsDate :: GetSystemDateTimeString() + Seperator;
            strUserRecord += GetUsername() + Seperator;
            strUserRecord += clsUtility::EncryptText(GetPassword()) + Seperator;
            strUserRecord += to_string(GetPermissions());
            return strUserRecord;
        }

        static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
        {
            vector<string> vUserData = clsString::Split(Line, "#//#");

            return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
                        vUserData[4], clsUtility :: DecryptText(vUserData[5]), stod(vUserData[6]));
        }

        static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
        {
            string strUserRecord = "";
            strUserRecord += User.FirstName() + Seperator;
            strUserRecord += User.LastName() + Seperator;
            strUserRecord += User.Phone() + Seperator;
            strUserRecord += User.Email() + Seperator;
            strUserRecord += User.GetUsername() + Seperator;
            strUserRecord += clsUtility :: EncryptText(User.GetPassword()) + Seperator;
            strUserRecord += to_string(User._Permissions);
            return strUserRecord;
        }

        static vector<clsUser> _LoadUsersDataFromFile()
        {
            vector<clsUser> vUsers;

            fstream MyFile;
            MyFile.open(UsersFile, ios::in);

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    vUsers.push_back(_ConvertLineToUserObject(Line));
                }
                MyFile.close();
            }
            return vUsers;
        }

        static void _SaveCleintsDataToFile(vector<clsUser> vUsers)
        {
            fstream MyFile;
            MyFile.open(UsersFile, ios::out); // overwrite
            if (MyFile.is_open())
            {
                for (clsUser C : vUsers)
                {
                    if (C.MarkedForDeleted() == false)
                    {
                        MyFile << _ConvertUserObjectToLine(C) << endl;
                    }
                }
                MyFile.close();
            }
        }

        void _AddDataLineToFile(string DataLine)
        {
            fstream MyFile;
            MyFile.open(UsersFile, ios::out | ios::app);
            if (MyFile.is_open())
            {
                MyFile << DataLine << endl;
                MyFile.close();
            }
        }

        void _AddNew()
        {
            _AddDataLineToFile(_ConvertUserObjectToLine(*this));
        }

        void _Update()
        {
            vector<clsUser> _vUsers = _LoadUsersDataFromFile();
            for (clsUser &User : _vUsers)
            {
                // if(User.GetUsername() == this->GetUsername())
                if (User.GetUsername() == GetUsername())
                {
                    User = *this;
                    break;
                }
            }
            _SaveCleintsDataToFile(_vUsers);
        }

        static clsUser _GetEmptyUserObject()
        {
            return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
        }

    public:
        enum enPermissions
        {
            eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, 
            pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
            pShowLogInRegister = 128, pCurrencyExchange = 256
        };

        struct stLoginRegisterRecord
        {
            string DateTime;
            string UserName;
            string Password;
            int Permissions;

        };

        clsUser(enMode Mode, string FirstName, string LastName, string Phone,
                string Email, string Username, string Password, short Permissions) : clsPerson(FirstName, LastName, Phone, Email)
        {
            _Mode = Mode;
            _Username = Username;
            _Password = Password;
            _Permissions = Permissions;
        }

        bool IsEmpty()
        {
            return (_Mode == enMode ::EmptyMode);
        }

        bool MarkedForDeleted()
        {
            return _MarkedForDelete;
        }

        string GetUsername()
        {
            return _Username;
        }

        void SetUsername(string Username)
        {
            _Username = Username;
        }

        void SetPassword(string Password)
        {
            _Password = Password;
        }

        string GetPassword()
        {
            return _Password;
        }

        void SetPermissions(short Permissions)
        {
            _Permissions = Permissions;
        }

        short GetPermissions()
        {
            return _Permissions;
        }

        static clsUser Find(string Username)
        {
            fstream MyFile;
            MyFile.open(UsersFile, ios::in);
            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsUser User = _ConvertLineToUserObject(Line);
                    if (User.GetUsername() == Username)
                    {
                        MyFile.close();
                        return User;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyUserObject();
        }

        static clsUser Find(string Username, string Password)
        {
            fstream MyFile;
            MyFile.open(UsersFile, ios::in);
            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsUser User = _ConvertLineToUserObject(Line, "#//#");
                    if (User._Username == Username && User._Password == Password)
                    {
                        MyFile.close();
                        return User;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyUserObject();
        }

        static bool IsUserExist(string Username)
        {
            clsUser User = clsUser ::Find(Username);
            return (!User.IsEmpty());
        }

        enum enSaveResults
        {
            svFaildEmptyObject = 0,
            svSucceeded = 1,
            svFaildUsernameExists = 2
        };

        enSaveResults Save()
        {
            switch (_Mode)
            {
                case enMode ::EmptyMode:
                {
                    if (IsEmpty())
                    {
                        return enSaveResults ::svFaildEmptyObject;
                    }
                }
                case enMode ::UpdateMode:
                {
                    _Update();
                    return enSaveResults ::svSucceeded;
                    break;
                }
                case enMode ::AddNewMode:
                {
                    if (IsUserExist(_Username))
                    {
                        return enSaveResults ::svFaildUsernameExists;
                    }
                    else
                    {
                        _AddNew();
                        _Mode = enMode::UpdateMode;
                        return enSaveResults::svSucceeded;
                    }
                    break;
                }
            }
            // //! Not Neccesary
            // return enSaveResults::svSucceeded;
        }

        static clsUser GetAddNewUserObject(string Username)
        {
            return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
        }

        bool Delete()
        {
            vector<clsUser> _vUsers;
            _vUsers = _LoadUsersDataFromFile();
            for (clsUser &C : _vUsers)
            {
                if (C.GetUsername() == _Username)
                {
                    C._MarkedForDelete = true;
                    break;
                }
            }
            _SaveCleintsDataToFile(_vUsers);
            *this = _GetEmptyUserObject();
            return true;
        }

        static vector<clsUser> GetUsersList()
        {
            return _LoadUsersDataFromFile();
        }

        bool CheckAccessPermission(enPermissions Permission)
        {
            if (this->_Permissions == enPermissions::eAll)
                return true;
            if ((Permission & this->_Permissions) == Permission)
                return true;
            else
                return false;

            // return (this->_Permissions == enPermissions::eAll ||  (Permission & this->_Permissions) == Permission  );
        }

        void RegisterLogIn()
        {
            string stDataLine = _PrepareLogInrecord();
            fstream MyFile;
            MyFile.open(LogFile, ios::out | ios::app);
            if(MyFile.is_open())
            {
                MyFile<<stDataLine<<endl;
                MyFile.close();
            }
        }

        static  vector <stLoginRegisterRecord> GetLoginRegisterList()
        {
            vector <stLoginRegisterRecord> vLoginRegisterRecord;
            fstream MyFile;
            MyFile.open(LogFile, ios::in);//read Mode
            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    vLoginRegisterRecord.push_back(_ConvertLoginRegisterLineToRecord(Line));
                }
                MyFile.close();
            }
            return vLoginRegisterRecord;
        }

};
