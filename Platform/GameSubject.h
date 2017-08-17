#pragma once

class GameObserver;

namespace chess {


class GameSubject {

public:
    virtual void registerObserver(GameObserver *observer) = 0;

};


}
