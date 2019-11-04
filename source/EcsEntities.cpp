#include "EcsEntities.h"

#include "Renderer.h"
#include "Game.h"

void Player::OnCreated()
{
    GetComp<CompParty>()->party = CompParty::ALLIANCE;

    int attackAreaTileId = game::gRenderer.AddTile(sf::Color(255, 0, 0, 64));
    auto eid = ecs::gEntityManager.CreateEntity<AttackArea>();
    ecs::IEntity *ent = ecs::gEntityManager.GetEntityByDesc(eid);
    ent->GetComp<CompDrawTileInfo>()->tileId = attackAreaTileId;
    ent->GetComp<CompDrawTileInfo>()->layer = CompDrawTileInfo::LAYER_EFFECTS;
    ent->GetComp<CompVisibility>()->visible = false;
    ent->GetComp<CompOwner>()->owner = this->GetDesc();

    GetComp<CompCurrentAttackArea>()->ent = eid;
}

void Player::OnDestroy() {
    ecs::gEntityManager.DestroyEntity(GetComp<CompCurrentAttackArea>()->ent);
}

void Player::OnUpdate() {
    CompHealth *h = GetComp<CompHealth>();
    CompStamina *s = GetComp<CompStamina>();
    CompMana *m = GetComp<CompMana>();
    if (h->value < 100.0f)
        h->value = std::min(100.0f, h->value + 0.01f);
	if (s->value < 10.0f) {
		s->value = std::min(100.0f, s->value + 0.06f);
	} else if (s->value < 100.0f)
        s->value = std::min(100.0f, s->value + 0.12f);
    if (m->value < 100.0f)
        m->value = std::min(100.0f, m->value + 0.1f);
}

void Enemy::OnCreated() {
    GetComp<CompParty>()->party = CompParty::ENEMIES;

    auto eid = ecs::gEntityManager.CreateEntity<AttackArea>();
    ecs::IEntity *area = ecs::gEntityManager.GetEntityByDesc(eid);

    area->GetComp<CompVisibility>()->visible = false;
    area->GetComp<CompOwner>()->owner = this->GetDesc();
    area->GetComp<CompActivity>()->active = false;
    area->GetComp<CompActivity>()->disableAfterOneTick = true;
    
    // 3x3 attack area.
    area->GetComp<CompPosPattern>()->positions.Init(3, 3, 1);

    GetComp<CompCurrentAttackArea>()->ent = eid;
    GetComp<CompCurrentAttackArea>()->shift = sf::Vector2i(-1, -1);
}

void Enemy::OnDestroy()
{
    ecs::gEntityManager.DestroyEntity(GetComp<CompCurrentAttackArea>()->ent);
}

void Enemy::OnUpdate()
{
    ++curTick;
    
    IEntity *area = ecs::gEntityManager.GetEntityByDesc(GetComp<CompCurrentAttackArea>()->ent);
    CompDamage *myDamage = GetComp<CompDamage>();
    area->GetComp<CompDamage>()->physDamage = myDamage->physDamage;
    area->GetComp<CompDamage>()->magicDamage = myDamage->magicDamage;

	if (!(curTick % 20)) { //20 - attack speed for all enemies
		area->GetComp<CompActivity>()->active = true;
	}

    unsigned vr = GetComp<CompVisionRadius>()->value;

    sf::Vector2i dir(0, 0);
    sf::Vector2i pos = GetComp<CompPos>()->v;

    // Now enemies are just hunt for the player.
    // Now there is very stupid algorithm:
    // just go in the player direction.
    ecs::Apply<TagPlayer>([&](IEntity *player)
    {
        CompPos *playerPos = player->GetComp<CompPos>();
        
        int dx = abs(playerPos->v.x - pos.x);
        int dy = abs(playerPos->v.y - pos.y);
        if (std::max(dx, dy) > GetComp<CompVisionRadius>()->value)
            return;
		GetComp<CompVisionRadius>()->value = 1000;

        if (playerPos->v.x < pos.x)
            dir.x = -1;
        else if (playerPos->v.x > pos.x)
            dir.x = 1;
        if (playerPos->v.y < pos.y)
            dir.y = -1;
        else if (playerPos->v.y > pos.y)
            dir.y = 1;
    });

    GetComp<CompMoveDir>()->v = dir;
}

