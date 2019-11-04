#include "Game.h"

#include "stl.h"
#include "GameStructures.h"
#include "GameDataLoad.h"
#include "ECS.h"
#include "Timer.h"
#include "EcsSystems.h"

#include "Renderer.h"
#include "GameLevelData.h"
using namespace game;

unsigned curLevel = 1;

namespace game
{

LevelData gLevelData;

static bool swordPattern[1 * 2] = {
    1, 1
};

static bool clubPattern[3 * 3] = {
    1, 0, 0,
    1, 1, 1,
    1, 0, 0
};

static bool staffPattern[1 * 4] = {
	1, 1, 1, 1
};


stl::vector<Weapon> gGameWeapons;

#define UPDATE_PERIOD 0.01f

void Game::Init(const stl::shared_ptr<sf::RenderWindow> &window)
{
    this->window = window;
    gRenderer.Init(window);
    SendEvent(EventRendererWasInited());

    Weapon w;
    int id;

    w.areaSize = sf::Vector2u(1, 2);
    w.staminaConsumption = 8.0f;
	if (curLevel == 2) {
		w.staminaConsumption = 4.0f;
	}
    w.physDamage = 9.0f;
    w.pattern.resize(sizeof(swordPattern) / sizeof(bool));
    for (unsigned i = 0; i < w.pattern.size(); ++i)
        w.pattern[i] = swordPattern[i];
    id = gRenderer.AddTexture("tileset/Sliced/items_16x16/oryx_16bit_fantasy_items_209.png");
    w.tileId = gRenderer.AddTile(id);
    gGameWeapons.push_back(w);

	w.areaSize = sf::Vector2u(3, 3);
    w.staminaConsumption = 25.0f;
	if (curLevel == 2) {
		w.staminaConsumption = 9.0f;
	}
    w.physDamage = 20.0f;
	w.magicDamage = 0.0f;
    w.pattern.resize(sizeof(clubPattern) / sizeof(bool));
    for (unsigned i = 0; i < w.pattern.size(); ++i)
        w.pattern[i] = clubPattern[i];
    id = gRenderer.AddTexture("tileset/Sliced/items_16x16/oryx_16bit_fantasy_items_190.png");
    w.tileId = gRenderer.AddTile(id);
    gGameWeapons.push_back(w);

	if (curLevel == 2) {
		w.areaSize = sf::Vector2u(1, 4);
		w.staminaConsumption = 3.0f;
		w.manaConsumption = 55.0f;
		w.physDamage = 0.0f;
		w.magicDamage = 40.0f;
		w.pattern.resize(sizeof(staffPattern) / sizeof(bool));
		for (unsigned i = 0; i < w.pattern.size(); ++i)
			w.pattern[i] = staffPattern[i];
		id = gRenderer.AddTexture("tileset/Sliced/items_16x16/oryx_16bit_fantasy_items_186.png");
		w.tileId = gRenderer.AddTile(id);
		gGameWeapons.push_back(w);
	}
}

void Game::Release()
{
    //window.reset();
    gRenderer.Release();
    gGameWeapons.clear();
    ecs::gEntityManager.DestroyAllEntities();
}

GameResults Game::StartLevel(const char *levelFilename)
{
    gLevelData = LoadLevel(levelFilename);

    

    ecs::Apply<CompOwnedItems, CompCurrentAttackArea>([&](ecs::IEntity *ent) {
        CompOwnedItems *ammo = ent->GetComp<CompOwnedItems>();
        ammo->weapons.push_back(&gGameWeapons[0]);
        ammo->weapons.push_back(&gGameWeapons[1]);
		if (curLevel == 2)
			ammo->weapons.push_back(&gGameWeapons[2]);
        ammo->curWeaponId = 0;
        CompCurrentAttackArea *area = ent->GetComp<CompCurrentAttackArea>();
    });

    gTime.Reset();
    volatile float lastTime = gTime.GetTime();
	unsigned tmp = curLevel;
    while (window->isOpen() && curLevel == tmp)
    {
        gRenderer.BeginDraw(sf::Color(0x000000FFU));
        ecs::gEntityManager.UpdateEntities();
		gRenderer.EndDraw();
        while (lastTime + UPDATE_PERIOD > gTime.GetTime());
        lastTime = gTime.GetTime();
        // Sleep(200);
    }
    return GameResults();
}

}