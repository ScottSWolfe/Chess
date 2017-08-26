#pragma once

#include "PlayerAction.h"

namespace chess {

class GameManager;


class Claim50MoveDraw : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};


}
