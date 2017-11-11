#include <cmath>
#include <iostream>
#include <vector>
#include "Board.h"
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Piece.h"
#include "PieceIterator.h"
#include "Position.h"

namespace chess {


Board::Board(int board_dimension)
    : dimension(board_dimension)
{
    if (board_dimension < 6 || board_dimension > 99) {
        throw std::invalid_argument("board dimension is out of range");
    }
    const int num_squares = dimension * dimension;
    squares.reserve(num_squares);
    for (int i = 0; i < num_squares; ++i) {
        squares.push_back(Square());
    }
}

Board::Board(const Board &other_board) :
    dimension(other_board.getDimension())
{
    squares = other_board.squares;
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

bool Board::willKingBeInCheck(PieceColor king_color, const Move &move) const {
    Position king_position = getKingPosition(king_color);
    Position move_position = move.getStart();
    if (king_position == move_position) {
        return isKingAttackedAfterKingMoves(move, king_color);
    }
    if (areCellsInSameLine(king_position, move_position)) {
        if (isKingAttacked(king_position, move, getLineDeltas, Piece::doesPieceAttackInLine)) {
            return true;
        }
    }
    else if (areCellsInSameDiagonal(king_position, move_position)) {
        if (isKingAttacked(king_position, move, getDiagonalDeltas, Piece::doesPieceAttackInDiagonal)) {
            return true;
        }
    }
    return false;
}

bool Board::areCellsInSameLine(const Position &pos1, const Position &pos2) const {
    if (pos1.x == pos2.x) {
        return true;
    }
    if (pos1.y == pos2.y) {
        return true;
    }
    return false;
}

bool Board::areCellsInSameDiagonal(const Position &pos1, const Position &pos2) const {
    int x_diff = std::abs(pos1.x - pos2.x);
    int y_diff = std::abs(pos1.y - pos2.y);
    if (x_diff == y_diff) {
        return true;
    }
    return false;
}

bool Board::isKingAttacked(const Position &king_position, const Move &move,
                           void getDeltas(const Position &pos_a, const Position &pos_b, int &x_delta, int &y_delta),
                           bool doesPieceAttackCorrectly(const Piece *piece)) const
{
    Position move_start = move.getStart();
    int x_delta, y_delta;
    getDeltas(king_position, move_start, x_delta, y_delta);
    return isKingAttacked(king_position, move, x_delta, y_delta, doesPieceAttackCorrectly);
}

bool Board::isKingAttacked(const Position &king_position, const Move &move, int x_delta, int y_delta,
                           bool doesPieceAttackCorrectly(const Piece *piece)) const
{
    Position move_start = move.getStart();
    Position move_end = move.getStart();
    Position current = king_position;
    while (inBounds(current)) {
        if (isPiece(current) && current != move_start) {
            if (isPieceThreatToKing(getPiece(current), getPieceColor(king_position), doesPieceAttackCorrectly)) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (current == move_end) {
            return false;
        }
        current.add(x_delta, y_delta);
    }
    return false;
}

bool Board::isPieceThreatToKing(const Piece *piece, PieceColor king_color,
                                bool doesPieceAttackCorrectly(const Piece *piece)) const
{
    if (doesPieceAttackCorrectly(piece)) {
        if (piece->getColor() != king_color) {
            return true;
        }
    }
    return false;
}

bool Board::isKingAttackedAfterKingMoves(const Move &move, PieceColor king_color) const {
    Board copy_of_board(*this);
    copy_of_board.makeMove(move);
    return copy_of_board.canPieceAttackSquare(move.getEnd(), king_color);
}

void Board::getLineDeltas(const Position &pos_a, const Position &pos_b, int &x_delta, int &y_delta) {
    x_delta = 0;
    y_delta = 0;
    if (pos_a.x == pos_b.x) {
        if (pos_a.y < pos_b.y) {
            y_delta = 1;
        }
        else {
            y_delta = -1;
        }
    }
    else if (pos_a.y == pos_b.y) {
        if (pos_a.x < pos_b.x) {
            x_delta = 1;
        }
        else {
            x_delta = -1;
        }
    }
}

void Board::getDiagonalDeltas(const Position &pos_a, const Position &pos_b, int &x_delta, int &y_delta) {
    x_delta = 0;
    y_delta = 0;
    
    if (pos_a.y < pos_b.y) {
        y_delta = 1;
    }
    else {
        y_delta = -1;
    }
    
    if (pos_a.x < pos_b.x) {
        x_delta = 1;
    }
    else {
        x_delta = -1;
    }
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

PieceIterator Board::getPieceIterator(PieceColor color) const {
    return PieceIterator(*this, color);
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
