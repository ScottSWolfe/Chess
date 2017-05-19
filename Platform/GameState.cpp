#include "GameState.h"

Board *GameState::getBoard() {
	return &board;
}

Player *GameState::getCurrentPlayer() {
	if (current_player == PlayerTurn::WHITE) {
		return &white_player;
	}
	else {
		return &black_player;
	}
}
