#include "Control.h"

void Control::initialize() 
{
  _mount.initialize();
  _keypad.initialize();

  delay(100);
  _state = GOTO;
}

void Control::update() 
{
  _keypad.update();
  _mount.update();

  switch (_state) {
    case GOTO: 	       gotoItem(); break;
    case MANUAL        manualControlItem(); break;
    case COORDINATE:   coordinateItem(); break;
    case TIME:         timeItem(); break;
    case BRIGHT:       brightItem(); break;
    case OBJECTS:      objectsItem(); break;
  }

  switch (_state) {
    case GOTO: 	       gotoMenu(); break;
    case MANUAL        manualControlMenu(); break;
    case COORDINATE:   coordinateMenu(); break;
    case TIME:         timeMenu(); break;
    case BRIGHT:       brightMenu(); break;
    case OBJECTS:      objectsMenu(); break;
  }
}

void Control::gotoItem() 
{
  if (_keypad.pushed(C_ARROW_UP)) changeState(OBJECTS);
  if (_keypad.pushed(C_ARROW_DOWN)) changeState(MANUAL);
  if (_keypad.pushed(C_ENTER))
  {
    changeState(NULL);
    changeSubState(GOTO);
  }

  _display.renderGotoItem();
}

void Control::manualControlItem() 
{
  if (_keypad.pushed(C_ARROW_UP)) changeState(GOTO);
  if (_keypad.pushed(C_ARROW_DOWN)) changeState(COORDINATE);
  if (_keypad.pushed(C_ENTER))
  {
    changeState(NULL);
    changeSubState(MANUAL);
  }

  _display.renderManualItem();
}

void Control::coordinateItem() 
{
  if (_keypad.pushed(C_ARROW_UP)) changeState(MANUAL);
  if (_keypad.pushed(C_ARROW_DOWN)) changeState(TIME);
  if (_keypad.pushed(C_ENTER))
  {
    changeState(NULL);
    changeSubState(COORDINATE);
  }

  _display.renderCoordinateItem();
}

void Control::timeItem() 
{
  if (_keypad.pushed(C_ARROW_UP)) changeState(COORDINATE);
  if (_keypad.pushed(C_ARROW_DOWN)) changeState(BRIGHT);
  if (_keypad.pushed(C_ENTER))
  {
    changeState(NULL);
    changeSubState(TIME);
  }

  _display.renderTimeItem();
}

void Control::brightnessItem() 
{
  if (_keypad.pushed(C_ARROW_UP)) changeState(TIME);
  if (_keypad.pushed(C_ARROW_DOWN)) changeState(OBJECTS);
  if (_keypad.pushed(C_ENTER))
  {
    changeState(NULL);
    changeSubState(BRIGHT);
  }

  _display.renderBrightnessItem();
}

void Control::objectsItem() 
{
  if (_keypad.pushed(C_ARROW_UP)) changeState(BRIGHT);
  if (_keypad.pushed(C_ARROW_DOWN)) changeState(GOTO);
  if (_keypad.pushed(C_ENTER))
  {
    changeState(NULL);
    changeSubState(OBJECTS);
  }

  _display.renderObjectsItem();
}

void Control::gotoMenu() 
{
  if (_keypad.pushed(C_EXIT))
  {
    changeState(GOTO);
    changeSubState(NULL);
  }
}

void Control::manualControlMenu() 
{
  if (_keypad.pushed(C_EXIT))
  {
    changeState(MANUAL);
    changeSubState(NULL);
  }
}

void Control::coordinateMenu() 
{
  if (_keypad.pushed(C_EXIT))
  {
    changeState(COORDINATE);
    changeSubState(NULL);
  }
}

void Control::timeMenu() 
{
  if (_keypad.pushed(C_EXIT))
  {
    changeState(TIME);
    changeSubState(NULL);
  }
}

void Control::brightnessMenu() 
{
  if (_keypad.pushed(C_EXIT))
  {
    changeState(BRIGHT);
    changeSubState(NULL);
  }
}

void Control::objectsMenu() 
{
  if (_keypad.pushed(C_EXIT))
  {
    changeState(OBJECTS);
    changeSubState(NULL);
  }
}