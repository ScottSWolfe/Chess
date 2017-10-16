#include "BTREngine.h"
#include "GameState.h"

namespace chess {


std::shared_ptr<PlayerAction> BTREngine::getAction(const GameState &state) const {
    std::vector<Move> moves = state.getAvailableMoves();
    return std::make_shared<Move>(moves[0]);
}

PieceType BTREngine::getPromotionPiece(const GameState &state, const Move &move) const {
    return PieceType::QUEEN;
}


}
