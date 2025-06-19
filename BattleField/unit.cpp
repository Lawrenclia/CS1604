#include <string>
#include <cassert>
#include "unit.h"
#include <iostream>
using namespace std;

// Constructor
Unit::Unit(UnitType t, bool sd, int row, int col, int heart)
    : type(t), side(sd), urow(row), ucol(col), uheart(heart)
    {}

// Get the symbol of the unit
string Unit::getSymbol() const
{
    switch (type) {
    case SOLDIER:
        return "S" + to_string(uheart);
    case TANK:
        return "T" + to_string(uheart);
    case BEE:
        return "b" + to_string(uheart);
    case FIGHTER:
        return "F" + to_string(uheart);
    case SNACK:
        return "h" + to_string(uheart);
    }
}

// Get the symbol of the unit with +
string Unit::getSymbolPlus() const
{
    if ((!umoved || !uattacked) && !side) {
        return "+" + getSymbol();
    }
    return getSymbol();
}

// Reset action status
void Unit::resetActionStatus()
{
    umoved = false;
    uattacked = false;
}

// Get whether moved
bool Unit::hasMoved() const
{
    return umoved;
}

// Get whether attacked
bool Unit::hasAttacked() const
{
    return uattacked;
}

// Set moved
void Unit::setMoved(bool moved)
{
    umoved = moved;
}

// Set attacked
void Unit::setAttacked(bool attacked)
{
    uattacked = attacked;
}

// Get the coordinate of the current unit
int Unit::getRow() const
{
    return urow;
}

int Unit::getCol() const
{
    return ucol;
}

// Get unit type
UnitType Unit::getuType() const
{
    return type;
}
// Set the coordinates
void Unit::setCoord(int row, int col)
{
    urow = row;
    ucol = col;
}

// unit performs move action
void Unit::move(int row, int col) {
    // setCoord(row, col);
    urow = row;
    ucol = col;
}

// Set unit HP
void Unit::setHeart(int newHeart) {
    uheart = newHeart;
}

// Get attack point
int Unit::getAttack() const
{
    switch (type) {
    case SOLDIER:
        return 1;
    case TANK:
        return 1;
    case BEE:
        return 3;
    case FIGHTER:
        return 2;
    case SNACK:
        return 2;
    }
    return 0;
}

// Get side
bool Unit::getSide() const
{
    return side;
}

// Get movement point
int Unit::getMovPoints() const
{
    switch (type) {
    case SOLDIER:
        return 3;
    case TANK:
        return 2;
    case BEE:
        return 3;
    case FIGHTER:
        return 5;
    case SNACK:
        return 3;
    }
    return 0;
}

int Unit::getHeart() const
{
    return uheart;
}
