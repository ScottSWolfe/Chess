#include "GameState.h"
#include "BoardInitializer.h"


GameState::GameState() :
	board(BoardInitializer::initializeStandardSetup()),
	white_player(new HumanPlayer(PieceColor::WHITE)),
	black_player(new HumanPlayer(PieceColor::BLACK)),
	current_player(PlayerTurn::WHITE)
{}

const Board &GameState::getBoard() const {
	return *board;
}

const Player &GameState::getCurrentPlayer() const {
	if (current_player == PlayerTurn::WHITE) {
		return *white_player;
	}
	else {
		return *black_player;
	}
}
