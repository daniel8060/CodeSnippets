#include "player.h"
#include <QDebug>
#include "board.h"
#include "property.h"
#include "chancecard.h"
#include "mainwindow.h"
#include "bank.h"

#include <string>
#include <sstream>
#include <fstream>
#include <exception>

using std::string;

Board::Board(MainWindow* game) :w(game), tiles(16, nullptr) {


    srand(time(nullptr));

    string first("prop	1	purple	Kerchoff	60	50	12	24	45	90	160	250");
    string sec("prop	3	purple	Powell	60	50	30	55  90  180	320	450");
    string six("prop	5	magenta	Dickson	140	100	70	100	150	450	625	750");
    string sev("prop	6	magenta	Music	140	100	70	100	150	450	625	750");
    string eight("prop	7	magenta	Socialogy	160	100	40	120	180	500	700	900");
    string parkPlace("prop\t9\tblue\tRoyce Hall\t350\t200\t35\t175\t500\t1100\t1300\t1500");
    string mathSci("prop\t11\tblue\tFowler Museum\t400\t200\t50\t200\t1600\t1400\t1700\t2000");
    string nine("prop	13	yellow	MS	180	100	50	100	200	550	700	900");
    string ten("prop	14	yellow	Intermural Field	180	100	50	100	200	550	700	950");
    string eleven("prop	15	yellow	Bear Statues	200	100	30	80	220	600	900	1000");

    //bottom row
    tiles.at(0) = new Tile(0, this, game);
    tiles.at(1) = new Property(first, this, game);
    tiles.at(2) = new Railroad(2, "Metro", this, game);
    tiles.at(3) = new Property(sec, this, game);

    //right column
    tiles.at(4) = new ChanceTile(4, this, game);
    tiles.at(5) = new Property(six, this, game);
    tiles.at(6) = new Property(sev, this, game);
    tiles.at(7) = new Property(eight, this, game);

    //top row
    tiles.at(8) = new Tile(8, this, game);
    tiles.at(13) = new Property(nine, this, game);
    tiles.at(14) = new Property(ten, this, game);
    tiles.at(15) = new Property(eleven, this, game);

    //left column
    tiles.at(9) = new Property(parkPlace, this, game);
    tiles.at(10) = new Railroad(10, "Big Blue", this, game);
    tiles.at(11) = new Property(mathSci, this, game);
    tiles.at(12) = new ChanceTile(12, this, game);
}

Board::~Board() {
    for (size_t i; i < tiles.size(); i++)
        delete tiles[i];
    for (size_t i; i < tiles.size(); i++)
        delete chanceCards[i];
}

Tile* Board::getTile(int boardPos) {
    return tiles.at(boardPos);
}

void Board::buildChancecards(MainWindow* game) {

    chanceCards.emplace_back(new ChanceCard("Lose 200 Dollars!",
        [game](Player* currPlayer) -> void {
            game->bank->take(*currPlayer, 200);
        }
    )

    );

    chanceCards.emplace_back(new ChanceCard("Gain 100 Dollars!",
        [game](Player* currPlayer) -> void {
            game->bank->pay(*currPlayer, 100);
        }
    )
    );
    chanceCards.emplace_back(new ChanceCard("Go to Jail!",
        [](Player* currPlayer) -> void {
            currPlayer->getmovement()->instant_trans(8);
            currPlayer->changeDisable();
        }
    )
    );

    chanceCards.emplace_back(new ChanceCard("Take a break! (Nothing happens).",
        [](Player*) {})
    );




    chanceCards.emplace_back(new ChanceCard("Take $50 from each other player",
        [game](Player* currPlayer) -> void {
            for (auto player : game->playerlist) {
                if (player->getmovement()->getorder() != currPlayer->getmovement()->getorder())
                {
                    currPlayer->take(player, 50);
                }

            }
        }
    )
    );

    chanceCards.emplace_back(new ChanceCard("Pay each other player $50",
        [game](Player* currPlayer) -> void {
            for (auto player : game->playerlist) {
                if (player->getmovement()->getorder() != currPlayer->getmovement()->getorder())
                {
                    currPlayer->take(player, -50);
                }
            }
        }
    )
    );
}