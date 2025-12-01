#pragma once
#include <vector>
#include <Types/Core.h>
#include <Entity.h>
#include <Component.h>

class System
{
private:
	// Which components an entity must have for the system to consider the entity
	Signature componentSignature;
	// List of all entities that the system is interested in
	std::vector<Entity> entities;
public:
	System() = default;
	virtual ~System() = default;

	void AddEntityToSystem( Entity entity );

	void RemoveAllEntityEntriesFromSystem( Entity entity );

	void RemoveEntityFromSystem( Entity entity );

	const std::vector<Entity>& GetSystemEntities() const;

	const Signature& GetComponentSignature() const;

	template <typename TComponent>
	void RequireComponent();
};

template <typename TComponent>
void System::RequireComponent()
{
	const size_t componentId = Component<TComponent>::GetId();
	componentSignature.set( componentId );
}