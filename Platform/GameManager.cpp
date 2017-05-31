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
		cout << playerTurnToString() << "'s Turn" << endl;
		auto move = getPlayerMove();
		current_state.makeMove(*move);
		presenter->displayBoard(current_state.getBoard());
	}

}

std::shared_ptr<Move> GameManager::getPlayerMove() const {
	const Player *current_player = getCurrentPlayer();
	auto move = current_player->makeMove(current_state);
	if (validateMoveIsSafe(*move) == false) {
		move = getAnotherMove();
	}
	current_state.checkForAndAddMoveEffect(*move);
	if (validateMoveIsLegal(*move) == false) {
		move = getAnotherMove();
	}
	return move;
}

bool GameManager::validateMoveIsSafe(const Move &move) const {
	MoveValidator moveValidator(current_state, move);
	return moveValidator.validateMoveIsSafe();
}

bool GameManager::validateMoveIsLegal(const Move &move) const {
	MoveValidator moveValidator(current_state, move);
	return moveValidator.validateMoveIsLegal();
}

std::shared_ptr<Move> GameManager::getAnotherMove() const {
	cout << "Illegal Move. Try again:" << endl;
	return getPlayerMove();
}

const Player *GameManager::getCurrentPlayer() const {
	if (current_state.getPlayersTurn() == PlayerTurn::WHITE) {
		return white_player.get();
	}
	else {
		return black_player.get();
	}
}

string GameManager::playerTurnToString() const {
	if (current_state.getPlayersTurn() == PlayerTurn::BLACK) {
		return "Black";
	}
	else {
		return "White";
	}
}
