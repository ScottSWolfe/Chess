#pragma once

#include <memory>
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
	const Move GameManager::getPlayerMove() const;

};
