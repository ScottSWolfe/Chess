#include <memory>
#include "ChessDebug.h"
#include "GameState.h"
#include "MoveEffect.h"
#include "Piece.h"
#include "Position.h"
#include "GameObserver.h"
using namespace std;


GameState::GameState(Board board, PieceColor beginning_player) : 
    board(board),
    current_turn(beginning_player),
    turns_since_capture_or_pawn_push(0)
{}

GameState::GameState(const GameState &other)
    : board(other.board), current_turn(other.current_turn),
    turns_since_capture_or_pawn_push(other.turns_since_capture_or_pawn_push)
{
    for (Move move : other.move_history) {
        move_history.push_back(move);
    }
}

shared_ptr<GameState> GameState::getCopy() const {
    return make_shared<GameState>(*this);
}

const Board &GameState::getBoard() const {
    return board;
}

int GameState::getBoardDimension() const {
    return board.getDimension();
}

bool GameState::isPiece(Position pos) const {
    return board.isPiece(pos);
}

const Piece *GameState::getPiece(Position pos) const {
    return board.getPiece(pos);
}

PieceColor GameState::getPieceColor(Position pos) const {
    return board.getPieceColor(pos);
}

PieceType GameState::getPieceType(Position pos) const {
    return board.getPieceType(pos);
}

bool GameState::isMoveAvailable(const Move &move) const {
    const Piece *piece = board.getPiece(move.getStart());
    vector<Move> moves = piece->getAvailableMoves(*this, move.getStart());
    for (Move curr_move : moves) {
        if (curr_move == move) {
            return true;
        }
    }
    return false;
}

bool GameState::willKingBeInCheck(const Move &move) const {
    shared_ptr<GameState> copy_of_state = this->getCopy();
    return copy_of_state->board.willKingBeInCheck(*copy_of_state, move);
}

bool GameState::isKingInCheck() const {
    return board.isKingInCheck(*this);
}

Position GameState::getKingPosition(PieceColor king_color) const {
    return board.getKingPosition(king_color);
}

void GameState::makeMove(const Move &move) {
    incrementCaptureAndPawnCounter(move);
    board.makeMove(move);
    move_history.push_back(move);
    changePlayersTurn();
}

std::unique_ptr<Piece> GameState::removePieceFromSquare(Position pos) {
    return board.removePieceFromSquare(pos);
}

void GameState::addPieceToSquare(Position pos, std::unique_ptr<Piece> &piece) {
    board.addPieceToSquare(pos, piece);
}

void GameState::addMoveEffect(Move &move) const {
    if (move.getEffect() != nullptr) {
        return;
    }
    const Piece *piece = getPiece(move.getStart());
    piece->addMoveEffect(*this, move);
}

const Move *GameState::getLastMove() const {
    if (move_history.empty()) {
        return nullptr;
    }
    return &move_history.back();
}

vector<Move> GameState::getAvailableMoves() const {
    vector<Move> moves;
    PieceColor current_color = getCurrentPlayersTurn();
    int dimension = getBoardDimension();
    for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension; i++) {
            Position pos(i, j);
            if (board.isPiece(pos) && board.getPieceColor(pos) == current_color) {
                vector<Move> pieces_moves = board.getPiece(pos)->getAvailableMoves(*this, pos);
                moves.insert(moves.end(), pieces_moves.begin(), pieces_moves.end());
            }
        }
    }
    return moves;
}

bool GameState::canCurrentPlayerMakeMove() const {
    int dimension = getBoardDimension();
    for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension; i++) {
            Position pos(i, j);
            if (board.isPiece(pos) && board.getPieceColor(pos) == current_turn) {
                if (board.getPiece(pos)->canPieceMakeMove(*this, pos) == true) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GameState::isOppPieceColor(Position pos, PieceColor color) const {
    return board.isOppPieceColor(pos, color);
}

bool GameState::inBounds(Position pos) const {
    return board.inBounds(pos);
}

bool GameState::hasPieceMoved(Position pos) const {
    return board.hasPieceMoved(pos);
}

PieceColor GameState::getCurrentPlayersTurn() const {
    return current_turn;
}

int GameState::get50MoveDrawCount() const {
    return turns_since_capture_or_pawn_push;
}

void GameState::changePlayersTurn() {
    if (current_turn == PieceColor::WHITE) {
        current_turn = PieceColor::BLACK;
    }
    else {
        current_turn = PieceColor::WHITE;
    }
}

void GameState::incrementCaptureAndPawnCounter(const Move &move) {
    // if pawn is being moved
    Position start = move.getStart();
    if (board.isPiece(start) && board.getPieceSymbol(start) == Piece::PAWN_SYMBOL) {
        turns_since_capture_or_pawn_push = 0;
        return;
    }

    // if piece is being captured
    Position end = move.getEnd();
    const MoveEffect *effect = move.getEffect();
    if (board.isPiece(end) && (effect == nullptr || effect->getType() != MoveEffectType::CASTLE)) {
        turns_since_capture_or_pawn_push = 0;
        return;
    }

    turns_since_capture_or_pawn_push++;
}