void EnemyGhost::OnCreated() {
	GetComp<CompParty>()->party = CompParty::ENEMIES;

	auto eid = ecs::gEntityManager.CreateEntity<AttackArea>();
	ecs::IEntity* area = ecs::gEntityManager.GetEntityByDesc(eid);

	area->GetComp<CompVisibility>()->visible = false;
	area->GetComp<CompOwner>()->owner = this->GetDesc();
	area->GetComp<CompActivity>()->active = false;
	area->GetComp<CompActivity>()->disableAfterOneTick = true;

	// 3x3 attack area.
	area->GetComp<CompPosPattern>()->positions.Init(3, 3, 1);

	GetComp<CompCurrentAttackArea>()->ent = eid;
	GetComp<CompCurrentAttackArea>()->shift = sf::Vector2i(-1, -1);
}

void EnemyGhost::OnDestroy()
{
	ecs::gEntityManager.DestroyEntity(GetComp<CompCurrentAttackArea>()->ent);
}

void EnemyGhost::OnUpdate()
{
	++curTick;

	IEntity* area = ecs::gEntityManager.GetEntityByDesc(GetComp<CompCurrentAttackArea>()->ent);
	CompDamage* myDamage = GetComp<CompDamage>();
	area->GetComp<CompDamage>()->physDamage = myDamage->physDamage;
	area->GetComp<CompDamage>()->magicDamage = myDamage->magicDamage;

	if (!(curTick % 20)) { //20 - attack speed for all enemies
		area->GetComp<CompActivity>()->active = true;
	}

	unsigned vr = GetComp<CompVisionRadius>()->value;

	sf::Vector2i dir(0, 0);
	sf::Vector2i pos = GetComp<CompPos>()->v;

	// Now enemies are just hunt for the player.
	// Now there is very stupid algorithm:
	// just go in the player direction.
	ecs::Apply<TagPlayer>([&](IEntity* player)
		{
			CompPos* playerPos = player->GetComp<CompPos>();

			int dx = abs(playerPos->v.x - pos.x);
			int dy = abs(playerPos->v.y - pos.y);
			if (std::max(dx, dy) > GetComp<CompVisionRadius>()->value)
				return;
			GetComp<CompVisionRadius>()->value = 1000;

			if (playerPos->v.x < pos.x)
				dir.x = -1;
			else if (playerPos->v.x > pos.x)
				dir.x = 1;
			if (playerPos->v.y < pos.y)
				dir.y = -1;
			else if (playerPos->v.y > pos.y)
				dir.y = 1;
		});

	GetComp<CompMoveDir>()->v = dir;
}

void Boss::OnCreated() {
	GetComp<CompParty>()->party = CompParty::ENEMIES;
}

int firerate = 160;

void createFireball(CompPos *pos, sf::Vector2i dir, const char* filename) {
	auto eid = ecs::gEntityManager.CreateEntity<Fireball>();
	ecs::IEntity* ball = ecs::gEntityManager.GetEntityByDesc(eid);

	ball->GetComp<CompPos>()->v = pos->v + dir;
	ball->GetComp<CompMoveDir>()->v = dir;
	ball->GetComp<CompDrawTileInfo>()->layer = 1;
	ball->GetComp<CompDrawTileInfo>()->tileId = game::gRenderer.AddTile(game::gRenderer.AddTexture(filename));
	ball->GetComp<CompDamage>()->magicDamage = 0.5;
	ball->GetComp<CompDamage>()->physDamage = 0.2;
}

