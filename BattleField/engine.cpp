#include <iomanip>
#include "engine.h"
#include "terrain.h"
#include "unit.h"
#include "actions.h"
#include "algorithms.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Forward declaration of auxiliary functions
void printHLine(ostream& os, int n);
string getDpSymbol(dp_mode dp);
Grid<int> getFieldCosts(const Field& field, Unit* u);
bool performMove(ostream& os, istream& is, Field& field, Unit* u);
bool performAttack(ostream& os, istream& is, Field& field, Unit* u);
bool performAction(Field& field, istream& is, ostream& os, Unit* u, Action act);
void getCrashed(int tRow, int tCol, int newRow, int newCol, Field& field);
int checkWin(Field& field);

// load terrains and units into field
void loadMap(std::istream& is, Field& field) {
  //Fill in your code here
    int NT, NU;
    is >> NT >> NU;
    for (int i = 0; i < NT; ++i) {
        int row, col;
        string name;
        is >> row >> col >>name;
        TerrainType terrain;
        if (name == "M") {
            terrain = MOUNTAIN;
        } else if (name == "O") {
            terrain = OCEAN;
        } else if (name == "W") {
            terrain = WOODS;
        }
        field.setTerrain(row, col, terrain);
    }

    for (int i = 0; i < NU; ++i) {
        int row, col;
        string name;
        is >> row >> col >> name;
        UnitType unitType;
        int heart;
        if (name == "S") {
            unitType = UnitType(SOLDIER);
            heart = 2;
            field.setUnit(row, col, new Unit(unitType, false, row, col, heart));
        } else if (name == "T") {
            unitType = UnitType(TANK);
            heart = 3;
            field.setUnit(row, col, new Unit(unitType, false, row, col, heart));
        } else if (name == "B") {
            unitType = UnitType(BEE);
            heart = 2;
            field.setUnit(row, col, new Unit(unitType, true, row, col, heart));
        } else if (name == "F") {
            unitType = UnitType(FIGHTER);
            heart = 2;
            field.setUnit(row, col, new Unit(unitType, false, row, col, heart));
        } else if (name == "H") {
            unitType = UnitType(SNACK);
            heart = 1;
            field.setUnit(row, col, new Unit(unitType, true, row, col, heart));
        }
    }
}


