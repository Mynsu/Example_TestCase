#pragma once
#include <stdexcept>

class InvalidDateTimeFormat
  : public std::logic_error
{
public:
	InvalidDateTimeFormat()
	: std::logic_error( "invalid DateTime" )
	{
	}
};

class OutOfRange
  : public std::out_of_range
{
public:
	OutOfRange()
	: std::out_of_range( "invalid range of DateTime" )
	{
	}
};

class TimeSpan
{
public:
	friend class DateTime;
	typedef long long int RepresentationType;
	struct Units { enum Type { MILLISECOND, SECOND, MINUTE, HOUR, DAY, WEEK, MONTH, YEAR }; };

	TimeSpan(); // default 0
	TimeSpan( int ticks, Units::Type unit = Units::MILLISECOND );
	TimeSpan( float seconds );
	TimeSpan( const std::string& value ); // "yyyy-mm-dd hh:mm:ss.ss" or "hh:mm:ss.ss" (negative value possible)
	operator float() const; // seconds (for Lunia compatible) and this makes all operation as float type
	int GetTimeAs( Units::Type unit = Units::SECOND ) const; // floored.  If the value exceeds INT_MAX, throws OutOfRange.
private:
	RepresentationType innerTicks;
	static RepresentationType Convert2ndTokenToInnerTicks( const std::string& hhmmssss );
	static RepresentationType ToInnerTicks( int ticks, Units::Type unit );
};

class DateTime
{
public:
	typedef TimeSpan TimePoint; // Traits; TimeSpan means duration which doesn't fit DateTime-the time point.
	struct Days { enum Type { SUN, MON, TUE, WED, THR, FRI, SAT, END_OF_ENUM }; };

	DateTime(); // default 1970-01-01 00:00:00 by ANSI C (http://www.cplusplus.com/reference/clibrary/ctime/time/)
	DateTime( const std::string& value ); // "yyyy-mm-dd hh:mm:ss.ss" , throws InvalidDateTimeFormat by invalid date-time format string
	DateTime( int year, int month, int day, int hour, int minute, int second, int millisecond ); // throws InvalidDateTimeFormat by invalid unit of range.

	DateTime operator -( const TimeSpan& ) const;
	DateTime operator +( const TimeSpan& ) const;
	TimeSpan operator -( const DateTime& ) const; // same as Diff
	bool operator ==( const DateTime& ) const;
	bool operator !=( const DateTime& ) const;

	Days::Type GetDay() const;
	std::string ToString() const; // returns e.g. "yyyy-mm-dd hh:mm:ss.ss"
	TimeSpan Diff( const DateTime& time ) const; // returns negative values if the "time" parameter is further.
private:
	TimePoint timePoint;
	static bool IsDateValid( int year, int month, int day );
	static bool IsLeapYear( int year );
	static int GainNumberOfDaysIn( int year, int month, int day ); // Not including IsDateValid( year, month, day ).
	static int GainNumberOfDaysOn( int month ); // Neglects leap year, thus GainNumberOfDaysOn( 2 ) always returns 28, not 29.
	static std::string ToString( int year, int month, int day, int hour, int minute, int second, int millisecond ); // returns e.g. "2020-10-05 18:38:00.05"
};
