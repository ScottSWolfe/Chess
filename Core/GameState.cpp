#include <memory>
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "MoveEffect.h"
#include "MoveValidator.h"
#include "Piece.h"
#include "PieceIterator.h"
#include "Position.h"

namespace chess {


GameState::GameState(Board board, PieceColor beginning_player) : 
    board(board),
    current_turn(beginning_player),
    game_over_state(GameEndType::NOT_OVER)
{}

GameState::GameState(const GameState &other)
    : board(other.board), current_turn(other.current_turn), game_over_state(other.game_over_state),
    move_history(other.move_history),
    turns_with_capture_or_pawn_push(other.turns_with_capture_or_pawn_push)//,
    //captured_pieces(other.captured_pieces)
{
    /*
    move_history.reserve(other.move_history.size());
    for (Move move : other.move_history) {
        move_history.push_back(move);
    }
    */
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
    std::vector<Move> moves = piece->getAvailableMoves(*this, move.getStart());
    for (Move curr_move : moves) {
        if (curr_move == move) {
            return true;
        }
    }
    return false;
}

bool GameState::willKingBeInCheck(const Move &move) const {
    return board.willKingBeInCheck(current_turn, move);
}

bool GameState::isKingInCheck() const {
    return board.isKingInCheck(current_turn);
}

bool GameState::isSquareAttacked(Position pos, PieceColor color) const {
    return board.canPieceAttackSquare(pos, color);
}

void GameState::makeMove(const Move &move) {
    updateCaptureAndPawnPushTurns(move);
    auto captured_piece = board.makeMove(move, getCurrentTurnNumber());
    if (captured_piece.get()) {
        captured_pieces[getCurrentTurnNumber()] = std::move(captured_piece);
    }
    move_history.push_back(move);
    changePlayersTurn();
    updateGameOverState();
}

void GameState::undoLastMove() {
    if (move_history.empty()) {
        throw std::runtime_error("no moves to undo");
    }
    game_over_state = GameEndType::NOT_OVER;
    changePlayersTurn();
    Move move = move_history.back();
    move_history.pop_back();
    board.undoMove(move, getAndRemoveCapturedPiece(getCurrentTurnNumber()), getCurrentTurnNumber());
    undoCaptureAndPawnPushTurnsUpdate();
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

std::vector<Move> GameState::getAvailableMoves() const {
    std::vector<Move> moves = collectMoves();
    eliminateMovesThatPutKingInCheck(moves);
    return moves;
}

std::vector<Move> GameState::collectMoves() const {
    std::vector<Move> moves;
    PieceColor current_color = getCurrentPlayersTurn();
    int dimension = getBoardDimension();
    for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension; i++) {
            Position pos(i, j);
            if (board.isPiece(pos) && board.getPieceColor(pos) == current_color) {
                std::vector<Move> pieces_moves = board.getPiece(pos)->getAvailableMoves(*this, pos);
                moves.insert(moves.end(), pieces_moves.begin(), pieces_moves.end());
            }
        }
    }
    return moves;
}

void GameState::eliminateMovesThatPutKingInCheck(std::vector<Move> &moves) const {
    for (size_t i = 0; i < moves.size(); i++) {
        Move move = moves[i];
        if (willKingBeInCheck(move) == true) {
            moves.erase(moves.begin() + i);
            i--;
        }
    }
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

PieceIterator GameState::getPieceIterator(PieceColor color) const {
    return board.getPieceIterator(color);
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

bool GameState::isGameOver() const {
    if (game_over_state != GameEndType::NOT_OVER) {
        return true;
    }
    return false;
}

void GameState::updateGameOverState() {
    if (game_over_state != GameEndType::NOT_OVER) {
        return;
    }
    if (isMate()) {
        mate();
    }
}

bool GameState::isMate() const {
    return !canCurrentPlayerMakeMove();
}

bool GameState::have50MovesPassed() const {
    if (turns_with_capture_or_pawn_push.empty()) {
        return false;
    }
    int last_capture_or_pawn_push_turn = turns_with_capture_or_pawn_push.back();
    int turns_since_capture_or_pawn_push = getCurrentTurnNumber() - last_capture_or_pawn_push_turn;
    if (turns_since_capture_or_pawn_push >= 50 * 2) {
        return true;
    }
    return false;
}

void GameState::mate() {
    if (isKingInCheck() == false) {
        game_over_state = GameEndType::STALEMATE;
    }

    if (current_turn == PieceColor::WHITE) {
        game_over_state = GameEndType::BLACK_CHECKMATE;
    }
    else {
        game_over_state = GameEndType::WHITE_CHECKMATE;
    }
}

void GameState::resignation() {
    if (current_turn == PieceColor::WHITE) {
        game_over_state = GameEndType::WHITE_RESIGN;
    }
    else {
        game_over_state = GameEndType::BLACK_RESIGN;
    }
}

void GameState::drawByAgreement() {
    game_over_state = GameEndType::DRAW_AGREEMENT;
}

bool GameState::drawBy50Moves() {
    if (have50MovesPassed() == true) {
        game_over_state = GameEndType::DRAW_50_MOVES;
        return true;
    }
    return false;
}

void GameState::drawByRepetition() {
    game_over_state = GameEndType::DRAW_3_REPITITIONS;
}

GameEndType GameState::getGameOverState() const {
    return game_over_state;
}

void GameState::changePlayersTurn() {
    if (current_turn == PieceColor::WHITE) {
        current_turn = PieceColor::BLACK;
    }
    else {
        current_turn = PieceColor::WHITE;
    }
}

void GameState::updateCaptureAndPawnPushTurns(const Move &move) {
    // if pawn is being moved
    Position start = move.getStart();
    if (board.isPiece(start) && board.getPieceSymbol(start) == Piece::PAWN_SYMBOL) {
        turns_with_capture_or_pawn_push.push_back(getCurrentTurnNumber());
        return;
    }

    // if piece is being captured
    Position end = move.getEnd();
    const MoveEffect *effect = move.getEffect();
    if (board.isPiece(end) && (effect == nullptr || effect->getType() != MoveEffectType::CASTLE)) {
        turns_with_capture_or_pawn_push.push_back(getCurrentTurnNumber());
        return;
    }
}

void GameState::undoCaptureAndPawnPushTurnsUpdate() {
    if (turns_with_capture_or_pawn_push.empty()) {
        return;
    }
    if (turns_with_capture_or_pawn_push.back() == getCurrentTurnNumber()) {
        turns_with_capture_or_pawn_push.pop_back();
    }
}

int GameState::getCurrentTurnNumber() const {
    return move_history.size() + 1;
}

std::unique_ptr<Piece> GameState::getAndRemoveCapturedPiece(int turn_number) {
    std::unique_ptr<Piece> piece;
    auto map_iter = captured_pieces.find(turn_number);
    if (map_iter != captured_pieces.end()) {
        piece = std::move(map_iter->second);
        captured_pieces.erase(map_iter);
    }
    return std::move(piece);
}


}
