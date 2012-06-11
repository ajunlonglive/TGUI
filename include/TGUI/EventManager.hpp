/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _TGUI_EVENT_MANAGER_INCLUDED_
#define _TGUI_EVENT_MANAGER_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct TGUI_API EventManager : public sf::NonCopyable
	{
	    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // The default constructor.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EventManager();

        
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When this function is called then all the objects receive the event (if there are objects).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void handleEvent(sf::Event& event, const Vector2f& viewSize = Vector2f(1, 1));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function ic called automatically by some objects.
        // The object will be added to the list and will receive events.
        // Because most objects are added to this list this manager will also manage the focus on objects.
        //
        // return:  id of the object. You will need it when removing an object from the list.
        //          This id will never by 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int addObject(OBJECT* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // After this function is called the object will no longer receive the events.
        // It is called when the object is removed.
        //
        // return:  always 0 (new id for the object)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int removeObject(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Called by a panel when all objects are being removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllObjects();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // You can use this function to change the focus to another object.
        // You cannot manually call this function because you will need an id. You should call the setFocus function from
        // the object (e.g. the button) instead.
        //
        // return:  true when the focus has changed
        //          false on failure
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setFocus(unsigned int objectID);
        
        
        
        
        void unfocusObject(OBJECT* object);
        
        void unfocusAllObjects();
        
        
        void updateTime(const sf::Time& elapsedTime);
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Places an object before all other objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveObjectToFront(OBJECT* object);
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Places an object behind all other objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveObjectToBack(OBJECT* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the tab key is pressed then this function is called. The focus will move to the next object (if there is one).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void tabkeyPressed();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Checks above which object the mouse is standing.
        // The object can be signaled through Objects[ObjectNr] on condition that this function returned true.
        //
        // return:  true when the mouse is standing on an object
        //          false if the mouse isn't on any object
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(unsigned int& objectNr, float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        // This vector will hold all registered objects
        std::vector<OBJECT*> m_Objects;

        // When one of the elements of the array becomes true then the key is held down.
        // When nothing happend (e.g. focus another object) and it goes up again then the focused object receives a signal.
        // When something happens then this key will also becomes false again (while the key is still down).
        // Not all elements are used, only a few elements of the array are changed.
        bool m_KeyPress[sf::Keyboard::KeyCount];

        // See explaination KeyPress.
//        bool m_MouseButtonClick[sf::Mouse::ButtonCount];

        // This will store the last mouse position
//        Vector2i m_LastMousePosition;

        // The scale of the window (ratio between real size and the viewport)
        Vector2f m_WindowScale;
        
        // A pointer to the struct that owns the event manager (NULL when it is the window)
        OBJECT* m_Parent;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // The event handler can only be used by objects and by the window
//        friend struct OBJECT_EVENT;
        friend struct Group;
        friend struct Panel;
        friend struct Window;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_EVENT_MANAGER_INCLUDED_

