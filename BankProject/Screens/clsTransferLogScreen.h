#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "../Logic/clsBankClient.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{
    private:
        static void _PrintTransferLogRecordLine(clsBankClient :: stTransferLogRecord TransferLogRecord)
        {
            cout << setw(8) << left << "" << "| " << left << setw(25) << TransferLogRecord.DateTime;
            cout << "| " << left << setw(8)  << TransferLogRecord.SourceAccountNumber;
            cout << "| " << left << setw(8)  << TransferLogRecord.DestinationAccountNumber;    ;
            cout << "| " << left << setw(8)  << TransferLogRecord.Amount;
            cout << "| " << left << setw(10) << TransferLogRecord.SourceAccountBalance;
            cout << "| " << left << setw(10) << TransferLogRecord.DestinationAccountBalance;
            cout << "| " << left << setw(8)  << TransferLogRecord.Username;
        }
    
    public:
        static void ShowTransferLogScreen()
        {
            vector <clsBankClient :: stTransferLogRecord> vTransferRecord= clsBankClient :: GetTransfersLogList();
            string Title = "\t  Transfer Log Screen";
            string SubTitle ="\t    (" + to_string(vTransferRecord.size()) + ") Record(s).";
            _DrawScreenHeader(Title , SubTitle);

            cout << setw(8) << left << "" 
                << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
            cout << "| " << left << setw(8)  << "s.Acc";
            cout << "| " << left << setw(8)  << "D.Acc";
            cout << "| " << left << setw(8)  << "Amount";
            cout << "| " << left << setw(10) << "S.balance";
            cout << "| " << left << setw(10) << "D.balance";
            cout << "| " << left << setw(8)  << "User";
            cout << setw(8) << left << "" 
                << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            if (vTransferRecord.size() == 0)
                cout << "\t\t\t\tNo Transfer Logs Available In the System!";
            else
            {
                for (clsBankClient::stTransferLogRecord Record : vTransferRecord)
                {
                    _PrintTransferLogRecordLine(Record);
                    cout << endl;
                }
            }
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n" << endl;
        }

};
