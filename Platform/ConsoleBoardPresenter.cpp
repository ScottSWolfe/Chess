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
		cout << "----";
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

Color getPieceColor(Piece *piece) {
	if (piece == nullptr) {
		return Color::White;
	}
	else {
		return piece->getColor();
	}
}

void ConsoleBoardPresenter::displayBoard(Board board) {
	int dimension = board.getDimension();
	printVerticalLine(dimension);
	cout << endl;
	for (int row = dimension - 1; row >= 0; --row) {
		cout << "|";
		for (int col = 0; col < dimension; ++col) {
			Square *square = board.getSquare(col, row);
			Piece *piece = square->getPiece();

			string symbol = getPieceSymbol(piece);
			Color piece_color = getPieceColor(piece);
			SquareColor square_color = square->getColor();

			cout << " ";
			cout << symbol;
			cout << " ";
			cout << "|";
		}
		cout << endl;
		printVerticalLine(dimension);
		cout << endl;
	}
}

void tempFunctionToHoldCode() {
	// letting user close the application
	const WORD colors[] =
	{
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);


	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	// Tell the user how to stop
	// SetConsoleTextAttribute(hstdout, 0xEC);

	// Draw pretty colors
	for (WORD index = 0; index < sizeof(colors) / sizeof(colors[0]); ++index)
	{
		SetConsoleTextAttribute(hstdout, colors[index]);
		std::cout << "\t\t\t\t Hello World \t\t\t\t" << std::endl;
	}

	// Keep users happy
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}
