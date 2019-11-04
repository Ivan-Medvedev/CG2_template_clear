map {
  _filename = "debugLevel1.png"
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
  _name = "enemy_boss_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_343.png"
}

texture {
  _name = "enemy_rat_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_224.png"
}

texture {
  _name = "enemy_chest_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_198.png"
}

texture {
  _name = "enemy_boss_ghost_tex"
  _filename = "tileset/Sliced/creatures_24x24/oryx_16bit_fantasy_creatures_342.png"
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
  _name = "enemy_boss_tile"
  _texture = "enemy_boss_tex"
}

tile {
  _name = "enemy_rat_tile"
  _texture = "enemy_rat_tex"
}

tile {
  _name = "enemy_chest_tile"
  _texture = "enemy_chest_tex"
}

tile {
  _name = "enemy_boss_ghost_tile"
  _texture = "enemy_boss_ghost_tex"
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
  CompPos = 20/20
  CompDir = 0/1
  CompMana = 100
  CompStamina = 100
  CompSpeed = 20
  CompArmor = 0/0
}

entity {
  _type = "Enemy"
  _tile = "enemy_rat_tile"
  _colorBinding = #FF0000
  CompHealth = 30
  CompArmor = 0/0
  CompDamage = 8/0
  CompVisionRadius = 5
  CompSpeed = 15
}

entity {
  _type = "Enemy"
  _tile = "enemy_chest_tile"
  _colorBinding = #0000FF
  CompHealth = 100
  CompArmor = 0/0
  CompDamage = 60/0
  CompVisionRadius = 3
  CompSpeed = 30
}

entity {
  _type = "ChangeLevel"
  CompPos = 37/34
}

entity {
  _type = "ChangeLevel"
  CompPos = 37/35
}

entity {
  _type = "ChangeLevel"
  CompPos = 24/21
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
  CompHealth = 50
  CompArmor = 0/0
  CompDamage = 7/3
  CompVisionRadius = 5
  CompSpeed = 80
}

entity {
  _type = "HealingPlace"
  _tile = "healingplace_tile"
  _colorBinding = #FFFF00
  CompDrawTileInfo = 0/0
}


