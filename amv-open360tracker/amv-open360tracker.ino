
/* AMV Open Source 360° continuous rotation antenna tracker software
 * by Raúl Ortega https://github.com/raul-ortega/amv-open360tracker/
 * Sapanish community: http://www.aeromodelismovirtual.com/showthread.php?t=34530
 * 
 * Based on the original project from Samuel Brucksch https://github.com/SamuelBrucksch/open360tracker
 *
 * Digital Smooth method from Arduino playground: http://playground.arduino.cc/Main/DigitalSmooth
 * Local GPS uses parser from TinyGPS: http://arduiniana.org/libraries/tinygps/
 * Easing Ecuations by Robert Penner http://www.gizma.com/easing/
 */
 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "defines.h"
#include "config.h"
#include <Wire.h>
#include "compass.h"
#include "servos.h"
#include "inttypes.h"
#include "telemetry.h"
#include "math.h"
#include <TinyGPS.h>
#include "settings.h"

extern uint8_t Settings[EEPROM_SETTINGS];

#ifdef Mavlink
  #include <Mavlink.h>
#endif

//#ifdef TILT_EASING
  float _lasttilt=0.0;
  int tilt;
  bool _servo_tilt_has_arrived=true;
  uint8_t _tilt_pos=0;
  int16_t _servo_tilt_must_move=-1;
//#endif

int _contador=0;
void calcTilt();
void getError();
void calculatePID();
void getBatterieVoltage();

unsigned long time;
unsigned long calib_timer;

//PID stuff
long Error[11];
long Accumulator;
long PID;
uint8_t Divider = 15;
int PWMOutput;
long Dk;

// The target position (lat/lon)
geoCoordinate_t targetPosition;
// The tracker position (lat/lon)
geoCoordinate_t trackerPosition;

//only use tinygps when local gps is used
#ifdef LOCAL_GPS
  uint8_t localSats;
  
  #ifdef MEGA
    #define gpsSerial Serial1
  #else
    #include <SoftwareSerial.h>
    SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);
  #endif
  
  TinyGPS gps;
  void initGps();
  #define START_TRACKING_DISTANCE 0

#endif

#ifdef LCD_DISPLAY
  //download from https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
  #if (LCD_DISPLAY == I2C)
    #include <LiquidCrystal_I2C.h>
    #ifdef LCD_BANGGOOD_SKU166911
      LiquidCrystal_I2C lcd(LCD_I2C_ADDR,16,LCD_SIZE_ROW);
    #else  // Nueva Linea introducida
      //lcd.begin(LCD_SIZE_COL, LCD_SIZE_ROW); // GUILLESAN LCD ???
      //lcd.setBacklightPin(3, POSITIVE);      // GUILLESAN LCD ???
      //lcd.setBacklight(HIGH);                // GUILLESAN LCD ???
      LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); 
    #endif  // Nueva Linea introducida
  #elif (LCD_DISPLAY == SPI)
    #include <LiquidCrystal.h>
    LiquidCrystal lcd(12, 11, 13, 4, 3, 2);
  #endif
  
  char lcd_str[24];
  long lcd_time;
#endif

#ifdef BATTERYMONITORING
  #ifndef BATTERYMONITORING_AVERAGE
    #define BATTERYMONITORING_AVERAGE 2
  #endif
  #ifndef BATTERYMONITORING_VREF
    #define BATTERYMONITORING_VREF 1.1
  #endif
  #ifndef BATTERYMONITORING_VREF_SOURCE
    #define BATTERYMONITORING_VREF_SOURCE INTERNAL
  #endif
  uint16_t Bat_ADC_Last[BATTERYMONITORING_AVERAGE];
  float Bat_Voltage;
  float Bat_denominator = (float)BATTERYMONITORING_RESISTOR_2 / ((float)BATTERYMONITORING_RESISTOR_1 + (float)BATTERYMONITORING_RESISTOR_2);
#endif

#ifdef MFD
  uint16_t distance;
#endif


  int P;
  int I;
  int D;
  uint8_t MAX_PID_ERROR;

  int TILT_0;
  int TILT_90;
  int TILT_EASING;
  int TILT_EASING_STEPS;
  int TILT_EASING_MIN_ANGLE;
  int TILT_EASING_MILIS;
  int PAN_0;
  int MIN_PAN_SPEED;
  int OFFSET;

  uint8_t SERVOTEST;

  int cli_status=0;
 
  void (*pseudoReset)(void)=0;
  
