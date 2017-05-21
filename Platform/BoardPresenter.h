#pragma once

class Board;


class BoardPresenter {

public:
	virtual void displayBoard(const Board &board) const = 0;

};
