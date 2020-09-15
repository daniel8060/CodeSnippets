#ifndef RECORD_H
#define RECORD_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>


/**
  @Q: to be solved:
  looserlist[4] needs to be fixed. Or else in the record there should be 4 players
*/

/**
Daniel Changes 12/4 :
Note : FFTCB = Non important change. Feel Free to Change Back.
    * Added third Record Constructor that takes in a player and int _ranking
      it has the same functionility as your constructor.
    In .h
        * changed fileName
        * changed return type of getPlayerInfo to QWidget* vs QWidget cause wasn't working for me.  FFTCB
    In getPlayerInfo:
        * Changed return type to QWidget* from QWidget because it was giving difficulties w/o using pointer.  FFTCB
        * Changed while loop condition after some googling. FFTCB
        * Added Return Widget
        @Q: Removed Redefinition of file. We want to use the file in the private variables right?
        * Changed Font for labels to give a little bit of pizzazz.
    In 2nd Constructor:
        *Changed text that is printed a little. FFTCB.
*/
class Player;

class Record {
public:
    Record();
    Record(const QString&, int _PlayerRanking, int _moeny = 0);
    Record(const Player& player, int _PlayerRanking);
    QWidget* getPlayerInfo(QWidget* parent);
    int getPlayerRanking() const;
    QString getPlayerName() const;
    int getPlayerMoney() const;
    void setPlayerRanking(int);
    void setPlayerMoney(int _moeny = 0);
    void setPlayerName(const QString&);
private:
    QString PlayerName;
    int ranking;
    int moneyRemaining;

    QString filename = ":/txt/record.txt";
    QFile file;
protected:
};

#endif // RECORD_H