// Main loop for playing the game
void play(Field& field, istream& is, ostream& os)
{
    bool haveChecked = false;
    while (is)
    {
        if (haveChecked) {
            break;
        }
        //print field
        displayField(os, field);
        //print field END

        //check
        if(checkWin(field) == 1) {
            os << "Won" << endl;
            break;
        }
        if(checkWin(field) == 2) {
            os << "Failed" << endl;
            break;
        }
        //check END

        //PLAYER
        for (int i = 0; i < field.getHeight(); ++i) {
            for (int j = 0; j < field.getWidth(); ++j) {
                Unit* u1 = field.getUnit(i, j);
                if (u1 != nullptr && !u1->getSide()) {
                    u1->resetActionStatus();
                }
            }
        }

        while (true) {
            //check whether actable
            bool hasActableUnit = false;
            for (int i = 0; i < field.getHeight(); ++i) {
                for (int j = 0; j < field.getWidth(); ++j) {
                    Unit* u2 = field.getUnit(i, j);
                    if (u2 != nullptr && !u2->getSide() && (!u2->hasMoved() || !u2->hasAttacked())) {
                        hasActableUnit = true;
                        break;
                    }
                }
                if (hasActableUnit) break;
            }
            if (!hasActableUnit) {
                os << "No more actable units." << endl;
                break;
            }

            displayField(os, field, Grid<bool>(), DP_DEFAULT, true);

            os << "End this turn (y,n)? " << endl;
            char choice = 'n';
            is >> choice;
            if (choice == 'y') {
                break;
            }

            // select unit
            os << "Please select a unit:" << endl;
            int R, C;
            // select action
            while (true) {
                is >> R >> C;
                if (R < 0 || R >= field.getHeight() || C < 0 || C >= field.getWidth()) {
                    os << "(" << R << ", " << C << ") is out of bound" << endl;
                } else {
                    Unit* u = field.getUnit(R, C);
                    if (u == nullptr){
                        os << "No unit at (" << R << ", " << C << ")!" << endl;
                    } else if (u->getSide()) {
                        os << "Unit at (" << R << ", " << C << ") is an enemy!" << endl;
                    } else if (u->hasMoved() && u->hasAttacked()) {
                        os << "Unit at (" << R << ", " << C << ") is not actable!" << endl;
                    } else {
                        break;
                    }
                }
                os << "Please select a unit:" << endl;
            }

            Unit* u = field.getUnit(R, C);
            //select action
            vector<Action> actions;
            if (!u->hasMoved()) {
                actions.push_back(MOVE);
            }
            if (!u->hasAttacked()) {
                actions.push_back(ATTACK);
            }
            actions.push_back(SKIP);

            for (size_t i = 0; i < actions.size(); ++i) {
                switch (actions[i]) {
                case MOVE:
                    os << i + 1 << ".Move ";
                    break;
                case ATTACK:
                    os << i + 1 << ".Attack ";
                    break;
                case SKIP:
                    os << i + 1 << ".Skip ";
                    break;
                }
            }
            os << endl;

            os << "Select your action:" << endl;
            size_t actionChoice;
            is >> actionChoice;
            while (actionChoice < 1 || actionChoice > actions.size()) {
                os << "Invalid action!" << endl;
                os << "Select your action:" << endl;
                is >> actionChoice;
            }

            // perform action
            Action act = actions[actionChoice - 1];
            if (act == MOVE) {
                u->setMoved(true);
            } else if (act == ATTACK) {
                u->setAttacked(true);
            }
            performAction(field, is, os, u, act);

            //delete certain unit
            for (int i = 0; i < field.getHeight(); i++) {
                for (int j = 0; j < field.getWidth(); j++) {
                    if (field.getUnit(i, j) != nullptr) {
                        int heart = field.getUnit(i, j)->getHeart();
                        if (heart <= 0) {
                            field.setUnit(i, j, nullptr);
                            delete field.getUnit(i, j);
                        }
                    }
                }
            }

        }
        //PLAYER END

        //ENEMY
        //sequence enemys
        vector<Unit*> enemys;
        for (int i = 0; i < field.getHeight(); i++) {
            for (int j = 0; j < field.getWidth(); j++) {
                Unit* u = field.getUnit(i, j);
                if (u != nullptr && u->getSide()) {
                    enemys.push_back(u);
                }
            }
        }

        for (size_t i = 0; i < enemys.size(); ++i) {
            for (size_t j = 0; j < enemys.size() - i - 1; ++j) {
                Unit* a = enemys[j];
                Unit* b = enemys[j + 1];

                if (a->getRow() > b->getRow()) {
                    swap(enemys[j], enemys[j + 1]);
                } else if (a->getRow() == b->getRow() && a->getCol() > b->getCol()) {
                    swap(enemys[j], enemys[j + 1]);
                }
            }
        }

        //for each enemy
        for (Unit* enemy : enemys) {
            //move
            bool hasFriendly = false;
            for (int i = 0; i < field.getHeight(); ++i) {
                for (int j = 0; j < field.getWidth(); ++j) {
                    Unit* u = field.getUnit(i, j);
                    if (u != nullptr && !u->getSide()) {
                        hasFriendly = true;
                        break;
                    }
                }
                if (hasFriendly) break;
            }
            if (!hasFriendly) {
                continue;
            }

            //get the closest way
            Grid<bool> grd = searchReachable(getFieldCosts(field, enemy), enemy->getRow(), enemy->getCol(), enemy->getMovPoints());
            int tRow = -1;
            int tCol = -1;
            int minDistance = 100;
            for (int i = 0; i < field.getHeight(); i++) {
                for (int j = 0; j <field.getWidth(); j++) {
                    if (grd[i][j]) {
                        int closeDistance = 100;
                        for (int k = 0; k < field.getHeight(); k++) {
                            for (int l = 0; l < field.getWidth(); l++) {
                                Unit* friendly = field.getUnit(k, l);
                                if (friendly != nullptr && !friendly->getSide()) {
                                    int distance = std::abs(i - k) + std::abs(j - l);
                                    if (distance < closeDistance) {
                                        closeDistance = distance;
                                    }
                                }
                            }
                        }
                        if (closeDistance < minDistance) {
                            minDistance = closeDistance;
                            tRow = i;
                            tCol = j;
                        } else if (closeDistance == minDistance) {
                            if (tRow == -1 || i < tRow || (i == tRow && j < tCol)) {
                                tRow = i;
                                tCol = j;
                            }
                        }
                    }

                }
            }
            if (tRow != -1 && tCol != -1) {
                int cRow = enemy->getRow();
                int cCol = enemy->getCol();
                if (field.moveUnit(cRow, cCol, tRow, tCol)) {
                    enemy->move(tRow, tCol);
                }
            }

            //attack
            int cRow = enemy->getRow();
            int cCol = enemy->getCol();
            int tRow1 = cRow;
            int tCol1 = cCol;
            int newRow = tRow1;
            int newCol = tCol1;
            bool findTarget = false;
            if (cRow > 0 && field.getUnit(cRow - 1, cCol) != nullptr && !(field.getUnit(cRow - 1, cCol)->getSide())) {
                tRow1 = cRow - 1;
                newRow = tRow1 - 1;
                findTarget = true;
            } else if (cCol > 0 && field.getUnit(cRow, cCol - 1) != nullptr && !(field.getUnit(cRow, cCol - 1)->getSide())) {
                tCol1 = cCol - 1;
                newCol = tCol1 - 1;
                findTarget = true;
            } else if (cCol < field.getWidth() - 1 && field.getUnit(cRow, cCol + 1) != nullptr && !(field.getUnit(cRow, cCol + 1)->getSide())) {
                tCol1 = cCol + 1;
                newCol = tCol1 + 1;
                findTarget = true;
            } else if (cRow < field.getHeight() - 1 && field.getUnit(cRow + 1, cCol) != nullptr && !(field.getUnit(cRow + 1, cCol)->getSide())) {
                tRow1 = cRow + 1;
                newRow = tRow1 + 1;
                findTarget = true;
            }

            if (findTarget) {
                Unit* target = field.getUnit(tRow1, tCol1);
                int attackHeart = enemy->getAttack();
                int newHeart = target->getHeart() - attackHeart;
                target->setHeart(newHeart);
                //For SNACK
                if (enemy->getuType() == SNACK) {
                    getCrashed(tRow1, tCol1, newRow, newCol, field);
                }

                //delect certain unit
                for (int i = 0; i < field.getHeight(); i++) {
                    for (int j = 0; j < field.getWidth(); j++) {
                        if (field.getUnit(i, j) != nullptr) {
                            int heart = field.getUnit(i, j)->getHeart();
                            if (heart <= 0) {
                                field.setUnit(i, j, nullptr);
                                delete field.getUnit(i, j);
                            }
                        }
                    }
                }

            }
        }
        //ENEMY END

        //WOODS
        for (int i = 0; i < field.getHeight(); i++) {
            for (int j = 0; j < field.getWidth(); j++) {
                if (field.getTerrain(i, j).getType() == "WOODS") {
                    for (int k = 0; k < field.getHeight(); k++) {
                        for (int l = 0; l < field.getWidth(); l++) {
                            if (abs(i - k) <= 2 && abs(j - l) <= 2 && field.getUnit(k, l) != nullptr) {
                                int cHeart = field.getUnit(k, l)->getHeart();
                                cHeart++;
                                field.getUnit(k, l)->setHeart(cHeart);
                            }
                        }
                    }
                }
            }
        }
        //WOODS END
    }
}

