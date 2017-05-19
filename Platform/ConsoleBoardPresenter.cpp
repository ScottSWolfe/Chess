#include <iostream>
#include <string>

#include "Board.h"
#include "ConsoleBoardPresenter.h"
#include "Piece.h"
#include "Square.h"
#include "windows.h"

using namespace std;


void ConsoleBoardPresenter::displayBoard(Board *board) {

	int dimension = board->getDimension();

	setTextColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	printVerticalBorder(dimension);
	cout << endl;

	for (int row = dimension - 1; row >= 0; --row) {

		setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
		cout << " " << row + 1 << " ";

		for (int col = 0; col < dimension; ++col) {
			Square *square = board->getSquare(col, row);
			Piece *piece = square->getPiece();

			string symbol = getPieceSymbol(piece);
			PieceColor piece_color = getPieceColor(piece);
			SquareColor square_color = square->getColor();

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

void ConsoleBoardPresenter::setTextColor(const ConsoleColor background_color, const ConsoleColor text_color) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int background = static_cast<int>(background_color) << 4;
	int text = static_cast<int>(text_color);
	SetConsoleTextAttribute(hstdout, background | text);
}

void ConsoleBoardPresenter::setTextColor(const SquareColor square_color, const PieceColor piece_color) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int background = getConsoleSquareColor(square_color) << 4;
	int text = getConsolePieceColor(piece_color);
	SetConsoleTextAttribute(hstdout, background | text);
}

int ConsoleBoardPresenter::getConsolePieceColor(PieceColor color) {
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

int ConsoleBoardPresenter::getConsoleSquareColor(SquareColor color) {
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

void ConsoleBoardPresenter::printVerticalBorder(const int dimension) {
	cout << "   ";
	for (int i = 0; i < dimension; ++i) {
		cout << " " << static_cast<char>('A' + i) << " ";
	}
	cout << "   ";
}
