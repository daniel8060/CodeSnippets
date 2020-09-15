#ifndef TILE_H
#define TILE_H
#include <QDebug>
#include <string>
#include <QWidget>
#include "board.h"
#include "chancecard.h"

class MainWindow;
class Player;

//base class for tile system
class Tile {

public:
    friend class Board;

    Tile(int _tileNum, Board* _board, MainWindow* _game);

    /*
    Call to implement desired behavior of a given tile.
    (e.g. a popup window for landing on a property w/ the option to buy.)
    @currplayer point to the player land on the tile
    */
    virtual void landingEvent(Player* currPlayer); //TODO:revert change Han made and implement a nullTile so this goes back to being abstract

    /*
    return tile idx
    */
    int getNum();

    virtual ~Tile();

protected:
    int tileNumber;
    std::string name;
    Board* board;
    MainWindow* game;
};


//derived from tile, in charge of chance tile
class ChanceTile : public Tile {
public:
    ChanceTile(int _tileNum, Board* _board, MainWindow* _game);
    void landingEvent(Player* currPlayer);
};


//derived from tile, in charge of buyable tile
class ownableTile : public Tile {

public:
    ownableTile(int _tileNum, Board* _board, MainWindow* _game);
    virtual void landingEvent(Player* currPlayer) override;

    /*
    returns tile's rent to be paid.  Calculation varies on subtype of ownableTile
    @return rent due for this tile.
    */
    virtual int currentRent() const = 0;

    virtual QWidget* generateView() const { return nullptr; }

    /*
    @return owner of this tile
    */
    Player* propOwner() const;

    /*
    @return cost of this tile
    */
    virtual int getCost() const = 0;

    /*
    Changes owner of this tile to specified player.
    @param newOwner will become owner of this tile
    */
    void transfer(Player* newOwner);

    virtual ~ownableTile() override = default;

    virtual std::string getName() const = 0;

protected:
    Player* owner = nullptr;

};

class nullTile : public Tile {
public: 
    nullTile (int _tileNum , Board* _board, MainWindow* _game): Tile(_tileNum, _board, _game) {}

    //tile will do nothing when we land on it. 
    void landingEveng(Player&) override {}

    virtual ~eventTile() override = default; 
};


#endif
