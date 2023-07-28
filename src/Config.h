// Main
const int SERIAL_SPEED = 9600;
// Pin
const int DEC_DIRECTION_PIN = 2;
const int DEC_SPEED_PIN = 3;
const int RA_DIRECTION_PIN = 4;
const int RA_SPEED_PIN = 5;
const int WATCH_CLK_PIN = 6;
const int WATCH_DAT_PIN = 7;
const int WATCH_RST_PIN = 8;
// Default coordinate
const int DEFAULT_DEC_DEGREE = 90;
const int DEFAULT_DEC_MINUTE = 0;
const int DEFAULT_DEC_SECONDS = 0;
// Declination module
const double DEC_GEAR_TRAIN = 3.375;
const int DEC_DEFAULT_RPM = 800;
const int DEC_MOTOR_STEPS = 800;
const int DEC_MOUNT_STEPS = 65;
const int DEC_MICRO_STEPS = 16;
// RA module
const double RA_GEAR_TRAIN = 2;
const int RA_DEFAULT_RPM = 800;
const int RA_MOTOR_STEPS = 800;
const int RA_MOUNT_STEPS = 130;
const int RA_MICRO_STEPS = 16;
// Watch module
const int LOCAL_TIME = 3;
const long EARTH_TIME = 1689903317;  // 21.07.24 1:35:17 utc
const long STAR_TIME = 1689897600; // 21.07.24 00:00:00 utc
const double STAR_DAY_COEFFICIENT = 0.99726956643518518519;