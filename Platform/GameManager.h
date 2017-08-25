#pragma once

namespace chess {

class Move;


class GameManager {

public:
    virtual bool makeMove(Move move) = 0;
    virtual bool resign() = 0;
    virtual bool offerDraw() = 0;
    virtual bool claim50MoveDraw() = 0;
    virtual bool claim3RepetionDraw() = 0;

};


}
