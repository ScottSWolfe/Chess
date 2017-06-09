#pragma once

#include <memory>
#include <string>
#include "BoardPresenter.h"
#include "GameObserver.h"
#include "GameOverChecker.h"
#include "GameState.h"
#include "GameSubject.h"
#include "Player.h"


class GameManager : public GameSubject {
    
public:
    GameManager();
    void startGame();
    void registerObserver(GameObserver *observer);

private:
    // fields
    GameState current_state;
    std::unique_ptr<const Player> white_player;
    std::unique_ptr<const Player> black_player;
    std::vector<GameObserver*> observers;

    // actions
    std::unique_ptr<BoardPresenter> presenter;
    GameOverChecker gameOverChecker;

    // methods
    void runGameLoop();
    bool isGameOver() const;
    void makeMove();
    std::shared_ptr<Move> getMove() const;
    const Player *currentPlayer() const;
    std::shared_ptr<Move> getCurrentPlayersMove() const;
    bool validateMoveIsLegal(const Move &move) const;
    bool validateMoveIsSafe(const Move &move) const;
    void addMoveEffect(Move &move) const;
    PieceType askPlayerForPromotionPiece(const Move &move) const;
    std::shared_ptr<Move> getAnotherMove() const;
    void notifyObserversGameStarted() const;
    void notifyObserversGameEnded(GameEndType end_type) const;
    void notifyObserversTurnStarted() const;
    void notifyObserversTurnEnded() const;

};
