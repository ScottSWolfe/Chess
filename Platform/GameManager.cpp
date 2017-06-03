#include <iostream>
#include "BoardInitializer.h"
#include "ChessDebug.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveValidator.h"
#include "StateObserver.h"
using namespace std;


GameManager::GameManager() :
	presenter(new ConsoleBoardPresenter),
	current_state(BoardInitializer::initializeStandardSetup(), PieceColor::WHITE),
	white_player(new HumanPlayer(PieceColor::WHITE)),
	black_player(new HumanPlayer(PieceColor::BLACK))
{}

void GameManager::startGame() {
	runGameLoop();
}

void GameManager::registerStateObserver(StateObserver *observer) {
	current_state.registerObserver(observer);
}

void GameManager::runGameLoop() {
	while (true) {
		if (isGameOver().empty() == false) {
			break;
		}
		shared_ptr<Move> move = getMove();
		current_state.makeMove(*move);
	}
}

string GameManager::isGameOver() const {
	return gameOverChecker.isGameOver(current_state);
}

std::shared_ptr<Move> GameManager::getMove() const {
	auto move = getCurrentPlayersMove();
	if (validateMoveIsSafe(*move) == false) {
		move = getAnotherMove();
	}
	current_state.addMoveEffect(*move);
	if (validateMoveIsLegal(*move) == false) {
		move = getAnotherMove();
	}
	return move;
}

std::shared_ptr<Move> GameManager::getCurrentPlayersMove() const {
	const Player *current_player = getCurrentPlayer();
	auto move = current_player->makeMove(current_state);
	if (validateMoveIsSafe(*move) == false) {
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
	return getMove();
}

const Player *GameManager::getCurrentPlayer() const {
	if (current_state.getCurrentPlayersTurn() == PieceColor::WHITE) {
		return white_player.get();
	}
	else {
		return black_player.get();
	}
}
