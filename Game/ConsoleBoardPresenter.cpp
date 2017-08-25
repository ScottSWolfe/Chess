#include <iostream>
#include <string>
#include "ChessDebug.h"
#include "Board.h"
#include "ConsoleBoardPresenter.h"
#include "Piece.h"
#include "Position.h"
#include "Square.h"
#include "windows.h"

namespace chess {


void ConsoleBoardPresenter::displayBoard(const Board &board) const {
    int dimension = board.getDimension();
    printHorizontalBorder(dimension);
    printRows(board);
    printHorizontalBorder(dimension);
    setTextColor(ConsoleColor::BLACK, ConsoleColor::WHITE);
}

void ConsoleBoardPresenter::printRows(const Board &board) const {
    int dimension = board.getDimension();
    for (int row = dimension - 1; row >= 0; --row) {
        printLeftBorder(row, dimension);
        printRow(board, row);
        printRightBorder(row, dimension);
        std::cout << std::endl;
    }
}

void ConsoleBoardPresenter::printRow(const Board &board, int row) const {
    int dimension = board.getDimension();
    for (int col = 0; col < dimension; ++col) {
        Position pos(col, row);
        std::string symbol = board.getPieceSymbol(pos);
        PieceColor piece_color = board.getPieceColor(pos);
        SquareColor square_color = getSquareColor(pos);
        setTextColor(square_color, piece_color);
        std::cout << " " << symbol << " ";
    }
}

SquareColor ConsoleBoardPresenter::getSquareColor(Position pos) const {
    if ((pos.x + pos.y) % 2 == 0) {
        return SquareColor::DARK;
    }
    else {
        return SquareColor::LIGHT;
    }
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
        return ConsoleBoardPresenter::NO_PIECE;
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
        throw std::invalid_argument("incorret color argument");
    }
}

void ConsoleBoardPresenter::printHorizontalBorder(int dimension) const {
    setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
    std::cout << borderSpacing(dimension);
    for (int i = 0; i < dimension; ++i) {
        std::cout << getLetterForIndex(i) << " ";
    }
    std::cout << borderSpacing(dimension) << std::endl;
}

void ConsoleBoardPresenter::printLeftBorder(int row, int dimension) const {
    setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
    if (dimension < 10 || row >= 9) {
        std::cout << " " << row + 1 << " ";
        return;
    }	
    std::cout << "  " << row + 1 << " ";
}

void ConsoleBoardPresenter::printRightBorder(int row, int dimension) const {
    setTextColor(BORDER_BACKGROUND, BORDER_TEXT);
    if (dimension < 10 || row >= 9) {
        std::cout << " " << row + 1 << " ";
        return;
    }
    std::cout << " " << row + 1 << "  ";
}

std::string ConsoleBoardPresenter::getLetterForIndex(int index) const {
    std::string letters;
    if (index > 25) {
        letters += index / 26 + 'A' - 1;
    }
    else {
        letters += ' ';
    }
    letters += index % 26 + 'A';
    return letters;
}

std::string ConsoleBoardPresenter::borderSpacing(int dimension) const {
    if (dimension > 9) {
        return "    ";
    }
    return "   ";
}


}
