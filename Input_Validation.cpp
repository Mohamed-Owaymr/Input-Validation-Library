#include "Input_Validation.h"


bool Input_Validation::isNegative(float value)
{
    return value < 0;
}
bool Input_Validation::isPositive(float value)
{
    return value > 0;
}
bool Input_Validation::isZero(float value)
{
    return value == 0;
}
void Input_Validation::cleanCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void Input_Validation::printInvalidValueErrorMessage()
{
    cout << "Invalid input, please enter a valid number";
}
float Input_Validation::readPositiveNumber(const string& msg)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || isNegative(number) || isZero(number))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
float Input_Validation::readNegativeNumber(const string& msg)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || isPositive(number) || isZero(number))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
float Input_Validation::readRationalNumber(const string& msg)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail())
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
char Input_Validation::readLetter(const string& msg)
{
    char input;
    cout << msg <<": ";
    cin >> input;
    while(cin.fail() || !isalpha(input))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> input;
    }
    return input;
}
bool Input_Validation::isFalseLetterCharacter(char letter)
{
    return letter == 'n' || letter == 'N';
}
bool Input_Validation::isTrueLetterCharacter(char letter)
{
    return letter == 'y' || letter == 'Y';
}
bool Input_Validation::readYesNoAsBool(const string& msg)
{
    char letter = readLetter(msg);
    while(!(isFalseLetterCharacter(letter) || isTrueLetterCharacter(letter)))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        letter = readLetter(msg);
    }
    if(isFalseLetterCharacter(letter))
        return false;
    else
        return true;
}
bool Input_Validation::isInRange(float from , float to , float number , bool inclusive)
{
    if(inclusive)
        return number >= from && number <= to;
    else
        return number > from && number < to;
}
float Input_Validation::readNumberInRange(const string& msg , float from , float to , bool inclusive)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || !isInRange(from , to , number , inclusive))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
void Input_Validation::displayUserOptionsList(const string& options)
{
    cout << "\n****************************\n";
    cout << "Your Options: \n";
    cout << options << endl;
    cout << "****************************\n";
}
float Input_Validation::readNumber(const string& msg , enNumberTypes inputType)
{
    float inputNumber = 0;
    switch (inputType)
    {
    case enNumberTypes::NaturalNum:
        inputNumber = readRationalNumber(msg);
        break;
    case enNumberTypes::PositiveNum:
        inputNumber = readPositiveNumber(msg);
        break;
    case enNumberTypes::NegativeNum:
        inputNumber = readNegativeNumber(msg);
        break;

    
    default:
        inputNumber = readPositiveNumber(msg);
        break;
    }
    return inputNumber;
}
template <typename EnumType>
size_t Input_Validation::getEnumSizeUsingMagicEnumCount()
{
    static_assert(is_enum<EnumType>::value, "Error: The parameter must be an enum!");
    return magic_enum::enum_count<EnumType>();
}
template<typename EnumType>
bool Input_Validation::isValidOptionNumber(short opNumber)
{
    size_t enumSize = getEnumSizeUsingMagicEnumCount<EnumType>();
    return opNumber <= enumSize && !isNegative(opNumber);
}
template<typename EnumType>
EnumType Input_Validation::readOptionNumber(const string& msg, const string& optionsList)
{
    short optionNumber;
    displayUserOptionsList(optionsList);
    optionNumber = readPositiveNumber(msg);
    while (!isValidOptionNumber<EnumType>(optionNumber))
    {
        printInvalidValueErrorMessage();
        optionNumber = readPositiveNumber(msg);
    }
    return static_cast<EnumType>(optionNumber);
}
string Input_Validation::readString(const string& msg , short minLength , short maxLength , bool inclusive)
{
    if(!isCinBufferEmpty())
        cleanCin();

    string input;
    cout << msg << ": ";
    getline(cin , input);
    short length = input.length();
    while(input.empty() || !isInRange(minLength , maxLength , length , inclusive))
    {
        cout << msg << " Again: ";
        getline(cin , input);
        length = input.length();
    }
    return input;
}
bool Input_Validation::isCinBufferEmpty()
{
    return cin.rdbuf()->in_avail() == 0;
}
bool isDateBettwen(const Date& subDate , const Date& startDate , const Date& endDate , bool inclusive = true)
{
    return Date::isDateInRange(subDate , startDate , endDate , inclusive);
}