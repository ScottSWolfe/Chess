#include <iostream>
#include "OtherActionSelector.h"
#include "PlayerAction.h"
#include "Resignation.h"
using namespace std;


shared_ptr<PlayerAction> OtherActionSelector::selectAction(string input) const {
    if (input.empty() || input == "O") {
        input = getInput();
    }

    if (input == "A") {
        if (areYouSure() == true) {
            return make_shared<Resignation>();
        }
    }
    else if (input == "B") {
        return nullptr;
    }
    else if (input == "C") {
        return nullptr;
    }
    else if (input == "D") {
        return nullptr;
    }
    else if (input == "E") {
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
