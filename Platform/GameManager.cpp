#include <iostream>
#include "BoardInitializer.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
using namespace std;


GameManager::GameManager() :
	presenter(new ConsoleBoardPresenter),
	current_state(BoardInitializer::initializeStandardSetup(), PlayerTurn::WHITE),
	white_player(new HumanPlayer(PieceColor::WHITE)),
	black_player(new HumanPlayer(PieceColor::BLACK))
{}

void GameManager::startGame() {
	runGameLoop();
}

void GameManager::runGameLoop() {
	cout << "Game Loop Started" << endl;
	presenter->displayBoard(current_state.getBoard());

	while (true) {
		// check if game is over

		// get current player's move
		getPlayerMove();

		// make move on board
	}

}

const Player *GameManager::getCurrentPlayer() const {
	if (current_state.getPlayersTurn() == PlayerTurn::WHITE) {
		return white_player.get();
	}
	else {
		return black_player.get();
	}
}

void /*const Move*/ GameManager::getPlayerMove() const {
	const Player *current_player = getCurrentPlayer();
	// get move
	// validate move is legal
	// return move
}
