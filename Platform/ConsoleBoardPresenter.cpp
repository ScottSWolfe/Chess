#include "ConsoleBoardPresenter.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

void printVerticalLine(int dimension) {
	cout << " ";
	for (int i = 0; i < dimension; ++i) {
		cout << "---";
	}
}

string getPieceSymbol(Piece *piece) {
	if (piece == nullptr) {
		return " ";
	}
	else {
		return piece->getSymbol();
	}
}

PieceColor getPieceColor(Piece *piece) {
	if (piece == nullptr) {
		return PieceColor::WHITE;
	}
	else {
		return piece->getColor();
	}
}

void ConsoleBoardPresenter::displayBoard(Board board) {

	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	int dimension = board.getDimension();
	printVerticalLine(dimension);
	cout << endl;
	for (int row = dimension - 1; row >= 0; --row) {
		cout << "|";
		for (int col = 0; col < dimension; ++col) {
			Square *square = board.getSquare(col, row);
			Piece *piece = square->getPiece();

			string symbol = getPieceSymbol(piece);
			PieceColor piece_color = getPieceColor(piece);
			SquareColor square_color = square->getColor();

			SetConsoleTextAttribute(hstdout, getConsoleColor(square_color, piece_color));
			cout << " ";
			cout << symbol;
			cout << " ";

			SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			//cout << "|";
		}
		cout << "|";
		cout << endl;

		// Keep users happy
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	}
	printVerticalLine(dimension);

}

int ConsoleBoardPresenter::getConsolePieceColor(PieceColor color) {
	if (color == PieceColor::WHITE) {
		return ConsoleBoardPresenter::WHITE;
	}
	else if (color == PieceColor::BLACK) {
		return ConsoleBoardPresenter::BLACK;
	}
	else {
		throw invalid_argument("incorret color argument");
	}
}

int ConsoleBoardPresenter::getConsoleSquareColor(SquareColor color) {
	if (color == SquareColor::LIGHT) {
		return ConsoleBoardPresenter::LIGHT;
	}
	else if (color == SquareColor::DARK) {
		return ConsoleBoardPresenter::DARK;
	}
	else {
		throw invalid_argument("incorret color argument");
	}
}

int ConsoleBoardPresenter::getConsoleColor(SquareColor square_color, PieceColor piece_color) {
	return getConsoleSquareColor(square_color) | getConsolePieceColor(piece_color);
}

void ConsoleBoardPresenter::showAvailableColorCombinations() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	for (int k = 1; k < 255; k++)
	{
		SetConsoleTextAttribute(hstdout, k);
		cout << k << " Color Color Color Color Color " << endl;
	}

	SetConsoleTextAttribute(hstdout, csbi.wAttributes);

	system("pause");
}