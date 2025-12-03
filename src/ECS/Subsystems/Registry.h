#pragma once
#include <set>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <Types/Core.h>
#include <Types/Pool.h>
#include <Entity.h>
#include <System.h>

class Registry
{
private:
	size_t numEntities{ 0 };
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

	//Vector ind == component ID
	//Pool ind == entity ID
	std::vector<std::shared_ptr<IPool>> componentPools;

	//Vector ind == entity id
	//Components on/off for an entity
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
public:
	void Update();

	Entity CreateEntity();

	void KillEntity( Entity entity );

	void AddEntityToSystem( Entity entity );

	template<typename TComponent, typename ...TArgs>
	void AddComponent( Entity entity, TArgs&& ...args );

	template<typename TComponent>
	void RemoveComponent( Entity entity );

	template<typename TComponent>
	bool HasComponent( Entity entity );


	template<typename TSystem, typename ...TArgs>
	void AddSystem( TArgs&& ...args );

	template<typename TSystem>
	void RemoveSystem();

	template<typename TSystem>
	bool HasSystem();

	template<typename TSystem>
	TSystem& GetSystem();

	void AddEntityToSystems( Entity entity );
};


template<typename TComponent, typename ...TArgs>
void Registry::AddComponent( Entity entity, TArgs&& ...args )
{
	const size_t componentId = Component<TComponent>::GetId();
	const size_t entityId = entity.GetID();

	if ( componentId >= componentPools.size() )
	{
		componentPools.resize( std::max( componentPools.size() * 2, componentId + 1 ), nullptr );
	}

	if ( !componentPools[componentId] )
	{
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentPools[componentId] = newComponentPool;
	}

	std::shared_ptr<Pool<TComponent>> componentPool = componentPools[componentId];
	TComponent newComponent{ std::forward<TArgs>( args )... };
	componentPool->Set( entityId, newComponent );
	entityComponentSignatures[entityId].set( componentId );
}

template<typename TComponent>
void Registry::RemoveComponent( Entity entity )
{
	const size_t entityId = entity.GetID();
	const size_t componentId = Component<TComponent>::GetId();

	entityComponentSignatures[entityId].set( componentId, false );
}

template<typename TComponent>
bool Registry::HasComponent( Entity entity )
{
	const size_t entityId = entity.GetID();
	const size_t componentId = Component<TComponent>::GetID();

	return entityComponentSignatures[entityId].test( componentId );
}

template<typename TSystem, typename ...TArgs>
void Registry::AddSystem( TArgs && ...args )
{
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>( std::forward<TArgs>( args )... );
	systems[std::type_index( typeid( TSystem ) )] = newSystem;
}

template<typename TSystem>
void Registry::RemoveSystem()
{
	std::unordered_map<std::type_index, std::shared_ptr<System>>::iterator system = systems.find( std::type_index( typeid( TSystem ) ) );
	systems.erase( system );
}

template<typename TSystem>
bool Registry::HasSystem()
{
	return systems.find( std::type_index( typeid( TSystem ) ) ) != systems.end();
}

template<typename TSystem>
TSystem& Registry::GetSystem()
{
	return std::static_pointer_cast<TSystem&>( *systems.at( std::type_index( typeid( TSystem ) ) ) );
}