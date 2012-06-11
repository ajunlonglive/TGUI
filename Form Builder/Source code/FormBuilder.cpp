/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI Form Builder
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


#include "FormBuilder.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Builder::Builder() :
mainWindow    (sf::VideoMode(1024, 768), "TGUI Form Builder " VERSION),
objectsWindow (sf::VideoMode(112, 400), "", sf::Style::Titlebar),
propertyWindow(sf::VideoMode(300, 500), "", sf::Style::Titlebar | sf::Style::Resize),
currentID     (0),
draggingObject(false),
draggingSquare(0),
dragPos       (0, 0)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Builder::getUniqueID()
{
    static unsigned int id = 0;
    return ++id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Builder::newObject(unsigned int objectID, const std::string objectName)
{
    currentID = getUniqueID();

    // Check which object was created
    if (objectID == tgui::window)
    {
        // Create a new property list
        PropertiesWindow properties;
        properties.id = currentID;
        properties.name.value = objectName;
        properties.builder = this;
        windows.push_back(properties);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        windows.back().addProperties(propertyWindow);

        // Create the scale squares pictures
        mainWindow.addButton("Square_TopLeft")->load("images/Square");
        mainWindow.copyButton("Square_TopLeft", "Square_Top");
        mainWindow.copyButton("Square_TopLeft", "Square_TopRight");
        mainWindow.copyButton("Square_TopLeft", "Square_Right");
        mainWindow.copyButton("Square_TopLeft", "Square_BottomRight");
        mainWindow.copyButton("Square_TopLeft", "Square_Bottom");
        mainWindow.copyButton("Square_TopLeft", "Square_BottomLeft");
        mainWindow.copyButton("Square_TopLeft", "Square_Left");
    }
    else if (objectID == tgui::picture)
    {
        // Create a new property list
        PropertiesPicture properties;
        properties.id = currentID;
        properties.name.value = objectName;
        pictures.push_back(properties);

        // Add a picture to the form
        tgui::Picture* picture = mainWindow.addPicture(tgui::to_string(currentID));
        picture->load(pictures.back().filename.value);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        pictures.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::button)
    {
        // Create a new property list
        PropertiesButton properties;
        properties.id = currentID;
        properties.name.value = objectName;
        buttons.push_back(properties);

        // Add a button to the form
        tgui::Button* button = mainWindow.addButton(tgui::to_string(currentID));
        button->load(buttons.back().pathname.value);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        buttons.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::checkbox)
    {
        // Create a new property list
        PropertiesCheckbox properties;
        properties.id = currentID;
        properties.name.value = objectName;
        checkboxes.push_back(properties);

        // Add a checkbox to the form
        tgui::Checkbox* checkbox = mainWindow.addCheckbox(tgui::to_string(currentID));
        checkbox->load(checkboxes.back().pathname.value);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        checkboxes.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::radioButton)
    {
        // Create a new property list
        PropertiesRadioButton properties;
        properties.id = currentID;
        properties.name.value = objectName;
        properties.builder = this;
        radioButtons.push_back(properties);

        // Add a radio button to the form
        tgui::RadioButton* radioButton = mainWindow.addRadioButton(tgui::to_string(currentID));
        radioButton->load(radioButtons.back().pathname.value);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        radioButtons.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::label)
    {
        // Create a new property list
        PropertiesLabel properties;
        properties.id = currentID;
        properties.name.value = objectName;
        labels.push_back(properties);

        // Add a label to the form
        tgui::Label* label = mainWindow.addLabel(tgui::to_string(currentID));
        label->setText("Label");

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        labels.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::editBox)
    {
        // Create a new property list
        PropertiesEditBox properties;
        properties.id = currentID;
        properties.name.value = objectName;
        editBoxes.push_back(properties);

        // Add an edit box to the form
        tgui::EditBox* editBox = mainWindow.addEditBox(tgui::to_string(currentID));
        editBox->load(editBoxes.back().pathname.value);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        editBoxes.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::listbox)
    {
        // Create a new property list
        PropertiesListbox properties;
        properties.id = currentID;
        properties.name.value = objectName;
        listboxes.push_back(properties);

        // Add an listbox to the form
        tgui::Listbox* listbox = mainWindow.addListbox(tgui::to_string(currentID));
        listbox->load(200, 240, "images/objects/Scrollbar/Black", 30);
        listbox->setBorders(2, 2, 2, 2);
        listbox->changeColors(sf::Color( 50,  50,  50),
                              sf::Color(200, 200, 200),
                              sf::Color( 10, 110, 255),
                              sf::Color(255, 255, 255),
                              sf::Color::Black);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        listboxes.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::comboBox)
    {
        // Create a new property list
        PropertiesComboBox properties;
        properties.id = currentID;
        properties.name.value = objectName;
        comboBoxes.push_back(properties);

        // Add an combo box to the form
        tgui::ComboBox* comboBox = mainWindow.addComboBox(tgui::to_string(currentID));
        comboBox->load("images/objects/ComboBox/Black", 240, 10, "images/objects/Scrollbar/Black");
        comboBox->setBorders(2, 2, 2, 2);
        comboBox->changeColors(sf::Color( 50,  50,  50),
                               sf::Color(200, 200, 200),
                               sf::Color( 10, 110, 255),
                               sf::Color(255, 255, 255),
                               sf::Color::Black);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        comboBoxes.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::slider)
    {
        // Create a new property list
        PropertiesSlider properties;
        properties.id = currentID;
        properties.name.value = objectName;
        sliders.push_back(properties);

        // Add a slider to the form
        tgui::Slider* slider = mainWindow.addSlider(tgui::to_string(currentID));
        slider->load(sliders.back().pathname.value);
        slider->verticalScroll = false;

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        sliders.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::scrollbar)
    {
        // Create a new property list
        PropertiesScrollbar properties;
        properties.id = currentID;
        properties.name.value = objectName;
        scrollbars.push_back(properties);

        // Add a scrollbar to the form
        tgui::Scrollbar* scrollbar = mainWindow.addScrollbar(tgui::to_string(currentID));
        scrollbar->load(scrollbars.back().pathname.value);
        scrollbar->setMaximum(5);
        scrollbar->setLowValue(4);
        scrollbar->autoHide = false;

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        scrollbars.back().addProperties(propertyWindow);
    }
    else if (objectID == tgui::loadingBar)
    {
        // Create a new property list
        PropertiesLoadingBar properties;
        properties.id = currentID;
        properties.name.value = objectName;
        loadingBars.push_back(properties);

        // Add a loading bar to the form
        tgui::LoadingBar* loadingBar = mainWindow.addLoadingBar(tgui::to_string(currentID));
        loadingBar->load(loadingBars.back().pathname.value);

        // Show the properties of the window
        propertyWindow.removeAllObjects();
        loadingBars.back().addProperties(propertyWindow);
    }

    // Bring the scale squares to front
    mainWindow.getButton("Square_TopLeft")->moveToFront();
    mainWindow.getButton("Square_Top")->moveToFront();
    mainWindow.getButton("Square_TopRight")->moveToFront();
    mainWindow.getButton("Square_Right")->moveToFront();
    mainWindow.getButton("Square_BottomRight")->moveToFront();
    mainWindow.getButton("Square_Bottom")->moveToFront();
    mainWindow.getButton("Square_BottomLeft")->moveToFront();
    mainWindow.getButton("Square_Left")->moveToFront();

    resizePropertyWindow();
    changeVisibleProperties();

    return currentID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::changeVisibleProperties()
{
    unsigned int i;

    // Remove all the objects from the window
    propertyWindow.removeAllObjects();

    // Check if the window is selected
    for (i=0; i<windows.size(); ++i)
    {
        if (windows[i].id == currentID)
        {
            windows[i].addProperties(propertyWindow);

            mainWindow.getButton("Square_TopLeft")->setPosition(-3, -3);
            mainWindow.getButton("Square_Top")->setPosition((windows[i].width.value / 2.f) - 3, -3);
            mainWindow.getButton("Square_TopRight")->setPosition(windows[i].width.value - 3, -3);
            mainWindow.getButton("Square_Right")->setPosition(windows[i].width.value - 3, (windows[i].height.value / 2.f) - 3);
            mainWindow.getButton("Square_BottomRight")->setPosition(windows[i].width.value - 3, windows[i].height.value - 3);
            mainWindow.getButton("Square_Bottom")->setPosition((windows[i].width.value / 2.f) - 3, windows[i].height.value - 3);
            mainWindow.getButton("Square_BottomLeft")->setPosition(-3, windows[i].height.value - 3);
            mainWindow.getButton("Square_Left")->setPosition(-3, (windows[i].height.value / 2.f) - 3);
            return;
        }
    }

    // Create the delete button
    tgui::Button* button = propertyWindow.addButton();
    button->load("images/objects/Button/Black");
    button->setText("Delete object");
    button->setSize(propertyWindow.sf::RenderWindow::getSize().x - 8, 40);
    button->callbackID = 20;

    // Check if a radio button is selected
    for (i=0; i<radioButtons.size(); ++i)
    {
        if (radioButtons[i].id == currentID)
        {
            radioButtons[i].addProperties(propertyWindow);
            button->setPosition(4, 10 + (40 * (Property_Checkbox_CallbackID + 1)));

            mainWindow.getButton("Square_TopLeft")->setPosition(radioButtons[i].left.value - 3, radioButtons[i].top.value - 3);
            mainWindow.getButton("Square_Top")->setPosition(radioButtons[i].left.value + (radioButtons[i].width.value / 2.f) - 3, radioButtons[i].top.value - 3);
            mainWindow.getButton("Square_TopRight")->setPosition(radioButtons[i].left.value + radioButtons[i].width.value - 3, radioButtons[i].top.value - 3);
            mainWindow.getButton("Square_Right")->setPosition(radioButtons[i].left.value + radioButtons[i].width.value - 3, radioButtons[i].top.value + (radioButtons[i].height.value / 2.f) - 3);
            mainWindow.getButton("Square_BottomRight")->setPosition(radioButtons[i].left.value + radioButtons[i].width.value - 3, radioButtons[i].top.value + radioButtons[i].height.value - 3);
            mainWindow.getButton("Square_Bottom")->setPosition(radioButtons[i].left.value + (radioButtons[i].width.value / 2.f) - 3, radioButtons[i].top.value + radioButtons[i].height.value - 3);
            mainWindow.getButton("Square_BottomLeft")->setPosition(radioButtons[i].left.value - 3, radioButtons[i].top.value + radioButtons[i].height.value - 3);
            mainWindow.getButton("Square_Left")->setPosition(radioButtons[i].left.value - 3, radioButtons[i].top.value + (radioButtons[i].height.value / 2.f) - 3);
            return;
        }
    }

    // Check if the other objects are selected
    #define FindObjectWithID(Object, objects) \
    for (i=0; i<objects.size(); ++i) \
    { \
        if (objects[i].id == currentID) \
        { \
            objects[i].addProperties(propertyWindow); \
            button->setPosition(4, 10 + (40 * (Property_##Object##_CallbackID + 1))); \
          \
            mainWindow.getButton("Square_TopLeft")->setPosition(objects[i].left.value - 3, objects[i].top.value - 3); \
            mainWindow.getButton("Square_Top")->setPosition(objects[i].left.value + (objects[i].width.value / 2.f) - 3, objects[i].top.value - 3); \
            mainWindow.getButton("Square_TopRight")->setPosition(objects[i].left.value + objects[i].width.value - 3, objects[i].top.value - 3); \
            mainWindow.getButton("Square_Right")->setPosition(objects[i].left.value + objects[i].width.value - 3, objects[i].top.value + (objects[i].height.value / 2.f) - 3); \
            mainWindow.getButton("Square_BottomRight")->setPosition(objects[i].left.value + objects[i].width.value - 3, objects[i].top.value + objects[i].height.value - 3); \
            mainWindow.getButton("Square_Bottom")->setPosition(objects[i].left.value + (objects[i].width.value / 2.f) - 3, objects[i].top.value + objects[i].height.value - 3); \
            mainWindow.getButton("Square_BottomLeft")->setPosition(objects[i].left.value - 3, objects[i].top.value + objects[i].height.value - 3); \
            mainWindow.getButton("Square_Left")->setPosition(objects[i].left.value - 3, objects[i].top.value + (objects[i].height.value / 2.f) - 3); \
            return; \
        } \
    }

    FindObjectWithID(Picture, pictures)
    FindObjectWithID(Button, buttons)
    FindObjectWithID(Checkbox, checkboxes)
    FindObjectWithID(Label, labels)
    FindObjectWithID(EditBox, editBoxes)
    FindObjectWithID(Listbox, listboxes)
    FindObjectWithID(ComboBox, comboBoxes)
    FindObjectWithID(Slider, sliders)
    FindObjectWithID(Scrollbar, scrollbars)
    FindObjectWithID(LoadingBar, loadingBars)

    #undef FindObjectWithID
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::resizePropertyWindow()
{
    unsigned int i;

    for (i=0; i<windows.size(); ++i)
    {
        if (windows[i].id == currentID)
        {
            propertyWindow.sf::Window::setSize(sf::Vector2u(propertyWindow.sf::RenderWindow::getSize().x, 10 + (40 * (Property_Window_GlobalFont + 1))));
            return;
        }
    }

    for (i=0; i<radioButtons.size(); ++i)
    {
        if (radioButtons[i].id == currentID)
        {
            propertyWindow.sf::Window::setSize(sf::Vector2u(propertyWindow.sf::RenderWindow::getSize().x, 60 + (40 * (Property_Checkbox_CallbackID + 1))));
            return;
        }
    }

    #define FindObjectWithID(Object, objects) \
    for (i=0; i<objects.size(); ++i) \
    { \
        if (objects[i].id == currentID) \
        { \
            propertyWindow.sf::Window::setSize(sf::Vector2u(propertyWindow.sf::RenderWindow::getSize().x, 60 + (40 * (Property_##Object##_CallbackID + 1)))); \
            return; \
        } \
    }

    FindObjectWithID(Picture, pictures)
    FindObjectWithID(Button, buttons)
    FindObjectWithID(Checkbox, checkboxes)
    FindObjectWithID(Label, labels)
    FindObjectWithID(EditBox, editBoxes)
    FindObjectWithID(Listbox, listboxes)
    FindObjectWithID(ComboBox, comboBoxes)
    FindObjectWithID(Slider, sliders)
    FindObjectWithID(Scrollbar, scrollbars)
    FindObjectWithID(LoadingBar, loadingBars)

    #undef FindObjectWithID
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::updateProperty(unsigned int propertyNumber)
{
    unsigned int i;


    for (i=0; i<windows.size(); ++i)
    {

        if (windows[i].id == currentID)
        {
            windows[i].updateProperty(mainWindow, propertyWindow, propertyNumber); \
            mainWindow.getButton("Square_TopLeft")->setPosition(-3, -3);
            mainWindow.getButton("Square_Top")->setPosition((windows[i].width.value / 2.f) - 3, -3);
            mainWindow.getButton("Square_TopRight")->setPosition(windows[i].width.value - 3, -3);
            mainWindow.getButton("Square_Right")->setPosition(windows[i].width.value - 3, (windows[i].height.value / 2.f) - 3);
            mainWindow.getButton("Square_BottomRight")->setPosition(windows[i].width.value - 3, windows[i].height.value - 3);
            mainWindow.getButton("Square_Bottom")->setPosition((windows[i].width.value / 2.f) - 3, windows[i].height.value - 3);
            mainWindow.getButton("Square_BottomLeft")->setPosition(-3, windows[i].height.value - 3);
            mainWindow.getButton("Square_Left")->setPosition(-3, (windows[i].height.value / 2.f) - 3);
            return;
        }
    }

    #define FindObjectWithID(objects) \
    for (i=0; i<objects.size(); ++i) \
    { \
     \
        if (objects[i].id == currentID) \
        { \
            objects[i].updateProperty(mainWindow, propertyWindow, propertyNumber); \
            mainWindow.getButton("Square_TopLeft")->setPosition(objects[i].left.value - 3, objects[i].top.value - 3); \
            mainWindow.getButton("Square_Top")->setPosition(objects[i].left.value + (objects[i].width.value / 2.f) - 3, objects[i].top.value - 3); \
            mainWindow.getButton("Square_TopRight")->setPosition(objects[i].left.value + objects[i].width.value - 3, objects[i].top.value - 3); \
            mainWindow.getButton("Square_Right")->setPosition(objects[i].left.value + objects[i].width.value - 3, objects[i].top.value + (objects[i].height.value / 2.f) - 3); \
            mainWindow.getButton("Square_BottomRight")->setPosition(objects[i].left.value + objects[i].width.value - 3, objects[i].top.value + objects[i].height.value - 3); \
            mainWindow.getButton("Square_Bottom")->setPosition(objects[i].left.value + (objects[i].width.value / 2.f) - 3, objects[i].top.value + objects[i].height.value - 3); \
            mainWindow.getButton("Square_BottomLeft")->setPosition(objects[i].left.value - 3, objects[i].top.value + objects[i].height.value - 3); \
            mainWindow.getButton("Square_Left")->setPosition(objects[i].left.value - 3, objects[i].top.value + (objects[i].height.value / 2.f) - 3); \
            return; \
        } \
    }

    FindObjectWithID(pictures)
    FindObjectWithID(buttons)
    FindObjectWithID(checkboxes)
    FindObjectWithID(radioButtons)
    FindObjectWithID(labels)
    FindObjectWithID(editBoxes)
    FindObjectWithID(listboxes)
    FindObjectWithID(comboBoxes)
    FindObjectWithID(sliders)
    FindObjectWithID(scrollbars)
    FindObjectWithID(loadingBars)

    #undef FindObjectWithID
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::setGlobalFont(const sf::Font& font)
{
    TGUI_UNUSED_PARAM(font);
/*
    unsigned int i;

    // Loop through all buttons
    for (i=0; i<buttons.size(); ++i)
    {
        // Check if the global font is used
        if (buttons[i].textFont.value.compare("Global") == 0)
            buttons[i].updateProperty(mainWindow, propertyWindow, Property_Button_TextFont);
    }

    // Loop through all checkboxes
    for (i=0; i<checkboxes.size(); ++i)
    {
        // Check if the global font is used
        if (checkboxes[i].textFont.value.compare("Global") == 0)
            checkboxes[i].updateProperty(mainWindow, propertyWindow, Property_Checkbox_TextFont);
    }

    // Loop through all radio buttons
    for (i=0; i<radioButtons.size(); ++i)
    {
        // Check if the global font is used
        if (radioButtons[i].textFont.value.compare("Global") == 0)
            radioButtons[i].updateProperty(mainWindow, propertyWindow, Property_Checkbox_TextFont);
    }

    // Loop through all labels
    for (i=0; i<labels.size(); ++i)
    {
        // Check if the global font is used
        if (labels[i].textFont.value.compare("Global") == 0)
            labels[i].updateProperty(mainWindow, propertyWindow, Property_Label_TextFont);
    }

    // Loop through all edit boxes
    for (i=0; i<editBoxes.size(); ++i)
    {
        // Check if the global font is used
        if (editBoxes[i].textFont.value.compare("Global") == 0)
            editBoxes[i].updateProperty(mainWindow, propertyWindow, Property_EditBox_TextFont);
    }

    // Loop through all listboxes
    for (i=0; i<listboxes.size(); ++i)
    {
        // Check if the global font is used
        if (listboxes[i].textFont.value.compare("Global") == 0)
            listboxes[i].updateProperty(mainWindow, propertyWindow, Property_Listbox_TextFont);
    }

    // Loop through all combo boxes
    for (i=0; i<comboBoxes.size(); ++i)
    {
        // Check if the global font is used
        if (comboBoxes[i].textFont.value.compare("Global") == 0)
            comboBoxes[i].updateProperty(mainWindow, propertyWindow, Property_Listbox_TextFont);
    }
*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Builder::getClickedObjectID(sf::Event& event)
{
    // Check if the left mouse was pressed
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        float mouseX = event.mouseButton.x / (mainWindow.sf::RenderWindow::getSize().x / mainWindow.getView().getSize().x);
        float mouseY = event.mouseButton.y / (mainWindow.sf::RenderWindow::getSize().y / mainWindow.getView().getSize().y);

        unsigned int highestID = 0;
        unsigned int objectID = 1;

        #define FindObjectNr(Object, objects) \
        for (unsigned int i=0; i<objects.size(); ++i) \
        { \
            tgui::Object* object = mainWindow.get##Object(tgui::to_string(objects[i].id)); \
         \
            if (object->mouseOnObject(mouseX, mouseY)) \
            { \
                if (highestID < object->getObjectID()) \
                { \
                    if (highestID > 0) \
                        object->mouseNotOnObject(); \
                 \
                    highestID = object->getObjectID(); \
                    objectID = objects[i].id; \
                } \
            } \
        }

        FindObjectNr(Picture, pictures)
        FindObjectNr(Button, buttons)
        FindObjectNr(Checkbox, checkboxes)
        FindObjectNr(RadioButton, radioButtons)
        FindObjectNr(Label, labels)
        FindObjectNr(EditBox, editBoxes)
        FindObjectNr(Listbox, listboxes)
        FindObjectNr(ComboBox, comboBoxes)
        FindObjectNr(Slider, sliders)
        FindObjectNr(Scrollbar, scrollbars)
        FindObjectNr(LoadingBar, loadingBars)

        #undef FindObjectNr

        // If our mouse is on top of an object then return the id
        return objectID;
    }
    else
        return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Builder::getScaleSquareObjectID(float x, float y)
{
    float mouseX = x / (mainWindow.sf::RenderWindow::getSize().x / mainWindow.getView().getSize().x);
    float mouseY = y / (mainWindow.sf::RenderWindow::getSize().y / mainWindow.getView().getSize().y);

    unsigned int highestID = 0;
    unsigned int objectID;

    #define FindObjectNr(name, objID) \
    { \
        tgui::Button* button = mainWindow.getButton(name); \
      \
        if (button->mouseOnObject(mouseX, mouseY)) \
        { \
            if (highestID < button->getObjectID()) \
            { \
                button->mouseMoved(mouseX, mouseY); \
                highestID = button->getObjectID(); \
                objectID = objID; \
            } \
        } \
    }

    FindObjectNr("Square_TopLeft", SQUARE_TOP_LEFT)
    FindObjectNr("Square_TopRight", SQUARE_TOP_RIGHT)
    FindObjectNr("Square_BottomLeft", SQUARE_BOTTOM_LEFT)
    FindObjectNr("Square_BottomRight", SQUARE_BOTTOM_RIGHT)
    FindObjectNr("Square_Top", SQUARE_TOP)
    FindObjectNr("Square_Left", SQUARE_LEFT)
    FindObjectNr("Square_Right", SQUARE_RIGHT)
    FindObjectNr("Square_Bottom", SQUARE_BOTTOM)

    #undef FindObjectNr

    // If our mouse is on top of an object then return true
    if (highestID != 0)
        return objectID;
    else
        return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::deleteObject()
{
    unsigned int i;

    // Remove the object from the window
    mainWindow.removeObject(tgui::to_string(currentID));

    // Find and remove the properties of the object
    #define FindObjectWithID(object) \
    for (i=0; i<object.size(); ++i) \
    { \
        if (object[i].id == currentID) \
        { \
            object.erase(object.begin() + i); \
          \
            currentID = windows[0].id; \
            changeVisibleProperties(); \
            resizePropertyWindow(); \
            return; \
        } \
    }

    FindObjectWithID(pictures)
    FindObjectWithID(buttons)
    FindObjectWithID(checkboxes)
    FindObjectWithID(radioButtons)
    FindObjectWithID(labels)
    FindObjectWithID(editBoxes)
    FindObjectWithID(listboxes)
    FindObjectWithID(comboBoxes)
    FindObjectWithID(sliders)
    FindObjectWithID(scrollbars)
    FindObjectWithID(loadingBars)

    #undef FindObjectWithID
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::moveObjectX(int pixels)
{
    // Get the pointer to the property
    tgui::EditBox* editbox = propertyWindow.getEditBox("text_Left");

    // Adjust the property
    int left = atoi(editbox->getText().c_str());
    left += pixels;

    // Change the contents of the edit box
    editbox->setText(tgui::to_string(left));

    unsigned int i;

    #define FindObjectWithID(Object, objects) \
    for (i=0; i<objects.size(); ++i) \
    { \
        if (objects[i].id == currentID) \
        { \
            updateProperty(Property_##Object##_Left); \
            return; \
        } \
    }

    FindObjectWithID(Picture, pictures)
    FindObjectWithID(Button, buttons)
    FindObjectWithID(Checkbox, checkboxes)
    FindObjectWithID(Checkbox, radioButtons)
    FindObjectWithID(Label, labels)
    FindObjectWithID(EditBox, editBoxes)
    FindObjectWithID(Listbox, listboxes)
    FindObjectWithID(ComboBox, comboBoxes)
    FindObjectWithID(Slider, sliders)
    FindObjectWithID(Scrollbar, scrollbars)
    FindObjectWithID(LoadingBar, loadingBars)

    #undef FindObjectWithID
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::moveObjectY(int pixels)
{
    // Get the pointer to the property
    tgui::EditBox* editbox = propertyWindow.getEditBox("text_Top");

    // Adjust the property
    int top = atoi(editbox->getText().c_str());
    top += pixels;

    // Change the contents of the edit box
    editbox->setText(tgui::to_string(top));

    unsigned int i;

    #define FindObjectWithID(Object, objects) \
    for (i=0; i<objects.size(); ++i) \
    { \
        if (objects[i].id == currentID) \
        { \
            updateProperty(Property_##Object##_Top); \
            return; \
        } \
    }

    FindObjectWithID(Picture, pictures)
    FindObjectWithID(Button, buttons)
    FindObjectWithID(Checkbox, checkboxes)
    FindObjectWithID(Checkbox, radioButtons)
    FindObjectWithID(Label, labels)
    FindObjectWithID(EditBox, editBoxes)
    FindObjectWithID(Listbox, listboxes)
    FindObjectWithID(ComboBox, comboBoxes)
    FindObjectWithID(Slider, sliders)
    FindObjectWithID(Scrollbar, scrollbars)
    FindObjectWithID(LoadingBar, loadingBars)

    #undef FindObjectWithID
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::resizeObject(unsigned int addToWidth, unsigned int addToHeight)
{
    // Get the pointer to the properties
    tgui::EditBox* editboxWidth = propertyWindow.getEditBox("text_Width");
    tgui::EditBox* editboxHeight = propertyWindow.getEditBox("text_Height");

    // Adjust the properties
    int width = atoi(editboxWidth->getText().c_str());
    int height = atoi(editboxHeight->getText().c_str());
    width += addToWidth;
    height += addToHeight;

    // Change the contents of the edit boxes
    editboxWidth->setText(tgui::to_string(width));
    editboxHeight->setText(tgui::to_string(height));

    unsigned int i;

    #define FindObjectWithID(Object, objects) \
    for (i=0; i<objects.size(); ++i) \
    { \
        if (objects[i].id == currentID) \
        { \
            updateProperty(Property_##Object##_Width); \
            updateProperty(Property_##Object##_Height); \
            return; \
        } \
    }

    FindObjectWithID(Picture, pictures)
    FindObjectWithID(Button, buttons)
    FindObjectWithID(Checkbox, checkboxes)
    FindObjectWithID(Checkbox, radioButtons)
    FindObjectWithID(Label, labels)
    FindObjectWithID(EditBox, editBoxes)
    FindObjectWithID(Listbox, listboxes)
    FindObjectWithID(ComboBox, comboBoxes)
    FindObjectWithID(Slider, sliders)
    FindObjectWithID(Scrollbar, scrollbars)
    FindObjectWithID(LoadingBar, loadingBars)

    #undef FindObjectWithID
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Builder::loadForm()
{
    // Remove all existing objects from the form
    mainWindow.removeAllObjects();
    
    // Recreate the scale squares pictures
    mainWindow.addButton("Square_TopLeft")->load("images/Square");
    mainWindow.copyButton("Square_TopLeft", "Square_Top");
    mainWindow.copyButton("Square_TopLeft", "Square_TopRight");
    mainWindow.copyButton("Square_TopLeft", "Square_Right");
    mainWindow.copyButton("Square_TopLeft", "Square_BottomRight");
    mainWindow.copyButton("Square_TopLeft", "Square_Bottom");
    mainWindow.copyButton("Square_TopLeft", "Square_BottomLeft");
    mainWindow.copyButton("Square_TopLeft", "Square_Left");

    // Remove all properties
    pictures.clear();
    buttons.clear();
    checkboxes.clear();
    radioButtons.clear();
    labels.clear();
    editBoxes.clear();
    listboxes.clear();
    comboBoxes.clear();
    sliders.clear();
    scrollbars.clear();
    loadingBars.clear();
    
    // Make sure the window is selected when it goes wrong
    currentID = 1;
    
    // Create a temporary window
    tgui::Window tempWindow;
    
    // Load all the objects in the temporary window
    if (tempWindow.loadObjectsFromFile("form.txt"))
    {
        // Get a list of all the loaded objects
        std::vector<tgui::OBJECT*> objects = tempWindow.getObjects();
        std::vector<std::string> objectNames = tempWindow.getObjectNames();
        
        tgui::Checkbox c = *tempWindow.getCheckbox("t");
        
        // Loop through all objects
        for (unsigned int i=0; i<objects.size(); ++i)
        {
            // Check what the object type is
            if (objects[i]->getObjectType() == tgui::label)
            {
                // Convert the object to a label (which it is)
                tgui::Label* object = static_cast<tgui::Label*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::label, objectNames[i]);
                labels.back().left.value = object->getPosition().x;
                labels.back().top.value = object->getPosition().y;
                labels.back().width.value = object->getScaledSize().x;
                labels.back().height.value = object->getScaledSize().y;
                labels.back().text.value = object->getText();
                labels.back().textSize.value = object->getTextSize();
                labels.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                labels.back().textFont.value = "Global";
                labels.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::Label* realObject = mainWindow.getLabel(tgui::to_string(id));
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setText(object->getText());
                realObject->setTextSize(object->getTextSize());
                realObject->setTextColor(object->getTextColor());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::picture)
            {
                // Convert the object to a picture (which it is)
                tgui::Picture* object = static_cast<tgui::Picture*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::picture, objectNames[i]);
                pictures.back().filename.value = object->getLoadedFilename();
                pictures.back().left.value = object->getPosition().x;
                pictures.back().top.value = object->getPosition().y;
                pictures.back().width.value = object->getScaledSize().x;
                pictures.back().height.value = object->getScaledSize().y;
                pictures.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::Picture* realObject = mainWindow.getPicture(tgui::to_string(id));
                realObject->load(object->getLoadedFilename());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::button)
            {
                // Convert the object to a button (which it is)
                tgui::Button* object = static_cast<tgui::Button*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::button, objectNames[i]);
                buttons.back().pathname.value = object->getLoadedPathname();
                buttons.back().left.value = object->getPosition().x;
                buttons.back().top.value = object->getPosition().y;
                buttons.back().width.value = object->getScaledSize().x;
                buttons.back().height.value = object->getScaledSize().y;
                buttons.back().text.value = object->getText();
                buttons.back().textSize.value = object->getTextSize();
                buttons.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                buttons.back().textFont.value = "Global";
                buttons.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::Button* realObject = mainWindow.getButton(tgui::to_string(id));
                realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setText(object->getText());
                realObject->setTextSize(object->getTextSize());
                realObject->setTextColor(object->getTextColor());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::checkbox)
            {
                // Convert the object to a checkbox (which it is)
                tgui::Checkbox* object = static_cast<tgui::Checkbox*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::checkbox, objectNames[i]);
                checkboxes.back().pathname.value = object->getLoadedPathname();
                checkboxes.back().left.value = object->getPosition().x;
                checkboxes.back().top.value = object->getPosition().y;
                checkboxes.back().width.value = object->getScaledSize().x;
                checkboxes.back().height.value = object->getScaledSize().y;
                checkboxes.back().checked.value = object->isChecked();
                checkboxes.back().text.value = object->getText();
                checkboxes.back().textSize.value = object->getTextSize();
                checkboxes.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                checkboxes.back().textFont.value = "Global";
                checkboxes.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::Checkbox* realObject = mainWindow.getCheckbox(tgui::to_string(id));
                //realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setText(object->getText());
                realObject->setTextSize(object->getTextSize());
                realObject->setTextColor(object->getTextColor());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->callbackID = object->callbackID;
                
                if (object->isChecked())
                    realObject->check();
                else
                    realObject->uncheck();
            }
            else if (objects[i]->getObjectType() == tgui::radioButton)
            {
                // Convert the object to a radio button (which it is)
                tgui::RadioButton* object = static_cast<tgui::RadioButton*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::radioButton, objectNames[i]);
                radioButtons.back().pathname.value = object->getLoadedPathname();
                radioButtons.back().left.value = object->getPosition().x;
                radioButtons.back().top.value = object->getPosition().y;
                radioButtons.back().width.value = object->getScaledSize().x;
                radioButtons.back().height.value = object->getScaledSize().y;
                radioButtons.back().checked.value = object->isChecked();
                radioButtons.back().text.value = object->getText();
                radioButtons.back().textSize.value = object->getTextSize();
                radioButtons.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                radioButtons.back().textFont.value = "Global";
                radioButtons.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::RadioButton* realObject = mainWindow.getRadioButton(tgui::to_string(id));
                realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setText(object->getText());
                realObject->setTextSize(object->getTextSize());
                realObject->setTextColor(object->getTextColor());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->callbackID = object->callbackID;
                
                if (object->isChecked())
                    realObject->check();
                else
                    realObject->uncheck();
            }
            else if (objects[i]->getObjectType() == tgui::editBox)
            {
                // Convert the object to an edit box (which it is)
                tgui::EditBox* object = static_cast<tgui::EditBox*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::editBox, objectNames[i]);
                editBoxes.back().pathname.value = object->getLoadedPathname();
                editBoxes.back().left.value = object->getPosition().x;
                editBoxes.back().top.value = object->getPosition().y;
                editBoxes.back().width.value = object->getScaledSize().x;
                editBoxes.back().height.value = object->getScaledSize().y;
                editBoxes.back().text.value = object->getText();
                editBoxes.back().textSize.value = object->getTextSize();
                editBoxes.back().textFont.value = "Global";
                editBoxes.back().passwordChar.value = object->getPasswordChar();
                editBoxes.back().maximumCharacters.value = object->getMaximumCharacters();
                editBoxes.back().borders.value = "(" + tgui::to_string(object->getBorders().x1) + "," + tgui::to_string(object->getBorders().x2) + "," + tgui::to_string(object->getBorders().x3) + "," + tgui::to_string(object->getBorders().x4) + ")";
                editBoxes.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                editBoxes.back().selectedTextColor.value = tgui::convertColorToString(object->getSelectedTextColor());
                editBoxes.back().selectedTextBackgroundColor.value = tgui::convertColorToString(object->getSelectedTextBackgroundColor());
                editBoxes.back().unfocusedSelectedTextBackgroundColor.value = tgui::convertColorToString(object->getUnfocusedSelectedTextBackgroundColor());
                editBoxes.back().selectionPointColor.value = tgui::convertColorToString(object->selectionPointColor);
                editBoxes.back().selectionPointWidth.value = object->selectionPointWidth;
                editBoxes.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::EditBox* realObject = mainWindow.getEditBox(tgui::to_string(id));
                realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setText(object->getText());
                realObject->setTextSize(object->getTextSize());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->setPasswordChar(object->getPasswordChar());
                realObject->setMaximumCharacters(object->getMaximumCharacters());
                realObject->setBorders(object->getBorders().x1, object->getBorders().x2, object->getBorders().x3, object->getBorders().x4);
                realObject->changeColors(object->getTextColor(), object->getSelectedTextColor(), object->getSelectedTextBackgroundColor(), object->getUnfocusedSelectedTextBackgroundColor());
                realObject->selectionPointColor = object->selectionPointColor;
                realObject->selectionPointWidth = object->selectionPointWidth;
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::slider)
            {
                // Convert the object to a slider (which it is)
                tgui::Slider* object = static_cast<tgui::Slider*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::slider, objectNames[i]);
                sliders.back().pathname.value = object->getLoadedPathname();
                sliders.back().left.value = object->getPosition().x;
                sliders.back().top.value = object->getPosition().y;
                sliders.back().width.value = object->getScaledSize().x;
                sliders.back().height.value = object->getScaledSize().y;
                sliders.back().verticalScroll.value = object->getVerticalScroll();
                sliders.back().value.value = object->getValue();
                sliders.back().minimum.value = object->getMinimum();
                sliders.back().maximum.value = object->getMaximum();
                sliders.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::Slider* realObject = mainWindow.getSlider(tgui::to_string(id));
                realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setVerticalScroll(object->getVerticalScroll());
                realObject->setValue(object->getValue());
                realObject->setMinimum(object->getMinimum());
                realObject->setMaximum(object->getMaximum());
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::scrollbar)
            {
                // Convert the object to a scrollbar (which it is)
                tgui::Scrollbar* object = static_cast<tgui::Scrollbar*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::scrollbar, objectNames[i]);
                scrollbars.back().pathname.value = object->getLoadedPathname();
                scrollbars.back().left.value = object->getPosition().x;
                scrollbars.back().top.value = object->getPosition().y;
                scrollbars.back().width.value = object->getScaledSize().x;
                scrollbars.back().height.value = object->getScaledSize().y;
                scrollbars.back().verticalScroll.value = object->getVerticalScroll();
                scrollbars.back().value.value = object->getValue();
                scrollbars.back().lowValue.value = object->getLowValue();
                scrollbars.back().maximum.value = object->getMaximum();
                scrollbars.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::Scrollbar* realObject = mainWindow.getScrollbar(tgui::to_string(id));
                realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setVerticalScroll(object->getVerticalScroll());
                realObject->setValue(object->getValue());
                realObject->setLowValue(object->getLowValue());
                realObject->setMaximum(object->getMaximum());
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::listbox)
            {
                // Convert the object to a listbox (which it is)
                tgui::Listbox* object = static_cast<tgui::Listbox*>(objects[i]);
                
                // Get a list of the items
                std::vector<std::string> items = object->getItems();
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::listbox, objectNames[i]);
                listboxes.back().left.value = object->getPosition().x;
                listboxes.back().top.value = object->getPosition().y;
                listboxes.back().width.value = object->getScaledSize().x;
                listboxes.back().height.value = object->getScaledSize().y;
                listboxes.back().scrollbarPathname.value = object->getLoadedScrollbarPathname();
                listboxes.back().itemHeight.value = object->getItemHeight();
                listboxes.back().maximumItems.value = object->getMaximumItems();
                listboxes.back().borders.value = "(" + tgui::to_string(object->getBorders().x1) + "," + tgui::to_string(object->getBorders().x2) + "," + tgui::to_string(object->getBorders().x3) + "," + tgui::to_string(object->getBorders().x4) + ")";
                listboxes.back().backgroundColor.value = tgui::convertColorToString(object->getBackgroundColor());
                listboxes.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                listboxes.back().selectedBackgroundColor.value = tgui::convertColorToString(object->getSelectedBackgroundColor());
                listboxes.back().selectedTextColor.value = tgui::convertColorToString(object->getSelectedTextColor());
                listboxes.back().borderColor.value = tgui::convertColorToString(object->getBorderColor());
                listboxes.back().textFont.value = "Global";
                listboxes.back().callbackID.value = object->callbackID;
                
                // If there is an item then add it to the listbox
                if (items.empty() == false)
                {
                    listboxes.back().items.value = items[0];
                    
                    // Add the other items
                    for (unsigned int i=1; i<items.size(); ++i)
                        listboxes.back().items.value += "," + items[i];
                }
                listboxes.back().selectedItem.value = object->getSelectedItemID();
                
                // Draw the object in the correct way
                tgui::Listbox* realObject = mainWindow.getListbox(tgui::to_string(id));
                realObject->load(object->getScaledSize().x, object->getScaledSize().y, object->getLoadedScrollbarPathname(), object->getItemHeight());
                realObject->setPosition(object->getPosition());
                realObject->setMaximumItems(object->getMaximumItems());
                realObject->setBorders(object->getBorders().x1, object->getBorders().x2, object->getBorders().x3, object->getBorders().x4);
                realObject->changeColors(object->getBackgroundColor(), object->getTextColor(), object->getSelectedBackgroundColor(), object->getSelectedTextColor(), object->getBorderColor());
                for (unsigned int i=0; i<items.size(); ++i) realObject->addItem(items[i]);
                realObject->setSelectedItem(object->getSelectedItem());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::comboBox)
            {
                // Convert the object to a combo box (which it is)
                tgui::ComboBox* object = static_cast<tgui::ComboBox*>(objects[i]);
                
                // Get a list of the items
                std::vector<std::string> items = object->getItems();
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::comboBox, objectNames[i]);
                comboBoxes.back().pathname.value = object->getLoadedPathname();
                comboBoxes.back().left.value = object->getPosition().x;
                comboBoxes.back().top.value = object->getPosition().y;
                comboBoxes.back().width.value = object->getScaledSize().x;
                comboBoxes.back().height.value = object->getScaledSize().y;
                comboBoxes.back().scrollbarPathname.value = object->getLoadedScrollbarPathname();
                comboBoxes.back().borders.value = "(" + tgui::to_string(object->getBorders().x1) + "," + tgui::to_string(object->getBorders().x2) + "," + tgui::to_string(object->getBorders().x3) + "," + tgui::to_string(object->getBorders().x4) + ")";
                comboBoxes.back().backgroundColor.value = tgui::convertColorToString(object->getBackgroundColor());
                comboBoxes.back().textColor.value = tgui::convertColorToString(object->getTextColor());
                comboBoxes.back().selectedBackgroundColor.value = tgui::convertColorToString(object->getSelectedBackgroundColor());
                comboBoxes.back().selectedTextColor.value = tgui::convertColorToString(object->getSelectedTextColor());
                comboBoxes.back().borderColor.value = tgui::convertColorToString(object->getBorderColor());
                comboBoxes.back().itemsToDisplay.value = object->getItemsToDisplay();
                comboBoxes.back().textFont.value = "Global";
                comboBoxes.back().callbackID.value = object->callbackID;
                
                // If there is an item then add it to the listbox
                if (items.empty() == false)
                {
                    comboBoxes.back().items.value = items[0];
                    
                    // Add the other items
                    for (unsigned int i=1; i<items.size(); ++i)
                        listboxes.back().items.value += "," + items[i];
                }
                comboBoxes.back().selectedItem.value = object->getSelectedItemID();
                
                // Draw the object in the correct way
                tgui::ComboBox* realObject = mainWindow.getComboBox(tgui::to_string(id));
                realObject->load(object->getLoadedPathname(), object->getScaledSize().x, object->getItemsToDisplay() , object->getLoadedScrollbarPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setBorders(object->getBorders().x1, object->getBorders().x2, object->getBorders().x3, object->getBorders().x4);
                realObject->changeColors(object->getBackgroundColor(), object->getTextColor(), object->getSelectedBackgroundColor(), object->getSelectedTextColor(), object->getBorderColor());
                for (unsigned int i=0; i<items.size(); ++i) realObject->addItem(items[i]);
                realObject->setSelectedItem(object->getSelectedItem());
                realObject->setTextFont(mainWindow.globalFont);
                realObject->callbackID = object->callbackID;
            }
            else if (objects[i]->getObjectType() == tgui::loadingBar)
            {
                // Convert the object to a loading bar (which it is)
                tgui::LoadingBar* object = static_cast<tgui::LoadingBar*>(objects[i]);
                
                // Create and fill the properties of the object
                unsigned int id = newObject(tgui::loadingBar, objectNames[i]);
                loadingBars.back().pathname.value = object->getLoadedPathname();
                loadingBars.back().left.value = object->getPosition().x;
                loadingBars.back().top.value = object->getPosition().y;
                loadingBars.back().width.value = object->getScaledSize().x;
                loadingBars.back().height.value = object->getScaledSize().y;
                loadingBars.back().value.value = object->getValue();
                loadingBars.back().minimum.value = object->getMinimum();
                loadingBars.back().maximum.value = object->getMaximum();
                loadingBars.back().callbackID.value = object->callbackID;
                
                // Draw the object in the correct way
                tgui::LoadingBar* realObject = mainWindow.getLoadingBar(tgui::to_string(id));
                realObject->load(object->getLoadedPathname());
                realObject->setPosition(object->getPosition());
                realObject->setSize(object->getScaledSize().x, object->getScaledSize().y);
                realObject->setValue(object->getValue());
                realObject->setMinimum(object->getMinimum());
                realObject->setMaximum(object->getMaximum());
                realObject->callbackID = object->callbackID;
            }
        }
        
        // Select the window
        currentID = 1;
        resizePropertyWindow();
        
        // The file has been loaded successfully.
        return true;
    }
    else // Loading failed
        return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TAB "    "

#define FindLowestID(objects, ID) \
for (i=0; i<objects.size(); ++i) \
{ \
    if ((objects[i].id < lowestID) && (objects[i].id > doneID)) \
    { \
        lowestID = objects[i].id; \
        objectIndex = i; \
        objectID = ID; \
    } \
}

#define AddBrackets(string) \
if (string.size() > 0) \
{ \
    if (string[0] != '(') \
        string.insert(string.begin(), '('); \
  \
    if (string[string.length()-1] != ')') \
        string.insert(string.end(), ')'); \
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Builder::saveForm()
{
    // Open the form file for writing
    FILE* pFile = fopen("form.txt", "w");

    if (pFile == NULL)
        return;

    // Write the header
    std::string line("// This file was generated by TGUI Form Builder " VERSION "\n\n");
    fwrite(line.c_str(), 1, line.size(), pFile);


    unsigned int doneID = 0;

    // Write the start of the window
    line = "Window: \"";
    line.append(windows[0].name.value).append("\"\n{\n");
    fwrite(line.c_str(), 1, line.size(), pFile);

    unsigned int count = TGUI_MAX_OBJECTS;
    while (--count)
    {
        unsigned int  lowestID = TGUI_MAX_OBJECTS;
        unsigned char objectID = 0;
        unsigned int  objectIndex = 0;
        unsigned int  i;

        FindLowestID(pictures, tgui::picture)
        FindLowestID(buttons, tgui::button)
        FindLowestID(checkboxes, tgui::checkbox)
        FindLowestID(radioButtons, tgui::radioButton)
        FindLowestID(labels, tgui::label)
        FindLowestID(editBoxes, tgui::editBox)
        FindLowestID(listboxes, tgui::listbox)
        FindLowestID(comboBoxes, tgui::comboBox)
        FindLowestID(sliders, tgui::slider)
        FindLowestID(scrollbars, tgui::scrollbar)
        FindLowestID(loadingBars, tgui::loadingBar)

        // Check if you found another object
        if (objectID == 0)
            break;

        // The next id can be marked as done
        doneID = lowestID;

        // Check the type of the item
        if (objectID == tgui::picture)
        {
            line = TAB "Picture: \"";
            line.append(pictures[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Filename   = \"";
            line.append(pictures[objectIndex].filename.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left       = ";
            line.append(tgui::to_string(pictures[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top        = ";
            line.append(tgui::to_string(pictures[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width      = ";
            line.append(tgui::to_string(pictures[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height     = ";
            line.append(tgui::to_string(pictures[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID = ";
            line.append(tgui::to_string(pictures[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::button)
        {
            line = TAB "Button: \"";
            line.append(buttons[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname   = \"";
            line.append(buttons[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left       = ";
            line.append(tgui::to_string(buttons[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top        = ";
            line.append(tgui::to_string(buttons[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width      = ";
            line.append(tgui::to_string(buttons[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height     = ";
            line.append(tgui::to_string(buttons[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Text       = \"";
            line.append(buttons[objectIndex].text.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextSize   = ";
            line.append(tgui::to_string(buttons[objectIndex].textSize.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor  = ";
            AddBrackets(buttons[objectIndex].textColor.value)
            line.append(buttons[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID = ";
            line.append(tgui::to_string(buttons[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::checkbox)
        {
            line = TAB "Checkbox: \"";
            line.append(checkboxes[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname   = \"";
            line.append(checkboxes[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left       = ";
            line.append(tgui::to_string(checkboxes[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top        = ";
            line.append(tgui::to_string(checkboxes[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width      = ";
            line.append(tgui::to_string(checkboxes[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height     = ";
            line.append(tgui::to_string(checkboxes[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Checked    = ";
            line.append(tgui::to_string(checkboxes[objectIndex].checked.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Text       = \"";
            line.append(checkboxes[objectIndex].text.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextSize   = ";
            line.append(tgui::to_string(checkboxes[objectIndex].textSize.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor  = ";
            AddBrackets(checkboxes[objectIndex].textColor.value)
            line.append(checkboxes[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID = ";
            line.append(tgui::to_string(checkboxes[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::radioButton)
        {
            line = TAB "RadioButton: \"";
            line.append(radioButtons[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname   = \"";
            line.append(radioButtons[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left       = ";
            line.append(tgui::to_string(radioButtons[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top        = ";
            line.append(tgui::to_string(radioButtons[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width      = ";
            line.append(tgui::to_string(radioButtons[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height     = ";
            line.append(tgui::to_string(radioButtons[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Checked    = ";
            line.append(tgui::to_string(radioButtons[objectIndex].checked.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Text       = \"";
            line.append(radioButtons[objectIndex].text.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextSize   = ";
            line.append(tgui::to_string(radioButtons[objectIndex].textSize.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor  = ";
            AddBrackets(radioButtons[objectIndex].textColor.value)
            line.append(radioButtons[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID = ";
            line.append(tgui::to_string(radioButtons[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::label)
        {
            line = TAB "Label: \"";
            line.append(labels[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left       = ";
            line.append(tgui::to_string(labels[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top        = ";
            line.append(tgui::to_string(labels[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Text       = \"";
            line.append(labels[objectIndex].text.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextSize   = ";
            line.append(tgui::to_string(labels[objectIndex].textSize.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor  = ";
            AddBrackets(labels[objectIndex].textColor.value)
            line.append(labels[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID = ";
            line.append(tgui::to_string(labels[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::editBox)
        {
            line = TAB "EditBox: \"";
            line.append(editBoxes[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname          = \"";
            line.append(editBoxes[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left              = ";
            line.append(tgui::to_string(editBoxes[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top               = ";
            line.append(tgui::to_string(editBoxes[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width             = ";
            line.append(tgui::to_string(editBoxes[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height            = ";
            line.append(tgui::to_string(editBoxes[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Text              = \"";
            line.append(editBoxes[objectIndex].text.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextSize          = ";
            line.append(tgui::to_string(editBoxes[objectIndex].textSize.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            if (editBoxes[objectIndex].passwordChar.value != '\0')
            {
                line = TAB TAB "PasswordChar      = \"";
                line.push_back(editBoxes[objectIndex].passwordChar.value);
                line.append("\"\n");
                fwrite(line.c_str(), 1, line.size(), pFile);
            }

            line = TAB TAB "MaximumCharacters = ";
            line.append(tgui::to_string(editBoxes[objectIndex].maximumCharacters.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Borders           = ";
            AddBrackets(editBoxes[objectIndex].borders.value)
            line.append(editBoxes[objectIndex].borders.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor         = ";
            AddBrackets(editBoxes[objectIndex].textColor.value)
            line.append(editBoxes[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectedTextColor = ";
            AddBrackets(editBoxes[objectIndex].selectedTextColor.value)
            line.append(editBoxes[objectIndex].selectedTextColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectedTextBackgroundColor = ";
            AddBrackets(editBoxes[objectIndex].selectedTextBackgroundColor.value)
            line.append(editBoxes[objectIndex].selectedTextBackgroundColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "UnfocusedSelectedTextBackgroundColor = ";
            AddBrackets(editBoxes[objectIndex].unfocusedSelectedTextBackgroundColor.value)
            line.append(editBoxes[objectIndex].unfocusedSelectedTextBackgroundColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectionPointColor = ";
            AddBrackets(editBoxes[objectIndex].selectionPointColor.value)
            line.append(editBoxes[objectIndex].selectionPointColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectionPointWidth = ";
            line.append(tgui::to_string(editBoxes[objectIndex].selectionPointWidth.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID          = ";
            line.append(tgui::to_string(editBoxes[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::listbox)
        {
            line = TAB "Listbox: \"";
            line.append(listboxes[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left                    = ";
            line.append(tgui::to_string(listboxes[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top                     = ";
            line.append(tgui::to_string(listboxes[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width                   = ";
            line.append(tgui::to_string(listboxes[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height                  = ";
            line.append(tgui::to_string(listboxes[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "ScrollbarPathname       = \"";
            line.append(listboxes[objectIndex].scrollbarPathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "ItemHeight              = ";
            line.append(tgui::to_string(listboxes[objectIndex].itemHeight.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "MaximumItems            = ";
            line.append(tgui::to_string(listboxes[objectIndex].maximumItems.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Borders                 = ";
            AddBrackets(listboxes[objectIndex].borders.value)
            line.append(listboxes[objectIndex].borders.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "BackgroundColor         = ";
            AddBrackets(listboxes[objectIndex].backgroundColor.value)
            line.append(listboxes[objectIndex].backgroundColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor               = ";
            AddBrackets(listboxes[objectIndex].textColor.value)
            line.append(listboxes[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectedBackgroundColor = ";
            AddBrackets(listboxes[objectIndex].selectedBackgroundColor.value)
            line.append(listboxes[objectIndex].selectedBackgroundColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectedTextColor       = ";
            AddBrackets(listboxes[objectIndex].selectedTextColor.value)
            line.append(listboxes[objectIndex].selectedTextColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "BorderColor             = ";
            AddBrackets(listboxes[objectIndex].borderColor.value)
            line.append(listboxes[objectIndex].borderColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            // Make a list of all items
            {
                std::string strItems = listboxes[objectIndex].items.value;
                bool commaFound = true;

                // Loop all items
                while (commaFound)
                {
                    // Search for the next comma
                    std::string::size_type commaPos = strItems.find(',');

                    // Check if a comma was found
                    if (commaPos != std::string::npos)
                    {
                        // Add the item
                        line = TAB TAB "Item                    = \"";
                        line.append(strItems.substr(0, commaPos)).append("\"\n");
                        fwrite(line.c_str(), 1, line.size(), pFile);

                        // Erase the item from the string
                        strItems.erase(0, commaPos + 1);
                    }
                    else // No comma was found
                    {
                        // Add the last item, when the string isn't empty
                        if (strItems.size() > 0)
                        {
                            line = TAB TAB "Item                    = \"";
                            line.append(strItems).append("\"\n");
                            fwrite(line.c_str(), 1, line.size(), pFile);
                        }

                        // Stop the loop
                        commaFound = false;
                    }
                }
            }

            line = TAB TAB "SelectedItem            = ";
            line.append(tgui::to_string(listboxes[objectIndex].selectedItem.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID              = ";
            line.append(tgui::to_string(listboxes[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::comboBox)
        {
            line = TAB "ComboBox: \"";
            line.append(comboBoxes[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname                = \"";
            line.append(comboBoxes[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left                    = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top                     = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width                   = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height                  = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "ScrollbarPathname       = \"";
            line.append(comboBoxes[objectIndex].scrollbarPathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Borders                 = ";
            AddBrackets(comboBoxes[objectIndex].borders.value)
            line.append(comboBoxes[objectIndex].borders.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "BackgroundColor         = ";
            AddBrackets(comboBoxes[objectIndex].backgroundColor.value)
            line.append(comboBoxes[objectIndex].backgroundColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "TextColor               = ";
            AddBrackets(comboBoxes[objectIndex].textColor.value)
            line.append(comboBoxes[objectIndex].textColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectedBackgroundColor = ";
            AddBrackets(comboBoxes[objectIndex].selectedBackgroundColor.value)
            line.append(comboBoxes[objectIndex].selectedBackgroundColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "SelectedTextColor       = ";
            AddBrackets(comboBoxes[objectIndex].selectedTextColor.value)
            line.append(comboBoxes[objectIndex].selectedTextColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "BorderColor             = ";
            AddBrackets(comboBoxes[objectIndex].borderColor.value)
            line.append(comboBoxes[objectIndex].borderColor.value).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            // Make a list of all items
            {
                std::string strItems = comboBoxes[objectIndex].items.value;
                bool commaFound = true;

                // Loop all items
                while (commaFound)
                {
                    // Search for the next comma
                    std::string::size_type commaPos = strItems.find(',');

                    // Check if a comma was found
                    if (commaPos != std::string::npos)
                    {
                        // Add the item
                        line = TAB TAB "Item                    = \"";
                        line.append(strItems.substr(0, commaPos)).append("\"\n");
                        fwrite(line.c_str(), 1, line.size(), pFile);

                        // Erase the item from the string
                        strItems.erase(0, commaPos + 1);
                    }
                    else // No comma was found
                    {
                        // Add the last item, when the string isn't empty
                        if (strItems.size() > 0)
                        {
                            line = TAB TAB "Item                    = \"";
                            line.append(strItems).append("\"\n");
                            fwrite(line.c_str(), 1, line.size(), pFile);
                        }

                        // Stop the loop
                        commaFound = false;
                    }
                }
            }

            line = TAB TAB "SelectedItem            = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].selectedItem.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "ItemsToDisplay          = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].itemsToDisplay.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID              = ";
            line.append(tgui::to_string(comboBoxes[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::slider)
        {
            line = TAB "Slider: \"";
            line.append(sliders[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname       = \"";
            line.append(sliders[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "VerticalScroll = ";
            line.append(tgui::to_string(sliders[objectIndex].verticalScroll.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left           = ";
            line.append(tgui::to_string(sliders[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top            = ";
            line.append(tgui::to_string(sliders[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width          = ";
            line.append(tgui::to_string(sliders[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height         = ";
            line.append(tgui::to_string(sliders[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Value          = ";
            line.append(tgui::to_string(sliders[objectIndex].value.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Minimum        = ";
            line.append(tgui::to_string(sliders[objectIndex].minimum.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Maximum        = ";
            line.append(tgui::to_string(sliders[objectIndex].maximum.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID     = ";
            line.append(tgui::to_string(sliders[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::scrollbar)
        {
            line = TAB "Scrollbar: \"";
            line.append(scrollbars[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname       = \"";
            line.append(scrollbars[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "VerticalScroll = ";
            line.append(tgui::to_string(scrollbars[objectIndex].verticalScroll.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left           = ";
            line.append(tgui::to_string(scrollbars[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top            = ";
            line.append(tgui::to_string(scrollbars[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width          = ";
            line.append(tgui::to_string(scrollbars[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height         = ";
            line.append(tgui::to_string(scrollbars[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "LowValue       = ";
            line.append(tgui::to_string(scrollbars[objectIndex].lowValue.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Maximum        = ";
            line.append(tgui::to_string(scrollbars[objectIndex].maximum.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Value          = ";
            line.append(tgui::to_string(scrollbars[objectIndex].value.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID     = ";
            line.append(tgui::to_string(scrollbars[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
        else if (objectID == tgui::loadingBar)
        {
            line = TAB "LoadingBar: \"";
            line.append(loadingBars[objectIndex].name.value).append("\"\n" TAB "{\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Pathname   = \"";
            line.append(loadingBars[objectIndex].pathname.value).append("\"\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Left       = ";
            line.append(tgui::to_string(loadingBars[objectIndex].left.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Top        = ";
            line.append(tgui::to_string(loadingBars[objectIndex].top.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Width      = ";
            line.append(tgui::to_string(loadingBars[objectIndex].width.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Height     = ";
            line.append(tgui::to_string(loadingBars[objectIndex].height.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Minimum    = ";
            line.append(tgui::to_string(loadingBars[objectIndex].minimum.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Maximum    = ";
            line.append(tgui::to_string(loadingBars[objectIndex].maximum.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "Value      = ";
            line.append(tgui::to_string(loadingBars[objectIndex].value.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB TAB "CallbackID = ";
            line.append(tgui::to_string(loadingBars[objectIndex].callbackID.value)).append("\n");
            fwrite(line.c_str(), 1, line.size(), pFile);

            line = TAB "}\n\n";
            fwrite(line.c_str(), 1, line.size(), pFile);
        }
    }

    // Write the last bracket
    line = "}\n";
    fwrite(line.c_str(), 1, line.size(), pFile);

    // Close the file
    fclose(pFile);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
