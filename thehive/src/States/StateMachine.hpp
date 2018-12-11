#ifndef _STATE_MACHINE
#define _STATE_MACHINE
#include "State.hpp"
#include <stack>
//#include <memory>
template <typename T>
class Singleton;

class StateMachine{
	friend class Singleton<StateMachine>;
	public:
		StateMachine();
		~StateMachine();

		void AddState(State* newState, bool isReplacing = true);
		void RemoveState();
		// Run at start of each loop in Game.cpp
		void ProcessStateChanges();

		State* GetActiveState();

	private:

		std::stack<State*> states;
		State* newState;

		bool isRemoving;
		bool isAdding, isReplacing;
	};

#endif
