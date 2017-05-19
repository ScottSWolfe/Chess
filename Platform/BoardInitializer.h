#pragma once
#include <memory>

#include "Board.h"
#include "Piece.h"


class BoardInitializer {

public:
	std::unique_ptr<Board> initializeStandardGame();

private:
	void addStandardPieces(Board *board);
	void addRowOfPawns(Board *board, const int row, const PieceColor color);
	void addStandardRowOfPieces(Board *board, const int row, const PieceColor color);
	Board *board;
	int dimension;

};
