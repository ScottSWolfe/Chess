#pragma once

#include <unordered_map>
#include <memory>
#include <utility>
#include <vector>
#include "Board.h"
#include "CastlingAvailability.h"
#include "Move.h"
#include "Piece.h"

namespace chess {

class GameObserver;
class PieceIterator;
struct Position;


enum class GameEndType {
    WHITE_CHECKMATE, BLACK_CHECKMATE, WHITE_RESIGN, BLACK_RESIGN,
    DRAW_AGREEMENT, DRAW_50_MOVES, DRAW_3_REPITITIONS, STALEMATE,
    NOT_OVER
};

class GameState {

private:
    // Necessary for maintaining complete game state history
    Board board;
    PieceColor current_turn;
    std::vector<Move> move_history;
    std::unordered_map<int, std::unique_ptr<Piece>> captured_pieces; // map from half-move number to captured piece

    // Helpful for optimizing processing
    GameEndType game_over_state;
    CastlingAvailability castling_availability;
    std::vector<std::pair<int, CastlingAvailability>> castling_ability_changes; // stack with half-move number to castling ability for half-moves just before castling availability changed
    std::vector<int> turns_with_capture_or_pawn_push;
    Position white_king_pos;
    Position black_king_pos;

public:
    GameState(Board board, PieceColor beginning_player);
    GameState(const GameState &other);
    const Board &getBoard() const;
    int getBoardDimension() const;
    bool isPiece(Position pos) const;
    const Piece *getPiece(Position pos) const;
    PieceColor getPieceColor(Position pos) const;
    PieceType getPieceType(Position pos) const;
    bool isMoveAvailable(const Move &move) const;
    bool willKingBeInCheck(const Move &move) const;
    bool isKingInCheck() const;
    bool isCastlingAvailable() const;
    bool isCastlingAvailableKingside() const;
    bool isCastlingAvailableQueenside() const;
    bool isSquareAttacked(Position pos, PieceColor color) const;
    void makeMove(const Move &move);
    void undoLastMove();
    std::unique_ptr<Piece> removePieceFromSquare(Position pos);
    void addPieceToSquare(Position pos, std::unique_ptr<Piece> &piece);
    void addMoveEffect(Move &move) const;
    bool isOppPieceColor(Position pos, PieceColor color) const;
    bool inBounds(Position pos) const;
    PieceColor getCurrentPlayersTurn() const;
    const Move *getLastMove() const;
    bool canCurrentPlayerMakeMove() const;
    std::vector<Move> getAvailableMoves() const;
    PieceIterator getPieceIterator(PieceColor color) const;
    GameEndType getGameOverState() const;
    bool didWhiteWin() const;
    bool didBlackWin() const;
    bool isDraw() const;
    bool isGameOver() const;
    void resignation();
    void drawByAgreement();
    bool drawBy50Moves();
    void drawByRepetition();

private:
    void changePlayersTurn();
    void updateCaptureAndPawnPushTurns(const Move &move);
    void undoCaptureAndPawnPushTurnsUpdate();
    void updateCastlingAvailability(const Move &move);
    void undoCastlingAvailabilityUpdate();
    void updateKingPosition(const Move &move);
    void undoKingPositionUpdate(const Move &move);
    int getCurrentTurnNumber() const;
    Position getActiveColorKingPosition() const;
    std::unique_ptr<Piece> getAndRemoveCapturedPiece(int turn_number);
    void updateGameOverState();

    bool isMate() const;
    bool have50MovesPassed() const;
    void mate();

    std::vector<Move> collectMoves() const;
    void eliminateMovesThatPutKingInCheck(std::vector<Move> &moves) const;

};


}
