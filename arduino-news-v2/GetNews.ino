#include <Bridge.h>
#include <TembooYunShield.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Bridge.begin();
  Console.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Console.println("Running GetNews - Run #" + String(calls++));
    
    TembooYunShieldChoreo GetNewsChoreo;

    // Invoke the Temboo client
    GetNewsChoreo.begin();

    // Set Temboo account credentials
    GetNewsChoreo.setAccountName(TEMBOO_ACCOUNT);
    GetNewsChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GetNewsChoreo.setAppKey(TEMBOO_APP_KEY);
    GetNewsChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
    
    // Identify the Choreo to run
    GetNewsChoreo.setChoreo("/Library/Yahoo/Finance/GetNews");
    
    // Run the Choreo; when results are available, print them to Console
    GetNewsChoreo.run();
    
    while(GetNewsChoreo.available()) {
      char c = GetNewsChoreo.read();
      Console.print(c);
    }
    GetNewsChoreo.close();
  }

  Console.println("Waiting...");
  delay(30000); // wait 30 seconds between GetNews calls
}