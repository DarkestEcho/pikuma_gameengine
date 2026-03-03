#include "UtilsTests.h"
#include <TestRunner/TestRunner.h>
#include <Utils/Utils.h>

void TestAABBCollisionCheck();

void Tests::RunUtilsTests()
{
	RUN_TEST( TestAABBCollisionCheck );
}

void TestAABBCollisionCheck()
{
	{
		CollisionBox aBox{ glm::vec2( 2.0f, 2.0f ), glm::vec2( 8.0f, 8.0f ) };
		CollisionBox bBox{ glm::vec2( 1.0f, 5.0f ), glm::vec2( 5.0f, 10.0f ) };

		ASSERT( Utils::CheckAABBCollision( aBox, bBox ) );
	}

	{
		CollisionBox aBox{ glm::vec2( 10.0f, 2.0f ), glm::vec2( 12.0f, 8.0f ) };
		CollisionBox bBox{ glm::vec2( 1.0f, 5.0f ),glm::vec2( 8.0f, 10.0f ) };

		ASSERT( Utils::CheckAABBCollision( aBox, bBox ) );
	}
}

