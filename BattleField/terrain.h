#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <string>

// TerrainType
enum TerrainType {PLAIN, MOUNTAIN, OCEAN, WOODS};

class Terrain {
public:
    Terrain();
    Terrain(TerrainType terrain);

    std::string getSymbol();
    std::string getType();

private:
    TerrainType ttype;
};

#endif // TERRAIN_H_INCLUDED
