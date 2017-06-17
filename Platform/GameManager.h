#pragma once

#include <memory>
#include <string>
#include "GameObserver.h"
#include "GameState.h"
#include "GameSubject.h"
#include "Player.h"
class BoardPresenter;
class GameObserver;
class Move;
class PlayerAction;
enum class PieceType;


class GameManager : public GameSubject {
    
public:
    GameManager();
    void startGame();
    bool makeMove(Move move);
    bool resign();
    bool offerDraw();
    bool claimDraw();
    void registerObserver(GameObserver *observer);

private:
    // fields
    GameState current_state;
    std::unique_ptr<const Player> white_player;
    std::unique_ptr<const Player> black_player;
    std::vector<GameObserver*> observers;
    std::unique_ptr<BoardPresenter> presenter;

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
    void notifyObserversGameEnded() const;
    void notifyObserversTurnStarted() const;
    void notifyObserversTurnEnded() const;

};
