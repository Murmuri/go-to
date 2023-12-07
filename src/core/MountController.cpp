void MountController::initialize()
{
  dec.initialize();
  ra.initialize();
  long raTime = ra.getRaTime();

  raCoordinateHours = raTime/(HOURS_IN_SEC);
  raCoordinatesMinutes = (raTime / 60) % 60;
  raCoordinatesSeconds = raTime % 60;

  update();

  Serial.println("MOUNT CONTROLLER MODULE: initialization finished");
}

void MountController::update()
{
  ra.setRaTime(raCoordinateHours, raCoordinatesMinutes, raCoordinatesSeconds);
  dec.setSide(ra.getSide());
  dec.setDegree(decCoordinatesDegrees, decCoordinatesMinutes, decCoordinatesSeconds);

  dec.update();
  ra.update();
}

void MountController::setRaCoordinateHours(int hour)
{
  raCoordinateHours = hour;
}

void MountController::setRaCoordinateMinutes(int min)
{
  raCoordinatesMinutes = min;
}

void MountController::setRaCoordinateSeconds(int sec)
{
  raCoordinatesSeconds = sec;
}

void MountController::getRaCoordinateHours()
{
  return raCoordinateHours;
}

void MountController::getRaCoordinateMinutes()
{
  return raCoordinatesMinutes;
}

void MountController::getRaCoordinateSeconds()
{
  return raCoordinatesSeconds;
}

void MountController::setDecCoordinateDegrees(int deg)
{
  decCoordinatesDegrees = deg;
}

void MountController::setDecCoordinateMinutes(int min)
{
  decCoordinatesMinutes = min;
}

void MountController::setDecCoordinateSeconds(int sec)
{
  decCoordinatesSeconds = sec;
}

void MountController::getDecCoordinateDegrees()
{
  return decCoordinatesDegrees;
}

void MountController::getDecCoordinateMinutes()
{
  return decCoordinatesMinutes;
}

void MountController::getDecCoordinateSeconds()
{
  return decCoordinatesSeconds;
}
