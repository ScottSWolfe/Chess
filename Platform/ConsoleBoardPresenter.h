#pragma once
#include "BoardPresenter.h"
#include "ChessEnums.h"
class Board;


enum class ConsoleColor { BLACK = 0x0, BLUE = 0x1, RED = 0x4, YELLOW = 0xE, WHITE = 0xF };

class ConsoleBoardPresenter : public BoardPresenter {

public:
	void displayBoard(const Board &board) const override;

private:
	void setTextColor(ConsoleColor background_color, ConsoleColor text_color) const;
	void setTextColor(SquareColor square_color, PieceColor piece_color) const;
	ConsoleColor getConsoleSquareColor(SquareColor color) const;
	ConsoleColor getConsolePieceColor(PieceColor color) const;
	void printVerticalBorder(int dimension) const;

	const ConsoleColor WHITE_PIECE = ConsoleColor::WHITE;
	const ConsoleColor BLACK_PIECE = ConsoleColor::YELLOW;
	const ConsoleColor LIGHT_SQUARE = ConsoleColor::RED;
	const ConsoleColor DARK_SQUARE = ConsoleColor::BLACK;
	const ConsoleColor BORDER_BACKGROUND = ConsoleColor::WHITE;
	const ConsoleColor BORDER_TEXT = ConsoleColor::BLACK;
};
