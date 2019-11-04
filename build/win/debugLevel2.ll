map {
  _filename = "debugLevel2.png"
}

texture {
  _name = "walls_tex"
  _filename = "tileset/Sliced/world_24x24/oryx_16bit_fantasy_world_59.png"
}

texture {
  _name = "player_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_01.png"
}

texture {
  _name = "enemy_rat_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_224.png"
}

texture {
  _name = "enemy_ghost_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_294.png"
}


texture {
  _name = "enemy_boss_ghost_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_342.png"
}

texture {
  _name = "enemy_boss_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_343.png"
}

texture {
  _name = "enemy_spider_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_241.png"
}

texture {
  _name = "healingplace_tex"
  _filename = "tileset/Sliced/world_24x24/oryx_16bit_fantasy_world_1549.png"
}

tile {
  _name = "walls_tile"
  _texture = "walls_tex"
}

tile {
  _name = "player_tile"
  _texture = "player_tex"
}

tile {
  _name = "enemy_rat_tile"
  _texture = "enemy_rat_tex"
}

tile {
  _name = "enemy_ghost_tile"
  _texture = "enemy_ghost_tex"
}

tile {
  _name = "enemy_boss_ghost_tile"
  _texture = "enemy_boss_ghost_tex"
}

tile {
  _name = "enemy_boss_tile"
  _texture = "enemy_boss_tex"
}

tile {
  _name = "enemy_spider_tile"
  _texture = "enemy_spider_tex"
}

tile {
  _name = "healingplace_tile"
  _texture = "healingplace_tex"
}

entity {
  _type = "Walls"
  _tile = "walls_tile"
  _patterned = true
  _colorBinding = #FFFFFF
}

entity {
  _type = "Player"
  _tile = "player_tile"
  CompPos = 2/2
  CompDir = 0/1
  CompMana = 100
  CompStamina = 100
  CompSpeed = 20
  CompArmor = 0.35/0.35
}

entity {
  _type = "Enemy"
  _tile = "enemy_rat_tile"
  _colorBinding = #FF0000
  CompHealth = 30
  CompArmor = 0/0
  CompDamage = 8/0
  CompVisionRadius = 4
  CompSpeed = 15
}

entity {
  _type = "EnemyGhost"
  _tile = "enemy_ghost_tile"
  _colorBinding = #00FF00
  CompHealth = 50
  CompArmor = 0.5/0
  CompDamage = 2/8
  CompVisionRadius = 4
  CompSpeed = 30
}

entity {
  _type = "Enemy"
  _tile = "enemy_spider_tile"
  _colorBinding = #0000FF
  CompHealth = 60
  CompArmor = 0/0
  CompDamage = 20/0
  CompVisionRadius = 4
  CompSpeed = 33
}

entity {
  _type = "Boss"
  _tile = "enemy_boss_tile"
  _colorBinding = #C3C3C3
  CompHealth = 200
  CompArmor = 0.5/0
  CompVisionRadius = 6
}

entity {
  _type = "EnemyGhost"
  _tile = "enemy_boss_ghost_tile"
  _colorBinding = #CCCCCC
  CompHealth = 250
  CompArmor = 0/0
  CompDamage = 7/3
  CompVisionRadius = 5
  CompSpeed = 100
}

entity {
  _type = "HealingPlace"
  _tile = "healingplace_tile"
  _colorBinding = #FFFF00
  CompDrawTileInfo = 0/0
}





