#include <iostream>
#include <vector>
#include "ChessDebug.h"
#include "Board.h"
#include "GameState.h"
#include "Move.h"
#include "Piece.h"
#include "Position.h"
using namespace std;


Board::Board(int board_dimension)
    : dimension(board_dimension)
{
    if (board_dimension < 6 || board_dimension > 99) {
        throw invalid_argument("board dimension is out of range");
    }
    for (int i = 0; i < dimension * dimension; ++i) {
        Square square(getSquareColorByIndex(i));
        squares.emplace_back(square);
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
    return make_shared<Board>(*this);
}

Square &Board::getSquare(Position pos) {
    return squares[getIndex(pos)];
}

const Square &Board::getSquare(Position pos) const {
    return squares[getIndex(pos)];
}

SquareColor Board::getSquareColor(Position pos) const {
    return getSquare(pos).getColor();
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
    unique_ptr<Piece> piece = removePieceFromSquare(move.getStart());
    addPieceToSquare(move.getEnd(), piece);
    applyMoveEffect(move.getEffect());
}

void Board::addPieceToSquare(Position pos, unique_ptr<Piece> &piece) {
    getSquare(pos).setPiece(piece);
}

unique_ptr<Piece> Board::removePieceFromSquare(Position pos) {
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

string Board::getPieceSymbol(Position pos) const {
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

bool Board::willKingBeInCheck(GameState &state, const Move &move) const {
    PieceColor turn_before_move_color = state.getCurrentPlayersTurn();
    state.makeMove(move);
    Position king_position = getKingPosition(turn_before_move_color);
    return canPieceAttackSquare(state, king_position, turn_before_move_color);
}

bool Board::isKingInCheck(const GameState &state) const {
    PieceColor king_color = state.getCurrentPlayersTurn();
    Position king_position = getKingPosition(king_color);
    return canPieceAttackSquare(state, king_position, king_color);
}

Position Board::getKingPosition(PieceColor king_color) const {
    for (int i = 0; i < dimension * dimension; i++) {
        if (squares[i].containsKing(king_color)) {
            return getPosition(i);
        }
    }
    throw runtime_error("no king found for given color");
}

bool Board::canPieceAttackSquare(const GameState &state, Position pos, PieceColor color) const {
    for (int i = 0; i < dimension * dimension; i++) {
        const Piece *piece = squares[i].getPiece();
        if (piece != nullptr && piece->getColor() != color) {
            vector<Position> attacks = piece->getSquaresAttacked(state, getPosition(i));
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

SquareColor Board::getSquareColorByIndex(int index) const {
    SquareColor color;
    Position pos = getPosition(index);
    if ((pos.x + pos.y) % 2 == 0) {
        color = SquareColor::DARK;
    }
    else {
        color = SquareColor::LIGHT;
    }
    return color;
}

void Board::throwExceptionIfPieceIsNull(const Piece *piece) const {
    if (piece == nullptr) {
        throw invalid_argument("square does not contain a piece");
    }
}
