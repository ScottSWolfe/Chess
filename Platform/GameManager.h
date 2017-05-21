#pragma once

#include <memory>
#include "BoardPresenter.h"
#include "GameState.h"


class GameManager {
	
public:
	GameManager();
	void startGame();

private:
	GameState current_state;
	std::unique_ptr<BoardPresenter> presenter;
	void setup();
	void runGameLoop();
	void cleanup();

};
