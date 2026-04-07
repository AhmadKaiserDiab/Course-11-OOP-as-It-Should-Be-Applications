#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "clsString.h"
using namespace std;

class clsDate
{
    private:
        short _Day;
        short _Month;
        short _Year;

        static void PrintMonthDays(short FirstDayInMonth, short NumberOfDays)
        {
            int i;
            for (i = 0; i < FirstDayInMonth; i++)
                printf("     ");
            for (int j = 1; j <= NumberOfDays; j++)
            {
                printf("%5d", j);
                if (++i == 7)
                {
                    i = 0;
                    printf("\n");
                }
            }
        }

        static clsDate StringToDate(string DateString)
        {
            clsDate Date;
            vector<string> vDate = clsString :: Split(DateString, "/");
            Date._Day = stoi(vDate[0]);
            Date._Month = stoi(vDate[1]);
            Date._Year = stoi(vDate[2]);
            return Date;
        }

    public:
        clsDate()
        {
            time_t t = time(0); // get time now
            tm *now = localtime(&t);

            _Year = now->tm_year + 1900 ;
            _Month = now->tm_mon + 1 ;
            _Day = now->tm_mday ;
        }

        clsDate(string DateString)
        {
            *this =  StringToDate(DateString);
        }

        clsDate(short Day, short Month, short Year)
        {
            _Day = Day;
            _Month = Month;
            _Year = Year;
        }

        clsDate(short DaysFromTheBeginingOfTheYear, short Year)
        {
            *this = DateFromDayOrder(DaysFromTheBeginingOfTheYear,Year);
        }

        void SetDay(short Day)
        {
            _Day = Day;
        }
    
        short GetDay()
        {
            return _Day;
        }
        
        void SetMonth(short Month)
        {
            _Month = Month;
        }
    
        short GetMonth()
        {
            return _Month;
        }

        void SetYear(short Year)
        {
            _Year = Year;
        }
    
        short GetYear()
        {
            return _Year;
        }

        static bool IsLeapYear(clsDate Date)
        {
            return ( Date._Year % 400 == 0 ) || 
                ( Date._Year % 4 == 0 && Date._Year % 100 != 0 );
        }

        bool IsLeapYear()
        {
            return IsLeapYear(*this);
        }

        struct stYear
        {
            short numberOfDaysInYear;
            short numberOfHoursInYear;
            int numberOfMinutesInYear;
            int numberOfSecondsInYear;
        };

        struct stMonth
        {
            short numberOfDaysInMonth;
            short numberOfHoursInMonth;
            int numberOfMinutesInMonth;
            int numberOfSecondsInMonth;
        };

        static stYear GetYearDetails(clsDate Date)
        {
            stYear TempYear;

            TempYear.numberOfDaysInYear = IsLeapYear(Date) ? 366 : 365;
            TempYear.numberOfHoursInYear = TempYear.numberOfDaysInYear * 24;
            TempYear.numberOfMinutesInYear = TempYear.numberOfHoursInYear * 60;
            TempYear.numberOfSecondsInYear = TempYear.numberOfMinutesInYear * 60;

            return TempYear;
        }

        static stMonth GetMonthDetails(clsDate Date)
        {
            stMonth TempMonth;

                if (Date._Month < 1 || Date._Month > 12 )
            {
                TempMonth.numberOfDaysInMonth = 0;
            }
            else
            {
                short numberOfdays [12]  =  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
                TempMonth.numberOfDaysInMonth = (Date._Month == 2 && IsLeapYear(Date)) ? 
                                                29 : numberOfdays[ Date._Month-1] ;
            }

            TempMonth.numberOfHoursInMonth = TempMonth.numberOfDaysInMonth * 24;
            TempMonth.numberOfMinutesInMonth = TempMonth.numberOfHoursInMonth * 60;
            TempMonth.numberOfSecondsInMonth = TempMonth.numberOfMinutesInMonth * 60;

            return TempMonth;
        }

