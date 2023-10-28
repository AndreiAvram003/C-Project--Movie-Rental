#pragma once
#include <vector>
#include <algorithm>

using std::vector;

class Observer {
public:
	virtual void update() = 0;
};

