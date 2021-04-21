void serialReset() {
  serialConnAttempt = true;
  serialConnected = correctConnection = false;
  int maxAttempts = (isBuilt)? 1:1;
  print(Serial.list());
  
  if (isBuilt) {
    BTcomPort.clear();
    BTcomPort.stop();
  }
  
  for (int attempt = 0; attempt < maxAttempts; ++attempt) {
    delay(20);
    serialConnect(false);
    if (serialConnected) {
      if (isBuilt) delay(1000);
      break;
    }
  }
  if (serialConnected && isBuilt) delay(1000);
  serialUpdateLast = transform(hour())+':'+transform(minute())+':'+transform(second());
  serialConnAttempt = false;
}

void serialEvent(Serial BTcomPort) {
  String inputData = BTcomPort.readStringUntil(linefeed);
  
  if (inputData != null) {
    if (!correctConnection) correctConnection = true;
    inputData = trim(inputData);
    sensorsData = float(split(inputData, ','));
  }
