#pragma once

#include <memory>
#include <string>
#include "Player.h"
#include "BoardPresenter.h"
#include "GameOverChecker.h"
#include "GameState.h"
class GameObserver;


class GameManager {
	
public:
	GameManager();
	void startGame();
	void registerGameObserver(GameObserver *observer);

private:
	// state
	GameState current_state;
	std::unique_ptr<const Player> white_player;
	std::unique_ptr<const Player> black_player;

	// action classes
	std::unique_ptr<BoardPresenter> presenter;
	GameOverChecker gameOverChecker;

	// methods
	void runGameLoop();
	GameEndType isGameOver() const;
	std::shared_ptr<Move> getMove() const;
	const Player *getCurrentPlayer() const;
	std::shared_ptr<Move> getCurrentPlayersMove() const;
	bool validateMoveIsLegal(const Move &move) const;
	bool validateMoveIsSafe(const Move &move) const;
	std::shared_ptr<Move> getAnotherMove() const;

};
