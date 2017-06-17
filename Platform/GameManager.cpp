#include <iostream>
#include "BoardInitializer.h"
#include "ChessDebug.h"
#include "ChessEnums.h"
#include "ConsoleBoardPresenter.h"
#include "GameManager.h"
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
        runPlayersTurn();
    }
}

bool GameManager::isGameOver() const {
    if (current_state.isGameOver() == true) {
        notifyObserversGameEnded();
        return true;
    }
    return false;
}

void GameManager::runPlayersTurn() {
    notifyObserversTurnStarted();
    shared_ptr<PlayerAction> action = getPlayerAction();
    while (action->enactAction(*this) == false) {
        // TODO notify observer that action failed
        action = getPlayerAction();
    }
    notifyObserversTurnEnded();
}

shared_ptr<PlayerAction> GameManager::getPlayerAction() const {
    return currentPlayer()->getAction(current_state);
}

bool GameManager::makeMove(Move move) {
    if (validateMoveIsSafe(move) == false) {
        return false;
    }
    addMoveEffect(move);
    if (validateMoveIsLegal(move) == false) {
        return false;
    }
    current_state.makeMove(move);
    return true;
}

bool GameManager::resign() {
    current_state.resignation();
    return true;
}

bool GameManager::offerDraw() {
    return false;
}

bool GameManager::claimDraw() {
    return false;
}

bool GameManager::validateMoveIsSafe(const Move &move) const {
    MoveValidator moveValidator(current_state, move);
    return moveValidator.validateMoveIsSafe();
}

bool GameManager::validateMoveIsLegal(const Move &move) const {
    MoveValidator moveValidator(current_state, move);
    return moveValidator.validateMoveIsLegal();
}

void GameManager::addMoveEffect(Move &move) const {
    current_state.addMoveEffect(move);
    if (move.hasEffect() && move.getEffectType() == MoveEffectType::PROMOTION) {
        PieceType type = askPlayerForPromotionPiece(move);
        move.setPromotionPiece(type);
    }
}

PieceType GameManager::askPlayerForPromotionPiece(const Move &move) const {
    return currentPlayer()->getPromotionPiece(current_state, move);
}

const Player *GameManager::currentPlayer() const {
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

void GameManager::notifyObserversGameEnded() const {
    for (auto observer : observers) {
        observer->gameEnded(current_state);
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
