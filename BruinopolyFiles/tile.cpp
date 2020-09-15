#include "tile.h"
#include "qlandingwindow.h"
#include "player.h"
#include "mainwindow.h"
#include <string>
#include <QWidget>
#include <QPainter>


Tile::Tile(int _tileNum, Board* _board, MainWindow* _game) : tileNumber(_tileNum), board(_board), game(_game) {}

void Tile::landingEvent(Player* currPlayer) {}

int Tile::getNum() { return tileNumber; }

//Tile::~Tile() { delete board; }

ChanceTile::ChanceTile(int _tileNum, Board* _board, MainWindow* _game) :Tile(_tileNum, _board, _game) {}

void ChanceTile::landingEvent(Player* currPlayer) {
    int cardNum = rand() % board->chanceCards.size();
    board->chanceCards.at(cardNum)->conduct_change(currPlayer);
}


ownableTile::ownableTile(int _tileNum, Board* _board, MainWindow* _game) :
    Tile(_tileNum, _board, _game), owner(nullptr)
{}


void ownableTile::landingEvent(Player* currPlayer) {
    if (!propOwner()) { //property is unowned
        QLandingOptions* propWindow = new QLandingOptions
        (generateView(),
            "Unowned!\n Purchase this property?",
            game,
            "Yes", "No");
        propWindow->setGeometry(750, 300, 450, 350);
        propWindow->setWindowTitle("Notice");
        QObject::connect(propWindow->getLeft(), &QPushButton::clicked,     //connects Yes button to player buy fxn
            currPlayer, &Player::buyBankProp);

    }
    else if (propOwner() == currPlayer) {//player lands on their own tile
        if (dynamic_cast<Property*>(this)) {//if land on a property
            Property* prop = dynamic_cast<Property*>(this);
            if (!prop->getHotel())//if the property can still build house/hotel on
            {
                QLandingOptions* buildHouse = new QLandingOptions(
                    generateView(),
                    "Build a house/hotel on this property?",
                    currPlayer, "Yes", "No");
                huildHouse->setGeometry(750, 300, 450, 350);
                buildHouse->setWindowTitle("Notice");
                QObject::connect(buildHouse->getLeft(), &QPushButton::clicked, currPlayer, &Player::buildHouse);
            }
        }
        else if (dynamic_cast<Railroad*>(this)) {
            //EMIT ANOTHER SLOT IN THE PLAYER CLASS TO CALL THE TRANSPORTATION
             //check if the current owner ownes two railroads { }
            Railroad* current = dynamic_cast<Railroad*>(this);
            if (current->checkOwnerRailroads(currPlayer) == 2) {
                QLandingOptions* RailTransport = new QLandingOptions(
                    generateView(),
                    "So is that a yes or no? Charge is $5.",
                    currPlayer, "Yes", "No");
                RailTransport->setGeometry(750, 300, 450, 350);
                RailTransport->setWindowTitle("Notice");
                QObject::connect(RailTransport->getLeft(), &QPushButton::clicked, currPlayer, &Player::transferPlayer_Railroad);
            }
        }
    }
    else
    { //someone else owns the property so pay them rent
        std::string name = owner->return_name().toLocal8Bit().constData();
        std::string popupMessage(" This property is owned by " + name + "\nRent due:" + std::to_string(currentRent()) + "!");
        //generate message that asks for proper rent.
        NoOptionWindow(game, QString::fromStdString(popupMessage));
        this->owner->take(currPlayer, this->currentRent()); //owner of tile takes appropriate rent from person who landed on it.
    }
}

Player* ownableTile::propOwner() const { return owner; }
void ownableTile::transfer(Player* newOwner) { owner = newOwner; }
