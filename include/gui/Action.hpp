/*
Grid
Action.hpp

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

#ifndef ACTION_HPP_INCLUDED
#define ACTION_HPP_INCLUDED

namespace gui
{
	/*
        Action is used as a wrapper of
		member function pointers without parameters.
		use :
		// equivalent of myObj.method()
		MyObject myObj;
		GenericAction* action =
			new Action<MyObject>(myObj,&MyObject::method);
		action->execute();
    */

	class GenericAction
	{
		public :
			virtual void execute() {};
	};

	template<class T>
	class Action : public GenericAction
	{
    private :

        void (T::*f_action)(void); // pointer to the method
        T* r_actionTarget; // pointer to the method's target object

    public :

        Action(T* target, void (T::*action)(void))
        {
            r_actionTarget = target;
            f_action = action;
        }

        virtual void execute()
        {
            if(f_action == NULL || r_actionTarget == NULL)
                return;
            ((*r_actionTarget).*f_action)();
        }
	};

} // namespace gui


#endif // ACTION_HPP_INCLUDED
