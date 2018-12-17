#include "StateMachine.hpp"
#include <iostream>
StateMachine::StateMachine():cantidad(0) { }
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

void StateMachine::RemoveState(int _cantidad)
{
	cantidad=_cantidad;
	isRemoving = true;
}
//revisar
void StateMachine::prueba(){
}
void StateMachine::ProcessStateChanges()
{
	if (isRemoving && !states.empty())
	{
		int i=0;
		while(cantidad!=0){
			states.top()->CLIN();
			delete states.top();
			states.pop();
			cantidad--;
			if(cantidad<0){
				cantidad=0;
			}

			if (!states.empty())
			{
				states.top()->Resume();
			}
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
void StateMachine::clin(){
	while(!states.empty()){
		delete states.top();
		states.pop();

	}

}
State* StateMachine::GetActiveState()
{
	return states.top();
}
