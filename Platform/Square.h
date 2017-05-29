#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Piece.h"


class Square {

public:
	Square(SquareColor color);
	Square(SquareColor color, std::unique_ptr<const Piece> &piece);
	Square(const Square &other_square);
	const Piece *getPiece() const;
	void setPiece(std::unique_ptr<const Piece> &new_piece);
	std::unique_ptr<const Piece> removePiece();
	SquareColor getColor() const;

private:
	const SquareColor color;
	std::unique_ptr<const Piece> piece;
	std::unique_ptr<const Piece> getCopyOfPiece() const;
	void checkIfPieceIsNull(const Piece *piece) const;

};
