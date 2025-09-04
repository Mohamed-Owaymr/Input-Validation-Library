#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Date
{
private:
    short day;
    short month;
    short year;

    static short cutNumberBeforeDelimiter(string& str , const char& delimiter);
public:
    Date();
    Date(short day , short month , short year);
    Date(const string& dateFormat , const char& delimiter = '/');
    Date(short dayOfYear , short year);


    static short getHoursInYear(short year);
    static long getMinutesInYear(short year);
    static long getSecondsInYear(short year);

    short getHoursInCurrentYear();
    long getMinutesInCurrentYear();
    long getSecondsInCurrentYear();

    static Date getCurrentDate();

    static bool isValidDate(const Date& date);
    bool isValid();

    static bool isValidYear(const short& year);
    bool isValidYear();

    static bool isValidMonth(const short& month);
    bool isValidMonth();

    static bool isValidDay(const Date& date);
    bool isValidDay();

    static short getDaysInMonth(short month , short year);
    static short getDaysInMonth(const Date& date);
    short getDaysInCurrentMonth();

    static bool isLeapYear(short year);
    bool isLeapYear();
    
    static Date convertStringFormatToRecord(const string& dateFormat , const char& delimiter = '/');

    static short getDaysInYear(short year);
    short getDaysInCurrentYear();

    static Date increaseDateByOneMonth(const Date& date);
    static void increaseByOneMonth(short& month , short& year);
    Date increaseByOneMonth();
    

    static short getHoursInMonth(short month , short year);
    static long getMinutesInMonth(short month , short year);
    static long getSecondsInMonth(short month , short year);

    short getHoursInMonth();
    long getMinutesInMonth();
    long getSecondsInMonth();

    static void printYearDetails(short year);
    static void printMonthDetails(short month , short year);

    static string getDateFormat(short day , short month , short year);
    static string getDateFormat(const Date& date);
    static short getDayOrderInWeek(const Date& date);
    

    static string getDayNameByOrderInWeek(short dayIndex);
    static string getMonthName(short month);

    static void displayMonthCalendarHeader(short month);
    static void displayMonthCalendarNavBar(short spacesDelimiterLength);
    static short getFirstDayOrderInMonth(short year, short month);
    static short getDayOrderInWeek(short year, short month, short day);
    static void displayFirstWeekInMonthCalendar(short firstDayInMonth, short spacesDelimiterLength, short &day);
    static void displayWeekLineInMonthCaledar(short totalDays, short spacesDelimiterLength, short &day);
    static void displayMonthCalendarBody(short year, short month, short spacesDelimiterLength);
    static void displayMonthCalendar(short year, short month, short spacesDelimiterLength = 7);
    static void dispalyYearCalendarHeader(short year);
    static void displayYearCalendar(short year);


    void printYearDetails();
    void printMonthDetails();
    void displayMonthCalendar(short spacesDelimiterLength = 7);
    void displayYearCalendar();

    static bool isFirstDateBeforeSecondDate(const Date &firstDate, const Date &secondDate);
    bool isBeforeDate(const Date &secondDate);

    static bool isFirstDateAfterSecondDate(const Date& firstDate , const Date& secondDate);
    bool isAfterDate(const Date& secondDate);

    static bool isEqualDates(const Date &firstDate, const Date &secondDate);
    bool isEqual(const Date &secondDate);

    static bool isDateInRange(const Date& subDate , const Date& startRange , const Date& endRange , bool inclusive = true);
    bool isDateInRange(const Date& startRange , const Date& endRange , bool inclusive = true);





};