#ifndef PLAYER_H
#define PLAYER_H

#include <QLabel>
#include <QVector>
#include <QString>
#include <QObject>
#include "bank.h"
#include "tile.h"
#include "property.h"


class Movement;

class Player : public QWidget {
    friend class Movement;
    friend class Bank;
    friend class Railroad;
    friend class MainWindow;

    Q_OBJECT

public:


    Player(QWidget* parent = nullptr,
        Bank* b = nullptr,
        Board* board = nullptr,
        const QString& charactor = "panda",
        const QString& name = "",
        int money = 0, int order = 0,
        const QString& path = ":/fig/gb_panda.png");
    ~Player();

    /*
        pays another player, if possible
        @param payee player being paid
        @param amt to be paid
        */
    void pay(Player* payee, int amt);

    /*
        forcibly takes money from another player.  Can reduce their money to zero !!!
        @param target to be taken from
        @param amt to be taken
        */
    void take(Player* target, int amt);

    /*
    attempts to buy property that player is currently on from bank.
    @return false if not enough money to purchase property.
    */
    bool buyPropertyBank();

    /*
    @return the tile the player is currently on
    */
    Tile* getTile() const;

    /*
        check player's money. doesn't allow modification.
        @return gets playerMoney
     */
    int money() const;

    /*
     @return current board position of player
     */
    int getPos() const;

    //return current properties number owned by player
    int getProp() const;
    //return current house number owned by player
    int getHouse() const;
    //return current hotel number owned by player
    int getHotel() const;
    //return player's name
    QString getname()const;
    //return player's charactor
    QString getcharactor() const;
    //return a ptr pointing to player's movement class
    Movement* getmovement() const;
    bool isDefeated = 0;

    //@return the value of disable variable. >0 means the player is in jail with (4-return) turns left. otherwise not in jail
    int isDisable();

    //add disable by 1
    void changeDisable();
    Bank* bank;

    //clearup player's propertylist
    void setPlayerPropertiesDefault() {
        for (auto properties : playerProperties) {
            properties->transfer(nullptr);
        }
    }



public slots:
    void buyBankProp();//buy the ownable prop
    void payRent();
    void buildHouse();
    void transferPlayer_Railroad();
public:
    QString return_name();

signals:
    void buyPropFail();

private:
    Board* board;
    QString charactor;
    QString name;
    Movement* movement;//
    int property = 0;
    int house = 0;
    int hotel = 0;
    int disable = 0;
    int playerMoney;
    std::vector<ownableTile*> playerProperties; //properties owned by player
};


#endif