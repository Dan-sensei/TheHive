#include "StateMachine.hpp"
#include <iostream>
StateMachine::StateMachine():cantidad(0), isAdding(false), isRemoving(false) { }
StateMachine::~StateMachine() {}

void StateMachine::AddState(State* _newState, bool _isReplacing) {
	isAdding = true;
	isReplacing = _isReplacing;
	newState = _newState;

	CurrentUpd = &StateMachine::ProcessStateChanges;
}

void StateMachine::RemoveStates(uint8_t _cantidad) {
	isRemoving = true;
	cantidad = _cantidad;

	CurrentUpd = &StateMachine::ProcessStateChanges;
}

void StateMachine::ProcessStateChanges() {
	CurrentUpd = &StateMachine::UpdateTop;

	if (isRemoving && !states.empty())
	{
		while(cantidad && !states.empty()){
			states.top()->CLIN();
			delete states.top();
			states.pop();
			--cantidad;
		}

		if (!states.empty()) states.top()->Resume();

		isRemoving = false;
	}

	if (isAdding) {
		if (!states.empty()) {
			if (isReplacing) {
				states.top()->CLIN();
				delete states.top();
				states.pop();
				isReplacing = false;
			}
			else {
				states.top()->Pause();
			}
		}

		isAdding = false;
		states.push(newState);
		newState = nullptr;
		states.top()->Init();

	}
	UpdateTop();
}

void StateMachine::UpdateStateMachine(){
	(this->*CurrentUpd)();
}

void StateMachine::UpdateTop(){
	states.top()->Update();
};


void StateMachine::clin(){
	while(!states.empty()){
		delete states.top();
		states.pop();
	}
}

// State* StateMachine::GetActiveState() {
// 	return states.top();
// }
