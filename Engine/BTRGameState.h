#pragma once

#include "GameState.h"

namespace chess {


class BTRGameState : public GameState {

public:
    BTRGameState(const GameState &state);
    int getRelativePieceValue() const;

private:
    int relative_piece_value;

};


}
