#include "ESC.h"
#include <Logger/Logger.h>
#include <algorithm>

// TODO: Implement all the functions from ESC


Entity::Entity( int id ) : id( id ) {}

int Entity::GetID() const
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

void System::AddEntityToSystem( Entity entity )
{
	entities.push_back( entity );
}

void System::RemoveAllEntityEntriesFromSystem( Entity entity )
{
	std::vector<Entity>::iterator newEndIt = std::remove( entities.begin(), entities.end(), entity );
	entities.erase( newEndIt, entities.end() );
}

void System::RemoveEntityFromSystem( Entity entity )
{
	std::vector<Entity>::iterator it = std::find( entities.begin(), entities.end(), entity );
	if ( it != entities.end() )
	{
		*it = entities.back();
		entities.pop_back();
	}
}

const std::vector<Entity>& System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponentSignature() const
{
	return componentSignature;
}


std::ostream& operator << ( std::ostream& os, const Entity& entity )
{
	os << "Entity " << entity.GetID();
	return os;
}