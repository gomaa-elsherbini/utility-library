#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
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

	static void DistributeMonthDays(short year, short month)
	{
		short days = NumberOfDaysInMonth(year, month);

		short firstDayOrder = OrderOfDay(year, month, 1);

		for (int i = 1; i <= firstDayOrder; i++)
			printf("     ");

		for (int x = 1; x <= days; x++)
		{
			printf("%5d", x);
			if ((x + firstDayOrder) % 7 == 0)
				cout << endl;
		}
		cout << endl;
	}
	enum enCompareTwoDates { After = 1, Before = -1, Equal = 0 };
	static enCompareTwoDates CheckTwoDates(clsDate Date1, clsDate Date2)
	{
		return (IsDate1AfterDate2(Date1, Date2) ? enCompareTwoDates::After :
			(IsDate1EqualDate2(Date1, Date2)) ? enCompareTwoDates::Equal :
			enCompareTwoDates::Before);
	}

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon+1;
		_Year = now->tm_year + 1900;
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(string D)
	{
		vector<string>vDate = clsString::splitString(D, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Days, short Year)
	{
		clsDate Date = DateFromNumberOfDays(Year, Days);

		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short Day()
	{
		return _Day;
	}
	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short Month()
	{
		return _Month;
	}
	void SetYear(short Year)
	{
		_Year = Year;
	}
	short Year()
	{
		return _Year;
	}

	__declspec(property(get = Day, put = SetDay))short day;
	__declspec(property(get = Month, put = SetMonth))short month;
	__declspec(property(get = Year, put = SetYear))short year;

	static void Print(clsDate Date)
	{
		cout << to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}
	void Print()
	{
		return Print(*this);
	}

	static clsDate DateFromNumberOfDays(short year, short numberOfDays)
	{
		/*short month = 1;
		short monthDays = 0;

		do
		{
			monthDays = NumberOfDaysInMonth(year, month);
			numberOfDays -= monthDays;
			month++;

			if (month == 12)
			{
				year++;
				monthDays = NumberOfDaysInMonth(year, month);
				numberOfDays -= monthDays;
				month = 1;
			}
			else
				monthDays = NumberOfDaysInMonth(year, month);

		} while (numberOfDays > monthDays);

		Date._Day = numberOfDays;
		Date._Month = month;
		Date._Year = year;*/
		clsDate Date; // 1/1/2022

		Date._Day = 1;
		Date._Month = 1;
		Date._Year = year;

		while (numberOfDays != 0)
		{
			Date = Date.IncreaseDateByOneDay();

			numberOfDays--;
		}

		return Date;
	}
	clsDate DateFromNumberOfDays(short numberOfDays)
	{
		return DateFromNumberOfDays(_Year, numberOfDays);
	}

	static bool IsLeapYear(short year)
	{
		return (year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0)));
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInYear(short year)
	{
		return IsLeapYear(year) ? 366 : 365;
	}
	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_Year);
	}
	
	static int NumberOfHoursInYear(short year)
	{
		return (NumberOfDaysInYear(year) * 24);
	}
	int NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short year)
	{
		return NumberOfHoursInYear(year) * 60;
	}
	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short year)
	{
		return NumberOfMinutesInYear(year) * 60;
	}
	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_Year);
	}

	static short NumberOfDaysInMonth(short year, short month)
	{
		if (month == 2)
		{
			if (IsLeapYear(year))
				return  29;
			else
				return  28;
		}

		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return  31;

		else if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;

		else
			return 0;
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static int NumberOfHoursInMonth(short year, short month)
	{
		return (NumberOfDaysInMonth(year, month) * 24);
	}
	int NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInMonth(short year, short month)
	{
		return NumberOfHoursInMonth(year, month) * 60;
	}
	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short year, short month)
	{
		return NumberOfMinutesInMonth(year, month) * 60;
	}
	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short OrderOfDay(short year, short month, short day)
	{
		short a = (14 - month) / 12;
		short y = year - a;
		short m = month + (12 * a) - 2;

		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short OrderOfDay()
	{
		return OrderOfDay(_Year, _Month, _Day);
	}

	static string NameOfDay(short year, short month, short day)
	{
		short order = OrderOfDay(year, month, day);
		string arrOfDaysNames[7] = { "Sun","Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arrOfDaysNames[order];
	}
	string NameOfDay()
	{
		return NameOfDay(_Year, _Month, _Day);
	}

	static string NameOfMonth(short month)
	{
		string arrOfMonths[12] = { "Jan", "Feb", "Mar", "App", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		return arrOfMonths[month - 1];
	}
	string NameOfMonth()
	{
		return NameOfMonth(_Month);
	}
	
	static void PrintMonthCalender(short year, short month)
	{
		cout << "\n  ______________ " << NameOfMonth(month) << " ______________\n\n";

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		DistributeMonthDays(year, month);

		cout << "  _________________________________\n";

	}
	void PrintMonthCalender()
	{
		return PrintMonthCalender(_Year, _Month);
	}

	static short DaysFromBeginningOfYear(short year, short month, short day)
	{
		short numberOfDays = 0;

		for (short mon = 1; mon < month; mon++)
			numberOfDays += NumberOfDaysInMonth(year, mon);
		
		numberOfDays += day;

		return numberOfDays;
	}
	short DaysFromBeginningOfYear()
	{
		return DaysFromBeginningOfYear(_Year, _Month, _Day);
	}

	static clsDate AddDaysToDate(clsDate Date, short numberOfDays)
	{
		return IncreaseDateByXDays(Date, numberOfDays);
	}
	clsDate AddDaysToDate(short numberOfDays)
	{
		return AddDaysToDate(*this, numberOfDays);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? (Date1._Day < Date2._Day) : false)) : false);
	}
	bool IsBeforeDate(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);;
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? Date1._Day == Date2._Day : false) : false;
	}
	bool IsEqualDate(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDayIsLastDay(clsDate Date)
	{
		return Date._Day == NumberOfDaysInMonth(Date._Year, Date._Month);
	}
	bool IsDayIsLastDay()
	{
		return IsDayIsLastDay(*this);
	}

	static bool IsMonthIsLastMonth(clsDate Date)
	{
		return Date._Month == 12;
	}
	bool IsMonthIsLastMonth()
	{
		return IsMonthIsLastMonth(*this);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (IsDayIsLastDay(Date))
		{
			if (IsMonthIsLastMonth(Date))
			{
				Date._Month = 1;
				Date._Year++;
			}
			else
				Date._Month++;

			Date._Day = 1;
		}
		else
			Date._Day++;

		return Date;
	}
	clsDate IncreaseDateByOneDay()
	{
		return IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate Date, short numberDays)
	{
		for (short day = 1; day <= numberDays; day++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	clsDate IncreaseDateByXDays(short numberDays)
	{
		return IncreaseDateByXDays(*this,numberDays);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		return IncreaseDateByXDays(Date, 7);
	}
	clsDate IncreaseDateByOneWeek()
	{
		return IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, short numberWeeks)
	{
		for (short week = 1; week <= numberWeeks; week++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	clsDate IncreaseDateByXWeeks(short numberWeeks)
	{
		return IncreaseDateByXWeeks(*this, numberWeeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date._Month == 12)
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
			Date._Month++;

		short monthDays = NumberOfDaysInMonth(Date._Year, Date._Month);

		Date._Day = (Date._Day > monthDays) ? monthDays : Date._Day;

		return Date;
	}
	clsDate IncreaseDateByOneMonth()
	{
		return IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, short numberMonths)
	{
		for (short month = 1; month <= numberMonths; month++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	clsDate IncreaseDateByXMonths(short numberMonths)
	{
		return IncreaseDateByXMonths(*this, numberMonths);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date._Year++;
		return Date;
	}
	clsDate IncreaseDateByOneYear()
	{
		return IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, short numberOfYears)
	{
		for (short year = 1; year <= numberOfYears; year++)
			Date = IncreaseDateByOneYear(Date);
		return Date;
	}
	clsDate IncreaseDateByXYears(short numberOfYears)
	{
		return IncreaseDateByXYears(*this, numberOfYears);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short numberOfYears)
	{
		Date._Year += numberOfYears;
		return Date;
	}
	clsDate IncreaseDateByXYearsFaster(short numberOfYears)
	{
		return IncreaseDateByXYearsFaster(*this, numberOfYears);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		Date._Year += 10;
		return Date;
	}
	clsDate IncreaseDateByOneDecade()
	{
		return IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date, short numberDecades)
	{
		for (short decade = 1; decade <= numberDecades; decade++)
			Date = IncreaseDateByOneDecade(Date);

		return Date;
	}
	clsDate IncreaseDateByXDecades(short numberDecades)
	{
		return IncreaseDateByXDecades(*this, numberDecades);
	}
	
	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, short numberOfDecades)
	{
		Date._Year += numberOfDecades * 10;
		return Date;
	}
	clsDate IncreaseDateByXDecadesFaster(short numberOfDecades)
	{
		return IncreaseDateByXDecadesFaster(*this, numberOfDecades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		Date._Year += 100;
		return Date;
	}
	clsDate IncreaseDateByOneCentury()
	{
		return IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMilinium(clsDate Date)
	{
		Date._Year += 1000;
		return Date;
	}
	clsDate IncreaseDateByOneMilinium()
	{
		return IncreaseDateByOneMilinium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
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
				Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
			}
		}
		else
			Date._Day--;

		return Date;
	}
	clsDate DecreaseDateByOneDay()
	{
		return DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, short numberOfDays)
	{
		for (short day = 1; day <= numberOfDays; day++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}
	clsDate DecreaseDateByXDays(short numberOfDays)
	{
		return DecreaseDateByXDays(*this, numberOfDays);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		return DecreaseDateByXDays(Date, 7);
	}
	clsDate DecreaseDateByOneWeek()
	{
		return DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short numberOfWeeks)
	{
		for (short week = 1; week <= numberOfWeeks; week++)
			Date = DecreaseDateByOneWeek(Date);

		return Date;
	}
	clsDate DecreaseDateByXWeeks(short numberOfWeeks)
	{
		return DecreaseDateByXWeeks(*this, numberOfWeeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;

		short monthDays = NumberOfDaysInMonth(Date._Year, Date._Month);
		Date._Day = (Date._Day > monthDays) ? monthDays : Date._Day;

		return Date;
	}
	clsDate DecreaseDateByOneMonth()
	{
		return DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short numberOfMonths)
	{
		for (short month = 1; month <= numberOfMonths; month++)
			Date = DecreaseDateByOneMonth(Date);

		return Date;
	}
	clsDate DecreaseDateByXMonths(short numberOfMonths)
	{
		return DecreaseDateByXMonths(*this, numberOfMonths);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date._Year--;
		return Date;
	}
	clsDate DecreaseDateByOneYear()
	{
		return DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, short numberOfYears)
	{
		for (short year = 1; year <= numberOfYears; year++)
			Date = DecreaseDateByOneYear(Date);

		return Date;
	}
	clsDate DecreaseDateByXYears(short numberOfYears)
	{
		return DecreaseDateByXYears(*this, numberOfYears);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short numberOfYears)
	{
		Date._Year -= numberOfYears;
		return Date;
	}
	clsDate DecreaseDateByXYearsFaster(short numberOfYears)
	{
		return DecreaseDateByXYearsFaster(*this, numberOfYears);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		Date._Year -= 10;
		return Date;
	}
	clsDate DecreaseDateByOneDecade()
	{
		return DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short numberOfDecades)
	{
		for (short decade = 1; decade <= numberOfDecades; decade++)
			Date = DecreaseDateByOneDecade(Date);

		return Date;
	}
	clsDate DecreaseDateByXDecades(short numberOfDecades)
	{
		return DecreaseDateByXDecades(*this, numberOfDecades);
	}
	
	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, short numberOfDecades)
	{
		Date._Year -= numberOfDecades * 10;
		return Date;
	}
	clsDate DecreaseDateByXDecadesFaster(short numberOfDecades)
	{
		return DecreaseDateByXDecadesFaster(*this, numberOfDecades);
	}
	
	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		Date._Year -= 100;
		return Date;
	}
	clsDate DecreaseDateByOneCentury()
	{
		return DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMilinium(clsDate Date)
	{
		Date._Year -= 1000;
		return Date;
	}
	clsDate DecreaseDateByOneMilinium()
	{
		return DecreaseDateByOneMilinium(*this);
	}

	static short DateDifference(clsDate Date1, clsDate Date2, bool isIncludeEndDay = false)
	{
		short numberOfDays = 0;

		if (Date1.IsAfterDate2(Date2))// 31/12/2022
			Date1.SwapDates(Date2);//    28/ 2/2023

		while (!Date1.IsEqualDate(Date2))
		{
			Date1 = Date1.IncreaseDateByOneDay();
			numberOfDays++;
		}

		return (isIncludeEndDay) ? ++numberOfDays : numberOfDays;
	}
	short DateDifference(clsDate Date2, bool isIncludeEndDay = false)
	{
		return DateDifference(*this, Date2);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate container;

		container = Date1;
		Date1 = Date2;
		Date2 = container;
	}
	void SwapDates(clsDate& Date2)
	{
		return SwapDates(*this, Date2);
	}

	static short DateDifferenceInDays(clsDate Date1, clsDate Date2, bool isIncludeEndDay = false)
	{
		short numberOfDays = 0;
		short flagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			flagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			numberOfDays++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return (isIncludeEndDay) ? ++numberOfDays * flagValue : numberOfDays * flagValue;
	}
	short DateDifferenceInDays(clsDate Date2, bool isIncludeEndDay = false)
	{
		return DateDifferenceInDays(*this, Date2);
	}

	static void PrintYearCalender(short year)
	{
		cout << "  _________________________________\n\n";
		cout << "           Calender - " << year << "\n";
		cout << "  _________________________________\n\n";

		for (short month = 1; month <= 12; month++)
			PrintMonthCalender(year, month);
	}
	void PrintYearCalender()
	{
		return PrintYearCalender(_Year);
	}

	static bool IsValid(clsDate Date)
	{
		short day = Date._Day;
		short month = Date._Month;
		short year = Date._Year;

		if (month < 1 || month > 12)
			return false;

		else if (day < 1 || day>31)
			return false;

		else if (day > NumberOfDaysInMonth(year, month))
			return false;

		else
			return true;
	}
	bool IsValid()
	{
		return IsValid(*this);
	}

	static int CalculateMyAgeInDays(clsDate DateOfBirth, bool isIncludeEndDay = true)
	{
		clsDate Date2;
		int numberOfDays = 0;

		for (short year = DateOfBirth._Year; year < Date2._Year; year++)
			numberOfDays += NumberOfDaysInYear(year);

		for (short month = DateOfBirth._Month; month < Date2._Month; month++)
			numberOfDays += NumberOfDaysInMonth(DateOfBirth._Year, month);

		numberOfDays += Date2._Day - DateOfBirth._Day;

		return (isIncludeEndDay) ? ++numberOfDays : numberOfDays;
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return OrderOfDay(Date._Year, Date._Month, Date._Day) == 6;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short dayOrder = OrderOfDay(Date._Year, Date._Month, Date._Day);
		return dayOrder == 5 || dayOrder == 6;
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntillTheEndOfWeek(clsDate Date)
	{
		return 6 - OrderOfDay(Date._Year, Date._Month, Date._Day);
	}
	short DaysUntillTheEndOfWeek()
	{
		return DaysUntillTheEndOfWeek(*this);
	}

	static short DaysUntillTheEndOfMonth(clsDate Date)//   23/9/2022
	{
		/*clsDate DateOfEndOfYear;

		DateOfEndOfYear._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
		DateOfEndOfYear._Month = Date._Month;
		DateOfEndOfYear._Year = Date._Year;

		return DateDifference(Date, DateOfEndOfYear, 1);*/
		//return (numberOfDaysInMonth(Date.year, Date.month) - Date.day)+1;

		return Date.NumberOfDaysInMonth() - Date._Day;

	}
	short DaysUntillTheEndOfMonth()
	{
		return DaysUntillTheEndOfMonth(*this);
	}
	
	static short DaysUntillTheEndOfYear(clsDate Date)//   23/9/2022
	{
		clsDate DateOfEndOfYear;

		DateOfEndOfYear._Day = 31;
		DateOfEndOfYear._Month = 12;
		DateOfEndOfYear._Year = Date._Year;

		return DateDifference(Date, DateOfEndOfYear);
	}
	short DaysUntillTheEndOfYear()
	{
		return DaysUntillTheEndOfYear(*this);
	}

	static short ClaculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{//    1/9/2022    5/9/222
		short dateDifference = DateDifference(DateFrom, DateTo);

		for (short day = 1; day <= dateDifference; day++)
		{
			DateFrom._Day = day;
			if (IsWeekEnd(DateFrom))
				dateDifference--;
		}

		return dateDifference;
	}
	short ClaculateVacationDays(clsDate DateTo)
	{
		return ClaculateVacationDays(*this, DateTo);
	}

	static clsDate ReturnDateAfterVacationPeriod(clsDate startDate, short vPeriod)
	{
		while (vPeriod !=0)
		{
			if (!startDate.IsWeekEnd())
				vPeriod--;
			
			startDate = startDate.IncreaseDateByOneDay();
		}
		return startDate;
	}
	clsDate ReturnDateAfterVacationPeriod(short vPeriod)
	{
		return ReturnDateAfterVacationPeriod(*this, vPeriod);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}
	bool IsAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static short CompareTwoDates(clsDate Date1, clsDate Date2)
	{
		return IsDate1AfterDate2(Date1, Date2) ? 1 : (IsDate1EqualDate2(Date1, Date2)) ? 0 : -1;
	}
	short CompareTwoDates(clsDate Date2)
	{
		return CompareTwoDates(*this, Date2);
	}

	static bool IsPeriod1OverlapPeriod2(clsDate P1SDate, clsDate P1EDate,
										clsDate P2SDate, clsDate P2EDate)
	{
		struct stPeriod
		{
			clsDate startDate;
			clsDate endDate;
		};

		stPeriod period1, period2, container;

		period1.startDate = P1SDate;
		period1.endDate = P1EDate;
		period2.startDate = P2SDate;
		period2.endDate = P2EDate;


		short isPeriod2AfterStartPeriod1 = CompareTwoDates(period2.startDate, period1.startDate);
		short isPeriod2BeforeEndOfPeriod1 = CompareTwoDates(period2.startDate, period1.endDate);

		if (isPeriod2AfterStartPeriod1 == -1)
		{
			container = period1;
			period1 = period2;
			period2 = container;
		}

		isPeriod2AfterStartPeriod1 = CompareTwoDates(period2.startDate, period1.startDate);
		isPeriod2BeforeEndOfPeriod1 = CompareTwoDates(period2.startDate, period1.endDate);

		if ((isPeriod2AfterStartPeriod1 == 1 || isPeriod2AfterStartPeriod1 == 0)
			&& (isPeriod2BeforeEndOfPeriod1 == -1 || isPeriod2BeforeEndOfPeriod1 == 0))
			return true;
		else
			return false;
	}

	static short periodLengthInDays(clsDate PSDate, clsDate PEDate, bool includeEndDay = false)
	{
		return DateDifference(PSDate, PEDate);
	}

	static bool IsDateWithinPeriod(clsDate PSDate, clsDate PEDate, clsDate Date)
	{
		struct stPeriod
		{
			clsDate startDate;
			clsDate endDate;
		};
		stPeriod period;

		period.startDate = PSDate;
		period.endDate = PEDate;

		if ((CheckTwoDates(Date, period.startDate) == enCompareTwoDates::After
			|| CheckTwoDates(Date, period.startDate) == enCompareTwoDates::Equal)
			&& (CheckTwoDates(Date, period.endDate) == enCompareTwoDates::Before
				|| CheckTwoDates(Date, period.endDate) == enCompareTwoDates::Equal))
			return true;
		else
			return false;
	}
	bool IsWithinPeriod(clsDate PSDate, clsDate PEDate)
	{
		return IsDateWithinPeriod(PSDate , PEDate , *this);
	}

	static short CountOverlapDays(clsDate P1SDate, clsDate P1EDate,
									clsDate P2SDate, clsDate P2EDate)
	{
		if (IsDateWithinPeriod(P2SDate, P2EDate, P1EDate) &&
			IsDateWithinPeriod(P1SDate, P1EDate, P2SDate))
        return DateDifference(P2SDate, P1EDate);

    else if (IsDateWithinPeriod(P1SDate, P1EDate, P2EDate) &&
		IsDateWithinPeriod(P2SDate, P2EDate, P1SDate))
        return DateDifference(P1SDate, P2EDate);

    else if (IsDateWithinPeriod(P2SDate, P2EDate, P1SDate) &&
		IsDateWithinPeriod(P2SDate, P2EDate, P1EDate))
        return DateDifference(P1SDate, P1EDate);

    else if (IsDateWithinPeriod(P1SDate, P1EDate, P2SDate) &&
		IsDateWithinPeriod(P1SDate, P1EDate, P2SDate))
        return DateDifference(P2SDate, P2EDate);
    else
        return 0;
	}

	static string ConvertDateToString(clsDate Date, char delim)
	{
		return (to_string(Date._Day) + delim + to_string(Date._Month) + delim + to_string(Date._Year));
	}
	string ConvertDateToString(char delim)
	{
		return ConvertDateToString(*this, delim);
	}

	static string FormatDate(clsDate Date, string format = "dd/mm/yyyy")
	{
		string formattedDate = "";

		formattedDate = clsString::replaceString(format, "dd", to_string(Date._Day));
		formattedDate = clsString::replaceString(formattedDate, "mm", to_string(Date._Month));
		formattedDate = clsString::replaceString(formattedDate, "yyyy", to_string(Date._Year));

		return formattedDate;
	}
	string FormatDate(string format = "dd/mm/yyyy")
	{
		return FormatDate(*this, format);
	}

};
