#pragma once

class GameObserver;

class GameSubject {

public:
	virtual void registerObserver(GameObserver *observer) = 0;

};
