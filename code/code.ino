
#include <ESP32Servo.h>
#include "webpage.h"
#include "server.h"
#include <WiFi.h>
#include <WebServer.h>

//input output pins
#define ULTRA_ONE_TRIG_PIN 33 // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ULTRA_ONE_ECHO_PIN 25 // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define ULTRA_TWO_TRIG_PIN 17
#define ULTRA_TWO_ECHO_PIN 16
#define PIN_LED 2     //On board LED
#define PIN_OUTPUT 26
#define ENTRY_SERVO_PIN  32
#define EXIT_SERVO_PIN  19

//wifi variables
#define USE_INTRANET
#define AP_SSID "Parking-System"
#define AP_PASS "pass12345"

#include <Preferences.h>

Preferences preferences;

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;
// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;




bool status_led = true, system_status = true;
int entry_gate_distance = 0;
int exit_gate_distance = 0;
uint32_t SensorUpdate = 0;
int cars_num = 0;

//servos variables
Servo entry_gate_servo;  // create servo object to control a servo
Servo exit_gate_servo;  // create servo object to control a servo
bool entry_open = false;
bool exit_open = false;
int entry_servo_pos = 0;
int exit_servo_pos = 0;

// time variables
int moveTime = 15;
unsigned long int entry_open_time = 0;
unsigned long int entry_moving_time = 0;
unsigned long int exit_open_time = 0;
unsigned long int exit_moving_time = 0;


// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];
// just some buffer holder for char operations
char buf[32];




// create a server
WebServer server(80);

void setup() {

  preferences.begin("variables", false);

  cars_num = preferences.getInt("cars_num", 0);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  entry_gate_servo.setPeriodHertz(50);    // standard 50 hz servo
  entry_gate_servo.attach(ENTRY_SERVO_PIN, 500, 2400); // attaches the servo on pin 18 to the servo object

  exit_gate_servo.setPeriodHertz(50);    // standard 50 hz servo
  exit_gate_servo.attach(EXIT_SERVO_PIN, 500, 2400); // attaches the servo on pin 18 to the servo object

  // begin serial port
  Serial.begin (9600);
  pinMode(PIN_LED, OUTPUT);

  // turn off led
  //  status_led = false;
  digitalWrite(PIN_LED, status_led);

  // configure the trigger pin to output mode
  pinMode(ULTRA_ONE_TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ULTRA_ONE_ECHO_PIN, INPUT);
  pinMode(ULTRA_TWO_TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ULTRA_TWO_ECHO_PIN, INPUT);

  // disable watch dog timer 0
  disableCore0WDT();


  // setup the server
  Serial.println("starting server");
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(Actual_IP);
  printWifiStatus();


  //handle server requests
  server.on("/", SendWebsite);
  server.on("/xml", SendXML);

  // upon ESP getting /UPDATE_SLIDER string, ESP will execute the UpdateSlider function
  // same notion for the following .on calls
  // add as many as you need to process incoming strings from your web page
  // as you can imagine you will need to code some javascript in your web page to send such strings
  server.on("/BUTTON_0", ProcessButton_0);
  server.on("/BUTTON_1", ProcessButton_1);
  server.on("/BUTTON_2", ProcessButton_2);
  server.on("/BUTTON_3", ProcessButton_3);
  server.on("/restart", SystemRestart);


  // finally begin the server
  server.begin();

//  entry_gate_servo.write(0);
//  exit_gate_servo.write(0);



}

