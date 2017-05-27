#pragma once

#include <memory>
#include <vector>
#include <string>
#include "SquareCoordinates.h"
class Move;


class MoveInputParser {

public:
	std::shared_ptr<const Move> parseMoveInput(std::string input) const;

private:
	std::vector<std::string> parseInputIntoTokens(std::string input, char delimiter) const;
	SquareCoordinates convertTokensToCoords(std::string input) const;
	bool readLettersAndNumbers(const std::string input, std::string &letters, std::string &numbers) const;
	int convertLettersToXCoord(std::string letters) const;
	int convertNumbersToYCoord(std::string numbers) const;
	bool isLetter(char c) const;
	bool isNumber(char c) const;
	char uppercase(char c) const;

};
