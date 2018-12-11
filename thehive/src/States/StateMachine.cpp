#include "StateMachine.hpp"
#include <iostream>
StateMachine::StateMachine() { }
StateMachine::~StateMachine() {

	//for (size_t i = 0; i < states.size(); i++) {
	//	/* code */
	//	delete states.top();
	//	states.pop();
	//}

}
void StateMachine::AddState(State* _newState, bool _isReplacing)
{
	isAdding = true;
	isReplacing = _isReplacing;

	newState = _newState;
}

void StateMachine::RemoveState()
{
	isRemoving = true;
}
//revisar
void StateMachine::ProcessStateChanges()
{
	if (isRemoving && !states.empty())
	{
		states.top()->CLIN();
		delete states.top();
		states.pop();

		if (!states.empty())
		{
			//states.top()->Resume();
		}

		isRemoving = false;
	}

	if (isAdding)
	{
		if (!states.empty())
		{
			if (isReplacing)
			{
				states.top()->CLIN();
				delete states.top();
				states.pop();
			}
			else
			{
				//states.top()->Pause();
			}
		}
		states.push(newState);
		states.top()->Init();
		isAdding = false;
	}

}

State* StateMachine::GetActiveState()
{
	return states.top();
}