void loop() {
  if (system_status)
  {
    //Serial.println("Reading Sensors");
    SensorUpdate = millis();
    entry_gate_distance = get_distance(ULTRA_ONE_TRIG_PIN, ULTRA_ONE_ECHO_PIN);

    if (entry_gate_distance <= 10 && cars_num < 10 && !entry_open) {
      cars_num++;
      preferences.putInt("cars_num", cars_num);
      entry_open_time = millis();
      entry_moving_time = millis();
      entry_open = true;
    }

    exit_gate_distance = get_distance(ULTRA_TWO_TRIG_PIN, ULTRA_TWO_ECHO_PIN);
    if (exit_gate_distance <= 10 && cars_num >= 1 && !exit_open) {
      cars_num--;
      preferences.putInt("cars_num", cars_num);
      exit_open_time = millis();
      exit_moving_time = millis();
      exit_open = true;
    }

    


    //Entry Gate Moving control
    //check if the gate in open state to open it gradully
    if (entry_open
        //      && (entry_gate_distance <= 10)
        && entry_servo_pos < 90) {
      if (millis() - entry_moving_time >= moveTime) {
        entry_servo_pos = entry_servo_pos +  2;
        entry_gate_servo.write(entry_servo_pos);
      }
      entry_moving_time = millis();
    }
    // check to close the entry gate if it is open and time done
    if (millis() - entry_open_time >= 7000) {
      if (!(entry_gate_distance <= 10) && entry_servo_pos > 0) {
        entry_open = false;
        if (millis() - entry_moving_time >= moveTime) {
          entry_servo_pos = entry_servo_pos - 2;
          entry_gate_servo.write(entry_servo_pos);
        }
        entry_moving_time = millis();
      }
    }

    Serial.print("entry_open: ");
        Serial.println(entry_open);
        Serial.print("exit_open: ");
        Serial.println(entry_open);


    //Exit Gate Moving control
    //check if the gate in open state to open it gradully
    if (exit_open
        //      && (entry_gate_distance <= 10)
        && exit_servo_pos < 90) {
      if (millis() - exit_moving_time >= moveTime) {
        exit_servo_pos = exit_servo_pos +  2;
        exit_gate_servo.write(exit_servo_pos);
      }
      exit_moving_time = millis();
    }
    // check to close the entry gate if it is open and time done
    if (millis() - exit_open_time >= 7000) {
      if (!(exit_gate_distance <= 10) && exit_servo_pos > 0) {
        exit_open = false;
        if (millis() - entry_moving_time >= moveTime) {
          exit_servo_pos = exit_servo_pos - 2;
          exit_gate_servo.write(exit_servo_pos);
        }
        exit_moving_time = millis();
      }
    }
  }
  server.handleClient();
}



void SystemRestart() {


  if (entry_servo_pos > 0 || exit_servo_pos > 0 ) {


    server.send(200, "text/plain", "false"); //Send web page

  }
  else {
    server.send(200, "text/plain", "true"); //Send web page
    delay(2000);
    ESP.restart();

  }
}
// now process button_0 press from the web site. Typical applications are the used on the web client can
// turn on / off a light, a fan, disable something etc
void ProcessButton_0() {
  if (system_status) {
    if (entry_servo_pos > 0 || exit_servo_pos > 0) {
      server.send(200, "text/plain", "false"); //Send web page
    }
    else {
      system_status = false;
      status_led = false;
      server.send(200, "text/plain", "off"); //Send web page

    }
  }
  else {
    system_status = true;
    status_led = true;
    server.send(200, "text/plain", "on"); //Send web page
  }
  digitalWrite(PIN_LED, status_led);


}
// same notion for processing button_1
void ProcessButton_1() {
  // just a simple way to toggle a LED on/off. Much better ways to do this
  Serial.println("Button 1 press");

  //     server.send(200, "text/plain", ""); //Send web page

  if (!entry_open && !exit_open) {
    cars_num = 0;
    preferences.putInt("cars_num", cars_num);

    Serial.println("Cars number reset.");
    server.send(200, "text/plain", "true"); //Send web page

  }
  else {
    server.send(200, "text/plain", "false"); //Send web page
  }

}

void ProcessButton_2() {
  // just a simple way to toggle a LED on/off. Much better ways to do this
  Serial.println("Button 1 press");

  //     server.send(200, "text/plain", ""); //Send web page

  if (!entry_open ) {

    entry_open = true;
    entry_open_time = millis();

    //    Serial.println("Cars number reset.");/
    server.send(200, "text/plain", "true"); //Send web page

  }
  else {
    server.send(200, "text/plain", "false"); //Send web page
  }

}
void ProcessButton_3() {

  if (!exit_open ) {
    exit_open = true;
    exit_open_time = millis();

    //    Serial.println("Cars number reset.");/
    server.send(200, "text/plain", "true"); //Send web page

  }
  else {
    server.send(200, "text/plain", "false"); //Send web page
  }

}
// code to send the main web page
// PAGE_MAIN is a large char defined in SuperMon.h
void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);
}


//// code to send the main web page
//// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {
  // Serial.println("sending xml");
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");
  // send distance_cm
  sprintf(buf, "<B0>%d</B0>\n", cars_num);
  strcat(XML, buf);

  sprintf(buf, "<B1>%d</B1>\n", entry_gate_distance);
  strcat(XML, buf);


  sprintf(buf, "<B2>%d</B2>\n", exit_gate_distance);
  strcat(XML, buf);

  // show led0 status
  if (status_led) {
    strcat(XML, "<LED>1</LED>\n");
  }
  else {
    strcat(XML, "<LED>0</LED>\n");
  }
  //    if (!entry_open&&!exit_open) {
  //      strcat(XML, "<SWITCH>true</SWITCH>\n");
  //    }
  //    else {
  //      strcat(XML, "<SWITCH>false</SWITCH>\n");
  //    }

  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  //  Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);


}

// I think I got this code from the wifi example
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}


int get_distance(int trig_pin, int echo_pin) {
  digitalWrite(trig_pin, LOW);

  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  return (pulseIn(echo_pin, HIGH)) * 0.017;

}
