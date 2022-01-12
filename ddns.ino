#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char * ssid = "<ssid>";
const char * password = "<password>";

ESP8266WebServer server(80);

// Define NTP Client to get time
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org");

// Duckdns variables
String domain="<domain>.duckdns.org";
String token="<token>";

// returns current timestamp
String getTime() {
  timeClient.update();
  return timeClient.getFormattedTime();
}

// returns the day of the week in a readable format
String getDay() {
  timeClient.update();
  switch(timeClient.getDay()){
    case 0:
      return "Sunday";
    case 1:
      return "Monday";
    case 2:
      return "Tuesday";
    case 3:
      return "Wednesday";
    case 4:
      return "Thursday";
    case 5:
      return "Friday";
    case 6:
      return "Saturday";
    default:
      return "";
    }
}

// logger helper function
void log(String msg){
  Serial.println(getDay() + " " + getTime() + " " + msg);
}

// returns router's public IP
String getPublicIP(){
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://ifconfig.me/ip");
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      return http.getString();
    }
  } else {
    http.end();
    return "";
  }
  http.end();
}

// Duckdns DDNS update
void update(String domain, String token){
  String ip = getPublicIP();
  String update_url = "http://www.duckdns.org/update?domains=" + domain + "&token=" + token + "&ip=" + ip + "";

  WiFiClient client;
  HTTPClient http;
  http.begin(client, update_url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      log("IP Updated: " + ip);
    }
  } else {
    http.end();
    log("Error occured when trying to update IP. Status code received: " + httpCode);
  }
  http.end();
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  log("ESP8266 connected to WiFi with IP: " + WiFi.localIP());
  server.begin();
}

void loop() {
  update(domain, token);
  delay(60000); // one minute delay
}