void setup()
{

  
  Serial.begin(BAUD);
  checkEEPROM();
  readEEPROM();

  P             = getParamValue("P");
  I             = getParamValue("I");
  D             = getParamValue("D");
  MAX_PID_ERROR = getParamValue("max_pid_error");
  
  TILT_0        = getParamValue("tilt0");
  TILT_90       = getParamValue("tilt90");
  TILT_EASING   = getParamValue("easing");
  TILT_EASING_STEPS       = getParamValue("easing_steps");
  TILT_EASING_MIN_ANGLE   = getParamValue("easing_min_angle");
  TILT_EASING_MILIS       = getParamValue("easing_milis");
  PAN_0         = getParamValue("pan0");
  MIN_PAN_SPEED = getParamValue("min_pan_speed");
  OFFSET        = getParamValue("offset");

  SERVOTEST     = getParamValue("servotest");
  
  cli_status    = getParamValue("cli");
  
  if(cli_status) {
    delay(250);
    cli_welcome_message();
  }
    
  
  MAX_PID_ERROR=getParamValue("max_pid_error");
  //Serial.println();Serial.print("P=");Serial.println(P);
  ////
  #ifdef BATTERYMONITORING
    pinMode(VOLTAGEDIVIDER, INPUT);
    analogReference(BATTERYMONITORING_VREF_SOURCE);
    int n = 0;
    for (n = 0; n < BATTERYMONITORING_AVERAGE; n++) {
      getBatterieVoltage();
    }
  #endif
  #ifdef LCD_DISPLAY

    #ifdef LCD_BANGGOOD_SKU166911  // Nueva Linea introducida
      lcd.init();                           // Nueva línea introducida
      lcd.backlight();                      // Nueva línea introducida
    #else // Nueva Linea introducida
      lcd.begin(16, LCD_SIZE_ROW);
      lcd.setBacklightPin(3, POSITIVE);
      lcd.setBacklight(HIGH); 
    #endif // Nueva Linea introducida
    lcd.home();
    #if LCD_SIZE_ROW == 4
        lcd.setCursor ( 0, 1 );
    #endif
    lcd.print(" open360tracker ");
    #if LCD_SIZE_ROW == 4
      lcd.setCursor ( 0, 2 );
    #elif LCD_SIZE_ROW == 2
      lcd.setCursor ( 0, 1 );
    #endif
    lcd.print(" open360tracker ");
    lcd.setCursor ( 0, 1 );
    lcd.print(" version amv");
    lcd.print(FMW_VERSION);
    lcd.print("  ");
  #endif

  HAS_ALT = false;
  HAS_FIX = false;
  if(SERVOTEST && !cli_status){
    HOME_SET = true;
    TRACKING_STARTED = true;
  }
  else {
    HOME_SET = false;
    TRACKING_STARTED = false;
  }
  SETTING_HOME = false;
  PREVIOUS_STATE = true;

  CURRENT_STATE = true;
  NEW_HEADING = false;
  #ifdef MFD
    TEST_MODE = false;
  #endif

  

  #ifdef DEBUG
    Serial.println("Setup start");
  #endif

  pinMode(LED_PIN, OUTPUT);
  pinMode(HOME_BUTTON, INPUT);
  pinMode(CALIB_BUTTON, INPUT);

  //LED off
  digitalWrite(LED_PIN, LOW);

  //enable internal pullups
  digitalWrite(HOME_BUTTON, HIGH);
  digitalWrite(CALIB_BUTTON, HIGH);

  Wire.setClock(uint32_t(400000L));
  Wire.begin();

  // init pan/tilt servos controlled via hardware pwm
  #ifdef DEBUG
    Serial.println("Init Servos");
  #endif
  initServos();

  //if(TILT_EASING
  if(TILT_EASING) _lasttilt=0.0;
  //#endif
  
  #ifdef DEBUG
    Serial.println("Init Compass");
  #endif
  initCompass();

  #ifdef LOCAL_GPS
  #ifdef DEBUG
    Serial.println("Init local GPS");
  #endif
    gpsSerial.begin(GPS_BAUDRATE);
    //let gps serial initialize before we configure it
    delay(20);
    initGps();
  #endif

  #ifdef LCD_DISPLAY
    lcd.clear();
    lcd.setCursor(0, 0);
    sprintf(lcd_str, "HDG:%03u AZI:%03u", 0, 0);
    lcd.print(lcd_str);
    lcd.setCursor(0, 1);
    sprintf(lcd_str, "A:%05d D:%05u", 0, 0);
    lcd.print(lcd_str);
    lcd_time = millis();
  #endif

  time = millis();

  #ifdef DEBUG
    Serial.println("Setup finished");
  #endif

}
/*#ifdef SERVOTEST
if(SERVOTEST && !cli_status){
  long servoTimer = 0;
}*/
 //#endif
