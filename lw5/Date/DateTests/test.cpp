#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CDate.h>

#include <iostream>

namespace
{
	constexpr unsigned MAX_TIMESTAMP = UINT_MAX;
	constexpr unsigned MIN_TIMESTAMP = 0;
}

TEST_CASE("Invalid dates")
{
	CDate invalidDate1(-1);
	CHECK_FALSE(invalidDate1.IsValid());

	CDate invalidDate2(UINT_MAX);
	CHECK_FALSE(invalidDate2.IsValid());

	CHECK_THROWS_AS(CDate(0, static_cast<Month>(1), 1970), std::invalid_argument);
	CHECK_THROWS_AS(CDate(32, static_cast<Month>(1), 1970), std::invalid_argument);

	CHECK_THROWS_AS(CDate(1, static_cast<Month>(0), 1970), std::invalid_argument);
	CHECK_THROWS_AS(CDate(1, static_cast<Month>(13), 1970), std::invalid_argument);

	CHECK_THROWS_AS(CDate(1, static_cast<Month>(1), 1969), std::invalid_argument);
	CHECK_THROWS_AS(CDate(1, static_cast<Month>(1), 10000), std::invalid_argument);
}

TEST_CASE("Valid dates borders")
{
	CHECK_NOTHROW(CDate(1, static_cast<Month>(1), 1970));
	CHECK_NOTHROW(CDate(31, static_cast<Month>(12), 9999));
}

TEST_CASE("Leap year test")
{
	CHECK_THROWS(CDate(29, Month::FEBRUARY, 1900));
	CHECK_THROWS(CDate(29, Month::FEBRUARY, 2001));
	
	CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2000));
	CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2004));
	CHECK_NOTHROW(CDate(29, Month::FEBRUARY, 2020));

	CDate date1(28, Month::FEBRUARY, 2023);
	++date1;
	CHECK(date1.GetDay() == 1);
	CHECK(date1.GetMonth() == Month::MARCH);
	
	CDate date2(28, Month::FEBRUARY, 2024);
	++date2;
	CHECK(date2.GetDay() == 29);
	CHECK(date2.GetMonth() == Month::FEBRUARY);
}

TEST_CASE("Test compare operations for date")
{
	CDate date1(MIN_TIMESTAMP);
	CDate date2(MAX_TIMESTAMP);

	CDate nonLimitDate1(50);
	CDate nonLimitDate2(75);

	CHECK(date1 < date2);
	CHECK_FALSE(date1 < date1);

	CHECK_FALSE(date1 > date2);
	CHECK_FALSE(date1 > date1);

	CHECK(nonLimitDate1 == nonLimitDate1);
	CHECK_FALSE(nonLimitDate1 == nonLimitDate2);

	CHECK(nonLimitDate1 != nonLimitDate2);
	CHECK_FALSE(nonLimitDate1 != nonLimitDate1);

	CHECK(nonLimitDate1 >= date1);
	CHECK(nonLimitDate1 >= nonLimitDate1);

	CHECK(nonLimitDate2 <= date2);
	CHECK(nonLimitDate2 <= nonLimitDate2);
}

TEST_CASE("Date arithmetic operations")
{
	CDate date1(1, Month::JANUARY, 1970);
	CDate date2 = date1 + 1;
	CHECK(date2.GetDay() == 2);
	CHECK(date2.GetMonth() == Month::JANUARY);

	CDate date3 = date1 + 365;
	CHECK(date3.GetDay() == 1);
	CHECK(date3.GetMonth() == Month::JANUARY);
	CHECK(date3.GetYear() == 1971);

	CDate date4 = date3 - 365;
	CHECK(date4 == date1);

	CDate date5(31, Month::DECEMBER, 2020);
	CDate date6 = date5 + 1;
	CHECK(date6.GetDay() == 1);
	CHECK(date6.GetMonth() == Month::JANUARY);
	CHECK(date6.GetYear() == 2021);

	CDate date7 = date6 - 1;
	CHECK(date7 == date5);
}

