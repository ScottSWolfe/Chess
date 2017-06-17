#pragma once

#include "PlayerAction.h"
class GameManager;


class Resignation : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};
