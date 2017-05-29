#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Square.h"
class Piece;
struct Position;


class Board {

public:
	Board(int board_dimension);
	Board(const Board &other_board);
	Square &getSquare(Position pos);
	const Square &getSquare(Position pos) const;
	SquareColor getSquareColor(Position pos) const;
	bool inBounds(Position pos) const;
	void addPieceToSquare(Position pos, std::unique_ptr<const Piece> &piece);
	std::unique_ptr<const Piece> removePieceFromSquare(Position pos);
	std::vector<Move> getMoves(Position pos) const;
	bool isPiece(Position pos) const;
	const Piece *getPiece(Position pos) const;
	PieceColor getPieceColor(Position pos) const;
	std::string getPieceSymbol(Position pos) const;
	int getDimension() const;

private:
	const int dimension;
	std::vector<Square> squares;
	int getIndex(Position pos) const;
	SquareColor getSquareColorByIndex(int index) const;
	void checkIfPieceIsNull(const Piece *piece) const;

};
