#pragma once

class Board;

class BoardPresenter {
public:
	virtual void displayBoard(Board *board) = 0;
};
