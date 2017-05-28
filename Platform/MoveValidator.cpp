#include "ChessDebug.h"
#include "MoveValidator.h"
#include "Pawn.h"


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
	if (!isPieceCorrectColor()) {
		return false;
	}
	if (!isDestAvailable()) {
		return false;
	}
	if (!isAvailableMove()) {
		return false;
	}
	return true;
}

bool MoveValidator::doSquaresExist() const {
	int x = move.getStart().x;
	int y = move.getStart().y;
	if (!doesSquareExist(x, y)) {
		return false;
	}

	x = move.getEnd().x;
	y = move.getEnd().y;
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
	int x = move.getStart().x;
	int y = move.getStart().y;
	return state.isPiece(x, y);
}

bool MoveValidator::isPieceCorrectColor() const {
	int x = move.getStart().x;
	int y = move.getStart().y;
	PieceColor color = state.getPieceColor(x, y);
	PlayerTurn turn = state.getPlayersTurn();
	return color == turn;
}

bool MoveValidator::isDestAvailable() const {
	int x = move.getEnd().x;
	int y = move.getEnd().y;

	if (!state.isPiece(x, y)) {
		return true;
	}
	if (state.getPieceColor(x, y) != state.getPlayersTurn()) {
		return true;
	}
	return false;
}

bool MoveValidator::isAvailableMove() const {
	// temp
	const Piece *piece = state.getPiece(move.getStart().x, move.getStart().y);
	if (dynamic_cast<const Pawn*>(piece)) {
		if (state.isMoveAvailable(move)) {
			return true;
		}
		return false;
	}
	// end temp
	return true;
}
