#include <Config.h>
#include <Dec.h>
#include <Ra.h>

const int motorInterfaceType = 1;
Dec dec;
Ra ra;

class Control
{
public:
  Control()
  {
    OS.attach(1, dec.init());
    OS.attach(2, ra.init());
    
    
    Serial.println("CONTROL MODULE: initialization finished");
  }

  void init()
  {
    while (true)
    {
        while (Serial.available() == 0) {}
        
        int code = Serial.parseInt(); 
        int args[6];
        int i = 0;

        if (Serial.available() > 0) {
            args[i] = Serial.parseInt();
            i++;
        }
        
        switch(code)
        {
            case 1: 
                OS.start(1); 
                OS.start(2); 
                break;
            case 2: 
                dec.setDegree(args[0], args[1], args[2]);
                ra.setMountStarTime(args[3],args[4],args[5]);
                break;
            case 3: 
                dec.setDegree(args[0], args[1], args[2]);
                break;
            case 4: 
                ra.setDegree(args[0], args[1], args[2]);
                break;
        }
    }
  }
};