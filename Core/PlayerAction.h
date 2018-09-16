#pragma once


namespace chess {

class GameManager;


class PlayerAction {

public:
    virtual bool enactAction(GameManager &manager) const = 0;

};


}
