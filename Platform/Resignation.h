#pragma once

#include "PlayerAction.h"
class GameManager;

namespace chess {


class Resignation : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};


}