        static void PrintYearDetails(clsDate Date)
        {
            stYear stYearDetails = GetYearDetails(Date);

            cout << "\nNumber Of Days    In Year [" << Date._Year << "] is: " 
                << stYearDetails.numberOfDaysInYear << endl;
            cout << "Number Of Hours   In Year [" << Date._Year << "] is: " 
                << stYearDetails.numberOfHoursInYear << endl;
            cout << "Number Of Minutes In Year [" << Date._Year << "] is: " 
                << stYearDetails.numberOfMinutesInYear << endl;
            cout << "Number Of Seconds In Year [" << Date._Year << "] is: " 
                << stYearDetails.numberOfSecondsInYear << endl;
        }

        void PrintYearDetails()
        {
            PrintYearDetails(*this);
        }

        void PrintMonthDetails(clsDate Date)
        {
            stMonth stMonthDetails = GetMonthDetails(Date);

            cout << "\nNumber Of Days    In Month [" << Date._Month << "] is: " 
                << stMonthDetails.numberOfDaysInMonth << endl;
            cout << "Number Of Hours   In Month [" << Date._Month << "] is: " 
                << stMonthDetails.numberOfHoursInMonth << endl;
            cout << "Number Of Minutes In Month [" << Date._Month << "] is: " 
                << stMonthDetails.numberOfMinutesInMonth << endl;
            cout << "Number Of Seconds In Month [" << Date._Month << "] is: " 
                << stMonthDetails.numberOfSecondsInMonth << endl;
        }

        static short DayOfWeekOrder(clsDate Date)
        {
            short a, y, m;
            a = (14 - Date._Month) / 12;
            y = Date._Year - a;
            m = Date._Month + (12 * a) - 2;
            return (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + ((m * 31) / 12)) % 7;
        }

        short DayOfWeekOrder()
        {
            return DayOfWeekOrder(*this);
        }

