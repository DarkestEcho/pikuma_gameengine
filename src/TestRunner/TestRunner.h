#pragma once

#include <Logger/Logger.h>

#include <sstream>
#include <stdexcept>
#include <string>
#include <stdint.h>


class TestRunner
{
public:
	template <class TestFunction>
	static void RunTest( TestFunction testFunction, const std::string& testName )
	{
		try
		{
			testFunction();
			Logger::Log( "TEST::" + testName + ":OK" );
		}
		catch ( std::runtime_error& error )
		{
			++failCount;
			Logger::Error( "TEST::FAIL::" + testName + ":" + error.what() );
		}
	}

	template <class T, class U>
	static void AssertEqual( const T& left, const U& right, const std::string& hint )
	{
		if ( !( left == right ) )
		{
			std::ostringstream os;
			os << "Assertion Failed: " << left << " != " << right << " Hint: " << hint;
			throw std::runtime_error( os.str() );
		}
	}

	static void Assert( bool value, const std::string& hint );

	static void ResetFailCount();
	static uint32_t GetFailCount();

	static void TerminateIfHasFails();

private:
	static uint32_t failCount;
};


#define ASSERT_EQUAL( x, y ) {            \
	std::ostringstream assertEqualPrivateOutStream;                \
	assertEqualPrivateOutStream << #x << " != " << #y << ", "      \
	<< __FILE__ << ":" << __LINE__;     \
	TestRunner::AssertEqual(x, y, assertEqualPrivateOutStream.str());          \
}

#define ASSERT( x ) {                     \
  std::ostringstream assertPrivateOutStream;                     \
  assertPrivateOutStream << #x << " Is False, "             \
    << __FILE__ << ":" << __LINE__;     \
  TestRunner::Assert(x, assertPrivateOutStream.str());                  \
}

#define RUN_TEST( function ) {               \
	TestRunner::RunTest( function, #function );  \
}

#define TERMINATE_IF_FAILED( ) {        \
	TestRunner::TerminateIfHasFails();  \
}
