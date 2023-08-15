#include <Dec.h>
#include <Ra.h>

const int motorInterfaceType = 1;

Dec dec;
Ra ra;
Thread decThread = Thread();
Thread raThread = Thread();

void initDecThread()
{
  dec.init();
}

void initRaThread()
{
  ra.init();
}

class Control
{
public:
  Control()
  {
    decThread.enabled = true;
    decThread.onRun(initDecThread);

    raThread.enabled = true;
    raThread.onRun(initRaThread);

    Serial.println("CONTROL MODULE: initialization finished");
  }

  void init()
  {
    while (true)
    {
      while (Serial.available() == 0)
      {
      }

      int code = Serial.parseInt();
      int args[6];
      int i = 0;

      if (Serial.available() > 0)
      {
        args[i] = Serial.parseInt();
        i++;
      }

      switch (code)
      {
      case 1:
        decThread.run();
        raThread.run();
        break;
      case 2:
        dec.setDegree(args[0], args[1], args[2]);
        ra.setRaTime(args[3], args[4], args[5]);
        break;
      case 3:
        dec.setDegree(args[0], args[1], args[2]);
        break;
      case 4:
        ra.setRaTime(args[0], args[1], args[2]);
        break;
      }
    }
  }
};