#include "DateTime.h"
#include <cassert>
#include <vector>
#include <string>

// 생성자 TimeType( arg )가 예외를 던지지 않음을 확인합니다.
template< typename TimeType >
void AssertTrue( const std::string& arg )
{
	try
	{
		TimeType test( arg );
		assert( true );
	}
	catch ( const InvalidDateTimeFormat& )
	{
		assert( false );
	}
	catch ( const OutOfRange& )
	{
		assert( false );
	}
}

// 생성자 TimeType( arg )가 예외를 던짐을 확인합니다.
template< typename TimeType >
void AssertFalse( const std::string& arg )
{
	try
	{
		TimeType test( arg );
		assert( false );
	}
	catch ( const InvalidDateTimeFormat& )
	{
		assert( true );
	}
	catch ( const OutOfRange& )
	{
		assert( true );
	}
}

// 생성자 DateTime( int year, int month, ... )가 예외를 던지지 않음을 확인합니다.
void AssertTrue( int year, int month, int day, int hour, int minute, int second, int millisecond )
{
	try
	{
		DateTime test( year, month, day, hour, minute, second, millisecond );
		assert( true );
	}
	catch ( const OutOfRange& )
	{
		assert( false );
	}
}

// 생성자 DateTime( int year, int month, ... )가 예외를 던짐을 확인합니다.
void AssertFalse( int year, int month, int day, int hour, int minute, int second, int millisecond )
{
	try
	{
		DateTime test( year, month, day, hour, minute, second, millisecond );
		assert( false );
	}
	catch ( const OutOfRange& )
	{
		assert( true );
	}
}

