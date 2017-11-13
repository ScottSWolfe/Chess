#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Square.h"

namespace chess {

class GameState;
class MoveEffect;
class Piece;
class PieceIterator;
struct Position;


class Board {

public:
    Board(int board_dimension);
    Board(const Board &other_board);
    bool inBounds(Position pos) const;
    bool hasPieceMoved(Position pos) const;
    void makeMove(const Move &move);
    void addPieceToSquare(Position pos, std::unique_ptr<Piece> &piece);
    std::unique_ptr<Piece> removePieceFromSquare(Position pos);
    bool isPiece(Position pos) const;
    const Piece *getPiece(Position pos) const;
    PieceColor getPieceColor(Position pos) const;
    std::string getPieceSymbol(Position pos) const;
    PieceType getPieceType(Position pos) const;
    bool isOppPieceColor(Position pos, PieceColor color) const;
    void setPiece(Position pos, std::unique_ptr<Piece> &piece);
    bool isKingInCheck(PieceColor king_color) const;
    bool willKingBeInCheck(PieceColor king_color, const Move &move) const;
    bool canPieceAttackSquare(Position pos, PieceColor color) const;
    int getDimension() const;
    PieceIterator getPieceIterator(PieceColor color) const;


private:
    const int dimension;
    std::vector<Square> squares;

    Square &getSquare(Position pos);
    const Square &getSquare(Position pos) const;
    int getIndex(Position pos) const;
    Position getPosition(int index) const;
    void applyMoveEffect(const MoveEffect *effect);
    Position getKingPosition(PieceColor king_color) const;
    bool areCellsInSameLine(const Position &pos1, const Position &pos2) const;
    bool areCellsInSameDiagonal(const Position &pos1, const Position &pos2) const;
    bool isKingAttacked(const Position &king_position, const Move &move,
                        void getDeltas(const Position &pos_a, const Position &pos_b, int &x_delta, int &y_delta),
                        bool doesPieceAttackCorrectly(const Piece *piece)) const;
    bool isKingAttacked(const Position &king_position, const Move &move, int x_delta, int y_delta,
                        bool doesPieceAttackCorrectly(const Piece *piece)) const;
    bool isKingAttackedAfterKingMoves(const Move &move, PieceColor king_color) const;
    bool isPieceThreatToKing(const Piece *piece, PieceColor king_color,
                             bool doesPieceAttackCorrectly(const Piece *piece)) const;
    static void getLineDeltas(const Position &pos_a, const Position &pos_b, int &x_delta, int &y_delta);
    static void getDiagonalDeltas(const Position &pos_a, const Position &pos_b, int &x_delta, int &y_delta);

};


}
