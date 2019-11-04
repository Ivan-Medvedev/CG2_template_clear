#pragma once

#include "stl.h"
#include <sfml/Graphics.hpp>
#include "Renderer.h"
#include "GameStructures.h"

extern unsigned curLevel;

namespace game
{
	
class GameLevel
{

};

struct GameResults
{
public:
    enum CompleteStatus
    {
        FAILED,
        COMPLETE
    }
    status;
};

class Game
{
public:

    void Init(const stl::shared_ptr<sf::RenderWindow> &window);
    void Release();

    GameResults StartLevel(const char *levelFilename);

protected:

    stl::map<stl::string, unsigned> texNames;
    stl::shared_ptr<sf::RenderWindow> window;
};
extern Game g;
extern stl::vector<Weapon> gGameWeapons;
}