void DateTimeTest()
{
//
// 기본으로 주어진 테스트 케이스들
//
	TimeSpan s1( "00:00:05" ); // 5 seconds
	TimeSpan s2( 5000 );

	assert( s1.GetTimeAs( TimeSpan::Units::SECOND ) == 5 );
	assert( s1 == s2 );
	assert( ( s2 - 5.0f ) == TimeSpan() );
	assert( s2 * s1 == 25 );

//
// 작성자가 추가한 테스트 케이스들
//
	AssertTrue< TimeSpan >( "00:00:05" );
	AssertTrue< TimeSpan >( "00:00:05.00" );
	AssertTrue< TimeSpan >( "00:00:05.01" );
	AssertTrue< TimeSpan >( "00:00:05.99" );
	AssertTrue< TimeSpan >( "-00:00:05" );
	AssertTrue< TimeSpan >( "-00:00:05.01" );
	AssertTrue< TimeSpan >( "+00:00:05" );
	AssertTrue< TimeSpan >( "+00:00:05.01" );
	AssertTrue< TimeSpan >( "2020-09-29 10:41:00" ); // 62855952060 seconds
	AssertTrue< TimeSpan >( "2020-09-29 10:41:00.00" );
	AssertTrue< TimeSpan >( "2020-09-29 10:41:00.01" );
	AssertTrue< TimeSpan >( "2020-09-29 10:41:00.99" );
	AssertTrue< TimeSpan >( "0000-00-00 00:00:00" );
	AssertTrue< TimeSpan >( "9999-12-31 23:59:59" );
	AssertTrue< TimeSpan >( "-2020-09-29 10:41:00" );
	AssertTrue< TimeSpan >( "-2020-09-29 10:41:00.01" );
	AssertTrue< TimeSpan >( "-0000-00-00 00:00:00" );
	AssertTrue< TimeSpan >( "-9999-12-31 23:59:59" );
	AssertTrue< TimeSpan >( "+2020-09-29 10:41:00" );
	AssertTrue< TimeSpan >( "+2020-09-29 10:41:00.01" );
	AssertTrue< TimeSpan >( "+0000-00-00 00:00:00" );
	AssertTrue< TimeSpan >( "+9999-12-31 23:59:59" );

	AssertFalse< TimeSpan >( "" );
	AssertFalse< TimeSpan >( " " );
	AssertFalse< TimeSpan >( "0:00:05" );
	AssertFalse< TimeSpan >( "00:0:05" );
	AssertFalse< TimeSpan >( "00:00:5" );
	AssertFalse< TimeSpan >( "000:00:05" );
	AssertFalse< TimeSpan >( "00:000:05" );
	AssertFalse< TimeSpan >( "00:00:055" );
	AssertFalse< TimeSpan >( "00:00:05.0" );
	AssertFalse< TimeSpan >( "00:00:05.000" );
	AssertFalse< TimeSpan >( "00:00:05:00" );
	AssertFalse< TimeSpan >( "00-00-05-00" );
	AssertFalse< TimeSpan >( "20-09-29 10:41:00" );
	AssertFalse< TimeSpan >( "2020-9-29 10:41:00" );
	AssertFalse< TimeSpan >( "2020-09-1 10:41:00" );
	AssertFalse< TimeSpan >( "2020-09-29 1:41:00" );
	AssertFalse< TimeSpan >( "2020-09-29 10:4:00" );
	AssertFalse< TimeSpan >( "2020-09-29 10:41:1" );
	AssertFalse< TimeSpan >( "2020-09-29 10:41:00.1" );
	AssertFalse< TimeSpan >( "2020-09-29 +10:41:00" );
	AssertFalse< TimeSpan >( "2020-09-29 -10:41:00" );
	AssertFalse< TimeSpan >( "+2020-09-29 +10:41:00" );
	AssertFalse< TimeSpan >( "+2020-09-29 -10:41:00" );
	AssertFalse< TimeSpan >( "+2020-09-29 -10:41:00" );
	AssertFalse< TimeSpan >( "-2020-09-29 +10:41:00" );
	AssertFalse< TimeSpan >( "-2020-09-29 -10:41:00" );
	
	TimeSpan s3( "0001-01-01 01:01:01" );
	TimeSpan s4( 33786061, TimeSpan::Units::SECOND );
		
	assert( s3.GetTimeAs( TimeSpan::Units::YEAR ) == 1 );
	assert( s3.GetTimeAs( TimeSpan::Units::MONTH ) == 13 );
	assert( s3.GetTimeAs( TimeSpan::Units::WEEK ) == 55 ); //56
	assert( s3.GetTimeAs( TimeSpan::Units::DAY ) == 391 ); //396
	assert( s3.GetTimeAs( TimeSpan::Units::HOUR ) == 9385 ); //9505
	assert( s3.GetTimeAs( TimeSpan::Units::MINUTE ) == 563101 ); //570301
	assert( s3.GetTimeAs( TimeSpan::Units::SECOND ) == 33786061 ); //34218061
	try
	{
		s3.GetTimeAs( TimeSpan::Units::MILLISECOND ); //33786061000
		assert( false );
	}
	catch ( const OutOfRange& )
	{
		assert( true );
	}

	assert( s3 == s4 );
	assert( (s4 - 33786061.f) == TimeSpan() );

//
// 기본으로 주어진 테스트 케이스들
//
	AssertFalse< DateTime >( "2009/01-30" );
	AssertFalse< DateTime >( "2009-02-30" );
	AssertFalse( 2009, 2, 30, 0, 0, 0, 0 );

	DateTime t1( "2009-1-1" );
	DateTime t2( 2099, 1, 2, 13, 15, 15, 0 );
	assert( t1.ToString() == "2009-01-01 00:00:00.00" );
	assert( t2.ToString() == "2099-01-02 13:15:15.00" );
	assert( ( t1 + 80.5f ).ToString() == "2009-01-01 00:01:20.50" );
	TimeSpan v( t2 - t1 );
	assert( t1 + v == t2 );
	assert( DateTime( "2009-5-26" ).GetDay() == DateTime::Days::TUE );
//
// 작성자가 추가한 테스트 케이스들
//
	AssertFalse< DateTime >( "2020-10/06" );
	AssertFalse< DateTime >( "2020-10-06 10:00:00" );
	AssertFalse< DateTime >( "2020-0-06" );
	AssertFalse< DateTime >( "2020-13-06" );
	AssertFalse< DateTime >( "2020-10-0" );
	AssertFalse< DateTime >( "2020-10-32" );
	AssertTrue< DateTime >( "2020-2-29" );
	AssertFalse< DateTime >( "2021-2-29" );
	AssertFalse( 2020, 0, 6, 0, 0, 0, 0 );
	AssertFalse( 2020, 13, 6, 0, 0, 0, 0 );
	AssertFalse( 2020, 10, 0, 0, 0, 0, 0 );
	AssertFalse( 2020, 10, 32, 0, 0, 0, 0 );
	AssertTrue( 2020, 2, 29, 0, 0, 0, 0 );
	AssertFalse( 2021, 2, 29, 0, 0, 0, 0 );
	
	DateTime t3( "2020-1-31" );
	assert( t3.ToString() == "2020-01-31 00:00:00.00" );
	assert( t3 == DateTime( 2020, 1, 31, 0, 0, 0, 0 ) );
	DateTime t4( "2020-2-1" );
	assert( t4.ToString() == "2020-02-01 00:00:00.00" );
	assert( t4 == DateTime( 2020, 2, 1, 0, 0, 0, 0 ) );
	assert( ( t3 + 24*60*60.f ) == t4 );
	DateTime t5( "2020-2-29" );
	assert( t5.ToString() == "2020-02-29 00:00:00.00" );
	assert( t5 == DateTime( 2020, 2, 29, 0, 0, 0, 0 ) );
	DateTime t6 = t5 + 24*60*60.f + 5.f;
	assert( t6.ToString() == "2020-03-01 00:00:05.00" );
	assert( ( t6 - 5.f ).ToString() == "2020-03-01 00:00:00.00" );
	assert( t6 != DateTime( "2020-3-1" ) );
	assert( t5.Diff( t6 ) == -24*60*60.f - 5.f );
	assert( DateTime( "2020-10-06" ).GetDay() == DateTime::Days::TUE );
}

int main()
{
	DateTimeTest();
}