#include "GameState.h"


GameState::GameState(Board board, PlayerTurn beginning_player) : 
	board(board),
	current_player(beginning_player)
{}

Board GameState::getBoard() const {
	return board;
}
