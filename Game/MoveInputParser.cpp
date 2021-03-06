#include <array>
#include <cmath>
#include <vector>
#include "ChessDebug.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "Position.h"

namespace chess {


std::shared_ptr<Move> MoveInputParser::parseMoveInput(std::string input) const {
    std::shared_ptr<Move> move(nullptr);

    std::vector<std::string> tokens = parseInputIntoTokens(input, ' ');
    if (tokens.size() < 2) {
        return move;
    }

    std::array<Position, 2> squares;
    for (int i = 0; i < 2; i++) {
        squares[i] = convertTokensToCoords(tokens[i]);
        if (squares[i].empty()) {
            return move;
        }
    }

    move.reset(new Move(squares[0], squares[1]));
    return move;
}

std::vector<std::string> MoveInputParser::parseInputIntoTokens(std::string input, char delimiter) const {
    std::vector<std::string> tokens;
    input += delimiter;
    int i = 0;
    while (!input.empty()) {
        char c = input[i];
        if (c == delimiter) {
            std::string token = input.substr(0, i);
            if (!token.empty()) {
                tokens.push_back(token);
            }
            input = input.erase(0, i + 1);
            i = 0;
        }
        else {
            i++;
        }
    }
    return tokens;
}

Position MoveInputParser::convertTokensToCoords(std::string input) const {
    Position coords;
    if (input.size() < 2) {
        return coords;
    }
    std::string letters;
    std::string numbers;
    if (readLettersAndNumbers(input, letters, numbers) == false) {
        return coords;
    }
    int x_coord = convertLettersToXCoord(letters);
    int y_coord = convertNumbersToYCoord(numbers);
    coords = { x_coord, y_coord };
    return coords;
}

bool MoveInputParser::readLettersAndNumbers(const std::string &input, std::string &letters, std::string &numbers) const {
    
    for (size_t i = 0; i < input.size(); i++) {
        char c = input[i];
        if (isLetter(c)) {
            letters += uppercase(c);
        }
        else if (isNumber(c)) {
            break;
        }
        else {
            return false;
        }
    }

    for (size_t i = letters.size(); i < input.size(); i++) {
        char c = input[i];
        if (isNumber(c)) {
            numbers += c;
        }
        else {
            return false;
        }
    }

    if (letters.empty() || numbers.empty()) {
        return false;
    }

    return true;
}

int MoveInputParser::convertLettersToXCoord(std::string letters) const {
    int sum = 0;
    for (size_t i = 0; i < letters.size(); i++) {
        char c = letters[i];
        sum += static_cast<int>(pow(26, letters.size() - 1 - i)) * (c - 'A' + 1);
    }
    return sum - 1;
}

int MoveInputParser::convertNumbersToYCoord(std::string numbers) const {
    int sum = 0;
    for (size_t i = 0; i < numbers.size(); i++) {
        char c = numbers[i];
        sum += static_cast<int>(pow(10, numbers.size() - 1 - i)) * (c - '0');
    }
    return sum - 1;
}

bool MoveInputParser::isLetter(char c) const {
    c = uppercase(c);
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

bool MoveInputParser::isNumber(char c) const {
    if (c >= '0' || c <= '9') {
        return true;
    }
    return false;
}

char MoveInputParser::uppercase(char c) const {
    if (c >= 'a' && c <= 'z') {
        c -= 32;
    }
    return c;
}


}
