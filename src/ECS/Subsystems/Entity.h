#pragma once
#include <ostream>

class Entity
{
private:
	size_t id;
public:
	Entity( size_t id );
	Entity( const Entity& entity ) = default;

	size_t GetID() const;

	Entity& operator = ( const Entity& entity ) = default;

	bool operator == ( const Entity& other ) const;
	bool operator != ( const Entity& other ) const;
	bool operator < ( const Entity& other ) const;
	bool operator > ( const Entity& other ) const;
};

std::ostream& operator << ( std::ostream& os, const Entity& entity );