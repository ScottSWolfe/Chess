#include "ChessDebug.h"
#include "MoveValidator.h"

MoveValidator::MoveValidator(const GameState &state, const Move &move)
	: state(state), move(move)
{}

bool MoveValidator::validateMove() const {
	if (!doSquaresExist()) {
		return false;
	}
	if (!isPiece()) {
		return false;
	}
	if (!isCorrectColor()) {
		return false;
	}
	return true;
}

bool MoveValidator::doSquaresExist() const {
	int x = move.getStartCoords().x;
	int y = move.getStartCoords().y;
	if (!doesSquareExist(x, y)) {
		return false;
	}

	x = move.getEndCoords().x;
	y = move.getEndCoords().y;
	if (!doesSquareExist(x, y)) {
		return false;
	}

	return true;
}

bool MoveValidator::doesSquareExist(int x, int y) const {
	if (x < 0 || x >= state.getBoardDimension()) {
		return false;
	}
	if (y < 0 || y >= state.getBoardDimension()) {
		return false;
	}
	return true;
}

bool MoveValidator::isPiece() const {
	int x = move.getStartCoords().x;
	int y = move.getStartCoords().y;
	return state.isPiece(x, y);
}

bool MoveValidator::isCorrectColor() const {
	int x = move.getStartCoords().x;
	int y = move.getStartCoords().y;
	PieceColor color = state.getPieceColor(x, y);
	PlayerTurn turn = state.getPlayersTurn();
	return color == turn;
}
