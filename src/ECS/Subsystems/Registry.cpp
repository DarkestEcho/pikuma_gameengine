#include <Registry.h>
#include <string>
#include <Logger/Logger.h>


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
	const size_t entityId = entity.GetID();
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