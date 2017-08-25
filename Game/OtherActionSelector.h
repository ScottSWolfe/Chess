#pragma once

#include <memory>
#include <string>
#include "MoveInputParser.h"

namespace chess {

class PlayerAction;


class OtherActionSelector {

public:
    std::shared_ptr<PlayerAction> selectAction(std::string input) const;

private:
    std::string getInput() const;
    void printOptions() const;
    bool areYouSure() const;
    
    static const std::string resign;
    static const std::string offer_draw;
    static const std::string claim_50_move_draw;
    static const std::string claim_3_repetition_draw;
    static const std::string return_to_move;
    
};


}
