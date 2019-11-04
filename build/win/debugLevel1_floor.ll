map {
  _filename = "debugLevel1_floor.png"
}

texture {
  _name = "floor1_tex"
  _filename = "tileset/Sliced/world_24x24/oryx_16bit_fantasy_world_917.png"
}

texture {
  _name = "floor2"
  _filename = "tileset/Sliced/world_24x24/oryx_16bit_fantasy_world_918.png"
}

texture {
  _name = "floor3"
  _filename = "tileset/Sliced/world_24x24/oryx_16bit_fantasy_world_120.png"
}

tile {
  _name = "floor1"
  _texture = "floor1_tex"
}

tile {
  _name = "floor2"
  _texture = "floor2"
}

tile {
  _name = "floor3"
  _texture = "floor3"
}

entity {
  _type = "Floor"
  _tile = "floor1"
  _patterned = true
  _colorBinding = #000000
}

entity {
  _type = "Floor"
  _tile = "floor2"
  _patterned = true
  _colorBinding = #202020
}

entity {
  _type = "Floor"
  _tile = "floor3"
  _patterned = true
  _colorBinding = #404040
}

