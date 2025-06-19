#include <cassert>
#include "terrain.h"

// Constructor
Terrain::Terrain()
  : ttype(PLAIN) {}

Terrain::Terrain(TerrainType terrain)
    : ttype(terrain) {}

std::string Terrain::getSymbol() {
    switch (ttype) {
    case PLAIN:
        return "  ";
    case MOUNTAIN:
        return "/\\";
    case OCEAN:
        return "~~";
    case WOODS:
        return "\\/";
    }

  // assert(false);
  return "";
}

std::string Terrain::getType() {
    switch (ttype) {
    case PLAIN:
        return "PLAIN";
    case MOUNTAIN:
        return "MOUNTAIN";
    case OCEAN:
        return "OCEAN";
    case WOODS:
        return "WOODS";
    }
}
