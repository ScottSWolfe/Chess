#pragma once

#include "PlayerAction.h"
class GameManager;


class DrawOffer : public PlayerAction {

public:
    bool enactAction(GameManager &manager) const override;

};
