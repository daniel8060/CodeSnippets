#include "movement.h"
#include "qlandingwindow.h"
#include "mainwindow.h"
#include <QDebug>

Player::Player(QWidget* parent, Bank* b, Board* b2, const QString& ch, const QString& name, int money, int order, const QString& path)
    : QWidget(parent), bank(b), board(b2), charactor(ch), name(name), playerMoney(money)
{
    movement = new Movement(this, this, order, path);
}

//player should not delete their properties or else they will be deleted from the board.
//all properties will be deleted in board destructor.
//
Player::~Player() {
    delete movement;
    //    for(size_t i=0;i<playerProperties.size();i++)
    //        delete playerProperties[i];
}

int Player::money() const
{
    return playerMoney;
}

int Player::getPos() const
{
    return movement->getpos();
}

bool pay(Player* payee, int amt);

bool take(Player* target, int amt);

int Player::getProp() const { return property; }

int Player::getHouse() const { return house; }

int Player::getHotel() const { return hotel; }

Tile* Player::getTile() const { return board->getTile(this->getPos()); }

int Player::isDisable() { return disable; }

void Player::changeDisable() {
    if (disable == 3) {// if in jail 3 turns, stop being in jail
        disable = 0;
    }
    else {//if less than 3 turns in jail, add one turn
        disable++;
    }
}

QString Player::getname() const { return name; }

QString Player::getcharactor() const { return charactor; }

Movement* Player::getmovement() const { return movement; }

void Player::pay(Player* payee, int amt) {
    if (!payee->isDefeated) { //target player is valid
        if (playerMoney <= amt) {//have enough money
            payee->playerMoney += amt;
            playerMoney -= amt;
        }
        else {
            payee->playerMoney += playerMoney;
            playerMoney = 0; //give payee all of current money
        }
    }
}

void Player::take(Player* target, int amt) {
    if (!target->isDefeated) {//valid target
        if (target->playerMoney >= amt) {//target has enough money
            target->playerMoney -= amt; //adjust target money
            playerMoney += amt; //adjust this's money
        }
        else { //target doesn't have enough money.
            playerMoney += target->playerMoney; //take money they have left
            target->playerMoney = 0;
        }
    }
}



bool Player::buyPropertyBank() {
    ownableTile* currProp = dynamic_cast<ownableTile*>(getTile());//cast curr tile that player is on to property type
    if (playerMoney >= currProp->getCost() && currProp->propOwner() == nullptr) {//if player has at least enough money to buy and property unowned
        bank->take(*this, currProp->getCost()); //charge player for property
        property += 1;
        playerProperties.push_back(currProp); //add to back of player's properties
        currProp->transfer(this);
        board->w->infoupdate();
        return true;
    }
    return false;//player doesn't have enough money to buy
}



void Player::buyBankProp() {
    if (buyPropertyBank()) {//able to buy property
        NoOptionWindow(this, "Property purchased!");
    }
    else {
        NoOptionWindow(this, "Unable to purchase property (:/)");
    }
}

void Player::payRent() {
    ownableTile* prop = dynamic_cast<ownableTile*> (getTile()); //prop is the tile the player is on.
    prop->propOwner()->take(this, prop->currentRent()); //owner of the property that the curr player is on takes appropriate amount of money from curr player .
    board->w->infoupdate();
}
void Player::transferPlayer_Railroad() {
    //first get the tail pos, then transfer
    int pos = 2;
    if (this->getmovement()->getpos() == 2) {
        pos = 10;
    }
    else { pos = 2; }
    this->take(this, 5);
    this->getmovement()->instant_trans(pos);
}
void Player::buildHouse() {
    {
        if (dynamic_cast<Property*>(getTile()))//if land on a property
        {//if we're on a property
            Property* currProp = dynamic_cast<Property*>(getTile());//cast currTile to property
            int build_result = currProp->buildHouse(this->bank);
            if (build_result == 1)// build house successfully
            {
                house++;
                board->w->infoupdate();
            }
            else if (build_result == 2)//build hotel successfully
            {
                hotel++;
                house -= 4;
                board->w->infoupdate();
            }
        }
        else {
            throw std::logic_error("buildHouse on non property tile");
        }
    }
}

QString Player::return_name() {
    return name;
}