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

void serialConnect(boolean debug) {
  boolean lSerialConnected = serialConnected;
  try {
    try {
      BTcomPort = null;
      BTcomPort = new Serial(this, Serial.list()[0], 57600);
      lSerialConnected = true;
    }
    catch (RuntimeException ex) {
      BTcomPort = null;
      lSerialConnected = false;
      if (debug) {
      print("COM Port busy >> ");
      println(ex);
      }
    }
  }
  catch (ArrayIndexOutOfBoundsException ex) {
    BTcomPort = null;
    lSerialConnected = false;
    if (debug) {
      print("No serial_ports available found >> ");
      println(ex);
    }
  }
  finally {
    serialConnected = lSerialConnected;
  }
}
