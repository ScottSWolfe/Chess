#pragma once
#include "BoardPresenter.h"
#include "Square.h"
#include "Piece.h"

class ConsoleBoardPresenter : public BoardPresenter {
public:
	void displayBoard(Board board) override;
	void showAvailableColorCombinations();

private:
	int getConsoleColor(SquareColor square_color, PieceColor piece_color);
	int getConsoleSquareColor(SquareColor color);
	int getConsolePieceColor(PieceColor color);
	const int WHITE = 0x0F;
	const int BLACK = 0x0E;
	const int LIGHT = 0x40;
	const int DARK  = 0x00;
};
