/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_LIST_BOX_HPP
#define TGUI_LIST_BOX_HPP


#include <TGUI/CopiedSharedPtr.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Renderers/ListBoxRenderer.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief List box widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ListBox : public Widget
    {
      public:

        typedef std::shared_ptr<ListBox> Ptr; //!< Shared widget pointer
        typedef std::shared_ptr<const ListBox> ConstPtr; //!< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The horizontal text alignment
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class TextAlignment
        {
            Left,   //!< Put the text on the left side (default)
            Center, //!< Center the text horizontally
            Right   //!< Put the text on the right side
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox(const char* typeName = "ListBox", bool initRenderer = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new list box widget
        ///
        /// @return The new list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ListBox::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another list box
        ///
        /// @param listBox  The other list box
        ///
        /// @return The new list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ListBox::Ptr copy(ListBox::ConstPtr listBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBoxRenderer* getSharedRenderer();
        const ListBoxRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBoxRenderer* getRenderer();
        const ListBoxRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the list box
        ///
        /// @param size  The new size of the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds an item to the list
        ///
        /// @param itemName  The name of the item you want to add (this is the text that will be displayed inside the list box)
        /// @param id        Optional unique id given to this item for the purpose to later identifying this item
        ///
        /// @return
        ///   - Index of inserted item if no maximum items are set or when index is still less than getMaximumItems()
        ///   - Value of getMaximumItems() when adding item failed because there are too many items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t addItem(const String& itemName, const String& id = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects an item in the list box
        ///
        /// @param itemName  The item you want to select
        ///
        /// In case the names are not unique, the first item with that name will be selected.
        ///
        /// @return
        ///         - true on success
        ///         - false when none of the items matches the name
        ///
        /// @see setSelectedItemById
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(const String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects an item in the list box
        ///
        /// @param id  Unique id passed to addItem
        ///
        /// In case the id would not be unique, the first item with that id will be selected.
        ///
        /// @return
        ///         - true on success
        ///         - false when none of the items has the given id
        ///
        /// @see setSelectedItem
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItemById(const String& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects an item in the list box
        ///
        /// @param index  Index of the item in the list box
        ///
        /// @return
        ///         - true on success
        ///         - false when the index was too high
        ///
        /// @see setSelectedItem
        /// @see setSelectedItemById
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItemByIndex(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Deselects the selected item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselectItem();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the item from the list with the given name
        ///
        /// @param itemName  The item to remove
        ///
        /// In case the names are not unique, only the first item with that name will be removed.
        ///
        /// @return
        ///        - true when the item was removed
        ///        - false when the name did not match any item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItem(const String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the item that were added with the given id
        ///
        /// @param id  Id that was given to the addItem function
        ///
        /// In case the id is not unique, only the first item with that id will be removed.
        ///
        /// @return
        ///        - true when the item was removed
        ///        - false when there was no item with the given id
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItemById(const String& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the item from the list box
        ///
        /// @param index  Index of the item in the list box
        ///
        /// @return
        ///        - true when the item was removed
        ///        - false when the index was too high
        ///
        /// @see removeItem
        /// @see removeItemById
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItemByIndex(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all items from the list
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the item name of the item with the given id
        ///
        /// @param id  The id of the item that was given to it when it was added
        ///
        /// In case the id is not unique, the first item with that id will be returned.
        ///
        /// @return The requested item, or an empty string when no item matches the id
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getItemById(const String& id) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the item name of the item at the given index
        ///
        /// @param index  The index of the item to return
        ///
        /// @return The requested item, or an empty string when the index was too high
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getItemByIndex(std::size_t index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the index of the item with the given id
        ///
        /// @param id  The id of the item that was given to it when it was added
        ///
        /// In case the id is not unique, the index of the first item with that id will be returned.
        ///
        /// @return The index of the item that matched the id, or -1 when no item matches the id
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getIndexById(const String& id) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the id of the item at the given index
        ///
        /// @param index  The index of the item to find
        ///
        /// @return The id of the requested item, or an empty string when the index was too high
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getIdByIndex(std::size_t index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the currently selected item
        ///
        /// @return The selected item
        ///         When no item was selected then this function will return an empty string.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getSelectedItem() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the id of the selected item
        ///
        /// @return The id of the selected item, which was the optional id passed to the addItem function.
        ///         When no item was selected then this function returns an empty string
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String getSelectedItemId() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the index of the selected item
        ///
        /// @return The index of the selected item, or -1 when no item was selected
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectedItemIndex() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes an item with name originalValue to newValue
        ///
        /// @param originalValue The name of the item which you want to change
        /// @param newValue      The new name for that item
        ///
        /// In case the names are not unique, only the first item with that name will be changed.
        ///
        /// @return
        ///        - true when the item was changed
        ///        - false when none of the items had the given name
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeItem(const String& originalValue, const String& newValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the name of an item with the given id to newValue
        ///
        /// @param id       The unique id of the item which you want to change
        /// @param newValue The new name for that item
        ///
        /// In case the id is not unique, only the first item with that id will be changed.
        ///
        /// @return
        ///        - true when the item was changed
        ///        - false when none of the items had the given id
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeItemById(const String& id, const String& newValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the name of an item at the given index to newValue
        ///
        /// @param index    The index of the item which you want to change
        /// @param newValue The new name for that item
        ///
        /// @return
        ///        - true when the item was changed
        ///        - false when the index was too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeItemByIndex(std::size_t index, const String& newValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of items in the list box
        ///
        /// @return Number of items inside the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getItemCount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a copy of the items in the list box
        ///
        /// @return items
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<String> getItems() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a copy of the item ids in the list box
        ///
        /// @return item ids
        ///
        /// Items that were not given an id simply have an empty string as id.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<String> getItemIds() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Store some user data with the item
        ///
        /// @param index Index of the item
        /// @param data  User data to store
        ///
        /// Examples:
        /// @code
        /// listBox->setItemData(idx, "Data"); // Note: type to retrieve with getItemData is 'const char*' here
        /// listBox->setItemData(idx, 5);
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemData(std::size_t index, Any data);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns user data stored in the item
        /// @return Stored data
        /// @throw std::bad_cast if the template type does not match the type inside the std::any variable passed in setItemData
        ///        or when the index was too high (which acts as if you access an empty std::any variable).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        T getItemData(std::size_t index) const
        {
            if (index < m_items.size())
                return AnyCast<T>(m_items[index].data);
            else
                throw std::bad_cast();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the items in the list box
        ///
        /// @param itemHeight  The size of a single item in the list
        ///
        /// @warning When there is no scrollbar then the items will be removed when they no longer fit inside the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemHeight(unsigned int itemHeight);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the items in the list box
        ///
        /// @return The item height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum items that the list box can contain
        ///
        /// @param maximumItems  The maximum items inside the list box.
        ///                      When the maximum is set to 0 then the limit will be disabled
        ///
        /// If no scrollbar was loaded then there is always a limitation because there will be a limited space for the items.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumItems(std::size_t maximumItems = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum items that the list box can contain
        ///
        /// @return The maximum items inside the list box.
        ///         If the function returns 0 then there is no limit
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getMaximumItems() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the list box scrolls to the bottom when a new item is added
        ///
        /// @param autoScroll  Should list box scroll to the bottom when new items are added?
        ///
        /// Auto scrolling is enabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAutoScroll(bool autoScroll);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the list box scrolls to the bottom when a new item is added
        /// @return Does the list box scroll to the bottom when new items are added
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getAutoScroll() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the horizontal text alignment
        ///
        /// @param alignment  The new horizontal text alignment
        ///
        /// By default the text is aligned to the left.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextAlignment(TextAlignment alignment);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the current horizontal text alignment
        ///
        /// @return Horizontal text alignment
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextAlignment getTextAlignment() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the list box contains the given item
        ///
        /// @param item  The item to search for
        ///
        /// @return Does the list box contain the item?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool contains(const String& item) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the list box contains an item with the given id
        ///
        /// @param id  The id of the item to search for
        ///
        /// @return Does the list box contain the id?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool containsId(const String& id) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the thumb position of the scrollbar
        ///
        /// @param value  New value of the scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollbarValue(unsigned int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the thumb position of the scrollbar
        ///
        /// @return Value of the scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getScrollbarValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isMouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseWheelScrolled(float delta, Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseButtonNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const Event::KeyEvent& event) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(BackendRenderTarget& target, RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(String signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called when the text size is changed (either by setTextSize or via the renderer)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextSize() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position of the items and the scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateItemPositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the colors and text style of the selected and hovered items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectedAndHoveringItemColorsAndStyle();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the color and text style of all the items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateItemColorsAndStyle();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update on which item the mouse is standing
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateHoveringItem(int item);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update which item is selected
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectedItem(int item);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool updateTime(Duration elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalItem onItemSelect   = {"ItemSelected"};   //!< An item was selected in the list box. Optional parameter: selected item or its index
        SignalItem onMousePress   = {"MousePressed"};   //!< The mouse went down on an item. Optional parameter: selected item or its index
        SignalItem onMouseRelease = {"MouseReleased"};  //!< The mouse was released on one of the items. Optional parameter: selected item or its index
        SignalItem onDoubleClick  = {"DoubleClicked"};  //!< An item was double clicked. Optional parameter: selected item or its index


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        struct Item
        {
            Text text;
            Any data;
            String id;
        };

        std::vector<Item> m_items;

        // What is the index of the selected item?
        // This is also used by combo box, so it can't just be changed to a pointer!
        int m_selectedItem = -1;

        int m_hoveringItem = -1;

        unsigned int m_itemHeight = 0;

        // This will store the maximum number of items in the list box (zero by default, meaning that there is no limit)
        std::size_t m_maxItems = 0;

        // When there are too many items a scrollbar will be shown
        CopiedSharedPtr<ScrollbarChildWidget> m_scroll;

        // Will be set to true after the first click, but gets reset to false when the second click does not occur soon after
        bool m_possibleDoubleClick = false;

        bool m_autoScroll = true;
        ListBox::TextAlignment m_textAlignment = ListBox::TextAlignment::Left;

        Sprite m_spriteBackground;

        // Cached renderer properties
        Borders   m_bordersCached;
        Borders   m_paddingCached;
        Color     m_borderColorCached;
        Color     m_backgroundColorCached;
        Color     m_backgroundColorHoverCached;
        Color     m_selectedBackgroundColorCached;
        Color     m_selectedBackgroundColorHoverCached;
        Color     m_textColorCached;
        Color     m_textColorHoverCached;
        Color     m_selectedTextColorCached;
        Color     m_selectedTextColorHoverCached;
        TextStyles m_textStyleCached;
        TextStyles m_selectedTextStyleCached;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_LIST_BOX_HPP
