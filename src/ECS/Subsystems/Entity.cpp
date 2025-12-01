#include <Entity.h>

Entity::Entity( size_t id ) : id( id ) {}

size_t Entity::GetID() const
{
	return id;
}

bool Entity::operator==( const Entity& other ) const
{
	return id == other.id;
}

bool Entity::operator!=( const Entity& other ) const
{
	return id != other.id;
}

bool Entity::operator<( const Entity& other ) const
{
	return id < other.id;
}

bool Entity::operator>( const Entity& other ) const
{
	return id > other.id;
}

std::ostream& operator << ( std::ostream& os, const Entity& entity )
{
	os << "Entity " << entity.GetID();
	return os;
}