void Boss::OnUpdate()
{
	ecs::Apply<TagPlayer>([&](IEntity* player) {
		CompPos* playerPos = player->GetComp<CompPos>();

		int dx = abs(playerPos->v.x - GetComp<CompPos>()->v.x);
		int dy = abs(playerPos->v.y - GetComp<CompPos>()->v.y);
		if (std::max(dx, dy) > GetComp<CompVisionRadius>()->value) {
			GetComp<CompHealth>()->value = 200;
			return;
		}
		player->GetComp<CompHealth>()->value -= 0.01;
		if (player->GetComp<CompHealth>()->value <= 0.0f)
			ecs::gEntityManager.DestroyEntity(player->GetDesc());
		++curTick;

		/*if (curTick % (2 * firerate - 80) == 0) {
			GetComp<CompPos>()->v += sf::Vector2i(1, 0);
		} else if (curTick % (2 * firerate - 80) == (2 * firerate - 80) / 4) {
			GetComp<CompPos>()->v += sf::Vector2i(0, -1);
		} else if (curTick % (2 * firerate - 80) == (2 * firerate - 80) / 2) {
			GetComp<CompPos>()->v += sf::Vector2i(-1, 0);
		} else if (curTick % (2 * firerate - 80) == (2 * firerate - 80) / 4 + (2 * firerate - 80) / 2) {
			GetComp<CompPos>()->v += sf::Vector2i(0, 1);
		}*/
		if (curTick % (5 * firerate) == 1) {
			auto eid = ecs::gEntityManager.CreateEntity<EnemyGhost>();
			ecs::IEntity* ball = ecs::gEntityManager.GetEntityByDesc(eid);

			ball->GetComp<CompPos>()->v = GetComp<CompPos>()->v;
			ball->GetComp<CompDrawTileInfo>()->layer = 1;
			ball->GetComp<CompDrawTileInfo>()->tileId = game::gRenderer.AddTile(game::gRenderer.AddTexture("tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_342.png"));
			ball->GetComp<CompDamage>()->magicDamage = 1.0f;
			ball->GetComp<CompDamage>()->physDamage = 2.0f;
			ball->GetComp<CompSpeed>()->speed = 100.0f;
			ball->GetComp<CompVisionRadius>()->value = 5;
			ball->GetComp<CompHealth>()->value = 40.0f;
		}
		if (curTick % firerate == 0) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(0, 1), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_112.png");
		} else if (curTick % firerate == firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(1, 1), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_118.png");
		} else if (curTick % firerate == 2 * firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(1, 0), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_111.png");
		} else if (curTick % firerate == 3 * firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(1, -1), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_115.png");
		} else if (curTick % firerate == 4 * firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(0, -1), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_114.png");
		} else if (curTick % firerate == 5 * firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(-1, -1), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_116.png");
		} else if (curTick % firerate == 6 * firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(-1, 0), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_113.png");
		} else if (curTick % firerate == 7 * firerate / 8) {
			createFireball(GetComp<CompPos>(), sf::Vector2i(-1, 1), "tileset/Sliced/fx_24x24/oryx_16bit_fantasy_fx2_117.png");
		}
	});
}

void Fireball::OnCreated() {
	GetComp<CompParty>()->party = CompParty::ENEMIES;
}

void Fireball::OnUpdate()
{
	if (count >= 8) {
		ecs::gEntityManager.DestroyEntity(this->GetDesc());
		return;
	}
	++curTick;
	if (curTick % 30 == 0) {
		GetComp<CompPos>()->v += GetComp<CompMoveDir>()->v;
		count++;
	}
	ecs::Apply<TagPlayer>([&](IEntity* player) {
		if (GetComp<CompPos>()->v == player->GetComp<CompPos>()->v) {
			CompDamage* damage = GetComp<CompDamage>();
			CompArmor* resist = player->GetComp<CompArmor>();
			float physResist = 0.0f;
			float magicResist = 0.0f;
			if (resist)
			{
				physResist = resist->physResist;
				magicResist = resist->magicResist;
			}
			CompHealth* h = player->GetComp<CompHealth>();

			h->value -= stl::max(damage->physDamage * (1.0f - physResist), 0.0f);
			h->value -= stl::max(damage->magicDamage * (1.0f - magicResist), 0.0f);
			if (h->value <= 0.0f)
				ecs::gEntityManager.DestroyEntity(player->GetDesc());
		}
	});
}

void HealingPlace::OnUpdate() {
	CompPos* pos = GetComp<CompPos>();
	ecs::Apply<TagPlayer>([&](IEntity* player) {
		CompPos* playerPos = player->GetComp<CompPos>();
		if (playerPos->v.x == pos->v.x && playerPos->v.y == pos->v.y) {
			player->GetComp<CompHealth>()->value = 100;
			player->GetComp<CompStamina>()->value = 100;
			player->GetComp<CompMana>()->value = 100;
			ecs::gEntityManager.DestroyEntity(this->GetDesc());
			return;
		}
	});
}

void ChangeLevel::OnUpdate() {
	CompPos* pos = GetComp<CompPos>();
	ecs::Apply<TagPlayer>([&](IEntity* player) {
		CompPos* playerPos = player->GetComp<CompPos>();
		if (playerPos->v.x == pos->v.x && playerPos->v.y == pos->v.y) {
			curLevel++;
		}
	});
}
