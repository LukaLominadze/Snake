#pragma once

#include <Nigozi.h>

class Observer
{
public:
	Observer(std::function<void()>&& func) {
		m_function = func;
	}

	inline void Invoke() { m_function(); }
private:
	std::function<void()> m_function;
};