TEST_CASE("Increment and decrement operators")
{
	CDate date1(31, Month::DECEMBER, 2020);
	CDate date2 = date1++;
	CHECK(date2 == date1 - 1);

	CDate date3 = ++date1;
	CHECK(date3 == date1);

	CDate date4(1, Month::JANUARY, 2021);
	CDate date5 = date4--;
	CHECK(date5 == date4 + 1);

	CDate date6 = --date4;
	CHECK(date6 == date4);
}

TEST_CASE("Day of week calculation")
{
	CDate date1(1, Month::JANUARY, 1970); 
	CHECK(date1.GetWeekDay() == WeekDay::THURSDAY);

	CDate date2(2, Month::JANUARY, 1970);
	CHECK(date2.GetWeekDay() == WeekDay::FRIDAY);

	CDate date3(3, Month::JANUARY, 1970); 
	CHECK(date3.GetWeekDay() == WeekDay::SATURDAY);

	CDate date4(4, Month::JANUARY, 1970);
	CHECK(date4.GetWeekDay() == WeekDay::SUNDAY);

	CDate date5(1, Month::JANUARY, 2000); 
	CHECK(date5.GetWeekDay() == WeekDay::SATURDAY);
}

TEST_CASE("Output operator (<<) formatting")
{
    SECTION("Valid dates formatting")
    {
        CDate date1(5, Month::JANUARY, 2023);
        std::ostringstream out1;
        out1 << date1;
        CHECK(out1.str() == "05.01.2023"); 

        CDate date2(15, Month::OCTOBER, 1999);
        std::ostringstream out2;
        out2 << date2;
        CHECK(out2.str() == "15.10.1999"); 

        CDate date3(31, Month::DECEMBER, 9999);
        std::ostringstream out3;
        out3 << date3;
        CHECK(out3.str() == "31.12.9999"); 
    }

    SECTION("Invalid date output")
    {
        CDate invalidDate(-1);
        std::ostringstream out;
        out << invalidDate;
        CHECK(out.str() == "INVALID DATE"); 
    }

    SECTION("Single-digit day and month")
    {
        CDate date(1, Month::FEBRUARY, 2000);
        std::ostringstream out;
        out << date;
        CHECK(out.str() == "01.02.2000"); 
    }
}

TEST_CASE("Input operator (>>) parsing")
{
    SECTION("Valid date parsing")
    {
        CDate date1;
        std::istringstream in1("05.01.2023");
        in1 >> date1;
        CHECK(date1.GetDay() == 5);
        CHECK(date1.GetMonth() == Month::JANUARY);
        CHECK(date1.GetYear() == 2023);

        CDate date2;
        std::istringstream in2("31.12.9999");
        in2 >> date2;
        CHECK(date2.GetDay() == 31);
        CHECK(date2.GetMonth() == Month::DECEMBER);
        CHECK(date2.GetYear() == 9999);

        CDate date3;
        std::istringstream in3("01.02.1970");
        in3 >> date3;
        CHECK(date3.GetDay() == 1);
        CHECK(date3.GetMonth() == Month::FEBRUARY);
        CHECK(date3.GetYear() == 1970);
    }

    SECTION("Invalid date parsing")
    {
        CDate date;

        std::istringstream in1("05-01-2023");
        in1 >> date;
        CHECK(in1.fail());

        std::istringstream in2("05,01,2023");
        in2 >> date;
        CHECK(in2.fail());

        std::istringstream in3("ab.cd.efgh");
        in3 >> date;
        CHECK(in3.fail());

        std::istringstream in4("32.01.2023");
        in4 >> date;
        CHECK(in4.fail());

        std::istringstream in5("");
        in5 >> date;
        CHECK(in5.fail());

        std::istringstream in6("05.01");
        in6 >> date;
        CHECK(in6.fail());
    }

    SECTION("Leading zeros handling")
    {
        CDate date1;
        std::istringstream in1("05.01.2023");
        in1 >> date1;
        CHECK(date1.GetDay() == 5);
        CHECK(date1.GetMonth() == Month::JANUARY);

        CDate date2;
        std::istringstream in2("5.1.2023");
        in2 >> date2;
        CHECK(date2.GetDay() == 5);
        CHECK(date2.GetMonth() == Month::JANUARY);
    }
}