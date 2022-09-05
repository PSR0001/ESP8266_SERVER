
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"
#include <memory.h>
// #include <PROGMEM.h>
/*****************************************************************
 * ssid - (const char *) (in "quotes") ssid of wifi station      *
 * pass - (const char *) (in "quotes") password of wifi station  *
 *****************************************************************/
//Macros------------
#define PORT 80
#define BAUD_RATE 115200
#define TIMEOUT 2000 // ms


WiFiServer server(PORT);

//Function prototype------
void setup_wifi();
String page();
// html page
const char HTTP_HEADER[] PROGMEM          ="<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>PSR</title><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">";
const char HTTP_STYLE[] PROGMEM         ="<style>.card{box-shadow:04px8px0rgba(0,0,0,0.2);max-width:300px;margin:auto;text-align:center;border-radius:5px;}.title{color:grey;font-size:18px;}button{border:none;outline:0;display:inline-block;padding:8px;color:white;background-color:#000;text-align:center;cursor:pointer;width:100%;font-size:18px;}a{text-decoration:none;font-size:22px;color:black;}button:hover,a:hover{opacity:0.7;}</style>";
const char HTTP_HEAD_START[] PROGMEM    ="</head><body><section><br><br><div class=\"card\"><br><h1>Partha Singha Roy</h1><p class=\"title\">I am a Web Developer, IoT Enthusiast and Electronics Hobbyist.</p><a href=\"#\"><i class=\"fa fa-dribbble\"></i></a><a href=\"#\"><i class=\"fa fa-twitter\"></i></a><a href=\"#\"><i class=\"fa fa-linkedin\"></i></a><a href=\"#\"><i class=\"fa fa-facebook\"></i></a><p><button type=\"button\">Contact</button></p></div></section></body></html>";


void setup()
{
  Serial.begin(BAUD_RATE);
  setup_wifi();
  //Server begin
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); //when client available
  if (!client)
    return;

  String req = client.readStringUntil('\n');
  req.trim();
  if(req){
  client.print(page());   // this is only for the sending client
  server.flush();
  }
}

void setup_wifi(){
  Serial.print(F("Connecting to : "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(". ");
  }
  Serial.print(F("\nConnected with "));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
}


String page(){
  String page;
  page+=FPSTR(HTTP_HEADER);
  page+=FPSTR(HTTP_STYLE);
  page+=FPSTR(HTTP_HEAD_START);

  return page;
}

