#pragma once

class GameManager;

namespace chess {


class PlayerAction {

public:
    virtual bool enactAction(GameManager &manager) const = 0;

};


}
