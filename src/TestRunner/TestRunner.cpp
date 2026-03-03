#include "TestRunner.h"

uint32_t TestRunner::failCount{ 0 };

void TestRunner::Assert( bool value, const std::string& hint )
{
	TestRunner::AssertEqual( value, true, hint );
}

void TestRunner::ResetFailCount()
{
	failCount = 0;
}

uint32_t TestRunner::GetFailCount()
{
	return failCount;
}

void TestRunner::TerminateIfHasFails()
{
	if ( failCount > 0 )
	{
		Logger::Error( "TEST::|" + std::to_string( failCount ) + "| Unit Tests Failed. Terminate..." );
		exit( 1 );
	}
}
