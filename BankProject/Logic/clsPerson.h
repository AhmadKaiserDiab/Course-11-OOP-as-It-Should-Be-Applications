#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
    private:
        string _FirstName;
        string _LastName;
        string _Phone;
        string _Email;

    public:
        clsPerson(string FirstName, string LastName, string Phone, string Email)
        {
            _FirstName =  FirstName;
            _LastName = LastName;
            _Phone = Phone;
            _Email = Email;
        }

        void SetFirstName(string FirstName)
        {
            _FirstName = FirstName;
        }

        string FirstName()
        {
            return _FirstName;
        }

        void SetLastName(string LastName)
        {
            _LastName = LastName;
        }

        string LastName()
        {
            return _LastName;
        }

        void SetEmail(string Email)
        {
            _Email = Email;
        }

        string Email()
        {
            return _Email;
        }

        void SetPhone(string Phone)
        {
            _Phone = Phone;
        }

        string Phone()
        {
            return _Phone;
        }

        string FullName()
        {
            return _FirstName + " "+ _LastName;
        }

        void Print()
        {
            cout<<"\nInfo:";
            cout<<"\n_______________________________________";
            cout<<"\nFirst Name: " <<_FirstName;
            cout<<"\nLast Name : " <<_LastName;
            cout<<"\nFull Name : " <<FullName();
            cout<<"\nEmail     : " <<_Email;
            cout<<"\nPhone     : " <<_Phone;
            cout<<"\n_______________________________________"<<endl;
            }

};
