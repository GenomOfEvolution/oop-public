#include "CDate.h"

namespace
{
	bool IsLeapYear(unsigned year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	unsigned GetDaysInMonth(Month month, unsigned year)
	{
		switch (month)
		{
		case Month::FEBRUARY:
			return IsLeapYear(year) ? 29 : 28;
		case Month::APRIL:
		case Month::JUNE:
		case Month::SEPTEMBER:
		case Month::NOVEMBER:
			return 30;
		default:
			return 31;
		}
	}

	void TimestampToDate(unsigned timestamp, unsigned& day, Month& month, unsigned& year)
	{
		unsigned timeRemain = timestamp;
		year = 1970;

		while (true)
		{
			unsigned daysInYear = IsLeapYear(year) ? 366 : 365;
			if (timeRemain < daysInYear)
			{
				break;
			}
			timeRemain -= daysInYear;
			++year;
		}

		month = Month::JANUARY;
		while (true)
		{
			unsigned daysInCurrentMonth = GetDaysInMonth(month, year);
			if (timeRemain < daysInCurrentMonth)
			{
				break;
			}
			timeRemain -= daysInCurrentMonth;
			month = static_cast<Month>(static_cast<unsigned>(month) + 1);
		}

		day = timeRemain + 1;
	}

	bool IsCorrectDate(unsigned day, Month month, unsigned year)
	{
		return (
			day >= 1 && day <= GetDaysInMonth(month, year) &&
			month >= Month::JANUARY && month <= Month::DECEMBER &&
			year >= 1970 && year <= 9999
		);
	}

	unsigned DateToTimestamp(unsigned day, Month month, unsigned year)
	{
		if (!IsCorrectDate(day, month, year))
		{
			throw std::invalid_argument("Invalid date format");
		}

		unsigned totalDays = 0;
		for (unsigned y = 1970; y < year; ++y)
		{
			totalDays += IsLeapYear(y) ? 366 : 365;
		}

		for (unsigned m = 1; m < static_cast<unsigned>(month); ++m)
		{
			totalDays += GetDaysInMonth(static_cast<Month>(m), year);
		}

		totalDays += day - 1;
		return totalDays;
	}
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (!IsCorrectDate(day, month, year))
	{
		throw std::invalid_argument("Invalid date format");
	}

	m_timestamp = DateToTimestamp(day, month, year);
}

CDate::CDate(unsigned timestamp) : m_timestamp(timestamp)
{
}

CDate::CDate() : m_timestamp(0)
{
}

CDate& CDate::operator++()
{
	if (IsValid())
	{
		++m_timestamp;
	}

	return *this;
}

CDate CDate::operator++(int)
{
	CDate dateCopy = *this;
	++(*this);
	return dateCopy;
}

CDate& CDate::operator--()
{
	if (IsValid())
	{
		--m_timestamp;
	}

	return *this;
}

CDate CDate::operator--(int)
{
	CDate dateCopy = *this;
	--(*this);
	return dateCopy;
}

CDate CDate::operator+(int days) const
{
	return CDate(m_timestamp + days);
}

CDate CDate::operator-(int days) const
{
	return CDate(m_timestamp - days);
}

int CDate::operator-(const CDate& other) const
{
	return m_timestamp - other.m_timestamp;
}

CDate& CDate::operator+=(int days)
{
	if (IsValid())
	{
		m_timestamp += days;
	}

	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (IsValid() && static_cast<int>(m_timestamp) >= days)
	{
		m_timestamp -= days;
	}
	else
	{
		m_timestamp = 0;
	}

	return *this;
}

unsigned CDate::GetDay() const
{
	unsigned day, year = 0;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);

	return day;
}

Month CDate::GetMonth() const
{
	unsigned day, year = 0;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);

	return month;
}

unsigned CDate::GetYear() const
{
	unsigned day, year = 0;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);

	return year;
}

WeekDay CDate::GetWeekDay() const
{
	if (!IsValid())
	{
		throw std::runtime_error("Invalid date");
	}

	return static_cast<WeekDay>((m_timestamp + 4) % 7);
}

bool CDate::IsValid() const
{
	unsigned day, year = 0;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);

	return IsCorrectDate(day, month, year);
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	if (!date.IsValid())
	{
		os << "INVALID DATE";
	}
	else
	{
		unsigned day = date.GetDay();
		Month month = date.GetMonth();
		unsigned year = date.GetYear();

		os << (day < 10 ? "0" : "") << day << "."
			<< (static_cast<unsigned>(month) < 10 ? "0" : "") << static_cast<unsigned>(month) << "."
			<< year;
	}

	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned day, month, year;
	char dot1, dot2;
	is >> day >> dot1 >> month >> dot2 >> year;

	if (is.fail())
	{
		return is;
	}

	if (dot1 == '.' && dot2 == '.')
	{
		try
		{
			date.m_timestamp = DateToTimestamp(day, static_cast<Month>(month), year);
		}
		catch (const std::exception&)
		{
			is.setstate(std::ios::failbit);
		}
	}
	else
	{
		is.setstate(std::ios::failbit);
	}

	return is;
}
