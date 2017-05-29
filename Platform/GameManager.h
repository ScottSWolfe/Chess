#pragma once

#include <memory>
#include <string>
#include "Player.h"
#include "BoardPresenter.h"
#include "GameState.h"


class GameManager {
	
public:
	GameManager();
	void startGame();

private:
	// variables
	GameState current_state;
	std::unique_ptr<const Player> white_player;
	std::unique_ptr<const Player> black_player;
	std::unique_ptr<BoardPresenter> presenter;

	// methods
	void runGameLoop();
	const Player *GameManager::getCurrentPlayer() const;
	std::shared_ptr<Move> GameManager::getPlayerMove() const;
	std::string playerTurnToString() const;

};
