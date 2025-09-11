#include <iostream>
#include <limits>
#include <cctype>
#include <string>
#include "magic_enum.hpp"
#include "date.cpp"
using namespace std;

class Input_Validation
{
private:
    static void printInvalidValueErrorMessage();
    static void displayUserOptionsList(const string& options);
    static bool isCinBufferEmpty();

public:
    static bool   isNegative(float value);
    static bool   isPositive(float value);
    static bool   isZero(float value);
    static void   cleanCin();
    static float  readPositiveNumber(const string& msg);
    static float  readNegativeNumber(const string& msg);
    static float  readRationalNumber(const string& msg);
    static char   readLetter(const string& msg);
    static bool   isFalseLetterCharacter(char letter);
    static bool   isTrueLetterCharacter(char letter);
    static bool   readYesNoAsBool(const string& msg);
    static bool   isInRange(float from , float to , float number , bool inclusive  = true);
    static float  readNumberInRange(const string& msg , float from , float to , bool inclusive  = true);


    template <typename EnumType>
    static size_t getEnumSizeUsingMagicEnumCount();

    template<typename EnumType>
    static bool isValidOptionNumber(short opNumber);

    template<typename EnumType>
    static EnumType readOptionNumber(const string& msg, const string& optionsList);

    enum enNumberTypes{NaturalNum = 1 , PositiveNum = 2 , NegativeNum = 3};

    static float readNumber(const string& msg , enNumberTypes inputType);

    static string readString(const string& msg , short minLength = 0 , short maxLength = 1000 , bool inclusive = true);

    static bool isDateBettwen(const Date& subDate , const Date& startDate , const Date& endDate , bool inclusive = true);
};