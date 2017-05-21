#include <iostream>
#include <string>
#include "Board.h"
#include "ConsoleBoardPresenter.h"
#include "Piece.h"
#include "Square.h"
#include "windows.h"
using namespace std;


void ConsoleBoardPresenter::displayBoard(const Board &board) const {

	int dimension = board.getDimension();

	setTextColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	printVerticalBorder(dimension);
	cout << endl;

	for (int row = dimension - 1; row >= 0; --row) {

		setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
		cout << " " << row + 1 << " ";

		for (int col = 0; col < dimension; ++col) {
			const Square &square = board.getSquare(col, row);
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
		cout << " " << row + 1 << " ";
		cout << endl;
	}
	setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
	printVerticalBorder(dimension);

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

void ConsoleBoardPresenter::printVerticalBorder(int dimension) const {
	cout << "   ";
	for (int i = 0; i < dimension; ++i) {
		cout << " " << static_cast<char>('A' + i) << " ";
	}
	cout << "   ";
}
