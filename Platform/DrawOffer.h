#pragma once

#include "PlayerAction.h"

namespace chess {

class GameManager;


class DrawOffer : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};


}
