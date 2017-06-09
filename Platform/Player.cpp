#include "ChessDebug.h"
#include "Player.h"


Player::Player(PieceColor piece_color)
    : color(piece_color)
{}

PieceType Player::getPromotionPiece(const GameState &state, const Move &move) const {
    return PieceType::QUEEN;
}
