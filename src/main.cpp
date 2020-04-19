/**
 * @file main.cpp
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2020, Fabio Fernandes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * @section Description
 * Main program code.
 */
#include <Arduino.h>
#include "wifi/WifiManager.h"
#include "web/WebServer.h"

WifiManager *wifi;
WebServer *server;

void webActionHandler(HttpServer sender, String eventArgs){
      Serial.println("Novo evento HTTP:");
      Serial.println(eventArgs);

      // Do something with event
      if (eventArgs!=NULL)
      {
          if (eventArgs.indexOf("forward") >= 0) {
              // move both motors foward
          }
          else if (eventArgs.indexOf("backward") >= 0) {
              // move both motors foward
          }
          else if (eventArgs.indexOf("left") >= 0) {
              // move left motors backward
              // move right motors foward
          }
          else if (eventArgs.indexOf("right") >= 0) {
              // move left motors foward
              // move right motors backward
          }
      }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setup - Starting main appication path");

  // Here you can initialize your devices managers and services
  
  // Connecting ESP8266 to current wifi network
  wifi = new WifiManager();
  wifi->start();
  

  server = new WebServer();
  Serial.println("Setup - Starting websetup");
  server->setCallBack(&webActionHandler);
  server->webSetup();
  Serial.println("Setup - Finishing websetup");

  // Start webserver and api server


  
  Serial.println("Setup - Finishing main application path");
}

bool printStatus = false;
void loop() {
  // put your main code here, to run repeatedly:
  if (wifi->getStatus()!=WL_CONNECTED) { 
    Serial.print(".");
    delay(1000);
  }
  else { 
      if (!printStatus){ 
        printStatus = true;
        Serial.println("");
        Serial.print("Numero IP atual: ");
        IPAddress *ip = (IPAddress*)wifi->getParameters(); 
        Serial.println(ip->toString());
        Serial.println("Para acessar o webserver utilize: http://" + ip->toString() + "/ no seu browser.");
      }
      server->webLoop();
  }
}
