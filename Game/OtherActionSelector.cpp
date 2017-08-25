#include <iostream>
#include "ChessDebug.h"
#include "Claim50MoveDraw.h"
#include "DrawOffer.h"
#include "OtherActionSelector.h"
#include "PlayerAction.h"
#include "Resignation.h"

namespace chess {


const std::string OtherActionSelector::resign = "A";
const std::string OtherActionSelector::offer_draw = "B";
const std::string OtherActionSelector::claim_50_move_draw = "C";
const std::string OtherActionSelector::claim_3_repetition_draw = "D";
const std::string OtherActionSelector::return_to_move = "E";

std::shared_ptr<PlayerAction> OtherActionSelector::selectAction(std::string input) const {
    if (input.empty() || input == "O") {
        input = getInput();
    }

    if (input == resign) {
        if (areYouSure() == true) {
            return std::make_shared<Resignation>();
        }
    }
    else if (input == offer_draw) {
        if (areYouSure() == true) {
            return std::make_shared<DrawOffer>();
        }
    }
    else if (input == claim_50_move_draw) {
        if (areYouSure() == true) {
            return std::make_shared<Claim50MoveDraw>();
        }
    }
    else if (input == claim_3_repetition_draw) {
        return nullptr;
    }
    else if (input == return_to_move) {
        return nullptr;
    }
    else {
        std::cout << "Incorrect option chosen." << std::endl;
        return nullptr;
    }
    return nullptr;
}

std::string OtherActionSelector::getInput() const {
    printOptions();
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool OtherActionSelector::areYouSure() const {
    std::cout << "Are you sure? (Y/N)" << std::endl;
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "Y") {
            return true;
        }
        if (input == "N") {
            return false;
        }
    }
}

void OtherActionSelector::printOptions() const {
    std::cout << std::endl;
    std::cout << "Choose an action: " << std::endl;
    std::cout << "A. Resign" << std::endl;
    std::cout << "B. Offer Draw" << std::endl;
    std::cout << "C. Claim 50 Move Draw" << std::endl;
    std::cout << "D. Claim 3 Repetition Draw" << std::endl;
    std::cout << "E. Return to Make Move" << std::endl;
}


}
