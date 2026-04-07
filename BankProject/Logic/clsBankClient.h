#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Global.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsString.h"
using namespace std;

const string ClientsFile = "./DataFiles/Clients.txt";
const string TransferLogFile = "./DataFiles/TransferLog.txt";

class clsBankClient : public clsPerson
{
    private:
        enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
        
        enMode _Mode;
        string _AccountNumber;
        string _PinCode;
        double _AccountBalance;
        bool _MarkedForDelete = false;

    public:
        struct stTransferLogRecord
        {
            string DateTime;
            string SourceAccountNumber;
            string DestinationAccountNumber;
            float Amount;
            float SourceAccountBalance;
            float DestinationAccountBalance;
            string Username;
        };

    private:

        static stTransferLogRecord _ConvertTransferLogLineToRecord(string Record, string Seperator = "#//#")
        {
            stTransferLogRecord TransferLog;
            vector <string> vRecord = clsString::Split(Record,Seperator);
            
            TransferLog.DateTime = vRecord[0];
            TransferLog.SourceAccountNumber = vRecord[1];
            TransferLog.DestinationAccountNumber = vRecord[2];
            TransferLog.Amount = stod(vRecord[3]);
            TransferLog.SourceAccountBalance = stod(vRecord[4]);
            TransferLog.DestinationAccountBalance = stod(vRecord[5]);
            TransferLog.Username = vRecord[6];
            
            return TransferLog;
        }

        void _RegisterTransferLog(clsBankClient DestinationClient, double Amount)
        {
            string stDataLine = _PrepareTransferRecord(DestinationClient, Amount);
            fstream MyFile;
            MyFile.open(TransferLogFile, ios::out | ios::app);
            if(MyFile.is_open())
            {
                MyFile<<stDataLine<<endl;
                MyFile.close();
            }
        }

        string _PrepareTransferRecord(clsBankClient DestinationClient, double Amount ,string Seperator = "#//#")
        {
            string strUserRecord = "";
            strUserRecord += clsDate :: GetSystemDateTimeString() + Seperator;
            strUserRecord += AccountNumber() + Seperator;
            strUserRecord += DestinationClient.AccountNumber() + Seperator;
            strUserRecord += to_string(Amount) + Seperator;
            strUserRecord += to_string(GetAccountBalance()) + Seperator;
            strUserRecord += to_string(DestinationClient.GetAccountBalance()) + Seperator;
            strUserRecord += CurrentUser.GetUsername();
            return strUserRecord;
        }

        static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
        {
            vector <string> vClientData = clsString::Split(Line,"#//#");
            
            return clsBankClient(enMode::UpdateMode, vClientData[0],vClientData[1],vClientData[2],vClientData[3],
                vClientData[4],vClientData[5],stod(vClientData[6]));
        }

        static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
        {
            string strClientRecord = "";
            strClientRecord += Client.FirstName() + Seperator;
            strClientRecord += Client.LastName() + Seperator;
            strClientRecord += Client.Phone() + Seperator;
            strClientRecord += Client.Email() + Seperator;
            strClientRecord += Client.AccountNumber() + Seperator;
            strClientRecord += Client.GetPinCode() + Seperator;
            strClientRecord += to_string(Client._AccountBalance);
            return strClientRecord;
        }

        static vector <clsBankClient> _LoadClientsDataFromFile()
        {
            vector <clsBankClient> vClients;
            
            fstream MyFile;
            MyFile.open(ClientsFile , ios::in);
            
            if(MyFile.is_open()){
                string Line;
                while(getline(MyFile,Line))
                {
                    vClients.push_back(_ConvertLineToClientObject(Line));
                }
                MyFile.close();
            }
            return vClients;
        }

        static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
        {
            fstream MyFile;
            MyFile.open(ClientsFile, ios::out);//overwrite
            if (MyFile.is_open())
            {
                for (clsBankClient C : vClients)
                {
                    if (C.MarkedForDeleted() == false)
                    {
                        MyFile << _ConvertClientObjectToLine(C) << endl;
                    }
                }
                MyFile.close();
            }
        }

        void _AddDataLineToFile(string DataLine)
        {
            fstream MyFile;
            MyFile.open(ClientsFile, ios::out | ios::app );
            if(MyFile.is_open())
            {
                MyFile<<DataLine<<endl;
                MyFile.close();
            }
        }

        void _AddNew()
        { 
            _AddDataLineToFile(_ConvertClientObjectToLine(*this)); 
        } 

        void _Update()
        {
            vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
            for (clsBankClient & Client : _vClients)
            {
                // if(Client.AccountNumber() == this->AccountNumber())
                if(Client.AccountNumber() == AccountNumber())
                {
                    Client = *this;
                    break;
                }
            }
            _SaveCleintsDataToFile(_vClients);
        }

