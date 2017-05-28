#pragma once

struct Position {
	Position();
	Position(int x, int y);
	bool operator==(const Position &other_coordinates) const;
	bool empty() const;
	int x;
	int y;
};
