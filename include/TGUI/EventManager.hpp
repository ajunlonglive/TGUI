/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2013 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_EVENT_MANAGER_HPP
#define TGUI_EVENT_MANAGER_HPP


#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  Keeps track of all widgets and passes the events to them.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API EventManager : public sf::NonCopyable
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // The default constructor.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EventManager();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When this function is called then all the widgets receive the event (if there are widgets).
        // The function returns true when the event is consumed and false when the event was ignored by all widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool handleEvent(sf::Event& event);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // You can use this function to change the focus to another widget.
        // You cannot manually call this function. You should call the focus function from the widget's parent instead.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusWidget(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Unfocus the given widget.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusWidget(Widget *const widget);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Unfocus all the widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusAllWidgets();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Places an widget before all other widgets.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTime(const sf::Time& elapsedTime);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the tab key is pressed then this function is called. The focus will move to the next widget (if there is one).
        // This function will only work when tabKeyUsageEnabled is true.
        // The function will return true when another widget was focused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool tabKeyPressed();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Checks above which widget the mouse is standing.
        // If there is no widget below the mouse then this function will return a null pointer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr mouseOnWidget(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Tells all the widgets that the mouse is not on top of them.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNotOnWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Tells all the widgets that the mouse is no longer down.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is similar to the tabKeyPressed function.
        // The difference is that this function will return false and unfocus all widgets when the last widget was focused.
        // The tabKeyPressed function on the other hand would just focus the first widget.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool focusNextWidget();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        // This vector will hold all widgets
        std::vector< Widget::Ptr > m_Widgets;

        // The id of the focused widget
        unsigned int m_FocusedWidget;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // The event handler can only be used by container widgets and by the window
        friend class Grid;
        friend class Container;
        friend class ContainerWidget;
        friend class Panel;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_EVENT_MANAGER_HPP

