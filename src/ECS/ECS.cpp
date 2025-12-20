#include "ECS.h"
#include <Logger/Logger.h>
#include <algorithm>
#include <string>


size_t IComponent::nextId = 0;


Entity::Entity( size_t id ) : id( id ) {}

size_t Entity::GetId() const
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

std::ostream& Entity::operator<<( std::ostream& os )
{
	os << "Entity " << GetId();
	return os;
}

Registry* Entity::registry = nullptr;

void Entity::SetRegistry(Registry* newRegistry)
{
	registry = newRegistry;
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


Entity Registry::CreateEntity()
{
	size_t entityId = numEntities++;
	if ( entityId >= entityComponentSignatures.size() )
	{
		size_t newSize = ( entityId + 1 ) * 2;
		entityComponentSignatures.resize( newSize );
	}
	Entity entity( entityId );
	entitiesToBeAdded.insert( entity );
	Logger::Log( ( "Created entity with id: " + std::to_string( entityId ) ) );
	return entity;
}

void Registry::AddEntityToSystems( Entity entity )
{
	const size_t entityId = entity.GetId();
	const Signature& entityComponentSignature = entityComponentSignatures[entityId];

	for ( const auto& [key, system] : systems )
	{
		const Signature& systemComponentSignature = system->GetComponentSignature();

		bool isInterested = ( entityComponentSignature & systemComponentSignature ) == systemComponentSignature;

		if ( isInterested )
		{
			system->AddEntityToSystem( entity );
		}
	}
}

void Registry::Update()
{
	// Add the entities that are waiting to be added to the active Systems
	for ( Entity entity : entitiesToBeAdded )
	{
		AddEntityToSystems( entity );
	}

	entitiesToBeAdded.clear();

	// Remove the entities that are waiting to be killed from the active Systems
}