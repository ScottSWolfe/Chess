#pragma once
#include "BoardPresenter.h"
#include "Square.h"
#include "Piece.h"

class ConsoleBoardPresenter : public BoardPresenter {
public:
	void displayBoard(Board board) override;

private:
	int getConsoleColor(SquareColor square_color, PieceColor piece_color);
	int getConsoleSquareColor(SquareColor color);
	int getConsolePieceColor(PieceColor color);
	const int WHITE = 0x0F;
	const int BLACK = 0x00;
	const int LIGHT = 0xE0;
	const int DARK  = 0x10;
};
