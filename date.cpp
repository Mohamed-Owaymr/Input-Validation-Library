#include "date.h"

Date::Date()
{
    time_t timestamp = time(NULL);
    struct tm* dateTimeNowPtr = localtime(&timestamp);

    day   = dateTimeNowPtr->tm_mday;
    month = dateTimeNowPtr->tm_mon + 1;
    year  = dateTimeNowPtr->tm_year + 1900;
}
Date::Date(short day , short month , short year)
{
    this->day   = day;
    this->month = month;
    this->year  = year;

    if(!this->isValid())
        throw invalid_argument("Invalid date");
}
Date::Date(const string& dateFormat , const char& delimiter)
{
    string tokenFormat = dateFormat;

    if (tokenFormat.empty())
        throw invalid_argument("Date string is empty");
    this->day = cutNumberBeforeDelimiter(tokenFormat, delimiter);

    if (tokenFormat.empty())
        throw invalid_argument("Month part is missing");
    this->month = cutNumberBeforeDelimiter(tokenFormat, delimiter);

    if (tokenFormat.empty())
        throw invalid_argument("Year part is missing");
    short yearValue = stoi(tokenFormat);
    if (yearValue < 0)
        throw out_of_range("Year cannot be negative");
    this->year = yearValue;

    if(!this->isValid())
       throw invalid_argument("Invalid date format or out of range date");
}
Date::Date(short dayOfYear , short year)
{
    if(dayOfYear <= 0)
        throw out_of_range("Days from beginning of year must be positive");


    short daysInYear = getDaysInYear(year);
    while(dayOfYear > daysInYear)
    {
        dayOfYear -= daysInYear;
        daysInYear = getDaysInYear(++year);
    }
    this->year = year;


    this->month = 1;
    short daysInMonth = getDaysInMonth(this->month , this->year);
    while(dayOfYear > daysInMonth)
    {
        dayOfYear -= daysInMonth;
        increaseByOneMonth(this->month , this->year);
    }


    this->day = dayOfYear;
}


Date Date::convertStringFormatToRecord(const string& dateFormat , const char& delimiter)
{
    Date convertedDate;
    
    string tokenFormat = dateFormat;

    if (tokenFormat.empty())
        throw invalid_argument("Date string is empty");
    convertedDate.day = cutNumberBeforeDelimiter(tokenFormat, delimiter);

    if (tokenFormat.empty())
        throw invalid_argument("Month part is missing");
    convertedDate.month = cutNumberBeforeDelimiter(tokenFormat, delimiter);

    if (tokenFormat.empty())
        throw invalid_argument("Year part is missing");
    short yearValue = stoi(tokenFormat);
    if (yearValue < 0)
        throw out_of_range("Year cannot be negative");
    convertedDate.year = yearValue;

    if(!convertedDate.isValid())
       throw invalid_argument("Invalid date format or out of range date");
    return convertedDate;
}


short Date::cutNumberBeforeDelimiter(string& str , const char& delimiter)
{
    size_t delimiterPos = str.find(delimiter);

    if(delimiterPos == string::npos)
        throw invalid_argument("Delimiter not found in string");

    string token = str.substr(0, delimiterPos);
    if (token.empty())
        throw invalid_argument("No number before delimiter");

    str.erase(0 , delimiterPos + 1);

    return static_cast<short>(stoi(token));
}






bool Date::isValidDate(const Date& date)
{
    return isValidYear(date.year) && isValidMonth(date.month) && isValidDay(date);
}
bool Date::isValid()
{
    return isValidDate(*this);
}

bool Date::isValidYear(const short& year)
{
    return year > 0;
}   
bool Date::isValidYear()
{
    return isValidYear(this->year);
}

bool Date::isValidMonth(const short& month)
{
    return month >= 1 && month <= 12;
}   
bool Date::isValidMonth()
{
    return isValidMonth(this->month);
}

