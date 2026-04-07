#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsPeriod
{

    private:
        clsDate StartDate;
        clsDate EndDate;

    public:
        clsPeriod(clsDate StartDate, clsDate EndDate)
        {
            this-> StartDate = StartDate;
            this-> EndDate = EndDate;
        }

        static void PrintPeriod(clsPeriod Period)
        {
            cout<<"\nPeriod Starts: ";
            clsDate :: PrintDate(Period.StartDate);
            cout<<"\n\nPeriod Ends: ";
            clsDate :: PrintDate(Period.EndDate);
        }

        void PrintPeriod()
        {
            PrintPeriod(*this);
        }

        static bool IsOverlapPeriods(clsPeriod Period1, clsPeriod Period2)
        {
            if (clsDate :: CompareDates(Period2.EndDate, Period1.StartDate) == enDateCompare::Before ||
                clsDate :: CompareDates(Period2.StartDate, Period1.EndDate) == enDateCompare::After)
                return false;
            else
                return true;
        }

        bool IsOverlapPeriods(clsPeriod Period)
        {
            return IsOverlapPeriods(*this, Period);
        }

        static short GetPeriodLengthInDays(clsPeriod Period, bool IncludeEndDate)
        {
            return clsDate:: GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
        }

        short GetPeriodLengthInDays(bool IncludeEndDate)
        {
            return GetPeriodLengthInDays(*this, IncludeEndDate);
        }

        static bool IsDateWithinPeriod(clsPeriod Period, clsDate Date)
        {
            return (clsDate::CompareDates(Period.StartDate, Date) == enDateCompare::Before &&
                    clsDate::CompareDates(Period.EndDate,Date) == enDateCompare::After);
        }

        bool IsDateWithinPeriod(clsDate Date)
        {
            return IsDateWithinPeriod(*this,Date);
        }

        static void SwapPeriods(clsPeriod & Period1, clsPeriod & Period2)
        {
            clsPeriod Temp = Period1;
            Period1 = Period2;
            Period2 = Temp;
        }

        void SwapPeriods(clsPeriod & Period)
        {
            SwapPeriods(*this,Period);
        }

        static short CountOverlapDays(clsPeriod Period1, clsPeriod Period2)
        {
            if (!IsOverlapPeriods(Period1, Period2))
                return 0;

            if (! clsDate :: IsDate1BeforeDate2(Period1.StartDate, Period2.StartDate))
            {
                SwapPeriods(Period1, Period2);
            }

            short NumberOfDays = 0;

            while (clsDate :: IsDate1BeforeDate2(Period2.StartDate, Period1.EndDate) )
                {
                    clsDate :: IncreaseDateByOneDay(Period2.StartDate);
                    NumberOfDays++;
                }
                return NumberOfDays;
        }

        short CountOverlapDays(clsPeriod Period)
        {
            return CountOverlapDays(*this,Period);
        }

};
