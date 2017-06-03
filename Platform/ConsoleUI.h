#pragma once

#include <string>
#include "ConsoleBoardPresenter.h"
#include "StateObserver.h"


class ConsoleUI : public StateObserver {

public:
	void stateChanged(const GameState &newState) override;

private:
	ConsoleBoardPresenter presenter;
	bool isStartOfGame(const GameState &newState) const;
	std::string currentTurnToString(const GameState &newState) const;

};
