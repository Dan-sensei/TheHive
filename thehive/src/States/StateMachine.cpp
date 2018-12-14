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
//std::cout << "size" <<states.size()<< '\n';
}
void StateMachine::ProcessStateChanges()
{
	if (isRemoving && !states.empty())
	{
		//std::cout << "removiendo Main" << '\n';
		int i=0;
		while(cantidad!=0){
			//std::cout << "cantidad:" <<i<< '\n';
			//std::cout << "size" <<states.size()<< '\n';
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
		//std::cout << "removiendo Main terminado" << '\n';

		isRemoving = false;
	}

	if (isAdding)
	{
		std::cout << "anyadiendo" << '\n';
		std::cout << "size" <<states.size()<< '\n';
		std::cout << "replacing" <<isReplacing<< '\n';

		if (!states.empty())
		{
			if (isReplacing)
			{
				//std::cout << "Replacing" << '\n';
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
		std::cout << "anyadiendo terminado" << '\n';
		std::cout << "size" <<states.size()<< '\n';
	}

}

State* StateMachine::GetActiveState()
{
	return states.top();
}