long servoTimer = 0;



void loop()
{
  if(SERVOTEST && !cli_status){
    if (millis() - servoTimer > 500) {
      Serial.print("Heading: "); Serial.print(trackerPosition.heading / 10);
      Serial.print(" Target Heading: "); Serial.print(targetPosition.heading / 10);
      Serial.print(" PAN: "); Serial.print(PWMOutput);
      Serial.print(" TILT: "); Serial.print(_lasttilt);
      Serial.print(" P: "); Serial.print(P);
      Serial.print(" I: "); Serial.print(I);
      Serial.print(" D: "); Serial.println(D);
      servoTimer = millis();
    }
  }

  //TODO change to telemetry serial port
  if (Serial.available() > 1)
  {
    
    uint8_t c = Serial.read();
    if(cli_status==0)
      cli_open_detect(c);
    else if(cli_status==1) {
      cli_encode_command(c);
    }
    else {
      // Salimos del modo comando
    }

    if(SERVOTEST && !cli_status)
        encodeServoTest(c);
    else
        encodeTargetData(c);
    
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  if(SERVOTEST && !cli_status){
      #ifdef LCD_DISPLAY
        if (millis() > lcd_time) {
          int lcd_nr;
          //switch screen every X seconds
          #if LCD_SIZE_ROW == 2
            if ((millis() % 10000 < 7000)) {
              lcd_nr = 1;
            }
            else {
              lcd_nr = 2;
            }
          #elif LCD_SIZE_ROW == 4
            lcd_nr = 0;
          #endif
          if (lcd_nr == 0 || lcd_nr == 1) {
            //headings, alt, distance, sats
            lcd.setCursor(0, 0);
            #ifdef MFD
                  sprintf(lcd_str, "H:%03u A:%03u", trackerPosition.heading / 10, targetPosition.heading / 10);
                  lcd.print(lcd_str);
            #else
                  #ifdef BATTERYMONITORING
                    sprintf(lcd_str, "H:%03u V%02u.%01u ", trackerPosition.heading / 10, (uint16_t)Bat_Voltage,(uint16_t)(Bat_Voltage*10)%10);
                  #else 
                    #ifdef RVOSD
                      targetPosition.heading = getAzimut();
                      sprintf(lcd_str, "H:%03u A:%03u ", trackerPosition.heading / 10, targetPosition.heading);
                    #else
                      sprintf(lcd_str, "H:%03u A:%03u ", trackerPosition.heading / 10, targetPosition.heading / 10);
                    #endif
                  #endif
                  
                  lcd.print(lcd_str);
                  
                  #ifdef LOCAL_GPS
                    sprintf(lcd_str, "S:%02d", localSats);
                  #else
                    //Si uso LCD pero no uso GPS local, el código genera un error de compilación
                    // que me obliga a descompentar en el config.h la línea //#define LOCAL_GPS
                    //para evitarlo introduzco este #ifdef GPS_TELEMETRY_NO_LOCAL_GPS que he definido en defines.h
                    //Comprueba que no uso ninguno de esos protocolos, solamente uso la telemetría directa, en cuyo caso devuelvo un 0 como número de satélites.
                    //#ifdef GPS_TELEMETRY_NO_LOCAL_GPS //nueva línea introducida
                    //  sprintf(lcd_str, "S:%02d", getSats());  //nueva línea introducida
                    //#else  //nueva línea introducida
                      sprintf(lcd_str, "S:%02d", getSats());  //línea original
                    //#endif   //nueva línea introducida 
                  #endif
                    lcd.print(lcd_str);
              #endif
              lcd.setCursor(0, 1);
              //#ifdef GPS_TELEMETRY_NO_LOCAL_GPS
              //  sprintf(lcd_str, "A:%05d  D:%05u", targetPosition.alt, targetPosition.distance);
              //#else
                sprintf(lcd_str, "A:%05d  D:%05u", targetPosition.alt, targetPosition.distance);
              //#endif;
              lcd.print(lcd_str);
            }
          if (lcd_nr == 0 || lcd_nr == 2) {
            //lat, lon
            #if LCD_SIZE_ROW == 4
              lcd.setCursor ( 0, 2 );
            #else
              lcd.setCursor(0, 0);
            #endif
            lcd.print("T LAT:");
            dtostrf(targetPosition.lat / 100000.0f, 10, 5, lcd_str);
            lcd.print(lcd_str);
            #if LCD_SIZE_ROW == 4
              lcd.setCursor ( 0, 3 );
            #else
              lcd.setCursor(0, 1);
            #endif
            lcd.print("T LON:");
            dtostrf(targetPosition.lon / 100000.0f, 10, 5, lcd_str);
            lcd.print(lcd_str);
          }
          #ifdef BATTERYMONITORING
            getBatterieVoltage();
          #endif
          lcd_time = millis() + 200;
        }
      #endif

      if (HAS_ALT) {
        targetPosition.alt = getTargetAlt();
    
        // mfd has all the data at once, so we do not have to wait for valid lat/lon
        #ifdef MFD
            distance = getDistance();
            targetPosition.heading = getAzimuth() * 10;
            #ifdef DEBUG
                Serial.print("Target alt: "); Serial.print(targetPosition.alt);
                Serial.print(" Target distance: "); Serial.print(targetPosition.distance);
                Serial.print(" Target heading: "); Serial.print(targetPosition.heading / 10);
                Serial.print(" Tracker heading: "); Serial.print(trackerPosition.heading / 10);
                Serial.print(" Target Sats: "); Serial.println(getSats());
            #endif //DEBUG
        #else
          #ifdef RVOSD
            targetPosition.heading = getAzimut();
          #endif
          #ifdef DEBUG
              Serial.print("Target alt: "); Serial.println(targetPosition.alt);
          #endif //DEBUG
        #endif //MDF
    
        HAS_ALT = false;
      }
      
      #ifndef MFD
        //only calculate distance and heading when we have valid telemetry data
        if (HAS_FIX) {
          targetPosition.lat = getTargetLat();
          targetPosition.lon = getTargetLon();

          // calculate distance without haversine. We need this for the slope triangle to get the correct pan value
          //distance = sqrt(sq(trackerPosition.lat - targetPosition.lat) + sq(trackerPosition.lon - targetPosition.lon));
          if (HOME_SET) {
            targetPosition.distance = TinyGPS::distance_between(trackerPosition.lat / 100000.0f, trackerPosition.lon / 100000.0f, targetPosition.lat / 100000.0f, targetPosition.lon / 100000.0f);
          }
          targetPosition.heading = TinyGPS::course_to(trackerPosition.lat / 100000.0f, trackerPosition.lon / 100000.0f, targetPosition.lat / 100000.0f, targetPosition.lon / 100000.0f) * 10.0f;
      
          //calcTargetDistanceAndHeading(&trackerPosition, &targetPosition);
      
          #ifdef DEBUG
              Serial.print("Lat: "); Serial.print(targetPosition.lat);
              Serial.print(" Lon: "); Serial.print(targetPosition.lon);
              Serial.print(" Distance: "); Serial.print(targetPosition.distance);
              Serial.print(" Heading: "); Serial.print(trackerPosition.heading / 10);
              Serial.print(" Target Heading: "); Serial.print(targetPosition.heading / 10);
              #ifdef MAVLINK
                  Serial.print(" Target Sats: "); Serial.print(getSats());
              #else
                  Serial.println();
              #endif //MAVLINK
          #endif //DEBUG
          HAS_FIX = false;
        }
      #endif //MDF
  }//#endif //SERVO_TEST
  // refresh rate of compass is 75Hz -> 13.333ms to refresh the data
  // we update the heading every 14ms to get as many samples into the smooth array as possible
  if (millis() > time) {
    time = millis() + 14;
    trackerPosition.heading = getHeading();
    NEW_HEADING = true;
  }

  CURRENT_STATE = digitalRead(CALIB_BUTTON);
  if (CURRENT_STATE != PREVIOUS_STATE) {
    digitalWrite(LED_PIN, !CURRENT_STATE);
    //pin changed
    if (!CURRENT_STATE && calib_timer == 0) {
      calib_timer = millis();
    } else if (CURRENT_STATE && millis() - calib_timer < 4000) {
      //button not pressed long enough
      calib_timer = 0;
    } else if (CURRENT_STATE && millis() - calib_timer > 4000) {
      //start calibration routine if button pressed > 4s and released
      //cli();
    #ifdef LCD_DISPLAY
      lcd.clear();
      #if LCD_SIZE_ROW == 4
        lcd.setCursor(0, 1);
      #else
        lcd.setCursor(0, 0);
      #endif
      //sprintf(lcd_str, "HDG:%03u AZI:%03u", 0, 0);
      lcd.print(" Calibration in ");
      #if LCD_SIZE_ROW == 4
        lcd.setCursor(0, 2);
      #else
        lcd.setCursor(0, 1);
      #endif
      lcd.print("   progress...  ");
    #endif //LCD_DISPLAY
      calibrate_compass();
      calib_timer = 0;
      //sei();
    }
    PREVIOUS_STATE = CURRENT_STATE;
  }
  if(!SERVOTEST){
    #ifndef LOCAL_GPS
      //only needed if no local gps
      if (!digitalRead(HOME_BUTTON)) {
        //set home
        #ifdef MFD
            //MFD protocol: set home must be pressed on driver!
        #else
          //trackerPosition.lat=370;
          //trackerPosition.lon=60;
          setHome(&trackerPosition, &targetPosition);
          //Serial.println("setHome");
          //Serial.print("Lat: ");Serial.print(trackerPosition.lat);Serial.print(" Lon: ");Serial.print(trackerPosition.lon);Serial.print(" Alt: ");Serial.println(trackerPosition.alt);
        #endif //MFD
      }
    #else
      if (gpsSerial.available()) {
        uint8_t c = gpsSerial.read();
        #ifdef DEBUG
            Serial.write(c);
        #endif
        if (gps.encode(c)) {
          unsigned long fix_age;
          gps.get_position(&trackerPosition.lat, &trackerPosition.lon, &fix_age);
          if (fix_age == TinyGPS::GPS_INVALID_AGE){
            //TODO no fix
            if (gps.satellites() != TinyGPS::GPS_INVALID_SATELLITES){
              localSats = (uint8_t)gps.satellites();
            }
            HOME_SET = false;
          }else if (fix_age >5000){
            //TODO fix too old, maybe tracker lost fix
            if (gps.satellites() != TinyGPS::GPS_INVALID_SATELLITES){
              localSats = (uint8_t)gps.satellites();
            }
            
            //attention, if gps is lost, last position will remain. So if gps somehow loses signal and the pos is not nulled in these 5s then it will continue tracking with last pos.
          }else{
            //TODO valid data
            trackerPosition.lat = trackerPosition.lat / 10;
            trackerPosition.lon = trackerPosition.lon / 10;
    
            if (gps.altitude() != TinyGPS::GPS_INVALID_ALTITUDE) {
              trackerPosition.alt = int16_t(gps.altitude()/100);
            }
    
            if (gps.satellites() != TinyGPS::GPS_INVALID_SATELLITES){
              localSats = (uint8_t)gps.satellites();
            }
            
            HOME_SET = true;
            //Serial.print("Lat: ");Serial.print(trackerPosition.lat);Serial.print(" Lon: ");Serial.print(trackerPosition.lon);Serial.print(" Alt: ");Serial.println(trackerPosition.alt);
          }
        }
      }
    #endif //LOCAL_GPS
  
    #ifdef MFD
      if (SETTING_HOME) {
        HOME_SET = true;
        SETTING_HOME = 0;
      }
    
      if (!HOME_SET && TEST_MODE && NEW_HEADING) {
        distance = getDistance();
        targetPosition.alt = getTargetAlt();
        targetPosition.heading = getAzimuth() * 10;
    
        getError();
        calculatePID();
        SET_PAN_SERVO_SPEED(PWMOutput);
        calcTilt();
        NEW_HEADING = false;
      }
      if (HOME_SET && HAS_FIX && NEW_HEADING && !TEST_MODE) {
        targetPosition.alt = getTargetAlt();
        targetPosition.heading = getAzimuth() * 10;
        distance = getDistance();
    
        getError();
        calculatePID();
        SET_PAN_SERVO_SPEED(PWMOutput);
        calcTilt();
        NEW_HEADING = false;
      }
    #endif //MFD
  }//#endif //SERVOTEST
  #ifndef MFD
    //Only track if home ist set.
    if (HOME_SET) {
    #if (START_TRACKING_DISTANCE > 0)
        //Only track if tracking process started.
        if (!TRACKING_STARTED) {
          //if plane is START_TRACKING_DISTANCE meter away from tracker start tracking process.
          if (targetPosition.distance >= uint16_t(START_TRACKING_DISTANCE)) {
            TRACKING_STARTED = true;
          }
        } else {
    #endif
        // only update pan value if there is new data
        if ( NEW_HEADING ) {
          getError();       // Get position error
          calculatePID();   // Calculate the PID output from the error
          SET_PAN_SERVO_SPEED(PWMOutput);
          NEW_HEADING = false;
          #ifndef SERVOTEST
                  calcTilt();
          #endif
          #if (START_TRACKING_DISTANCE > 0)
                }
          #endif
      }
    }
  #endif //MDF
  //#ifdef TILT_EASING
    if(TILT_EASING) servo_tilt_update();
  //#endif

}

//Tilt angle alpha = atan(alt/dist)
void calcTilt() {
  uint16_t alpha = 0;
  
  //this will fix an error where the tracker randomly points up when plane is lower than tracker
  if (targetPosition.alt < trackerPosition.alt){
    targetPosition.alt = trackerPosition.alt;
  }
  
  //prevent division by 0
  if (targetPosition.distance == 0) {
    // in larger altitude 1m distance shouldnt mess up the calculation.
    //e.g. in 100m height and dist 1 the angle is 89.4° which is actually accurate enough
    targetPosition.distance = 1;
  }

  alpha = toDeg(atan(float(targetPosition.alt - trackerPosition.alt) / targetPosition.distance));

  //just for current tests, later we will have negative tilt as well
  if (alpha < 0)
    alpha = 0;
  else if (alpha > 90)
    alpha = 90;
  //#ifdef TILT_EASING
  if(TILT_EASING){
    _servo_tilt_must_move=alpha;
    _servo_tilt_has_arrived=false;
  }
  //#else
  else
    SET_TILT_SERVO_SPEED(map(alpha, 0, 90, TILT_0, TILT_90));
  //#endif
}

void getError(void)
{
  // shift error values
  for (byte i = 0; i < 10; i++) {
    Error[i + 1] = Error[i];
  }

  int16_t delta = targetPosition.heading - trackerPosition.heading;
  if (delta > 1800) {
    delta -= 3600;
  }
  else if (delta < -1800) {
    delta += 3600;
  }
  // load new error into top array spot
  Error[0] = delta;
}

void calculatePID(void)
{

  

  // Calculate the PID

  PID = Error[0] * P;     // start with proportional gain
  Accumulator += Error[0];  // accumulator is sum of errors
  if (Accumulator > 5000)
    Accumulator = 5000;
  if (Accumulator < -5000)
    Accumulator = -5000;
  PID += I * Accumulator; // add integral gain and error accumulation
  Dk = D * (Error[0] - Error[10]);
  PID += Dk; // differential gain comes next
  PID = PID >> Divider; // scale PID down with divider
  // limit the PID to the resolution we have for the PWM variable
  if (PID >= 500)
    PID = 500;
  if (PID <= -500)
    PID = -500;
  if (Error[0] > MAX_PID_ERROR) {
    PWMOutput = PAN_0 + PID + MIN_PAN_SPEED;
  } else if (Error[0] < -1*MAX_PID_ERROR) {
    PWMOutput = PAN_0 + PID - MIN_PAN_SPEED;
  } else {
    PWMOutput = PAN_0;
  }
//#endif
}

#ifdef LOCAL_GPS
void initGps() {
  #ifdef MTK
    //set to 1Hz
    gpsSerial.println("$PMTK220,1000*1F");
    //delay for ack/nack as softserial cannot read and write at the same time
    delay(20);
  
    //only enable GGA sentences
    gpsSerial.print("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29");
    //delay for ack/nack as softserial cannot read and write at the same time
    delay(20);
  #endif //MTK
  }
#endif //LOCAL_GPS

#ifdef BATTERYMONITORING
  void getBatterieVoltage() {
    int n = 0;
    uint16_t Bat_ADC = (uint16_t)analogRead(VOLTAGEDIVIDER); //Hole Wert
    uint32_t Bat_AVG = (uint32_t)Bat_ADC;
    for (n = 0; n < BATTERYMONITORING_AVERAGE; n++) {
      Bat_AVG += (uint32_t)Bat_ADC_Last[n];
    }
    Bat_AVG /= BATTERYMONITORING_AVERAGE + 1;
    for (n = 0; n < BATTERYMONITORING_AVERAGE - 1; n++) {
      Bat_ADC_Last[n] = Bat_ADC_Last[n + 1];
    }
    Bat_ADC_Last[BATTERYMONITORING_AVERAGE - 1] = Bat_ADC;
    Bat_Voltage = ((float)Bat_AVG / 1024.0) * BATTERYMONITORING_VREF / Bat_denominator * BATTERYMONITORING_CORRECTION;
    Serial.print("V: "); Serial.println(Bat_Voltage);
  }
#endif

//#ifdef TILT_EASING
  void moveServoTilt(float value){
    int _pwmpulse;
    float easingout;
    if(abs(_lasttilt-value)>TILT_EASING_MIN_ANGLE) {
      #ifdef DEBUG
        Serial.println("Easing tilt...");
      #endif      
      for (int pos=0; pos<TILT_EASING_STEPS; pos++){
        if(_lasttilt<=value)
          easingout=_lasttilt+easeTilt(pos, 0, value-_lasttilt, TILT_EASING_STEPS);
        else
          easingout=_lasttilt-easeTilt(pos, 0, _lasttilt-value, TILT_EASING_STEPS);
        _pwmpulse=(int)map(easingout,0,90,TILT_0,TILT_90);
        SET_TILT_SERVO_SPEED(_pwmpulse);
        /*#ifdef DEBUG && TILT_EASING 
          Serial.print(" dur: "); Serial.print(TILT_EASING_STEPS);
          Serial.print(" pos: "); Serial.print(pos);
          Serial.print(" _lasttilt: "); Serial.print(_lasttilt);
          Serial.print(" value: "); Serial.print(value);
          Serial.print(" easingout: "); Serial.print(easingout);    
          Serial.print(" pwmpulse: "); Serial.println(_pwmpulse);
        #endif*/
        delay(15);
      }
    }
    else
      SET_TILT_SERVO_SPEED(map(value,0,90, TILT_0, TILT_90));
    _lasttilt=(float)value;  

  }
  void servo_tilt_update(){
    int _pwmpulse;
    float easingout;
    if(_servo_tilt_must_move<0) _tilt_pos=0;
    if(!_servo_tilt_has_arrived && _servo_tilt_must_move>-1){
      if(abs(_lasttilt-_servo_tilt_must_move)>TILT_EASING_MIN_ANGLE) {
        if(_tilt_pos<TILT_EASING_STEPS){
          if(_lasttilt<=_servo_tilt_must_move)
            easingout=_lasttilt+easeTilt(_tilt_pos, 0, _servo_tilt_must_move-_lasttilt, TILT_EASING_STEPS);
          else
            easingout=_lasttilt-easeTilt(_tilt_pos, 0, _lasttilt-_servo_tilt_must_move, TILT_EASING_STEPS);
          _pwmpulse=(int)map(easingout,0,90,TILT_0,TILT_90);
          SET_TILT_SERVO_SPEED(_pwmpulse);
          /*#ifdef DEBUG && TILT_EASING
            Serial.print(" dur: "); Serial.print(TILT_EASING_STEPS);
            Serial.print(" pos: "); Serial.print(_tilt_pos);
            Serial.print(" _lasttilt: "); Serial.print(_lasttilt);
            Serial.print(" value: "); Serial.print(_servo_tilt_must_move);
            Serial.print(" easingout: "); Serial.print(easingout);    
            Serial.print(" pwmpulse: "); Serial.println(_pwmpulse);
          #endif*/
          //#if TILT_EASING_MILIS
          if(TILT_EASING) delay(TILT_EASING_MILIS);
          //#endif;
          _tilt_pos++;
        }
        else {
          if(_tilt_pos==TILT_EASING_STEPS){
            SET_TILT_SERVO_SPEED(map(_servo_tilt_must_move,0,90, TILT_0, TILT_90));
            //#if TILT_EASING_MILIS
            if(TILT_EASING_MILIS) delay(TILT_EASING_MILIS);
            //#endif;
            _lasttilt=(float)_servo_tilt_must_move;
            _tilt_pos=0;
            _servo_tilt_has_arrived=true;
            _servo_tilt_must_move=-1;
          }
        }
      }
      else {
      _servo_tilt_has_arrived=true;
      _servo_tilt_must_move=-1;
      }
    }
  }

//#endif

void encodeServoTest(uint8_t c){
    
    if (c == 'H' || c == 'h') {
    //target heading in degree
    targetPosition.heading = Serial.parseInt();
  } else if (c == 'T' || c == 't') {
    //tilt angle in degree
    int value = Serial.parseInt();
    if (value > 90)
      value = 90;
    else if (value < 0)
      value = 0;
    //#ifdef TILT_EASING
    if(TILT_EASING) {
        //moveServoTilt(value);
        _servo_tilt_must_move=value;
        _servo_tilt_has_arrived=false;
    }
    else {
    //#else
      tilt = map(value, 0, 90, TILT_0, TILT_90);
      SET_TILT_SERVO_SPEED(tilt);
    }
    //#endif
    
  } else if (c == 'M' || c == 'm') {
    //tilt angle in ms
    tilt = Serial.parseInt();
    SET_TILT_SERVO_SPEED(tilt);
  } else if (c == 'P' || c == 'p') {
    //p = Serial.parseInt();
  } else if (c == 'I' || c == 'i') {
    //i = Serial.parseInt();
  } else if (c == 'D' || c == 'd') {
    //d = Serial.parseInt();
  } else if (c == 'C' || c == 'c') {
    calibrate_compass();
  }
}


////////
  String command_name = "";
  String parameter_name = "";
  uint8_t cli_header=0;
  uint8_t parameter_started=false;
  uint8_t value_started=false;
  String parameter_value="";
  uint8_t command_started=false;
////////
void cli_open_detect(char c){
  if(c == '#' && cli_header==0){
    cli_header = 1;
  }
  else if(c == '#'){
    cli_header ++;
  }
  else {
    cli_header = 0;
  }
  if(cli_header==3){
    cli_welcome_message();
    cli_status=1;
    cli_header = 0;
    command_name = "";
  }
  return;
 
}
void cli_encode_command(char c){
   
  if((c == '\n' || c == '\r') && !command_started){
    if(command_name == "help")
      command_help();
    else if(command_name == "save")
      command_save();
    else if(command_name == "defaults")
      command_defaults();
    else if(command_name == "version")
      command_version();
    else if(command_name == "set" && !parameter_started && !value_started && !command_started)
      dumpSettings();
    else if(command_name == "feature" && !parameter_started && !value_started && !command_started)
      list_features();
    command_name = "";
    command_started=false;
    return;
  }
  else if(c == 32 && !parameter_started && !value_started){

      parameter_name = "";
      parameter_started = true;
      parameter_value = "";
      value_started = false;
      command_started = true;
      return;

  }
  else if(c == '=' && parameter_started && !value_started){
    if(command_name == "set")
    {
      parameter_value = "";
      parameter_started = false;
      value_started = true;
      return;
    }
  }
  else if((c == '\n' || c == '\r') && parameter_started ){
    if(command_name == "feature" && (parameter_name=="lcd" || parameter_name=="local_gps" || parameter_name=="bat_mon" || parameter_name=="easing")) {
      int value=getParamValue(parameter_name);
      if(value==0)
        value=1;
      else
        value=0;
      setParamValue(parameter_name,value);
      list_features();
      
    }
    /*else if(command_name == "feature") {
      //change_settings(parameter_name,parameter_value.toInt());
      Serial.print("feature ");
    }*/

    parameter_value = "";
    parameter_name = "";
    command_name = "";
    parameter_started = false;
    value_started = false;
    command_started = false;
    return;
  }
  else if((c == '\n' || c == '\r') && value_started){
    setParamValue(parameter_name,parameter_value.toInt());
    parameter_value="";
    parameter_name="";
    command_name="";
    parameter_started=false;
    value_started=false;
    command_started=false;
    return;
  }
  else {
    if(parameter_started==true){
      parameter_name += c;
    }
    else if(value_started==true){
      parameter_value += c;
    }
    else
    {
      command_name += c;
    }
  }
}
void command_help()
{

    Serial.println();
    Serial.println(F("List of available commands:"));
    Serial.println(F(" help       list commands"));
    Serial.println(F(" defaults   reset settings to defaults"));
    Serial.println(F(" feature    enable/disable/list features"));
    Serial.println(F(" set        list parameters"));
    Serial.println(F(" *status    print out system status"));
    Serial.println(F(" version    print out firmware version"));
    Serial.println(F(" save       save settings and exit"));
    Serial.println(F(">"));
}
void command_save()
{
  Serial.println(F("Saving settings..."));
  setParamValue("cli",0); // First time saving disable cli by default;
  writeEEPROM();
  Serial.println(F("Command Line Interface closed"));
  Serial.flush();
  cli_status=0;
  pseudoReset();
}
void command_defaults() {
  Serial.println(F("Resetting to defaults..."));
  defaultsEEMPROM();
  Serial.println(F("Ok\n>"));
}
void command_version() {
    Serial.print(F("Firmware amv-open360tracker V"));Serial.println(FMW_VERSION);Serial.println(F(">"));
}
void list_features(){
  uint8_t value;
  Serial.println(F("Enabled features: "));
  value=getParamValue("easing");
  if(value>0) Serial.print(F("easing "));
  value=getParamValue("local_gps");
  if(value>0) Serial.print(F("local_gps "));
  value=getParamValue("lcd");
  if(value>0) Serial.print(F("lcd "));
  value=getParamValue("bat_mon");
  if(value>0) Serial.print(F("bat_mon "));
  value=getParamValue("servotest");
  if(value>0) Serial.print(F("servotest "));
  Serial.println(F("\n>"));
}
void cli_welcome_message(){
    Serial.println(F("amv-open360tracker"));
    Serial.println(F("------------------"));
    Serial.print(">");
}

