#include <string>
#include "ChessEnums.h"
#include "GameOverChecker.h"
#include "GameState.h"
#include "Move.h"
using namespace std;


GameEndType GameOverChecker::isGameOver(const GameState &state) const {
    GameEndType end_type = GameEndType::NOT_OVER;

    end_type = isMate(state);
    if (end_type != GameEndType::NOT_OVER) {
        return end_type;
    }

    end_type = have50MovesPassed(state);
    if (end_type != GameEndType::NOT_OVER) {
        return end_type;
    }

    return end_type;
}

GameEndType GameOverChecker::isMate(const GameState &state) const {
    if (state.canCurrentPlayerMakeMove() == true) {
        return GameEndType::NOT_OVER;
    }
    if (state.isKingInCheck() == false) {
        return GameEndType::STALEMATE;
    }
    return getCheckmateType(state.getCurrentPlayersTurn());
}

GameEndType GameOverChecker::getCheckmateType(PieceColor current_color) const {
    if (current_color == PieceColor::WHITE) {
        return GameEndType::BLACK_CHECKMATE;
    }
    return GameEndType::WHITE_CHECKMATE;
}

GameEndType GameOverChecker::have50MovesPassed(const GameState &state) const {
    if (state.get50MoveDrawCount() >= 50 * 2) {
        return GameEndType::DRAW_50_MOVES;
    }
    else {
        return GameEndType::NOT_OVER;
    }
}
