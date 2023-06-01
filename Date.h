#pragma once
/*
 *  Smart Date Class header file
 */
#pragma once
#include <iostream>
#include <string>
using UShort = unsigned short;
using UInt = unsigned int;

class Date
{
private:
    UShort day;
    UShort month;
    UShort year;
    std::string timezone;
    static std::string month_names[13];
    static short month_days[13];
public:
    UShort date_to_days();
    void days_to_date(UShort d);
    // static
    static const UShort start_year;
    // constructors
    Date();
    Date(const Date& obj2);
    Date(UShort d, UShort m, UShort y);
    // other methods
    void print_short();       // prints date in the format: "D.MM.YYYY";
    void print_long();        // prints date in the format: "D of MonthName, YYYY";
    void add_days(int d);    // adds <d> days to stored date
    void operator+=(UInt);        // += operator overloaded
    void operator++();
    void operator++(int);
    UShort operator--();
    Date operator = (const Date& obj2);
    Date operator+(int);
    bool operator<(const Date& obj2) const;
    bool operator>(const Date& obj2) const;
    bool operator%(int) const;
    UShort operator [](int) const;
    UShort& operator [](int);
    friend bool is_equal(const Date& obj1, const Date& obj2);
    friend bool operator==(const Date& obj1, const Date& obj2);
    friend Date operator-(const Date&, int);
    friend std::ostream& operator << (std::ostream& out, Date& arg);
};

const UShort Date::start_year = 1970;

std::string Date::month_names[13]{
    "", "Jan", "Feb", "March",
        "Apr", "May", "June", "July",
        "Aug", "Sept", "Okt", "Nov", "Dec"
};

short Date::month_days[13]{
    0, 31,28,31,30,31,30,31,31,30,31,30,31
};

/*
 * Constructors
 */

 // Default constructor
Date::Date()
{
    day = 1;
    month = 1;
    year = 1970;
    timezone = "GMT+3 (Moscow)";
}


// Copy constructor
Date::Date(const Date& obj2)
{
    this->day = obj2.day;
    this->month = obj2.month;
    this->year = obj2.year;
    this->timezone = obj2.timezone;
}


// Constructor with 3 params
Date::Date(UShort d, UShort m, UShort y) : Date()
{
    // check month
    if ((m < 1) || (m > 12)) return;
    // check day of month

    day = d;
    month = m;
    year = y;
}


// Print date in short format (D.MM.YYYY)
void Date::print_short()
{
    std::cout << this->day << '.';
    if (this->month < 10) std::cout << '0';
    std::cout << this->month << '.';
    std::cout << this->year << std::endl;
}


// Print date in long format (D of monthname YYYY)
void Date::print_long()
{
    std::cout << this->day << " of ";
    std::cout << month_names[month];
    std::cout << ", " << this->year << std::endl;
}


// Convert date to count of days from 1.01.1970 (start_year)
UShort Date::date_to_days()
{
    UShort result = 0;
    UShort full_years = this->year - Date::start_year;
    // calc full leap years count, excluding current
    UShort leaps_count = (this->year - 1972) / 4;
    if (this->year % 4) leaps_count++;
    if (this->year <= 1972) leaps_count = 0;
    result += (365 * full_years + leaps_count);
    // calc full months count
    UShort full_months = this->month - 1;
    for (int i = 0; i < full_months; i++) {
        result += month_days[i + 1];
    }
    // add 29-th day if current year is leap and month after feb
    if ((this->year % 4 == 0) && (this->month > 2)) result++;
    // add days
    result += this->day - 1;
    return result;
}


// Convert count of days since 1970 to Date
void Date::days_to_date(UShort d)
{
    // calc full years count
    UShort full_years = (float)d / 365.25;
    // exclude years days
    d %= (UShort)((float)full_years * 365.25);
    // calc full months count
    UShort full_months = 0;
    int i;
    for (i = 1; i <= 12; i++) {
        UShort m_days = month_days[i];
        // check for leap year's february
        if ((i == 2) && ((start_year + full_years) % 4 == 0))
            m_days++;
        if (d >= m_days) {
            d -= m_days;
            full_months++;
        }
        else break;
    }
    this->year = full_years + Date::start_year;
    this->month = full_months + 1;
    this->day = d + 1;
}


// Adds <d> days to date (d<=365)
void Date::add_days(int d)
{
    UShort date_in_days = date_to_days();
    date_in_days += d;
    this->days_to_date(date_in_days);
}

// Operator += overload
void Date::operator+=(UInt days_to_add)
{
    this->add_days(days_to_add);
}

// Prefix increment operator overload
void Date::operator++()
{
    this->day++;
    if (this->day > Date::month_days[this->month]) {
        day = 1;
        month++;
    }
    if (month == 13) {
        month = 1;
        year++;
    }
}

// Postfix increment operator overload
void Date::operator++(int)
{
    ++(*this);
}

// Prefix decrement operator overload
UShort Date::operator--()
{
    this->day--;
    if (day == 0) {
        month = (month > 1) ? month - 1 : 12;
        day = Date::month_days[month];
    }
    if (month == 12) year--;
    return this->day;
}

// Operator = overload
Date Date::operator = (const Date& obj2)
{
    this->day = obj2.day;
    this->month = obj2.month;
    this->year = obj2.year;
    this->timezone = obj2.timezone;
    return *this;
}


bool is_equal(const Date& obj1, const Date& obj2)
{
    if ((obj1.year == obj2.year) && (obj1.month == obj2.month)
        && (obj1.day == obj2.day))
        return true;
    else return false;
}


// Operator == overload by friend function
bool operator==(const Date& obj1, const Date& obj2)
{
    return is_equal(obj1, obj2);
}


// Operator + overload
Date Date::operator+(int days_to_add)
{
    Date temp{ *this };
    temp.add_days(days_to_add);
    return temp;
}

// Operator - overload by friend function
Date operator-(const Date& obj1, int days_to_add)
{
    Date temp{ obj1 };
    days_to_add = -days_to_add;
    temp.add_days(days_to_add);
    return temp;
}

// Operator < overload
bool Date::operator < (const Date& obj2) const
{
    bool res = false;
    if (this->year < obj2.year) res = true;
    else if ((this->year == obj2.year) && (this->month < obj2.month)) res = true;
    else if ((this->month == obj2.month) && (this->day < obj2.day)) res = true;
    return res;
}

// Operator > overload
bool Date::operator > (const Date& obj2) const
{
    if (*this < obj2) return false;
    if (*this == obj2) return false;
    return true;

}

// Operator % overload
// Gets int argument == 4
// Returns true if the year is leap and false otherwise
// Returns false if argument <> 4
bool Date::operator%(int x) const
{
    if (x != 4) return false;
    if (this->year % 4 == 0) return true;
    else return false;
}

// Operator [] overload
// Gets int argument == [1, 2, 3]
// Returns:
//  - day:      if arg == 1
//  - months:   if arg == 2
//  - year:     if arg == 3
UShort Date::operator[](int arg) const
{
    if ((arg < 1) || (arg > 3)) return 0;
    if (arg == 1) return this->day;
    if (arg == 2) return this->month;
    if (arg == 3) return this->year;
}

// Operator [] overload (changes the object)
UShort& Date::operator[](int arg)
{
    if (arg == 1) return this->day;
    if (arg == 2) return this->month;
    if (arg == 3) return this->year;
}

// Operator << for cout 
std::ostream& operator << (std::ostream& out, Date& arg)
{
    //arg.print_long();
    out << arg.day << '.' << arg.month << '.' << arg.year;
    return out;
}

