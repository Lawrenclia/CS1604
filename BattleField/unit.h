#ifndef UNITS_H_INCLUDED
#define UNITS_H_INCLUDED

/* Type of Units */
enum UnitType {SOLDIER, TANK, BEE, FIGHTER, SNACK};

/* Class for units */
class Unit {
public:
    Unit(UnitType u, bool sd, int col, int row, int heart);

    // UnitType information
    std::string getSymbol() const;
    std::string getSymbolPlus() const;
    void resetActionStatus();

    bool hasMoved() const;

    bool hasAttacked() const;

    void setMoved(bool moved);

    void setAttacked(bool attacked);


    // Get the coordinate of the current unit
    int getRow() const;
    int getCol() const;
    UnitType getuType() const;
    // Set the coordinates
    void setCoord(int row, int col);

    // unit performs move action
    void move(int row, int col);

    void setHeart(int newHeart);

    int getAttack() const;

    // Check which side the unit belongs to
    bool getSide() const;

    // Get movement point, which depends on unit type
    int getMovPoints() const;

    int getHeart() const;

private:
    UnitType type;
    bool side;
    int urow, ucol;
    int uheart;
    bool umoved, uattacked;
};

#endif // UNITS_H_INCLUDED
