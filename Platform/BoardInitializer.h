#pragma once
#include <memory>
#include "Board.h"

class BoardInitializer {

public:
	std::unique_ptr<Board> initializeStandardGame();

private:
	void addStandardPieces(Board *board);

};
