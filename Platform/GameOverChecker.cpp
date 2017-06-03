#include <string>
#include "ChessEnums.h"
#include "GameOverChecker.h"
#include "GameState.h"
#include "Move.h"
using namespace std;


GameEndType GameOverChecker::isGameOver(const GameState &state) const {
	GameEndType end_type = GameEndType::NOT_OVER;

	end_type = isCheckMate(state);
	if (end_type != GameEndType::NOT_OVER) {
		return end_type;
	}

	return end_type;
}

GameEndType GameOverChecker::isCheckMate(const GameState &state) const {
	if (state.canCurrentPlayerMakeMove() == true) {
		return GameEndType::NOT_OVER;
	}
	if (state.isKingInCheck() == false) {
		return GameEndType::NOT_OVER;
	}
	return getCheckmateType(state.getCurrentPlayersTurn());
}

GameEndType GameOverChecker::getCheckmateType(PieceColor current_color) const {
	if (current_color == PieceColor::WHITE) {
		return GameEndType::BLACK_CHECKMATE;
	}
	return GameEndType::WHITE_CHECKMATE;
}
