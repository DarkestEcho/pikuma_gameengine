#pragma once
#include <Types/Core.h>
#include <Types/Pool.h>
#include <cstddef>
#include <ostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <typeindex>
#include <memory>


class IComponent
{
protected:
	static size_t nextId;
};

template<typename T>
class Component : public IComponent
{
public:
	static size_t GetId()
	{
		static size_t id = nextId++;
		return id;
	}
};


class Entity
{
private:
	size_t id;
	static class Registry* registry;
public:
	Entity( size_t id );
	Entity( const Entity& entity ) = default;

	static void SetRegistry( Registry* newRegistry );

	size_t GetId() const;

	Entity& operator = ( const Entity& entity ) = default;
	bool operator == ( const Entity& other ) const;
	bool operator != ( const Entity& other ) const;
	bool operator < ( const Entity& other ) const;
	bool operator > ( const Entity& other ) const;
	std::ostream& operator << ( std::ostream& os );

	template<typename TComponent, typename ...TArgs>
	void AddComponent( TArgs&& ...args );

	template<typename TComponent>
	void RemoveComponent();

	template<typename TComponent>
	bool HasComponent();

	template<typename TComponent>
	TComponent& GetComponent();
};


class System
{
private:
	// Which components an entity must have for the system to consider the entity
	Signature componentSignature;
	// List of all entities that the system is interested in
	std::vector<Entity> entities;

protected:
	template <typename TComponent>
	void RequireComponent();

public:
	System() = default;
	virtual ~System() = default;

	void AddEntityToSystem( Entity entity );

	void RemoveAllEntityEntriesFromSystem( Entity entity );

	void RemoveEntityFromSystem( Entity entity );

	const std::vector<Entity>& GetSystemEntities() const;

	const Signature& GetComponentSignature() const;
};


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
	Registry()
	{
		Entity::SetRegistry( this );
	}

	void Update();

	Entity CreateEntity();

	void KillEntity( Entity entity );

	void AddEntityToSystem( Entity entity );

	template<typename TComponent, typename ...TArgs>
	void AddComponent( Entity entity, TArgs&& ...args );

	template<typename TComponent>
	void RemoveComponent( Entity entity );

	template<typename TComponent>
	bool HasComponent( Entity entity ) const;

	template<typename TComponent>
	TComponent& GetComponent( Entity entity ) const;


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


#pragma region // -----> REGISTRY        
template<typename TComponent, typename ...TArgs>
void Registry::AddComponent( Entity entity, TArgs&& ...args )
{
	const size_t componentId = Component<TComponent>::GetId();
	const size_t entityId = entity.GetId();

	if ( componentId >= componentPools.size() )
	{
		componentPools.resize( std::max( componentPools.size() * 2, componentId + 1 ), nullptr );
	}

	if ( !componentPools[componentId] )
	{
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentPools[componentId] = newComponentPool;
	}

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>( componentPools[componentId] );
	TComponent newComponent( std::forward<TArgs>( args )... );
	componentPool->Set( entityId, newComponent );
	entityComponentSignatures[entityId].set( componentId );
	Logger::Log( "Component:Id:" + std::to_string( componentId ) + " was added to Entity:Id:" + std::to_string( entityId ) );
}

template<typename TComponent>
void Registry::RemoveComponent( Entity entity )
{
	const size_t entityId = entity.GetId();
	const size_t componentId = Component<TComponent>::GetId();

	entityComponentSignatures[entityId].set( componentId, false );
	Logger::Log( "Component:Id:" + std::to_string( componentId ) + " was removed from Entity:Id:" + std::to_string( entityId ) );
}

template<typename TComponent>
bool Registry::HasComponent( Entity entity ) const
{
	const size_t entityId = entity.GetId();
	const size_t componentId = Component<TComponent>::GetId();

	return entityComponentSignatures[entityId].test( componentId );
}

template<typename TComponent>
TComponent& Registry::GetComponent( Entity entity ) const
{
	const size_t componentId = Component<TComponent>::GetId();
	const size_t entityId = entity.GetId();
	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>( componentPools[componentId] );
	return componentPool->Get( entityId );
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
	return *std::static_pointer_cast<TSystem>( systems.at( std::type_index( typeid( TSystem ) ) ) );
}
#pragma endregion // -----> REGISTRY END        

#pragma region // -----> ENTITY        
template<typename TComponent, typename ...TArgs>
void Entity::AddComponent( TArgs&& ...args )
{
	Entity::registry->AddComponent<TComponent>( *this, std::forward<TArgs>( args )... );
}

template<typename TComponent>
void Entity::RemoveComponent()
{
	Entity::registry->RemoveComponent<TComponent>( *this );
}

template<typename TComponent>
bool Entity::HasComponent()
{
	return Entity::registry->HasComponent<TComponent>( *this );
}

template<typename TComponent>
TComponent& Entity::GetComponent()
{
	return Entity::registry->GetComponent<TComponent>( *this );
}
#pragma endregion // -----> ENTITY END        

#pragma region // -----> SYSTEM        
template <typename TComponent>
void System::RequireComponent()
{
	const size_t componentId = Component<TComponent>::GetId();
	componentSignature.set( componentId );
}
#pragma endregion // -----> SYSTEM END        