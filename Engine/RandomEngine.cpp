#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "MoveValidator.h"
#include "PlayerAction.h"
#include "RandomEngine.h"

namespace chess {


RandomEngine::RandomEngine() {}

std::shared_ptr<PlayerAction> RandomEngine::getAction(const GameState &state) const {
    std::vector<Move> moves = state.getAvailableMoves();
    if (moves.size() < 1) {
        return nullptr;
    }
    int rand_num = randomInteger(moves.size() - 1);
    return std::make_shared<Move>(moves[rand_num]);
}

PieceType RandomEngine::getPromotionPiece(const GameState &state, const Move &move) const {
    const int num_piece_types = 6;
    int piece_type_num = randomInteger(num_piece_types - 1);
    PieceType piece_type = static_cast<PieceType>(piece_type_num);
    if (piece_type == PieceType::PAWN || piece_type == PieceType::KING) {
        piece_type = getPromotionPiece(state, move);
    }
    return piece_type;
}

int RandomEngine::randomInteger(int max_int) const {
    if (max_int < 1) {
        return 0;
    }
    return rand_int_device() % max_int;
}


}
