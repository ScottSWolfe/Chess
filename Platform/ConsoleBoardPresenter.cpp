#include <iostream>
#include <string>
#include "ChessDebug.h"
#include "Board.h"
#include "ConsoleBoardPresenter.h"
#include "Piece.h"
#include "Position.h"
#include "Square.h"
#include "windows.h"
using namespace std;


void ConsoleBoardPresenter::displayBoard(const Board &board) const {

	int dimension = board.getDimension();

	setTextColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	printHorizontalBorder(dimension);
	cout << endl;

	for (int row = dimension - 1; row >= 0; --row) {

		setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
		printLeftBorder(row, dimension);

		for (int col = 0; col < dimension; ++col) {
			const Square &square = board.getSquare(Position(col, row));
			const Piece *piece = square.getPiece();

			string symbol = getPieceSymbol(piece);
			PieceColor piece_color = getPieceColor(piece);
			SquareColor square_color = square.getColor();

			setTextColor(square_color, piece_color);
			cout << " ";
			cout << symbol;
			cout << " ";
		}
		setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
		printRightBorder(row, dimension);
		cout << endl;
	}
	setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
	printHorizontalBorder(dimension);

	setTextColor(ConsoleColor::BLACK, ConsoleColor::WHITE);
	cout << endl;
}

void ConsoleBoardPresenter::setTextColor(ConsoleColor background_color, ConsoleColor text_color) const {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int background = static_cast<int>(background_color) << 4;
	int text = static_cast<int>(text_color);
	SetConsoleTextAttribute(hstdout, background | text);
}

void ConsoleBoardPresenter::setTextColor(SquareColor square_color, PieceColor piece_color) const {
	ConsoleColor background = getConsoleSquareColor(square_color);
	ConsoleColor text = getConsolePieceColor(piece_color);
	setTextColor(background, text);
}

ConsoleColor ConsoleBoardPresenter::getConsolePieceColor(PieceColor color) const {
	if (color == PieceColor::WHITE) {
		return ConsoleBoardPresenter::WHITE_PIECE;
	}
	else if (color == PieceColor::BLACK) {
		return ConsoleBoardPresenter::BLACK_PIECE;
	}
	else {
		throw invalid_argument("incorret color argument");
	}
}

ConsoleColor ConsoleBoardPresenter::getConsoleSquareColor(SquareColor color) const {
	if (color == SquareColor::LIGHT) {
		return ConsoleBoardPresenter::LIGHT_SQUARE;
	}
	else if (color == SquareColor::DARK) {
		return ConsoleBoardPresenter::DARK_SQUARE;
	}
	else {
		throw invalid_argument("incorret color argument");
	}
}

void ConsoleBoardPresenter::printHorizontalBorder(int dimension) const {
	cout << borderSpacing(dimension);
	for (int i = 0; i < dimension; ++i) {
		cout << getLetterForIndex(i) << " ";
	}
	cout << borderSpacing(dimension);
}

void ConsoleBoardPresenter::printLeftBorder(int row, int dimension) const {
	if (dimension < 10 || row >= 9) {
		cout << " " << row + 1 << " ";
		return;
	}	
	cout << "  " << row + 1 << " ";	
}

void ConsoleBoardPresenter::printRightBorder(int row, int dimension) const {
	if (dimension < 10 || row >= 9) {
		cout << " " << row + 1 << " ";
		return;
	}
	cout << " " << row + 1 << "  ";
}

string ConsoleBoardPresenter::getLetterForIndex(int index) const {
	string letters;
	if (index > 25) {
		letters += index / 26 + 'A' - 1;
	}
	else {
		letters += ' ';
	}
	letters += index % 26 + 'A';
	return letters;
}

string ConsoleBoardPresenter::borderSpacing(int dimension) const {
	if (dimension > 9) {
		return "    ";
	}
	return "   ";
}
