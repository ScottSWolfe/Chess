#include <iostream>
#include "BoardInitializer.h"
#include "ChessDebug.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveValidator.h"
#include "GameObserver.h"
using namespace std;


GameManager::GameManager() :
	presenter(new ConsoleBoardPresenter),
	current_state(BoardInitializer::initializeStandardSetup(), PieceColor::WHITE),
	white_player(new HumanPlayer(PieceColor::WHITE)),
	black_player(new HumanPlayer(PieceColor::BLACK))
{}

void GameManager::startGame() {
	current_state.notifyObserversGameStarted();
	runGameLoop();
}

void GameManager::registerGameObserver(GameObserver *observer) {
	current_state.registerObserver(observer);
}

void GameManager::runGameLoop() {
	while (true) {
		GameEndType end_type = isGameOver();
		if (end_type != GameEndType::NOT_OVER) {
			break;
		}
		shared_ptr<Move> move = getMove();
		current_state.makeMove(*move);
	}
}

GameEndType GameManager::isGameOver() const {
	GameEndType end_type = gameOverChecker.isGameOver(current_state);
	if (end_type == GameEndType::NOT_OVER) {
		current_state.notifyObserversTurnStarted();
	}
	else {
		current_state.notifyObserversGameEnded(end_type);
	}
	return end_type;
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
