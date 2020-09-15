#ifndef PROPERTY
#define PROPERTY

#include "tile.h"

#include <string>
#include <QWidget>
#include <QPainter>

class QVBoxLayout;
class Bank;
class Player;

/*
represents normal property tiles derived from ownableTile
*/
class Property : public ownableTile {
public:

    friend Player;
    class View;

    /*
    for use for building a property from a line of "tileBuilder.txt"
    @param formattedLine properly formatted line from tileBuilder.txt
    */
    Property(const std::string& formattedLine, Board* _board, MainWindow* game);
    Property(const Property& oth) = default;

    /*
    generates a QWidget with the approperiate property tile painted onto it
    @return pointer to viewing window to allow for manipulation.
    */
    QWidget* generateView() const override;

    /*
    adds a house/hotel as appropriate if there are any remaining in the bank
    and deducts the appropriate amount from their moneyRemaining.
    @param bank of this game.
    @return true if house is successfuly built.
    */
    int buildHouse(Bank* bank);

    /*
    returns rent amount taking into account current number of houses
    @return 0 if unowned, otherwise the appropriate rent.
    */
    int currentRent() const override;

    /*
    implements ownableTile::getCost() const
    @return cost of property
    */
    int getCost() const override { return cost; }

    /*
    @return name of property
    */

    std::string getName() const override { return name; }

    /*
    @return hotel number of property
    */
    int getHotel() { return hotelCount; }

    /*
    @return house number of property
    */
    int getHouse() { return houseCount; }


private:
    std::string color;
    std::string name;
    int houseCount;
    int hotelCount = 0;
    int cost;
    int houseCost;
    int rents[6];


};

/*
A minimal class to allow Property to be displayed. Upon being created with Property::generateView(),
the View instance will create a pixmap from the appropriate image for the calling property.
*/
class Property::View : public QWidget {
    Q_OBJECT
public:
    View() = delete;
    View(const Property& prop);
    std::string getName() const { return name; }
    void paintEvent(QPaintEvent*) override;
private:
    QPixmap image;
    QVBoxLayout* mainLayout;
    std::string name;
};


/*
 Railroad properties from regular game.  We will have 2.
*/
class Railroad : public ownableTile {
public:
    Railroad(int _tileNum, std::string name, Board* _board, MainWindow* game);

    /*
    checks how many Railroads owner has to calculate rent.
    @param player checks # of railroads they own
    @return int number of railroads they own.
    */
    int checkOwnerRailroads(const Player* player) const;

    /*
    @return rent that must be paid to owner.
    */
    int currentRent() const override;

    /*implements ownableTile::getCost() const
    @return cost of railroad
    */
    int getCost() const override { return cost; }

    //@return name of railroad
    std::string getName() const { return name; }

    //@return popup window of railroad
    QWidget* generateView() const override;
    class View;
protected:
    int cost;
    std::string name;
    int rents[2] = { 100,300 }; // each railroad has same rent values;
};




class Railroad::View : public QWidget {
    Q_OBJECT
public:
    View(const Railroad& rr);
    void paintEvent(QPaintEvent* event) override;
private:
    QPixmap image;
    QVBoxLayout* mainLayout;
};


#endif
