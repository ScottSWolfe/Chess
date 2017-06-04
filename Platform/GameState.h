#pragma once

#include <memory>
#include <vector>
#include "ChessEnums.h"
#include "Board.h"
#include "Move.h"
struct Position;
class GameObserver;


class GameState {

public:
    GameState(Board board, PieceColor beginning_player);
    GameState(const GameState &other);
    std::shared_ptr<GameState> getCopy() const;
    const Board &getBoard() const;
    int getBoardDimension() const;
    bool isPiece(Position pos) const;
    const Piece *getPiece(Position pos) const;
    PieceColor getPieceColor(Position pos) const;
    bool isMoveAvailable(const Move &move) const;
    bool willKingBeInCheck(const Move &move) const;
    bool isKingInCheck() const;
    Position getKingPosition(PieceColor king_color) const;
    void makeMove(const Move &move);
    void addMoveEffect(Move &move) const;
    bool isOppPieceColor(Position pos, PieceColor color) const;
    bool inBounds(Position pos) const;
    PieceColor getCurrentPlayersTurn() const;
    const Move *getLastMove() const;
    bool canCurrentPlayerMakeMove() const;
    std::vector<Move> getAvailableMoves() const;
    int get50MoveDrawCount() const;

private:
    Board board;
    PieceColor current_turn;
    std::vector<Move> move_history;
    int turns_since_capture_or_pawn_push;

    void changePlayersTurn();
    void incrementCaptureAndPawnCounter(const Move &move);

};
