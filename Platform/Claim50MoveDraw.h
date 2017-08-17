#pragma once

#include "PlayerAction.h"
class GameManager;

namespace chess {


class Claim50MoveDraw : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};


}