        static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
        }

    public:
        clsBankClient(enMode Mode,string FirstName, string LastName, string Phone, 
            string Email,string AccountNumber, string PinCode, double AccountBalance
        ) : clsPerson(FirstName,LastName,Phone,Email)
        {
            _Mode = Mode;
            _AccountNumber = AccountNumber; 
            _PinCode = PinCode; 
            _AccountBalance = AccountBalance; 
        }

        bool IsEmpty()
        {
            return (_Mode == enMode :: EmptyMode);
        }

        bool MarkedForDeleted()
        {
            return _MarkedForDelete;
        }

        string AccountNumber()
        {
            return _AccountNumber;
        }

        void SetPinCode(string PinCode)
        {
            _PinCode = PinCode;
        }

        string GetPinCode()
        {
            return _PinCode;
        }

        void SetAccountBalance(double AccountBalance)
        {
            _AccountBalance = AccountBalance;
        }

        double GetAccountBalance()
        {
            return _AccountBalance;
        }

        static clsBankClient Find(string AccountNumber)
        {
            fstream MyFile;
            MyFile.open(ClientsFile,ios::in);
            if(MyFile.is_open())
            {
                string Line;
                while(getline(MyFile,Line))
                {
                    clsBankClient Client = _ConvertLineToClientObject(Line);
                    if(Client.AccountNumber() == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyClientObject();
        }

        static clsBankClient Find(string AccountNumber , string PinCode)
        {
            fstream MyFile;
            MyFile.open(ClientsFile,ios::in);
            if(MyFile.is_open())
            {
                string Line;
                while (getline(MyFile,Line))
                {
                    clsBankClient Client = _ConvertLineToClientObject(Line, "#//#");
                    if(Client._AccountNumber == AccountNumber && Client._PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyClientObject();
        }

        static bool IsClientExist(string AccountNumber)
        {
            clsBankClient Client = clsBankClient :: Find(AccountNumber);
            return (!Client.IsEmpty());
        }

        enum enSaveResults{svFaildEmptyObject = 0 , svSucceeded = 1 , svFaildAccountNumberExists = 2};

        enSaveResults Save()
        {
            switch(_Mode)
            {
                case enMode :: EmptyMode :
                {
                    if (IsEmpty())
                    {
                        return enSaveResults :: svFaildEmptyObject;
                    }
                }
                case enMode :: UpdateMode :
                {
                    _Update();
                    return enSaveResults :: svSucceeded;
                    break;
                }
                case enMode :: AddNewMode :
                {   
                    if(IsClientExist(_AccountNumber))
                    {
                        return enSaveResults :: svFaildAccountNumberExists;
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
            //! Not Neccesary
            // return enSaveResults::svSucceeded;
        }

        static clsBankClient GetAddNewClientObject(string AccountNumber) 
        { 
            return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0); 
        } 

        bool Delete()
        {
            vector <clsBankClient> _vClients;
            _vClients = _LoadClientsDataFromFile();
            for (clsBankClient& C : _vClients)
            {
                if (C.AccountNumber() == _AccountNumber)
                {
                    C._MarkedForDelete = true;
                    break;
                }
            }
            _SaveCleintsDataToFile(_vClients);
            *this = _GetEmptyClientObject();
            return true;
        }

        static vector <clsBankClient> GetClientsList()
        {
            return _LoadClientsDataFromFile();
        }

        static double GetTotalBalances()
        {
            vector <clsBankClient> vClients = GetClientsList();
            double TotalBalances = 0;
            for(clsBankClient & C : vClients )
            {
                TotalBalances += C.GetAccountBalance();
            }
            return TotalBalances;
        }

        void Deposit(double Amount)
        {
            _AccountBalance += Amount;
            Save();
        }

        bool Withdraw(double Amount)
        {
            if (Amount > _AccountBalance)
            {
                return false;
            }
            else
            {
                _AccountBalance -= Amount;
                Save();
                return true;
            }
        }

        bool Transfer(clsBankClient & DestinationClient, double Amount)
        {
            if(!this->Withdraw(Amount))
            {
                return false;
            }
            else
            {
                DestinationClient.Deposit(Amount);
                _RegisterTransferLog(DestinationClient,Amount);
                return true;
            }
        }

        static vector<stTransferLogRecord> GetTransfersLogList()
        {
            vector<stTransferLogRecord> vTransfersLogRecord;
            fstream MyFile;
            MyFile.open(TransferLogFile , ios::in | ios::out);
            if(MyFile.is_open())
            {
                string Line;
                while (getline(MyFile,Line))
                {
                    vTransfersLogRecord.push_back(_ConvertTransferLogLineToRecord(Line));
                }
                MyFile.close();
            }
            return vTransfersLogRecord;
        }

};
