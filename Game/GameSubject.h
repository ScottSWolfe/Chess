#pragma once

namespace chess {

class GameObserver;


class GameSubject {

public:
    virtual void registerObserver(GameObserver *observer) = 0;

};


}
