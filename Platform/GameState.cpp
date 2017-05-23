#include "GameState.h"


GameState::GameState(Board board, PlayerTurn beginning_player) : 
	board(board),
	current_turn(beginning_player)
{}

Board GameState::getBoard() const {
	return board;
}

PlayerTurn GameState::getPlayersTurn() const {
	return current_turn;
}
