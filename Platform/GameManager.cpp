#include <iostream>
#include "BoardInitializer.h"
#include "ChessDebug.h"
#include "ChessEnums.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
#include "GameObserver.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveValidator.h"
#include "RandomPlayer.h"
using namespace std;


GameManager::GameManager() :
    presenter(new ConsoleBoardPresenter),
    current_state(BoardInitializer::initializeStandardSetup(), PieceColor::WHITE),
    white_player(new HumanPlayer(PieceColor::WHITE)),
    black_player(new HumanPlayer(PieceColor::BLACK))
{}

void GameManager::startGame() {
    notifyObserversGameStarted();
    runGameLoop();
}

void GameManager::runGameLoop() {
    while (true) {
        if (isGameOver()) {
            break;
        }
        makeMove();
    }
}

bool GameManager::isGameOver() const {
    GameEndType end_type = gameOverChecker.isGameOver(current_state);
    if (end_type != GameEndType::NOT_OVER) {
        notifyObserversGameEnded(end_type);
        return true;
    }
    return false;
}

void GameManager::makeMove() {
    notifyObserversTurnStarted();
    shared_ptr<Move> move = getMove();
    current_state.makeMove(*move);
    notifyObserversTurnEnded();
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

void GameManager::registerObserver(GameObserver *observer) {
    observers.push_back(observer);
}

void GameManager::notifyObserversGameStarted() const {
    for (auto observer : observers) {
        observer->gameStarted(current_state);
    }
}

void GameManager::notifyObserversGameEnded(GameEndType end_type) const {
    for (auto observer : observers) {
        observer->gameEnded(current_state, end_type);
    }
}

void GameManager::notifyObserversTurnStarted() const {
    for (auto observer : observers) {
        observer->turnStarted(current_state);
    }
}

void GameManager::notifyObserversTurnEnded() const {
    for (auto observer : observers) {
        observer->turnEnded(current_state);
    }
}
