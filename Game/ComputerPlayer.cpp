#include "ComputerPlayer.h"
#include "GameState.h"

namespace chess {


ComputerPlayer::ComputerPlayer(PieceColor color, Engine *engine)
    : Player(color), engine(engine)
{}

std::shared_ptr<PlayerAction> ComputerPlayer::getAction(const GameState &state) const {
    return engine->getAction(state);
}

PieceType ComputerPlayer::getPromotionPiece(const GameState &state, const Move &move) const {
    return engine->getPromotionPiece(state, move);
}


}
