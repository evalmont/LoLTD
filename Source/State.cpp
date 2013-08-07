#include <State.hpp>
#include <StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
: window(&window)
, textures(&textures)
, fonts(&fonts)
{
}

State::State(StateStack& stack, Context context)
: stack_(&stack)
, context_(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	stack_->pushState(stateID);
}

void State::requestStackPop()
{
	stack_->popState();
}

void State::requestStateClear()
{
	stack_->clearStates();
}

State::Context State::getContext() const
{
	return context_;
}
