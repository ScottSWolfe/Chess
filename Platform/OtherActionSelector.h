#pragma once

#include <memory>
#include <string>
#include "MoveInputParser.h"
class PlayerAction;


class OtherActionSelector {

public:
    std::shared_ptr<PlayerAction> selectAction(std::string input) const;

private:
    std::string getInput() const;
    void printOptions() const;
    bool areYouSure() const;

};
