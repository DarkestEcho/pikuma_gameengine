#include "Tests.h"
#include <TestRunner/TestRunner.h>
#include <Tests/UtilsTests.h>

void Tests::TestAllSafe()
{
	RunUtilsTests();
}

void Tests::TestAll()
{
	TestAllSafe();
	TERMINATE_IF_FAILED();
}
