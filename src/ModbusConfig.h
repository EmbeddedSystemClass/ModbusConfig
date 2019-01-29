/*
  The MIT License (MIT)

  Copyright (c) 2019 Andrey Fedorov

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
  Main code by Andrey Fedorov (fedorov@bizkit.ru)
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ModbusConfig_h
#define ModbusConfig_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <ArduinoJson.h>

/**
    @example ArduinoModbusConfig.ino
    Simple example of the ModbusConfig library.   
*/

bool processJsonError(int error);

typedef struct{
  int PollingInterval;  //default 
  unsigned long lastPolling; //
  int UnitId;
  int Function;
  int Address;
  int Len;        	//default 
  String DisplayName;
} Operation;

typedef std::vector<Operation> OperationsType;

enum ModbusType { RTU, TCP, NONE };

typedef struct{
  void* Connector;
  ModbusType Type;
  String Connection;
  int RxPin;           	//default 
  int TxPin;            //default 
  int RetryCount;    	//default 
  int RetryInterval; 	//default 
  int PollingInterval; 	//default 
  unsigned long lastPolling; //
  String HwId;
  int BaudRate; 	//default 
  String Config; 	//default SERIAL_8N1
  int TcpPort; 		//default 
  OperationsType Operations;
} Slave;

typedef std::vector<Slave> Slaves;

/*
    @brief  Callback function to process an operation polling interval.
*/
typedef void (*PHandler)(Slave* slave, Operation* operation);

/**
     The ModbusConfig class.
*/
class ModbusConfig
{
 public:

/*!
    @brief  Create an instance of the ModbusConfig class.

    @code
    // Create an instance of the ModbusConfig class.
    ModbusConfig() modbus;

    @endcode
*/
    ModbusConfig();


/*!
    @brief  Parse Modbus Config JSON file.
            
    @param    json
              JSON file with modbus configuration.
    @return True if the JSON script parsed successfully, otherwise false.
*/
    bool parseConfig(String json);
    bool parseConfig();		


/*!
    @brief  Print loaded and parsed config to Serial.
*/
    void printConfig();

/*!
    @brief  Polling interval periodical checker and callback function executer if some operation should be processed.
*/
    void loopModbusConfig();


/*
    @brief   Convert char* string to int. 
    @param   str
             String containing HEX or DEC digit to convert to int.
 
    @return  int with result of conversion.
*/
    int StrToHex(const char* str);
 
    PHandler pollingIntervalCallback;
    DynamicJsonDocument *doc;	
    char* filename;  
    String json;	
    Slaves slaves;
 
 protected:

 private:
    //unsigned int minSlavePollingInterval = 0;
    //unsigned int lastPolling = 0;
    void printValue(String name, String value, bool isHex = false);

};

#endif
