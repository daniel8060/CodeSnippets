#include "property.h"
#include "player.h"
#include "bank.h"
#include "qlandingwindow.h"

#include <QLayout>
#include <QPainter>
#include <QRect>
#include <QDebug>
#include <sstream>

class MainWindow;

using std::string; using std::stringstream;

Property::Property(const string& formattedLine, Board* _board, MainWindow* _game) : ownableTile(std::stoi(formattedLine.substr(formattedLine.find('\t'), 2)), _board, _game), houseCount(0) {
    stringstream buffer(formattedLine);
    string temp = "";
    stringstream vals;
    getline(buffer, temp, '\t'); getline(buffer, temp, '\t'); //buffer eats "prop" then "1"

    getline(buffer, temp, '\t');
    color = temp;
    getline(buffer, temp, '\t');
    name = temp;
    getline(buffer, temp, '\t');
    cost = std::stoi(temp);
    getline(buffer, temp, '\t');
    houseCost = std::stoi(temp);
    getline(buffer, temp, '\t');
    rents[0] = std::stoi(temp);
    getline(buffer, temp, '\t');
    rents[1] = std::stoi(temp);
    getline(buffer, temp, '\t');
    rents[2] = std::stoi(temp);
    getline(buffer, temp, '\t');
    rents[3] = std::stoi(temp);
    getline(buffer, temp, '\t');
    rents[4] = std::stoi(temp);
    getline(buffer, temp, '\t');
    rents[5] = std::stoi(temp);

}



QWidget* Property::generateView() const {
    return (new View(*this));
}



int Property::buildHouse(Bank* bank) {
    if (houseCount < 4)//if need to build house
    {
        if (bank->housesLeft() && (owner->money() >= houseCost))//if bank has houses left and player has money
        {
            bank->take(*owner, houseCost);
            houseCount += 1;
            bank->housesRemaining -= 1;
            return 1;
        }
        else
        {
            NoOptionWindow(owner, "Failed! No house left or insufficient money.");
            return 0;
        }
    }
    else if (houseCount == 4)//if need to build hotel
    {
        if (bank->hotelsLeft() && (owner->money() >= houseCost)) {//hotels left and owner has enough money
            bank->take(*owner, houseCost);//charge owner for a hotel
            houseCount += 1;
            hotelCount += 1;
            bank->hotelsRemaining -= 1;
            bank->housesRemaining += 4;
            return 2;
        }
        else
        {
            NoOptionWindow(owner, "Failed! No hotel left or insufficient money.");
            return 0;
        }
    }
    else
    {
        NoOptionWindow(owner, "Error: the housecount > 4");
        return 0;
    }
}

int Property::currentRent() const {
    if (propOwner()) {//if property is owned
        return rents[houseCount]; //return rent corresponding to current number of houses
    }
    return 0; //if unowned, no rent is due.
}

Property::View::View(const Property& prop) : mainLayout(new QVBoxLayout(this)) {
    std::string fileName = ":/properties/" + prop.color + "Property.png";
    QString qfileName(QString::fromStdString(fileName));
    image = QPixmap(qfileName);
    setFixedSize(400, 480);
    setWindowTitle("Property Purchase");

    //make label for name
    string temp = prop.name;
    QFont font("Kabel Heavy", 15);
    QLabel* _name = new QLabel(QString::fromStdString(temp), this);
    _name->setFont(font);
    mainLayout->addWidget(_name, 1, Qt::AlignHCenter);

    //make label for cost
    temp = "Cost: $" + std::to_string(prop.cost) + "\n";
    font = QFont("Kabel Heavy", 12);
    QLabel* line2 = new QLabel(QString::fromStdString(temp), this);
    line2->setFont(font);
    mainLayout->addWidget(line2, 4, Qt::AlignHCenter);

    //make label for the rest
    temp = "\t      Rent: $" + std::to_string(prop.rents[0]) + "\n" +
        "With 1 House\t\t$" + std::to_string(prop.rents[1]) + ".\n" +
        "With 2 Houses\t\t$" + std::to_string(prop.rents[2]) + ".\n" +
        "With 3 Houses\t\t$" + std::to_string(prop.rents[3]) + ".\n" +
        "With 4 Houses\t\t$" + std::to_string(prop.rents[4]) + ".\n" +
        "           With HOTEL     $" + std::to_string(prop.rents[5]) + ".\n";

    QLabel* rentsBlock = new QLabel(QString::fromStdString(temp), this);
    font = QFont("Kabel Heavy", 10);
    rentsBlock->setFont(font);
    mainLayout->addWidget(rentsBlock, 1, Qt::AlignHCenter);

    temp = "      Houses cost $" + std::to_string(prop.houseCost) + ". each\n" +
        "Hotels cost $" + std::to_string(prop.houseCost) + ". plus 4 houses\n";
    QLabel* bottomBlock = new QLabel(QString::fromStdString(temp), this);
    bottomBlock->setFont(font);
    mainLayout->addWidget(bottomBlock, 1, Qt::AlignHCenter);


}

