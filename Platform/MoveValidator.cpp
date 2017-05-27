#include "MoveValidator.h"

MoveValidator::MoveValidator(const GameState &state, const Move &move)
	: state(state), move(move)
{}

bool MoveValidator::validateMove() const {
	if (!isPiece()) {
		return false;
	}
	if (!isCorrectColor()) {
		return false;
	}
	return true;
}

bool MoveValidator::isPiece() const {
	int x = move.getStartSquareCoord().x;
	int y = move.getStartSquareCoord().y;
	if (state.getBoard().getSquare(x, y).getPiece() == nullptr) {
		return false;
	}
	return true;
}

bool MoveValidator::isCorrectColor() const {
	return true;
}
