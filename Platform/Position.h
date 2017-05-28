#pragma once

struct Position {
	Position();
	Position(int x, int y);
	Position(const Position &pos);
	bool operator==(const Position &other_pos) const;
	Position add(int x, int y) const;
	bool empty() const;
	int x;
	int y;
};
