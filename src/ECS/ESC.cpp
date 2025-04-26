#include "ESC.h"

// TODO: Implement all the functions from ESC

size_t IComponent::nextId = 0;

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

Entity Registry::CreateEntity()
{
	size_t entityId = numEntities++;
	if ( entityId >= entityComponentSignatures.size() )
	{
		size_t newSize = entityComponentSignatures.size() * 2;
		entityComponentSignatures.resize( newSize );
	}
	Entity entity( entityId );
	entitiesToBeAdded.insert( entity );
	Logger::Log( ( "Created entity with id = " + std::to_string( entityId ) ) );
	return entity;
}

void Registry::Update()
{
	// Add the entities that are waiting to be added to the active Systems
	// Remove the entities that are waiting to be killed from the active Systems


}
