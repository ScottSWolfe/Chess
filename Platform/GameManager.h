#pragma once

#include <memory>
#include <string>
#include "BoardPresenter.h"
#include "GameObserver.h"
#include "GameOverChecker.h"
#include "GameState.h"
#include "GameSubject.h"
#include "Player.h"
class PlayerAction;


class GameManager : public GameSubject {
    
public:
    GameManager();
    void startGame();
    bool makeMove(Move move);
    void registerObserver(GameObserver *observer);

private:
    // fields
    GameState current_state;
    std::unique_ptr<const Player> white_player;
    std::unique_ptr<const Player> black_player;
    std::vector<GameObserver*> observers;
    std::unique_ptr<BoardPresenter> presenter;
    GameOverChecker gameOverChecker;

    // methods
    void runGameLoop();
    bool isGameOver() const;
    void runPlayersTurn();
    std::shared_ptr<PlayerAction> getPlayerAction() const;
    const Player *currentPlayer() const;
    bool validateMoveIsLegal(const Move &move) const;
    bool validateMoveIsSafe(const Move &move) const;
    void addMoveEffect(Move &move) const;
    PieceType askPlayerForPromotionPiece(const Move &move) const;
    void notifyObserversGameStarted() const;
    void notifyObserversGameEnded(GameEndType end_type) const;
    void notifyObserversTurnStarted() const;
    void notifyObserversTurnEnded() const;

};
