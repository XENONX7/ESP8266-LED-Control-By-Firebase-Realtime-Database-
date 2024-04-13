#include <dummy.h>
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#define RLED 5
 
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>


#define WIFI_SSID "Your Wi-Fi Name"
#define WIFI_PASSWORD "Wi-Fi Password"


#define API_KEY "Your Api Key"


#define DATABASE_URL "Firebase Database Url" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app


#define USER_EMAIL "Firebse Auth Email"
#define USER_PASSWORD "Password"


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

void setup()
{

  Serial.begin(115200);

 pinMode(LED_BUILTIN, OUTPUT);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  
  config.api_key = API_KEY;

  
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  
  config.database_url = DATABASE_URL;


  config.token_status_callback = tokenStatusCallback; 

  

  Firebase.begin(&config, &auth);


  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  
}

void loop()
{

  
  
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

// Reciver
  String X=Firebase.getString(fbdo, F("/IoT")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();
Serial.print(X);
  if(X=="ON")
  {
    Serial.print("ON");
    digitalWrite(LED_BUILTIN, LOW);
   
  }

    if(X=="OFF")
  {
    Serial.print("OFF");
    digitalWrite(LED_BUILTIN, HIGH);
   
  }

   
   }
}
