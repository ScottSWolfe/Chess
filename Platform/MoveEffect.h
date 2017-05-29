#pragma once

#include <memory>
#include "Position.h"
#include "Piece.h"
struct Position;


class MoveEffect {

public:
	MoveEffect(Position pos);
	MoveEffect(Position pos, std::unique_ptr<const Piece> &piece);
	MoveEffect(const MoveEffect &other);
	bool operator==(const MoveEffect &other) const;
	Position getPosition() const;
	std::unique_ptr<const Piece> getCopyOfPiece() const;
	std::unique_ptr<const MoveEffect> getCopy() const;

private:
	const Position position;
	const std::unique_ptr<const Piece> piece;

};
