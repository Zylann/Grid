/*
Grid
StateMachine.hpp

Copyright (c) 2011 by Marc Gilleron, <marc.gilleron@free.fr>

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STATEMACHINE_HPP_INCLUDED
#define STATEMACHINE_HPP_INCLUDED

#include <iostream>
#include <map>

namespace util
{
    // Used in a state machine.
    class State
    {
    protected :

        const int m_ID; // Unique identifier (within the parent state machine)

    public :

        State(int ID) : m_ID(ID)
        {}

        virtual ~State()
        {}

        inline int getID() const { return m_ID; }

        // Called when the state is entered.
        virtual void onEnter() = 0;

        // Called when the state is left.
        virtual void onLeave() = 0;
    };

    // State_T must be a State.
    template <class State_T>
    class StateMachine
    {
    protected :

        std::map<int, State_T*> m_states;
        State_T * r_currentState;

    public :

        // Constructs the state machine, with no current state.
        StateMachine()
        {
            r_currentState = NULL;
        }

        // Destroys the state machine.
        virtual ~StateMachine()
        {
            typename std::map<int, State_T*>::iterator it;
            for(it = m_states.begin(); it != m_states.end(); it++)
                delete it->second;
        }

        // Returns the current state.
        State_T * getCurrentState()
        {
            return r_currentState;
        }

        // Enters a new state. Returns the new state, or NULL if it failed.
        virtual State_T * enterState(int stateID)
        {
            State_T * nextState = getState(stateID);
            if(nextState != NULL)
            {
                // Leave last state
                if(r_currentState != NULL)
                    r_currentState->onLeave();

                r_currentState = nextState;

                // Enter new state
                r_currentState->onEnter();

                return r_currentState;
            }
            else
            {
                std::cerr << "ERROR: StateMachine::enterState: "
                    << "the state '" << stateID << "' is not registered" << std::endl;
                return NULL;
            }
        }

        // Adds a state to the machine. Returns false if it fails.
        bool addState(State_T * state)
        {
            return m_states.insert(
                std::pair<int,State_T*>(state->getID(), state)).second;
        }

        // Finds a state of the machine. Returns NULL if it's not found.
        State_T * getState(int ID)
        {
            typename std::map<int, State_T*>::iterator it = m_states.find(ID);
            if(it != m_states.end())
                return it->second;
            return NULL;
        }
    };

} // namespace util


#endif // STATEMACHINE_HPP_INCLUDED
