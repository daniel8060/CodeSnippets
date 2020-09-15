#ifndef BOARD_H
#define BOARD_H

#include <vector>

class ChanceCard;
class MainWindow;
class Player;
class Tile;

class Board {
	friend Player;
	friend class ChanceTile;

public:
	Board(MainWindow* game = nullptr);

	//return the ptr of the tile on the idx
	//@boardPos the idx
	Tile* getTile(int boardPos);

	//construct chance card
	void buildChancecards(MainWindow* game);

	MainWindow* w;
	~Board();

private:
	std::vector <Tile*> tiles;
	std::vector <ChanceCard*> chanceCards;
};

#endif
