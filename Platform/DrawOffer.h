#pragma once

#include "PlayerAction.h"
class GameManager;

namespace chess {


class DrawOffer : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};


}
