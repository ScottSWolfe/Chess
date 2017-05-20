#pragma once

#include "GameState.h"


class GameManager {
	
public:
	GameManager();
	void startGame();

private:
	GameState current_state;
	void setup();
	void runGameLoop();
	void cleanup();

};
