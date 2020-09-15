
#include "chancecard.h"
#include "board.h"
#include "qlandingwindow.h"
#include "mainwindow.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QDialog>
#include <algorithm>
#include <ctime>


ChanceCard::ChanceCard(std::string _description, std::function<void(Player*)> f) :
    description(std::move(_description)),
    effect(std::move(f))
{
}

ChanceCard::~ChanceCard() { delete content; }

void ChanceCard::conduct_change(Player* currPlayer) {
    //set chance card popup window
    content = new QDialog(this);
    content->setAttribute(Qt::WA_DeleteOnClose);
    content->setWindowTitle("Chance Card");
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* statement = new QLabel(QString::fromStdString(description));
    statement->setFont(QFont("Times", 9));
    statement->setFixedSize(300, 400);
    layout->addWidget(statement);
    content->setLayout(layout);
    QLabel* bearlb = new QLabel;
    bearlb->setFixedSize(150, 180);
    QPixmap* bear = new QPixmap(":/fig/chance_deco.png");
    bearlb->setPixmap(*bear);
    bearlb->setPixmap(bear->scaled(bearlb->width(), bearlb->height(), Qt::KeepAspectRatio));
    layout->addWidget(bearlb, 0, Qt::AlignRight);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::yellow);
    content->setAutoFillBackground(true);
    content->setPalette(pal);
    content->setFixedSize(600, 400);
    content->show();

    //do the thing
    effect(currPlayer);
}