//check win or loss
int checkWin(Field& field) {
    bool hasEnemy = false;
    bool hasFriendly = false;
    for (int i = 0; i < field.getHeight(); ++i) {
        for (int j = 0; j < field.getWidth(); ++j) {
            Unit* u = field.getUnit(i, j);
            if (u != nullptr) {
                if (u->getSide()) {
                    hasEnemy = true;
                } else {
                    hasFriendly = true;
                }
            }
        }
    }
    if (!hasEnemy) {
        return 1;
        //won
    }
    if (!hasFriendly) {
        return 2;
        //failed
    }
    return 3;
    //nothing happened
}

// Display the field on the out stream os
void displayField(ostream& os, const Field& field, const Grid<bool>& grd, dp_mode dp, bool addPlus)
{
    int height = field.getHeight();
    int width = field.getWidth();
    string dp_symbol = getDpSymbol(dp);

    os << endl;
    // Print the x coordinates
    os << "  ";
    for (int i = 0; i < width; i++)
        os << setw(3) << i << " ";
    os << endl;

    printHLine(os, width);
    for (int i = 0; i < height; i++) {
        os << setw(2) << i;
        for (int j = 0; j < width; j++) {
            os << '|';
            const Unit* u = field.getUnit(i,j);
            Terrain t = field.getTerrain(i, j);
            string sym;
            int width = 3;
            if (grd.inBounds(i,j) && grd[i][j]) {
                os << setw(1) << dp_symbol;
                width -= 1;
            }

            if (u != nullptr) {
                if (addPlus) {
                    sym += u->getSymbolPlus();
                } else {
                    sym += u->getSymbol();
                }
            } else sym += t.getSymbol();
            os << setw(width) << sym;
        }
        os << '|' << endl;
        printHLine(os, width);
    }
    os << endl;
}

