#pragma once

class GameState;

class StateObserver {

public:
	virtual void stateChanged(const GameState &newState) = 0;

};
