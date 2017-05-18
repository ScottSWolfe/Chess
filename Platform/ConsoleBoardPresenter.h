#pragma once
#include "BoardPresenter.h"
#include "Square.h"
#include "Piece.h"

enum class ConsoleColor { BLACK = 0x0, BLUE = 0x1, RED = 0x4, YELLOW = 0xE, WHITE = 0xF };

class ConsoleBoardPresenter : public BoardPresenter {

public:
	void displayBoard(Board board) override;

private:
	void setTextColor(const ConsoleColor background_color, const ConsoleColor text_color);
	void setTextColor(const SquareColor square_color, const PieceColor piece_color);
	int getConsoleSquareColor(const SquareColor color);
	int getConsolePieceColor(const PieceColor color);
	void printVerticalBorder(const int dimension);

	const int WHITE_PIECE = static_cast<int>(ConsoleColor::WHITE);
	const int BLACK_PIECE = static_cast<int>(ConsoleColor::YELLOW);
	const int LIGHT_SQUARE = static_cast<int>(ConsoleColor::RED);
	const int DARK_SQUARE = static_cast<int>(ConsoleColor::BLACK);

	const ConsoleColor BORDER_BACKGROUND = ConsoleColor::WHITE;
	const ConsoleColor BORDER_TEXT = ConsoleColor::BLACK;
};