void Property::View::paintEvent(QPaintEvent*) {

    QPainter p(this);
    p.drawPixmap(QRect(0, 0, 400, 500), image, QRect(0, 0, 160, 192));
}




Railroad::Railroad(int _tileNum, std::string _name, Board* _board, MainWindow* _game) :
    ownableTile(_tileNum, _board, _game),
    cost(200), name(std::move(_name))
{}

int Railroad::checkOwnerRailroads(const Player* player) const {
    int railroadCount = 0;
    if (propOwner() == nullptr) { return 0; }
    for (auto prop : player->playerProperties) {//go through player properties
        if (dynamic_cast<Railroad*>(prop)) {//see which ones are railroads
            ++railroadCount;                //count them
        }
    }
    return railroadCount; //return number of railroads they own.
}

int Railroad::currentRent() const {
    return rents[checkOwnerRailroads(owner) - 1];
}

QWidget* Railroad::generateView() const {
    return new View(*this);
}


Railroad::View::View(const Railroad& rr) : mainLayout(new QVBoxLayout(this)) {
    //owner owns all railroads
    if (rr.checkOwnerRailroads(rr.propOwner()) == 2) {
        QString qfileName(":/properties/railroadProperty.png");
        image = QPixmap(qfileName);

        setFixedSize(400, 600);
        setWindowTitle("RailRoad Transportation System");

        mainLayout->addSpacerItem(new QSpacerItem(319, 130, QSizePolicy::Fixed, QSizePolicy::Fixed)); //block out the icon display portion of the card

        string temp(rr.getName() + " Bus Line");
        QFont font("Kabel Heavy", 12);
        QLabel* _name = new QLabel(QString::fromStdString(temp), this);
        _name->setStyleSheet("font-weight: bold ; color: black");
        _name->setFont(font);
        mainLayout->addWidget(_name, 1, Qt::AlignHCenter | Qt::AlignTop);

        // COST

        temp = "Cost: $" + std::to_string(rr.cost) + "\n\n";
        QLabel* _cost = new QLabel(QString::fromStdString(temp));
        font = QFont("Kabel Heavy", 10);
        _cost->setFont(font);
        mainLayout->addWidget(_cost, 1, Qt::AlignHCenter | Qt::AlignTop);

        // asking for transporting
        temp = "Congrats Big Bruin! Now you own all the railroads:)\nWould you like to transport to another railroad,\nbut with a tiny charge for maintainence.";
        font = QFont("Kabel Heavy", 8);
        QLabel* block = new QLabel(QString::fromStdString(temp), this);
        block->setFont(font);
        mainLayout->addWidget(block, 1, Qt::AlignHCenter | Qt::AlignTop);
    }
    //NO, THEN GOES TO THIS LOOP
    else {
        QString qfileName(":/properties/railroadProperty.png");
        image = QPixmap(qfileName);

        setFixedSize(400, 600);
        setWindowTitle("Dining Hall Purchase");

        mainLayout->addSpacerItem(new QSpacerItem(319, 130, QSizePolicy::Fixed, QSizePolicy::Fixed)); //block out the icon display portion of the card

        string temp(rr.getName() + " Bus Line");
        QFont font("Kabel Heavy", 12);
        QLabel* _name = new QLabel(QString::fromStdString(temp), this);
        _name->setStyleSheet("font-weight: bold ; color: black");
        _name->setFont(font);
        mainLayout->addWidget(_name, 1, Qt::AlignHCenter | Qt::AlignTop);

        temp = "Cost: $" + std::to_string(rr.cost) + "\n\n";
        QLabel* _cost = new QLabel(QString::fromStdString(temp));
        font = QFont("Kabel Heavy", 10);
        _cost->setFont(font);
        mainLayout->addWidget(_cost, 1, Qt::AlignHCenter | Qt::AlignTop);


        temp = "Rent\t\t\t$" + std::to_string(rr.rents[0]) + "\n\n" +
            "If both R.R.'s are owned \t$" + std::to_string(rr.rents[1]);
        font = QFont("Kabel Heavy", 8);
        QLabel* block = new QLabel(QString::fromStdString(temp), this);
        block->setFont(font);
        mainLayout->addWidget(block, 1, Qt::AlignHCenter | Qt::AlignTop);
    }
}


void Railroad::View::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.drawPixmap(QRect(0, 0, 400, 400), image, QRect(0, 0, 160, 192));
}