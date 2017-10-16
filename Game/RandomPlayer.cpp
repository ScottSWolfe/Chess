#include <random>
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "MoveValidator.h"
#include "PlayerAction.h"
#include "RandomPlayer.h"

namespace chess {


RandomPlayer::RandomPlayer(PieceColor color)
    : Player(color)
{}

std::shared_ptr<PlayerAction> RandomPlayer::getAction(const GameState &state) const {
    return engine.getAction(state);
}

PieceType RandomPlayer::getPromotionPiece(const GameState &state, const Move &move) const {
    return engine.getPromotionPiece(state, move);
}


}
