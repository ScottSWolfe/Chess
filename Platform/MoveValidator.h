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
	bool isPiece() const;
	bool isCorrectColor() const;

};