        static string DayShortName(clsDate Date) 
        {
            short DayOrder = DayOfWeekOrder(Date);
            string arrDayNames[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" }; 
            return arrDayNames[DayOrder];
        }

        string DayShortName()
        {
            return DayShortName(*this);
        }

        static void PrintDayDetails(clsDate Date)
        {
            short DayOrder = DayOfWeekOrder(Date);
            printf("Today Is %s , %d/%d/%d \n" , 
            DayShortName(Date).c_str(), Date._Day, Date._Month, Date._Year);
        }

        void PrintDayDetails()
        {
            PrintDayDetails(*this);
        }

        static short NumberOfDaysInAMonth(clsDate Date)
        {
            if (Date._Month < 1 || Date._Month > 12)
            {
                return 0;
            }
            else
            {
                short numberOfdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                return (Date._Month == 2 && IsLeapYear(Date)) ? 29 : numberOfdays[Date._Month - 1];
            }
        }

        short NumberOfDaysInAMonth()
        {
            return NumberOfDaysInAMonth(*this);
        }

        static string MonthShortName(clsDate Date)
        {
            string Months[12] =
                {
                    "Jan", "Feb", "Mar",
                    "Apr", "May", "Jun",
                    "Jul", "Aug", "Sep",
                    "Oct", "Nov", "Dec"};
            return (Months[Date._Month - 1]);
        }

        string MonthShortName()
        {
            return MonthShortName(*this);
        }

        static void PrintMonthCalender(clsDate Date)
        {
            short FirstDayInMonth = DayOfWeekOrder(clsDate(1, Date._Month, Date._Year));
            short NumberOfDays = NumberOfDaysInAMonth(Date);

            printf("________________%s________________\n\n",
                    MonthShortName(Date).c_str());

            cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n"
                << endl;

            PrintMonthDays(FirstDayInMonth, NumberOfDays);
            cout << "\n___________________________________" << endl;
        }

        void PrintMonthCalender()
        {
            PrintMonthCalender(*this);
        }

        static void PrintYearCalender(clsDate Date)
        {
            printf("\n _________________________________\n\n");
            printf("      Calendar - %d\n", Date._Year);
            printf(" _________________________________\n\n");

            for (int Month = 1; Month <= 12; Month++)
            {
                PrintMonthCalender(Date);
                cout << "\n"<< endl;
            }
        }

        void PrintYearCalender()
        {
            PrintYearCalender(*this);
        }

        static short NumberOfDaysFromTheBeginingOfTheYear(clsDate Date)
        {
            short TotalDays = 0;
            for ( short Counter = 1; Counter < Date._Month ; Counter++)
            {
                TotalDays += NumberOfDaysInAMonth(clsDate(Date._Day,Counter,Date._Year));
            }
            return TotalDays + Date._Day;
        }

        short NumberOfDaysFromTheBeginingOfTheYear()
        {
            return NumberOfDaysFromTheBeginingOfTheYear(*this);
        }

        static clsDate DateFromDayOrder(short DayOrder, short Year)
        {
            clsDate Date;
            Date._Day = DayOrder;
            Date._Month = 1;
            Date._Year = Date._Year;
            while (true)
            {
                short DaysInMonth = NumberOfDaysInAMonth(Date);
                if (DaysInMonth >= Date._Day)
                {
                    break;
                }
                else
                {
                    Date._Day-=DaysInMonth;
                    Date._Month++;
                }
            }
            return Date;
        }

        void DateAddDays(short Days)
        {
            short RemainingDays = Days +
                    NumberOfDaysFromTheBeginingOfTheYear(*this);
            short MonthDays = 0;
            this->_Month = 1;
            while (true)
            {
                MonthDays = NumberOfDaysInAMonth(*this);
                if (RemainingDays > MonthDays)
                {
                    RemainingDays -= MonthDays;
                    this->_Month++;
                    if (this->_Month > 12)
                    {
                        this->_Month = 1;
                        this->_Year++;
                    }
                }
                else
                {
                    this->_Day = RemainingDays;
                    break;
                }
            }
        }

        static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
        {
            return (Date1._Year < Date2._Year) ? true : 
            (   
                (Date1._Year == Date2._Year) ? 
                (
                    Date1._Month < Date2._Month ? true : 
                    (
                        Date1._Month == Date2._Month ? 
                        Date1._Day < Date2._Day : false
                    )
                ) 
                : false
            );
        }

        bool IsDate1BeforeDate2(clsDate Date)
        {
            return IsDate1BeforeDate2(*this, Date);
        }

        static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
        {
            return  Date1._Year == Date2._Year ? ( 
                        Date1._Month == Date2._Month ? (
                            Date1._Day == Date2._Day  ? true : false ) : false ) : false ;
        }

        bool IsDate1EqualDate2(clsDate Date)
        {
            return IsDate1EqualDate2(*this,Date);
        }

        static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
        {
            return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
        }

        bool IsDate1AfterDate2(clsDate Date)
        {
            return IsDate1AfterDate2(*this, Date);
        }

        static bool IsLastDayInMonth(clsDate Date)
        {
            return  Date._Day == NumberOfDaysInAMonth(Date)  ;
        }

        bool IsLastDayInMonth()
        {
            return  IsLastDayInMonth(*this)  ;
        }

        static bool IsLastMonthInYear(clsDate Date)
        {
            return  Date._Month == 12  ;
        }

        bool IsLastMonthInYear()
        {
            return  IsLastMonthInYear(*this);
        }

        static clsDate IncreaseDateByOneDay(clsDate & Date)
        {
            if (IsLastDayInMonth(Date))
            {
                if (IsLastMonthInYear(Date))
                {
                    Date._Day = 1;
                    Date._Month = 1;
                    Date._Year++;
                }
                else
                {
                    Date._Day = 1;
                    Date._Month++;
                }
            }
            else
            {
                Date._Day++;
            }
            return Date;
        }

        clsDate IncreaseDateByOneDay()
        {
            return IncreaseDateByOneDay(*this);
        }

        static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
        {
            int Days = 0;
            short SwapFlagValue = 1;
            if (!IsDate1BeforeDate2(Date1, Date2))
            {
                SwapDates(Date1, Date2);
                SwapFlagValue = -1;
            }
            while (IsDate1BeforeDate2(Date1, Date2))
            {
                Days++;
                Date1 = IncreaseDateByOneDay(Date1);
            }
            return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
        }

        int GetDifferenceInDays(clsDate Date, bool IncludeEndDay = false)
        {
            return GetDifferenceInDays(*this, Date, false);
        }

        static int CalculateAgeInDays(clsDate BirthDate)
        {
            return GetDifferenceInDays(BirthDate, clsDate(), true);
        }

        static void SwapDates(clsDate &Date1, clsDate &Date2)
        {
            clsDate TempDate;
            TempDate._Year = Date1._Year;
            TempDate._Month = Date1._Month;
            TempDate._Day = Date1._Day;
            Date1._Year = Date2._Year;
            Date1._Month = Date2._Month;
            Date1._Day = Date2._Day;
            Date2._Year = TempDate._Year;
            Date2._Month = TempDate._Month;
            Date2._Day = TempDate._Day;
        }

        void SwapDates(clsDate Date)
        {
            SwapDates(*this, Date);
        }

        static clsDate IncreaseDateByXDays(clsDate & Date, short NumberOfDays)
        {
            for (int i = 1; i <= NumberOfDays; i++)
            {
                Date = IncreaseDateByOneDay(Date);
            }
            return Date;
        }

        clsDate IncreaseDateByXDays(short NumberOfDays)
        {
            return IncreaseDateByXDays(*this, NumberOfDays);
        }

        static clsDate IncreaseDateByOneWeek(clsDate & Date)
        {
            for (int i = 1; i <= 7; i++)
            {
                Date = IncreaseDateByOneDay(Date);
            }
            return Date;
        }

        clsDate IncreaseDateByOneWeek()
        {
            return IncreaseDateByOneWeek(*this);
        }

        static clsDate IncreaseDateByXWeeks(clsDate & Date, short NumberOfWeeks)
        {
            for (int i = 1; i <= NumberOfWeeks; i++)
            {
                Date = IncreaseDateByOneWeek(Date);
            }
            return Date;
        }

        clsDate IncreaseDateByXWeeks(short NumberOfWeeks)
        {
            return IncreaseDateByXWeeks(*this, NumberOfWeeks);
        }

        static clsDate IncreaseDateByOneMonth(clsDate & Date)
        {
            if (IsLastMonthInYear(Date))
            {
                Date._Month = 1;
                Date._Year++;
            }
            else
            {
                Date._Month++;
            }
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByOneMonth()
        {
            return IncreaseDateByOneMonth(*this) ;
        }

        static clsDate IncreaseDateByXMonths(clsDate & Date, short NumberOfMonths)
        {
            for (int i = 1; i <= NumberOfMonths; i++)
            {
                Date = IncreaseDateByOneMonth(Date);
            }
            return Date;
        }

        clsDate IncreaseDateByXMonths(short NumberOfMonths)
        {
            return IncreaseDateByXMonths(*this, NumberOfMonths);
        }

        static clsDate IncreaseDateByOneYear(clsDate & Date)
        {
            Date._Year++;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByOneYear()
        {
            return IncreaseDateByOneYear(*this);
        }

        static clsDate IncreaseDateByXYears(clsDate & Date, short NumberOfYears)
        {
            for (int i = 1; i <= NumberOfYears; i++)
            {
                Date = IncreaseDateByOneYear(Date);
            }
            return Date;
        }

        clsDate IncreaseDateByXYears(short NumberOfYears)
        {
            return IncreaseDateByXYears(*this, NumberOfYears);
        }

        static clsDate IncreaseDateByXYearsFaster(clsDate & Date, short NumberOfYears)
        {
            Date._Year += NumberOfYears;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByXYearsFaster(short NumberOfYears)
        {
            return IncreaseDateByXYearsFaster(*this, NumberOfYears);
        }

        static clsDate IncreaseDateByOneDecade(clsDate & Date)
        {
            Date._Year += 10;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByOneDecade()
        {
            return IncreaseDateByOneDecade(*this);
        }

        static clsDate IncreaseDateByXDecades(clsDate & Date, short NumberOfDecades)
        {
            for (short i = 1; i <= NumberOfDecades * 10; i++)
            {
                Date = IncreaseDateByOneYear(Date);
            }
            return Date;
        }

        clsDate IncreaseDateByXDecades(short NumberOfDecades)
        {
            return IncreaseDateByXDecades(*this,NumberOfDecades);
        }

        static clsDate IncreaseDateByXDecadesFaster(clsDate & Date, short NumberOfDecades)
        {
            Date._Year += NumberOfDecades * 10;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByXDecadesFaster(short NumberOfDecades)
        {
            return IncreaseDateByXDecadesFaster(*this, NumberOfDecades);
        }

        static clsDate IncreaseDateByOneCentury(clsDate & Date)
        {
            Date._Year += 100;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByOneCentury()
        {
            return IncreaseDateByOneCentury(*this);
        }

        static clsDate IncreaseDateByOneMillennium(clsDate & Date)
        {
            Date._Year += 1000;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate IncreaseDateByOneMillennium()
        {
            return IncreaseDateByOneMillennium(*this);
        }

        static clsDate DecreaseDateByOneDay(clsDate & Date)
        {
            if (Date._Day == 1)
            {
                if (Date._Month == 1)
                {
                    Date._Day = 31;
                    Date._Month = 12;
                    Date._Year--;
                }
                else
                {
                    Date._Month--;
                    Date._Day = NumberOfDaysInAMonth(Date);
                }
            }
            else
            {
                Date._Day--;
            }
            return Date;
        }

        clsDate DecreaseDateByOneDay()
        {
            return DecreaseDateByOneDay(*this);
        }

        static clsDate DecreaseDateByXDays(clsDate & Date, short NumberOfDays)
        {
            for (int i = 1; i <= NumberOfDays; i++)
            {
                Date = DecreaseDateByOneDay(Date);
            }
            return Date;
        }

        clsDate DecreaseDateByXDays(short NumberOfDays)
        {
            return DecreaseDateByXDays(*this, NumberOfDays);
        }

        static clsDate DecreaseDateByOneWeek(clsDate & Date)
        {
            for (int i = 1; i <= 7; i++)
            {
                Date = DecreaseDateByOneDay(Date);
            }
            return Date;
        }

        clsDate DecreaseDateByOneWeek()
        {
            return DecreaseDateByOneWeek(*this);
        }

        static clsDate DecreaseDateByXWeeks(clsDate & Date, short NumberOfWeeks)
        {
            for (int i = 1; i <= NumberOfWeeks; i++)
            {
                Date = DecreaseDateByOneWeek(Date);
            }
            return Date;
        }

        clsDate DecreaseDateByXWeeks(short NumberOfWeeks)
        {
            return DecreaseDateByXWeeks(*this, NumberOfWeeks);
        }

        static clsDate DecreaseDateByOneMonth(clsDate & Date)
        {
            if (Date._Month == 1)
            {
                Date._Month = 12;
                Date._Year--;
            }
            else
            {
                Date._Month--;
            }
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByOneMonth()
        {
            return DecreaseDateByOneMonth(*this);
        }

        static clsDate DecreaseDateByXMonths(clsDate & Date, short NumberOfMonths)
        {
            for (int i = 1; i <= NumberOfMonths; i++)
            {
                Date = DecreaseDateByOneMonth(Date);
            }
            return Date;
        }

        clsDate DecreaseDateByXMonths(short NumberOfMonths)
        {
            return DecreaseDateByXMonths(*this, NumberOfMonths);
        }

        static clsDate DecreaseDateByOneYear(clsDate & Date)
        {
            Date._Year--;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByOneYear()
        {
            return DecreaseDateByOneYear(*this);
        }

        static clsDate DecreaseDateByXYears(clsDate & Date, short NumberOfYears)
        {
            for (int i = 1; i <= NumberOfYears; i++)
            {
                Date = DecreaseDateByOneYear(Date);
            }
            return Date;
        }

        clsDate DecreaseDateByXYears(short NumberOfYears)
        {
            return DecreaseDateByXYears(*this, NumberOfYears);
        }

        static clsDate DecreaseDateByXYearsFaster(clsDate & Date, short NumberOfYears)
        {
            Date._Year -= NumberOfYears;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByXYearsFaster(short NumberOfYears)
        {
            return DecreaseDateByXYearsFaster(*this, NumberOfYears);
        }

        static clsDate DecreaseDateByOneDecade(clsDate & Date)
        {
            Date._Year -= 10;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByOneDecade()
        {
            return DecreaseDateByOneDecade(*this);
        }

        static clsDate DecreaseDateByXDecades(clsDate & Date, short NumberOfDecades)
        {
            for (short i = 1; i <= NumberOfDecades * 10; i++)
            {
                Date = DecreaseDateByOneYear(Date);
            }
            return Date;
        }

        clsDate DecreaseDateByXDecades(short NumberOfDecades)
        {
            return DecreaseDateByXDecades(*this, NumberOfDecades);
        }

        static clsDate DecreaseDateByXDecadesFaster(clsDate & Date, short NumberOfDecades)
        {
            Date._Year -= NumberOfDecades * 10;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByXDecadesFaster(short NumberOfDecades)
        {
            return DecreaseDateByXDecadesFaster(*this,NumberOfDecades);
        }

        static clsDate DecreaseDateByOneCentury(clsDate & Date)
        {
            Date._Year -= 100;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByOneCentury()
        {
            return DecreaseDateByOneCentury(*this);
        }

        static clsDate DecreaseDateByOneMillennium(clsDate & Date)
        {
            Date._Year -= 1000;
            short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date);
            if (Date._Day > NumberOfDaysInCurrentMonth)
            {
                Date._Day = NumberOfDaysInCurrentMonth;
            }
            return Date;
        }

        clsDate DecreaseDateByOneMillennium()
        {
            return DecreaseDateByOneMillennium(*this);
        }

        static bool IsEndOfWeek(clsDate Date)
        {
            short DayOrder = DayOfWeekOrder(Date);
            return (DayOrder == 6);
        }

        bool IsEndOfWeek()
        {
            return IsEndOfWeek(*this);
        }

        static bool IsWeekEnd(clsDate Date)
        {
            short DayOrder = DayOfWeekOrder(Date);
            return (DayOrder == 5 || DayOrder == 6 );
        }

        bool IsWeekEnd()
        {
            return IsWeekEnd(*this);
        }

        static bool IsBusinessDay(clsDate Date)
        {
            return (!IsWeekEnd(Date));
        }

        bool IsBusinessDay()
        {
            return (!IsWeekEnd(*this));
        }

        static short DaysUntilEndOfTheWeek(clsDate Date)
        {
            short DayOrder = DayOfWeekOrder(Date);
            return 6 - DayOrder ;
        }

        short DaysUntilEndOfTheWeek()
        {
            return DaysUntilEndOfTheWeek(*this) ;
        }

        static short DaysUntilEndOfTheMonth(clsDate Date)
        {
            short RemainingDays = NumberOfDaysInAMonth(Date) - Date._Day;
            return RemainingDays;
        }

        short DaysUntilEndOfTheMonth()
        {
            return DaysUntilEndOfTheMonth(*this);
        }

        static short NumberOfDaysInAYear(clsDate Date)
        {
            return IsLeapYear(Date) ? 366 : 365 ;
        }

        short NumberOfDaysInAYear()
        {
            return NumberOfDaysInAYear(*this) ;
        }

        static short DaysUntilEndOfTheYear(clsDate Date)
        {
            short RemainingDays = NumberOfDaysInAYear(Date) - 
                NumberOfDaysFromTheBeginingOfTheYear(Date);
            return RemainingDays;
        }

        short DaysUntilEndOfTheYear()
        {
            return DaysUntilEndOfTheYear(*this);
        }

        static short CalculateVacationDays(clsDate StartDate, clsDate EndDate)
        {
            short numberOfVacationDays = 0;
            while (IsDate1BeforeDate2(StartDate, EndDate))
            {
                if (IsBusinessDay(StartDate))
                {
                    numberOfVacationDays++;
                }
                StartDate = IncreaseDateByOneDay(StartDate);
            }
            return numberOfVacationDays;
        }

        static clsDate CalculateVacationEndDate(clsDate StartDate, short NumberOfDays)
        {
            while (NumberOfDays != 0)
            {
                if (IsBusinessDay(StartDate))
                {
                    NumberOfDays--;
                }
                StartDate = IncreaseDateByOneDay(StartDate);
            }
            return StartDate;
        }

        enum enDateCompare
        { Before = -1, Equal = 0, After = 1 };

        static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
        {
            if (IsDate1BeforeDate2(Date1, Date2))
                return enDateCompare::Before;
            if (IsDate1EqualDate2(Date1, Date2))
                return enDateCompare::Equal;

            return enDateCompare::After;
        }

        enDateCompare CompareDates(clsDate Date)
        {
            return CompareDates(*this, Date) ;
        }

        static bool IsValidDate(clsDate Date)
        {
            return Date._Year > 0 ? 
            (Date._Month >= 1 && Date._Month <= 12) ? 
                    (Date._Day <= NumberOfDaysInAMonth(Date) 
                    && Date._Day > 0) 
            : false : false   ;
        }

        bool IsValidDate()
        {
            return IsValidDate(*this);
        }

        static string DateToString(clsDate Date)
        {
            return to_string(Date._Day) + "/" 
                    + to_string(Date._Month)
                    + "/" + to_string(Date._Year);
        }

        string DateToString()
        {
            return DateToString(*this);
        }

        static string FormateDate(clsDate Date, string DateFormat )
        {
            string FormattedDateString = "";
            FormattedDateString = clsString :: ReplaceWord(DateFormat, "dd", to_string(Date._Day));
            FormattedDateString = clsString :: ReplaceWord(FormattedDateString, "mm", to_string(Date._Month));
            FormattedDateString = clsString :: ReplaceWord(FormattedDateString, "yyyy", to_string(Date._Year));
            return FormattedDateString;
        }

        string FormateDate(string DateFormat)
        {
            return FormateDate(*this,DateFormat);
        }

        static void PrintDate(clsDate Date)
        {
            cout << DateToString(Date) << endl;
        }

        void PrintDate()
        {
            PrintDate(*this);
        }

        static clsDate GetSystemDate()
        {
            //system date
            time_t t = time(0);
            tm* now = localtime(&t);
            
            short Day, Month, Year;
            
            Year = now->tm_year + 1900;
            Month = now->tm_mon + 1;
            Day = now->tm_mday;
    
            return clsDate(Day, Month, Year);
        }

        static string GetSystemDateTimeString()
        {
            //system date
            time_t t = time(0);
            tm* now = localtime(&t);
            short Day, Month, Year , Hour, Minute , Second;
            
            Year = now->tm_year + 1900;
            Month = now->tm_mon + 1;
            Day = now->tm_mday;
            Hour = now->tm_hour;
            Minute = now->tm_min;
            Second = now->tm_sec;

            return ( 
                to_string(Day) + "/" +
                to_string(Month) + "/" +
                to_string(Year) + " - " +
                to_string(Hour) + ":" +
                to_string(Minute) + ":" +
                to_string(Second)
            );
        }

};
