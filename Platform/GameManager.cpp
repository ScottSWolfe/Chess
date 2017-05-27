#include <iostream>
#include "ChessDebug.h"
#include "BoardInitializer.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
#include "Move.h"
#include "MoveValidator.h"
#include "HumanPlayer.h"
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
		cout << static_cast<int>(current_state.getPlayersTurn()) << "'s turn" << endl;
		std::shared_ptr<const Move> move = getPlayerMove();
		current_state.makeMove(*move);
		presenter->displayBoard(current_state.getBoard());
	}

}

std::shared_ptr<const Move> GameManager::getPlayerMove() const {
	const Player *current_player = getCurrentPlayer();
	std::shared_ptr<const Move> move = current_player->move(current_state.getBoard());
	MoveValidator moveValidator(current_state, *move);
	if (!moveValidator.validateMove()) {
		move = getPlayerMove();
	}
	return move;
}

const Player *GameManager::getCurrentPlayer() const {
	if (current_state.getPlayersTurn() == PlayerTurn::WHITE) {
		return white_player.get();
	}
	else {
		return black_player.get();
	}
}
