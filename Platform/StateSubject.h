#pragma once

class StateObserver;

class StateSubject {

public:
	virtual void registerObserver(StateObserver *observer) = 0;

};
