#pragma once

#include <Nigozi.h>
#include "Observer.h"

class Event {
public:
	Event() = default;
	~Event() = default;

	void AddListener(Observer* observer) {
		m_observers.push_back(observer);
	}

	void RemoveListener(Observer* observer) {
		for (auto it = m_observers.begin(); it < m_observers.end();) {
			if ((*++it) == observer) {
				m_observers.erase(it);
				break;
			}
		}
	}

	void Invoke() {
		for (Observer* observer : m_observers) {
			if (observer) {
				observer->Invoke();
			}
		}
	}
private:
	std::vector<Observer*> m_observers;
};