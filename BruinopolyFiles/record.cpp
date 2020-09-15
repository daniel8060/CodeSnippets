#include "Record.h"
#include <fstream>
#include "player.h"
using std::string; using std::stringstream;
Record::Record() {

}
Record::Record(const QString& _PlayerName, int _PlayerRanking, int _money) :
    PlayerName(_PlayerName), ranking(_PlayerRanking), moneyRemaining(_money), file(filename) {
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Rank:" << '\t' << QString::number(ranking) << '\t' << "Name" << '\t' << PlayerName << '\t' << "Money " << QString::number(moneyRemaining);
    }
}

Record::Record(const Player& player, int _PlayerRanking) :
    PlayerName(player.getname()), ranking(_PlayerRanking), moneyRemaining(player.money()), file(filename) {
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Rank:" << '\t' << QString::number(ranking) << '\t' << "Name" << '\t' << PlayerName << '\t' << "Money " << QString::number(moneyRemaining);
    }
}

int Record::getPlayerRanking() const {
    return ranking;
}
QString Record::getPlayerName() const {
    return PlayerName;
}
int Record::getPlayerMoney() const {
    return moneyRemaining;
}


QWidget* Record::getPlayerInfo(QWidget* parent) {

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    QString line = "";

    QString name = "";
    QString ranking = "";
    QString money = "";

    while (in.readLineInto(&line)) {//i googled it and it said this was better??? feel free to change back
        line = in.readLine();// a string of whole line
        QStringList list(line.split('\t'));
        ranking = list[1];
        name = list[3];
        money = list[5];
    }

    QFont font("Kabel Heavy", 15); //set font to make alittle less plain.

    QLabel* _name = new QLabel(name);
    _name->setFont(font);
    QLabel* _ranking = new QLabel(ranking);
    _ranking->setFont(font);
    QLabel* _money = new QLabel(money);
    _money->setFont(font);

    QWidget* returnWid = new QWidget(parent);
    QHBoxLayout* layout = new QHBoxLayout(returnWid);

    layout->addWidget(_name);
    layout->addWidget(_money);
    layout->addWidget(_ranking);

    return returnWid;