#pragma once

#include <memory>
#include <vector>
#include "ChessEnums.h"
#include "Square.h"
class Piece;


class Board {

public:
	Board(int board_dimension);
	Board(const Board &other_board);
	Square &getSquare(int x, int y);
	const Square &getSquare(int x, int y) const;
	void addPieceToSquare(int x, int y, std::unique_ptr<const Piece> &piece);
	std::unique_ptr<const Piece> removePieceFromSquare(int x, int y);
	std::vector<Move> getMoves(int x, int y) const;
	bool isPiece(int x, int y) const;
	const Piece *getPiece(int x, int y) const;
	PieceColor getPieceColor(int x, int y) const;
	int getDimension() const;

private:
	const int dimension;
	std::vector<Square> squares;
	int convertCoordsToIndex(int x, int y) const;
	SquareColor getSquareColorByIndex(int index) const;

};
