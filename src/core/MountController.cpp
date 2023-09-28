void MountController::initialize()
{
  dec.initialize();
  ra.initialize();
  long raTime = ra.getRaTime();

  raCoordinates.hour = raTime/(HOURS_IN_SEC);
  raCoordinates.min = (raTime / 60) % 60;
  raCoordinates.sec = raTime % 60;

  update();

  Serial.println("MOUNT CONTROLLER MODULE: initialization finished");
}

void MountController::update()
{
  ra.setRaTime(raCoordinates.hour, raCoordinates.min, raCoordinates.sec);
  dec.setSide(ra.getSide());
  dec.setDegree(decCoordinates.deg, decCoordinates.min, decCoordinates.sec);

  dec.update();
  ra.update();
}

void MountController::setRaCoordinate(int h, int m, int s)
{
  raCoordinates.hour = h;
  raCoordinates.min = m;
  raCoordinates.sec = s;
}

void MountController::setDecCoordinate(int d, int m, int s)
{
  decCoordinates.deg = d;
  decCoordinates.min = m;
  decCoordinates.sec = s;
}

void MountController::getRaCoordinate(int &h, int &m, int &s)
{
  h = raCoordinates.hour;
  m = raCoordinates.min;
  s = raCoordinates.hour;
}

void MountController::getDecCoordinate(int &d, int &m, int &s)
{
  d = decCoordinates.deg;
  m = decCoordinates.min;
  s = decCoordinates.sec;
}