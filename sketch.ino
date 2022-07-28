#include <WiFi.h>
#include <HTTPClient.h>
#include <Stepper.h>;

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 26, 25, 33, 32);
int step = 0;
String previousString = "";


String HOST_NAME = "https://arspeechtotext.000webhostapp.com"; 
String PATH_NAME   = "/DisplayDB.php";


void setup() {
  myStepper.setSpeed(60);
}

void loop() {
Serial.begin(9600); 

  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.begin("Wokwi-GUEST", "", 6);
  // Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }

  HTTPClient http;

  // http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
    http.begin(HOST_NAME + PATH_NAME); //HTTP

  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      if(previousString != payload){
        if(payload == "يسار"){

          if(step == 0 ){
            step = 50;
          }else if (step == -50){
              step = 100;
          }
          myStepper.step(step);
                
        }else if (payload == "يمين"){

          if(step == 0 ){
            step = -50;
          }else if (step == 50){
              step = 100;
          }
          myStepper.step(step);
        }
        
        previousString = payload;

      }
      
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();


  delay(3000);

}