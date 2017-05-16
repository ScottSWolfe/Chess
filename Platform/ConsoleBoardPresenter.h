#pragma once
#include "BoardPresenter.h"

class ConsoleBoardPresenter : public BoardPresenter {
public:
	void displayBoard(Board board) override;
};
