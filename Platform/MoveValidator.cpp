#include "ChessDebug.h"
#include "MoveValidator.h"
#include "Pawn.h"
#include "Position.h"


MoveValidator::MoveValidator(const GameState &state, const Move &move)
	: state(state), move(move)
{}

bool MoveValidator::validateMove() const {
	if (!doSquaresExist()) {
		return false;
	}
	if (!isPieceAtStart()) {
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
	if (doesSquareExist(move.getStart()) == false) {
		return false;
	}
	if (doesSquareExist(move.getEnd()) == false) {
		return false;
	}
	return true;
}

bool MoveValidator::doesSquareExist(Position pos) const {
	if (pos.x < 0 || pos.x >= state.getBoardDimension()) {
		return false;
	}
	if (pos.y < 0 || pos.y >= state.getBoardDimension()) {
		return false;
	}
	return true;
}

bool MoveValidator::isPieceAtStart() const {
	return state.isPiece(move.getStart());
}

bool MoveValidator::isPieceCorrectColor() const {
	PieceColor color = state.getPieceColor(move.getStart());
	PlayerTurn turn = state.getPlayersTurn();
	return color == turn;
}

bool MoveValidator::isDestAvailable() const {
	if (state.isPiece(move.getEnd()) == false) {
		return true;
	}
	if (state.getPieceColor(move.getEnd()) != state.getPlayersTurn()) {
		return true;
	}
	return false;
}

bool MoveValidator::isAvailableMove() const {
	// temp
	const Piece *piece = state.getPiece(move.getStart());
	if (dynamic_cast<const Pawn*>(piece)) {
		if (state.isMoveAvailable(move)) {
			return true;
		}
		return false;
	}
	// end temp
	return true;
}
