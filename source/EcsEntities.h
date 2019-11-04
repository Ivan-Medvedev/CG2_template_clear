#pragma once

/*
    In current realisation, entity is something that
    have components and can work and interact with
    other entities through 'Update()' (called on each frame update).

    If you want to initialize an entity, use OnCreated() instead of constructor.

    Here you can place all of the entity types you want to use.
*/

#include "ECS.h"
#include "EcsComponents.h"
#include <iostream>

class Player : public ecs::Entity<
    CompPos,
    CompDir,
    CompMoveDir,
    CompHealth,
	CompSpeed,
    CompDrawTileInfo,
    CompOwnedItems,
    CompCurrentAttackArea,
    CompStamina,
    CompMana,
    CompArmor,
    CompParty,
    // CompVisibility, // May be used for hide player (feature).
    //TagAlly,
    TagCollidable,
    TagPlayer>
{
public:
    ECS_ENTITY_DEFAULTS(Player)
    void OnCreated() override;
    void OnDestroy() override;
    void OnUpdate() override;
private:
	unsigned curTick = 0;
};

class AttackArea : public ecs::Entity<
    CompPosPattern,
    CompActivity,
    CompDamage,
    CompOwner,
    CompVisibility,
    CompDrawTileInfo>
{
public:
    ECS_ENTITY_DEFAULTS(AttackArea)
};

class Walls : public ecs::Entity<
    CompPosPattern,
    CompDrawTileInfo,
    TagCollidable>
{
public:
    ECS_ENTITY_DEFAULTS(Walls)
};

class Floor : public ecs::Entity<
    CompPosPattern,
    CompDrawTileInfo>
{
public:
    ECS_ENTITY_DEFAULTS(Floor)
};

// Ususal enemies have no stamina and mana.
class Enemy : public ecs::Entity<
    CompPos,
    CompMoveDir,
    CompHealth,
	CompSpeed,
    CompDrawTileInfo,
    CompCurrentAttackArea,
    CompArmor,
    CompDamage,
    CompParty,
    CompVisionRadius,
    TagCollidable>
{
public:
    ECS_ENTITY_DEFAULTS(Enemy)
    void OnCreated() override;
    void OnDestroy() override;
    void OnUpdate() override;
private:
    unsigned curTick = 0;
};

class Boss : public ecs::Entity<
	CompPos,
	CompHealth,
	CompDrawTileInfo,
	CompArmor,
	CompParty,
	CompVisionRadius,
	TagCollidable>
{
public:
	ECS_ENTITY_DEFAULTS(Boss)
	void OnCreated() override;
	void OnUpdate() override;
private:
	unsigned curTick = 0;
};

class Fireball : public ecs::Entity<
	CompPos,
	CompMoveDir,
	CompDamage,
	CompParty,
	CompDrawTileInfo>
{
public:
	ECS_ENTITY_DEFAULTS(Fireball)
	void OnCreated() override;
	void OnUpdate() override;
private:
	unsigned curTick = 0;
	unsigned count = 0;
};


class EnemyGhost : public ecs::Entity<
	CompPos,
	CompMoveDir,
	CompHealth,
	CompSpeed,
	CompDrawTileInfo,
	CompCurrentAttackArea,
	CompArmor,
	CompDamage,
	CompParty,
	CompVisionRadius>
{
public:
	ECS_ENTITY_DEFAULTS(EnemyGhost)
	void OnCreated() override;
	void OnDestroy() override;
	void OnUpdate() override;
private:
	unsigned curTick = 0;
};

class Item : public ecs::Entity<
	CompPosPattern,
	CompDrawTileInfo,
	TagCollecatble>
{
public:
	ECS_ENTITY_DEFAULTS(Item)
};

class HealingPlace : public ecs::Entity<
	CompDrawTileInfo,	
	CompPos>
{
public:
	ECS_ENTITY_DEFAULTS(HealingPlace)
	void OnUpdate() override;
};

class ChangeLevel : public ecs::Entity<
	CompPos>
{
public:
	ECS_ENTITY_DEFAULTS(ChangeLevel)
	void OnUpdate() override;
};

#ifndef ECS_REGISTER_ENTITY_TYPE
#define ECS_REGISTER_ENTITY_TYPE(typeName)
#endif

/*
    Register here all of the entity types
    you want to create by string names (and therefore from files).
*/

ECS_REGISTER_ENTITY_TYPE(Player)
ECS_REGISTER_ENTITY_TYPE(AttackArea)
ECS_REGISTER_ENTITY_TYPE(Walls)
ECS_REGISTER_ENTITY_TYPE(Floor)
ECS_REGISTER_ENTITY_TYPE(Item)
ECS_REGISTER_ENTITY_TYPE(Enemy)
ECS_REGISTER_ENTITY_TYPE(EnemyGhost)
ECS_REGISTER_ENTITY_TYPE(Boss)
ECS_REGISTER_ENTITY_TYPE(Fireball)
ECS_REGISTER_ENTITY_TYPE(HealingPlace)
ECS_REGISTER_ENTITY_TYPE(ChangeLevel)