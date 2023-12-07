#include "Control.h"

void Control::initialize() 
{
  _mount.initialize();
  _keypad.initialize();

  delay(100);
  _state = GOTO_MENU;
}

void Control::update() 
{
  _keypad.update();
  _mount.update();

  switch (_state) {
    case GOTO_MENU: 	       goToMenu(); break;
    case COORDINATE_MENU:    coordinateMenu(); break;
    case TIME_MENU:          timeMenu(); break;
  }
}

void Control::goToMenu() 
{
  // TODO:
}

void Control::coordinateMenu() 
{
  // TODO:
}

void Control::timeMenu() 
{
  // TODO:
}