bool Date::isValidDay(const Date& date)
{
    return (date.day > 0) && (date.day <= getDaysInMonth(date.month , date.year));
}
bool Date::isValidDay()
{
    return isValidDay(*this);
}
short Date::getDaysInMonth(short month , short year)
{
    if (month < 1 || month > 12)
        return 0;

    short numberOfDaysInMonth[12] = {31, (isLeapYear(year) ? short(29) : short(28)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return numberOfDaysInMonth[month - 1];
}
short Date::getDaysInMonth(const Date& date)
{
    return getDaysInMonth(date.month , date.year);
}
short Date::getDaysInCurrentMonth()
{
    return getDaysInMonth(this->month , this->year);
}
bool Date::isLeapYear(short year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0); 
}
bool Date::isLeapYear()
{
    return isLeapYear(this->year);
}
Date Date::getCurrentDate()
{
    time_t timestamp = time(NULL);
    struct tm *dateTimeNowPtr = localtime(&timestamp);

    Date currentDate;

    currentDate.day = dateTimeNowPtr->tm_mday;
    currentDate.month = dateTimeNowPtr->tm_mon + 1;
    currentDate.year = dateTimeNowPtr->tm_year + 1900;

    return currentDate;
}
short Date::getDaysInYear(short year) { return isLeapYear(year) ? 366 : 365; }
short Date::Date::getDaysInCurrentYear(){return getDaysInYear(this->year);}


void Date::increaseByOneMonth(short& month , short& year)
{
    if (month == 12)
    {
        ++year;
        month = 1;
    }
    else
    {
        ++month;
    }
}
Date Date::increaseDateByOneMonth(const Date& date)
{
    Date tokenDate = date;
    increaseByOneMonth(tokenDate.month , tokenDate.year);

    short daysInMonth = tokenDate.getDaysInCurrentMonth();
    if(tokenDate.day > daysInMonth)
        tokenDate.day = daysInMonth;

    return date;
}
Date Date::increaseByOneMonth()
{
    *this = increaseDateByOneMonth(*this);
    return *this;
}
short Date::getHoursInYear(short year) { return getDaysInYear(year) * 24; }
long  Date::getMinutesInYear(short year) { return getHoursInYear(year) * 60; }
long  Date::getSecondsInYear(short year) { return getMinutesInYear(year) * 60; }
short Date::getHoursInCurrentYear(){return getHoursInYear(this->year);}
long  Date::getMinutesInCurrentYear(){return getMinutesInYear(this->year);}
long  Date::getSecondsInCurrentYear(){return getSecondsInYear(this->year);}


short Date::getHoursInMonth(short month , short year) { return getDaysInMonth(year, month) * 24; }
long Date::getMinutesInMonth(short month , short year) { return getHoursInMonth(year, month) * 60; }
long Date::getSecondsInMonth(short month , short year) { return getMinutesInMonth(year, month) * 60; }
short Date::getHoursInMonth(){return getHoursInMonth(this->month , this->year);}
long Date::getMinutesInMonth(){return getMinutesInMonth(this->month , this->year);}
long Date::getSecondsInMonth(){return getSecondsInMonth(this->month , this->year);}


void Date::printYearDetails(short year) 
{
    cout << "Number Of Days      : " << getDaysInYear(year) << endl;
    cout << "Number Of Hours     : " << getHoursInYear(year) << endl;
    cout << "Number Of Minutes   : " << getMinutesInYear(year) << endl;
    cout << "Number Of Seconds   : " << getSecondsInYear(year) << endl;
}

void Date::printMonthDetails(short month , short year) 
{
    cout << "Number Of Days in Month [" << month << "] : " << getDaysInMonth(year, month) << endl;
    cout << "Number Of Hours in Month [" << month << "] : " << getHoursInMonth(year, month) << endl;
    cout << "Number Of Minutes in Month [" << month << "] : " << getMinutesInMonth(year, month) << endl;
    cout << "Number Of Seconds in Month [" << month << "] : " << getSecondsInMonth(year, month) << endl;
}
void Date::printYearDetails() {printYearDetails(this->year);}
void Date::printMonthDetails() {printMonthDetails(this->month , this->year);}

string Date::getDateFormat(short day , short month , short year)
{
    return to_string(day) + '/' + to_string(month) + '/' + to_string(year);
}
string Date::getDateFormat(const Date& date)
{
    return getDateFormat(date.day , date.month , date.year);
}
short Date::getDayOrderInWeek(const Date& date)
{
    short a = (14 - date.month) / 12;
    short y = date.year - a;
    short m = date.month - (12 * a) - 2;

    return (date.day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
}
string daysNames[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
string Date::getDayNameByOrderInWeek(short dayIndex)
{
    return daysNames[dayIndex];
}
string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
string Date::getMonthName(short month) { return months[month - 1]; }

void Date::displayMonthCalendarHeader(short month) { cout << "\n____________________(" << getMonthName(month) << ")____________________\n"; }
void Date::displayMonthCalendarNavBar(short spacesDelimiterLength)
{
    cout << endl;
    for (size_t dayOrderInWeek = 0; dayOrderInWeek < 7; ++dayOrderInWeek)
        cout << left << setw(spacesDelimiterLength) << getDayNameByOrderInWeek(dayOrderInWeek);
    cout << endl;
}
short Date::getDayOrderInWeek(short year, short month, short day)
{
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month - (12 * a) - 2;

    return (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
}
short Date::getFirstDayOrderInMonth(short year, short month)
{
    return getDayOrderInWeek(year, month, 1);
}
void Date::displayFirstWeekInMonthCalendar(short firstDayInMonth, short spacesDelimiterLength, short &day)
{
    for (short i = 0; i < 7; ++i)
    {
        if (i < firstDayInMonth)
            cout << setw(spacesDelimiterLength) << " ";
        else
            cout << setw(spacesDelimiterLength) << day++;
    }
}
void Date::displayWeekLineInMonthCaledar(short totalDays, short spacesDelimiterLength, short &day)
{
    for (short i = 0; i < 7 && day <= totalDays; ++i)
        cout << setw(spacesDelimiterLength) << day++;
    cout << endl;
}
void Date::displayMonthCalendarBody(short year, short month, short spacesDelimiterLength)
{
    short totalDays = getDaysInMonth(month , year);
    short firstDayInMonth = getFirstDayOrderInMonth(year, month);
    short day = 1;
    displayFirstWeekInMonthCalendar(firstDayInMonth, spacesDelimiterLength, day);

    cout << endl;

    while (day <= totalDays)
        displayWeekLineInMonthCaledar(totalDays, spacesDelimiterLength, day);
}
void Date::displayMonthCalendar(short year, short month, short spacesDelimiterLength)
{
    displayMonthCalendarHeader(month);
    displayMonthCalendarNavBar(spacesDelimiterLength);
    displayMonthCalendarBody(year, month, spacesDelimiterLength);
    cout << "\n_____________________________________________\n";
}
void Date::dispalyYearCalendarHeader(short year)
{
    cout << "\n---------------------------------------------\n";
    cout << "                    " << year;
    cout << "\n---------------------------------------------\n";
}
void Date::displayYearCalendar(short year)
{
    dispalyYearCalendarHeader(year);
    for (short month = 1; month <= 12; ++month)
        displayMonthCalendar(year, month);
}

void Date::displayMonthCalendar(short spacesDelimiterLength)
{
    displayMonthCalendar(this->year , this->month);
}
void Date::displayYearCalendar()
{
    displayYearCalendar(this->year);
}
bool Date::isDateInRange(const Date& subDate , const Date& startRange , const Date& endRange , bool inclusive)
{
    if(inclusive)
    {
        if(isEqualDates(subDate , startRange) || isEqualDates(subDate , endRange))
            return true;
    }
    return isFirstDateAfterSecondDate(subDate , startRange) &&  isFirstDateBeforeSecondDate(subDate , endRange);
}
bool Date::isDateInRange(const Date& startRange , const Date& endRange , bool inclusive)
{
    return isDateInRange(*this , startRange , endRange , inclusive);
}

bool Date::isFirstDateBeforeSecondDate(const Date &firstDate, const Date &secondDate)
{
    if (firstDate.year < secondDate.year)
        return true;
    if (firstDate.year > secondDate.year)
        return false;

    if (firstDate.month < secondDate.month)
        return true;
    if (firstDate.month > secondDate.month)
        return false;

    return firstDate.day < secondDate.day;
}
bool Date::isBeforeDate(const Date &secondDate)
{
    return isFirstDateBeforeSecondDate(*this , secondDate);
}
bool Date::isFirstDateAfterSecondDate(const Date& firstDate , const Date& secondDate)
{
    return !isFirstDateBeforeSecondDate(firstDate , secondDate) && !isEqualDates(firstDate , secondDate);
}
bool Date::isAfterDate(const Date& secondDate)
{
    return isFirstDateAfterSecondDate(*this , secondDate);
}
bool Date::isEqualDates(const Date &firstDate, const Date &secondDate)
{
    return (firstDate.year == secondDate.year) && (firstDate.month == secondDate.month) && (firstDate.day == secondDate.day);
}
bool Date::isEqual(const Date &secondDate)
{
    return isEqualDates(*this , secondDate);
}