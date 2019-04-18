#ifndef _STATE_MACHINE
#define _STATE_MACHINE
#include "State.hpp"
#include <stack>
#include <cstdint>
//#include <memory>

template <typename T>
class Singleton;

class StateMachine{
	friend class Singleton<StateMachine>;
	public:
		StateMachine();
		~StateMachine();

		void AddState(State* newState, bool _isReplacing = false);
		void RemoveStates(uint8_t cantidad = 1);
		// Run at start of each loop in Game.cpp
		void UpdateStateMachine();
		void clin();
	private:
		uint8_t cantidad;
		std::stack<State*> states;
		State* newState;

		void UpdateTop();
		void ProcessStateChanges();

		bool isRemoving;
		bool isAdding, isReplacing;

		void (StateMachine::*CurrentUpd)();
	};

#endif