// Print the horizontal line
void printHLine(ostream& os, int n)
{
    os << "  ";
    for (int i = 0; i < n; i++)
        os << "+---";
    os << "+" << endl;
}

// symbol used in displayField
string getDpSymbol(dp_mode dp) {
    if (dp == DP_MOVE) {
        return ".";
    } else if (dp == DP_ATTACK) {
        return "*";
    }
    return " ";
}

//select action
bool performAction(Field& field, istream& is, ostream& os, Unit* u, Action act) {
    switch(act) {
    case MOVE:
        return performMove(os, is, field, u);

    case ATTACK:
        return performAttack(os, is, field, u);

    case SKIP:
        return true;

    default:
        os << "(Action not implemented yet)" << endl;
        return false;
    }
}

// Perform the move action
bool performMove(ostream& os, istream& is, Field& field, Unit* u)
{
    // Display the reachable points
    Grid<bool> grd =
        searchReachable(getFieldCosts(field, u), u->getRow(), u->getCol(), u->getMovPoints());

    displayField(os, field, grd, DP_MOVE);

    os << "Please enter your destination:" << endl;
    int tRow ,tCol;
    is >> tRow >> tCol;
    while (tRow < 0 ||tRow >= field.getHeight() || tCol < 0 || tCol >= field.getWidth() || (!grd[tRow][tCol]) ) {
        os << "Not a valid destination" << endl;
        os << "Please enter your destination:" << endl;
        is >> tRow >> tCol;
    }
    int cRow = u->getRow();
    int cCol = u->getCol();
    if (field.moveUnit(cRow, cCol, tRow, tCol)) {
        u->move(tRow, tCol);
    }
    return true;
}



//perform attack
bool performAttack(ostream& os, istream& is, Field& field, Unit* u)
{
    //get attack field
    int cRow = u->getRow();
    int cCol = u->getCol();
    UnitType type = u->getuType();
    Grid<bool> attackField(8, 8, false);

    switch (type) {
    case SOLDIER:
        if (cRow > 0) attackField[cRow - 1][cCol] = true;
        if (cCol > 0) attackField[cRow][cCol - 1] = true;
        if (cRow < 7) attackField[cRow + 1][cCol] = true;
        if (cCol < 7) attackField[cRow][cCol + 1] = true;
        break;
    case TANK:
        for (int r = cRow - 1; r >= 0; --r) {
            Terrain t = field.getTerrain(r, cCol);
            Unit* target = field.getUnit(r, cCol);
            if (t.getType() != "PLAIN" || target != nullptr) {
                attackField[r][cCol] = true;
                break;
            }
            attackField[r][cCol] = true;
        }
        for (int r = cRow + 1; r < field.getHeight(); ++r) {
            Terrain t = field.getTerrain(r, cCol);
            Unit* target = field.getUnit(r, cCol);
            if (t.getType() != "PLAIN" || target != nullptr) {
                attackField[r][cCol] = true;
                break;
            }
            attackField[r][cCol] = true;
        }
        for (int c = cCol - 1; c >= 0; --c) {
            Terrain t = field.getTerrain(cRow, c);
            Unit* target = field.getUnit(cRow, c);
            if (t.getType() != "PLAIN" || target != nullptr) {
                attackField[cRow][c] = true;
                break;
            }
            attackField[cRow][c] = true;
        }
        for (int c = cCol + 1; c < field.getWidth(); ++c) {
            Terrain t = field.getTerrain(cRow, c);
            Unit* target = field.getUnit(cRow, c);
            if (t.getType() != "PLAIN" || target != nullptr) {
                attackField[cRow][c] = true;
                break;
            }
            attackField[cRow][c] = true;
        }
        break;
    case FIGHTER:
        if (cRow > 1) attackField[cRow - 2][cCol] = true;
        if (cCol > 1) attackField[cRow][cCol - 2] = true;
        if (cRow < 6) attackField[cRow + 2][cCol] = true;
        if (cCol < 6) attackField[cRow][cCol + 2] = true;
    }

    displayField(os, field, attackField, DP_ATTACK);

    //select target
    os << "Please enter your target:" << endl;
    int tRow ,tCol;
    is >> tRow >> tCol;
    while (tRow < 0 ||tRow >= field.getHeight() || tCol < 0 || tCol >= field.getWidth() || (!attackField[tRow][tCol]) ) {
        os << "Not a valid target" << endl;
        os << "Please enter your target:" << endl;
        is >> tRow >> tCol;
    }

    Unit* target = field.getUnit(tRow, tCol);

    if (target != nullptr) {
        //For TANK and FIGHTER
        if (type == TANK) {
            int newRow = tRow;
            int newCol = tCol;
            if (tRow - cRow > 0) {
                newRow++;
            } else if (tRow - cRow < 0) {
                newRow--;
            } else if (tCol - cCol > 0) {
                newCol++;
            } else if (tCol - cCol < 0) {
                newCol--;
            }
            getCrashed(tRow, tCol, newRow, newCol, field);
        } else if (type == FIGHTER) {
            getCrashed(tRow + 1, tCol, tRow + 2, tCol, field);
            getCrashed(tRow - 1, tCol, tRow - 2, tCol, field);
            getCrashed(tRow, tCol + 1, tRow, tCol + 2, field);
            getCrashed(tRow, tCol - 1, tRow, tCol - 2, field);
        }

        int attackHeart = u->getAttack();
        int newHeart = target->getHeart() - attackHeart;
        target->setHeart(newHeart);

    } else {
        if (type == TANK && field.getTerrain(tRow, tCol).getType() == "MOUNTAIN") {
            TerrainType plain = PLAIN;
            field.setTerrain(tRow, tCol, plain);
        } else if (type == FIGHTER) {
            getCrashed(tRow + 1, tCol, tRow + 2, tCol, field);
            getCrashed(tRow - 1, tCol, tRow - 2, tCol, field);
            getCrashed(tRow, tCol + 1, tRow, tCol + 2, field);
            getCrashed(tRow, tCol - 1, tRow, tCol - 2, field);
        }
    }
    return true;
}


