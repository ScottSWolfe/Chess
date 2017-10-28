#include <iostream>
#include "BoardInitializer.h"
#include "BTREngine.h"
#include "ChessDebug.h"
#include "ComputerPlayer.h"
#include "ConsoleBoardPresenter.h"
#include "StandardGameManager.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveValidator.h"
#include "RandomPlayer.h"

namespace chess {


StandardGameManager::StandardGameManager() :
    current_state(BoardInitializer::initializeStandardSetup(), PieceColor::WHITE),
    white_player(new ComputerPlayer(PieceColor::WHITE, new BTREngine)),
    black_player(new ComputerPlayer(PieceColor::BLACK, new RandomEngine))
{}

void StandardGameManager::startGame() {
    notifyObserversGameStarted();
    runGameLoop();
}

void StandardGameManager::runGameLoop() {
    while (true) {
        if (isGameOver()) {
            break;
        }
        runPlayersTurn();
    }
}

bool StandardGameManager::isGameOver() const {
    if (current_state.isGameOver() == true) {
        notifyObserversGameEnded();
        return true;
    }
    return false;
}

void StandardGameManager::runPlayersTurn() {
    notifyObserversTurnStarted();
    auto action = getPlayerAction();
    while (action->enactAction(*this) == false) {
        // TODO notify observer that action failed
        action = getPlayerAction();
    }
    notifyObserversTurnEnded();
}

std::shared_ptr<PlayerAction> StandardGameManager::getPlayerAction() const {
    return currentPlayer()->getAction(current_state);
}

bool StandardGameManager::makeMove(Move move) {
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

bool StandardGameManager::resign() {
    current_state.resignation();
    return true;
}

bool StandardGameManager::offerDraw() {
    bool accepted = otherPlayer()->drawOffered(current_state);
    if (accepted == true) {
        current_state.drawByAgreement();
        return true;
    }
    return false;
}

bool StandardGameManager::claim50MoveDraw() {
    return current_state.drawBy50Moves();
}

bool StandardGameManager::claim3RepetionDraw() {
    return false;
}

bool StandardGameManager::validateMoveIsSafe(const Move &move) const {
    MoveValidator moveValidator(current_state, move);
    return moveValidator.validateMoveIsSafe();
}

bool StandardGameManager::validateMoveIsLegal(const Move &move) const {
    MoveValidator moveValidator(current_state, move);
    return moveValidator.validateMoveIsLegal();
}

void StandardGameManager::addMoveEffect(Move &move) const {
    current_state.addMoveEffect(move);
    if (move.hasEffect() && move.getEffectType() == MoveEffectType::PROMOTION) {
        PieceType type = askPlayerForPromotionPiece(move);
        move.setPromotionPiece(type);
    }
}

PieceType StandardGameManager::askPlayerForPromotionPiece(const Move &move) const {
    return currentPlayer()->getPromotionPiece(current_state, move);
}

const Player *StandardGameManager::currentPlayer() const {
    if (current_state.getCurrentPlayersTurn() == PieceColor::WHITE) {
        return white_player.get();
    }
    else {
        return black_player.get();
    }
}

const Player *StandardGameManager::otherPlayer() const {
    if (current_state.getCurrentPlayersTurn() == PieceColor::WHITE) {
        return black_player.get();
    }
    else {
        return white_player.get();
    }
}

void StandardGameManager::registerObserver(GameObserver *observer) {
    observers.push_back(observer);
}

void StandardGameManager::notifyObserversGameStarted() const {
    for (auto observer : observers) {
        observer->gameStarted(current_state);
    }
}

void StandardGameManager::notifyObserversGameEnded() const {
    for (auto observer : observers) {
        observer->gameEnded(current_state);
    }
}

void StandardGameManager::notifyObserversTurnStarted() const {
    for (auto observer : observers) {
        observer->turnStarted(current_state);
    }
}

void StandardGameManager::notifyObserversTurnEnded() const {
    for (auto observer : observers) {
        observer->turnEnded(current_state);
    }
}


}
