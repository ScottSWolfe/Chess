#include <iostream>
#include "ChessDebug.h"
#include "Claim50MoveDraw.h"
#include "DrawOffer.h"
#include "OtherActionSelector.h"
#include "PlayerAction.h"
#include "Resignation.h"
using namespace std;


const string OtherActionSelector::resign = "A";
const string OtherActionSelector::offer_draw = "B";
const string OtherActionSelector::claim_50_move_draw = "C";
const string OtherActionSelector::claim_3_repetition_draw = "D";
const string OtherActionSelector::return_to_move = "E";

shared_ptr<PlayerAction> OtherActionSelector::selectAction(string input) const {
    if (input.empty() || input == "O") {
        input = getInput();
    }

    if (input == resign) {
        if (areYouSure() == true) {
            return make_shared<Resignation>();
        }
    }
    else if (input == offer_draw) {
        if (areYouSure() == true) {
            return make_shared<DrawOffer>();
        }
    }
    else if (input == claim_50_move_draw) {
        if (areYouSure() == true) {
            return make_shared<Claim50MoveDraw>();
        }
    }
    else if (input == claim_3_repetition_draw) {
        return nullptr;
    }
    else if (input == return_to_move) {
        return nullptr;
    }
    else {
        cout << "Incorrect option chosen." << endl;
        return nullptr;
    }
    return nullptr;
}

string OtherActionSelector::getInput() const {
    printOptions();
    string input;
    getline(cin, input);
    return input;
}

bool OtherActionSelector::areYouSure() const {
    cout << "Are you sure? (Y/N)" << endl;
    string input;
    while (true) {
        getline(cin, input);
        if (input == "Y") {
            return true;
        }
        if (input == "N") {
            return false;
        }
    }
}

void OtherActionSelector::printOptions() const {
    cout << endl;
    cout << "Choose an action: " << endl;
    cout << "A. Resign" << endl;
    cout << "B. Offer Draw" << endl;
    cout << "C. Claim 50 Move Draw" << endl;
    cout << "D. Claim 3 Repetition Draw" << endl;
    cout << "E. Return to Make Move" << endl;
}
