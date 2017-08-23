#include <iostream>
#include <vector>
#include "Board.h"
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Piece.h"
#include "Position.h"

namespace chess {


Board::Board(int board_dimension)
    : dimension(board_dimension)
{
    if (board_dimension < 6 || board_dimension > 99) {
        throw std::invalid_argument("board dimension is out of range");
    }
    squares.reserve(dimension * dimension);
    for (int i = 0; i < dimension * dimension; ++i) {
        Square square;
        squares.push_back(square);
    }
}

Board::Board(const Board &other_board) :
    dimension(other_board.getDimension())
{
    for (int i = 0; i < dimension * dimension; ++i) {
        squares.emplace_back(other_board.squares[i]);
    }
}

std::shared_ptr<Board> Board::getCopy() const {
    return std::make_shared<Board>(*this);
}

Square &Board::getSquare(Position pos) {
    return squares[getIndex(pos)];
}

const Square &Board::getSquare(Position pos) const {
    return squares[getIndex(pos)];
}

bool Board::inBounds(Position pos) const {
    if (pos.x < 0 || pos.x >= dimension) {
        return false;
    }
    if (pos.y < 0 || pos.y >= dimension) {
        return false;
    }
    return true;
}

bool Board::hasPieceMoved(Position pos) const {
    return getSquare(pos).hasPieceMoved();
}

void Board::makeMove(const Move &move) {
    auto piece = removePieceFromSquare(move.getStart());
    addPieceToSquare(move.getEnd(), piece);
    applyMoveEffect(move.getEffect());
}

void Board::addPieceToSquare(Position pos, std::unique_ptr<Piece> &piece) {
    getSquare(pos).setPiece(piece);
}

std::unique_ptr<Piece> Board::removePieceFromSquare(Position pos) {
    return getSquare(pos).removePiece();
}

void Board::applyMoveEffect(const MoveEffect *effect) {
    if (effect == nullptr) {
        return;
    }
    effect->applyEffect(*this);
}

bool Board::isPiece(Position pos) const {
    if (getPiece(pos) == nullptr) {
        return false;
    }
    return true;
}

const Piece *Board::getPiece(Position pos) const {
    return getSquare(pos).getPiece();
}

PieceColor Board::getPieceColor(Position pos) const {
    return Piece::getPieceColor(getPiece(pos));
}

std::string Board::getPieceSymbol(Position pos) const {
    return Piece::getPieceSymbol(getPiece(pos));
}

PieceType Board::getPieceType(Position pos) const {
    return getSquare(pos).getPieceType();
}

bool Board::isOppPieceColor(Position pos, PieceColor color) const {
    if (getPieceColor(pos) == PieceColor::NO_PIECE) {
        return false;
    }
    return getPieceColor(pos) != color;
}

void Board::setPiece(Position pos, std::unique_ptr<Piece> &piece) {
    getSquare(pos).setPiece(piece);
}

bool Board::isKingInCheck(PieceColor king_color) const {
    Position king_position = getKingPosition(king_color);
    return canPieceAttackSquare(king_position, king_color);
}

Position Board::getKingPosition(PieceColor king_color) const {
    for (int i = 0; i < dimension * dimension; i++) {
        if (squares[i].containsKing(king_color)) {
            return getPosition(i);
        }
    }
    throw std::runtime_error("no king found for given color");
}

bool Board::canPieceAttackSquare(Position pos, PieceColor color) const {
    for (int i = 0; i < dimension * dimension; i++) {
        const Piece *piece = squares[i].getPiece();
        if (piece != nullptr && piece->getColor() != color) {
            std::vector<Position> attacks = piece->getSquaresAttacked(*this, getPosition(i));
            for (Position end : attacks) {
                if (end == pos) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Board::getDimension() const {
    return dimension;
}

int Board::getIndex(Position pos) const {
    return pos.y * dimension + pos.x;
}

Position Board::getPosition(int index) const {
    return Position(index % dimension, index / dimension);
}


}
