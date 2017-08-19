#pragma once

#include <memory>
#include <vector>
#include <string>

namespace chess {

class Move;
struct Position;


class MoveInputParser {

public:
    std::shared_ptr<Move> parseMoveInput(std::string input) const;

private:
    std::vector<std::string> parseInputIntoTokens(std::string input, char delimiter) const;
    Position convertTokensToCoords(std::string input) const;
    bool readLettersAndNumbers(const std::string input, std::string &letters, std::string &numbers) const;
    int convertLettersToXCoord(std::string letters) const;
    int convertNumbersToYCoord(std::string numbers) const;
    bool isLetter(char c) const;
    bool isNumber(char c) const;
    char uppercase(char c) const;

};


}
