#pragma once

class Board;
enum class PieceColor;


class Player {

public:
	virtual Board move(Board board) = 0;

private:
	const PieceColor color;

};
