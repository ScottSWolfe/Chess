#pragma once

#include "GameState.h"
#include "Move.h"


class MoveValidator {

public:
	MoveValidator(const GameState &state, const Move &move);
	bool validateMove() const;

private:
	const GameState &state;
	const Move &move;
	bool doSquaresExist() const;
	bool doesSquareExist(int x, int y) const;
	bool isPiece() const;
	bool isPieceCorrectColor() const;
	bool isDestAvailable() const;
	bool MoveValidator::isAvailableMove() const;

};