//do when crashing happens
void getCrashed(int tRow, int tCol, int newRow, int newCol, Field& field) {
    if (newRow >= 0 && newRow < field.getHeight() && newCol >= 0 && newCol < field.getWidth()) {
        Unit* target = field.getUnit(tRow, tCol);
        if (target != nullptr) {
            Unit* getCrash = field.getUnit(newRow, newCol);

            if (tRow >= 0 && tRow < field.getHeight() && tCol >= 0 && tCol < field.getWidth() && getCrash != nullptr) {
                int crashHeart1 = target->getHeart() - 1;
                int crashHeart2 = getCrash->getHeart() - 1;
                target->setHeart(crashHeart1);
                getCrash->setHeart(crashHeart2);
            } else if (tRow >= 0 && tRow < field.getHeight() && tCol >= 0 && tCol < field.getWidth() && getCrash == nullptr) {
                string ter = field.getTerrain(newRow, newCol).getType();
                if (ter == "PLAIN") {
                    if (field.moveUnit(tRow, tCol, newRow, newCol)) {
                        target->move(newRow, newCol);
                    }
                } else if (ter == "MOUNTAIN") {
                    TerrainType plain = PLAIN;
                    field.setTerrain(newRow, newCol, plain);
                    int crashHeart = target->getHeart() - 1;
                    target->setHeart(crashHeart);
                } else if (ter == "OCEAN") {
                    if (target->getuType() == SOLDIER || target->getuType() == TANK || target->getuType() == SNACK) {
                        target->setHeart(0);
                    } else {
                        if (field.moveUnit(tRow, tCol, newRow, newCol)) {
                            target->move(newRow, newCol);
                        }
                    }
                } else if (ter == "WOODS") {
                    if (target->getuType() == SOLDIER || target->getuType() == TANK || target->getuType() == SNACK) {
                        if (field.moveUnit(tRow, tCol, newRow, newCol)) {
                            target->move(newRow, newCol);
                        }
                    }
                }
            }

        }
    }
}



// Convert field to costs
// The cost should depend on the terrain type and unit type
Grid<int> getFieldCosts(const Field& field, Unit* u)
{
    int h = field.getHeight();
    int w = field.getWidth();
    Grid<int> costs(h, w);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            costs[i][j] = 1;
            Terrain t = field.getTerrain(i, j);
            Unit* unit = field.getUnit(i, j);

            if (unit != nullptr && unit != u) {
                costs[i][j] = 100;
            } else if (t.getType() == "MOUNTAIN") {
                costs[i][j] = 100;
            } else if (t.getType() == "OCEAN" && !(u->getuType() == FIGHTER || u->getuType() == BEE)) {
                costs[i][j] = 100;
            } else if (t.getType() == "WOODS" && (u->getuType() == FIGHTER || u->getuType() == BEE)) {
                costs[i][j] = 100;
            }
        }
    }
    int unitRow = u->getRow();
    int unitCol = u->getCol();
    costs[unitRow][unitCol] = 0;

    return costs;
}
