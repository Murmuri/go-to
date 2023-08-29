#include "Control.h"


void Control::initialize() 
{
    _mount.initialize();
    _clock.initialize();

    delay(100);

    _state = MAIN;
}


void Control::update() 
{   
    switch (_state) {
        case MAIN: 	    mainMenu(); break;
        case GOTO: 	    gotoMenu(); break;
        case CALIB:     calibrationMenu(); break;
        case CATALOG:   catalogueMenu(); break;
        case TIME:      timeMenu(); break;
        case BRIGHT:    brightnessMenu(); break;
        case POSITION:  positionMenu(); break;
    }
    // нужно делать обязательно, что бы труба двигалась
    // любое движение осуществляется черз смену координат на которые нужно следовать
    _mount.update();
}

void Control::positionMenu() 
{

}

void Control::brightnessMenu() 
{

}

void Control::mainMenu() 
{

}

void Control::gotoMenu() 
{

}

void Control::timeMenu() 
{

}

void Control::calibrationMenu() 
{

}

void Control::catalogueMenu() 
{

}
