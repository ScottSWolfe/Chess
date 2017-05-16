#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(const int new_dimension) {
	dimension = new_dimension;
	for (int i = 0; i < dimension * dimension; ++i) {
		Square square;
		squares.emplace_back(square);
	}
}

Square *Board::getSquare(const int x, const int y) {
	return &squares[convertCoordinatesToIndex(x, y)];
}

void Board::addPieceToSquare(const int x, const int y, Piece *piece) {
	squares[convertCoordinatesToIndex(x, y)].setPiece(piece);
}

void printVerticalLine(int dimension) {
	cout << " ";
	for (int i = 0; i < dimension; ++i) {
		cout << "----";
	}
}

void Board::printToConsole() {
	printVerticalLine(dimension);
	cout << endl;
	for (int row = dimension - 1; row >= 0; --row) {
		cout << "|";
		for (int col = 0; col < dimension; ++col) {
			getSquare(col, row)->printToConsole();
			cout << "|";
		}
		cout << endl;
		printVerticalLine(dimension);
		cout << endl;
	}
}

inline int Board::convertCoordinatesToIndex(const int x, const int y) {
	return y * dimension + x;
}
