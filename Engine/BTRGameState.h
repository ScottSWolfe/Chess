#pragma once

#include "GameState.h"
#include "Move.h"

namespace chess {


class BTRGameState : public GameState {

public:
    BTRGameState(const BTRGameState &state);
    BTRGameState(const GameState &state);
    int getRelativePieceValue() const;
    void makeMove(const Move &move);

private:
    int relative_piece_value;

    void updateRelativePieceValue(const Move &move);

};


}
