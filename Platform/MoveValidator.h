#pragma once

#include "GameState.h"
#include "Move.h"
struct Position;


class MoveValidator {

public:
	MoveValidator(const GameState &state, const Move &move);
	bool validateMove() const;

private:
	const GameState &state;
	const Move &move;
	bool doSquaresExist() const;
	bool doesSquareExist(Position pos) const;
	bool isPieceAtStart() const;
	bool isPieceCorrectColor() const;
	bool isDestAvailable() const;
	bool MoveValidator::isAvailableMove() const;

};
