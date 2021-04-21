void serialReset() {
  serialConnAttempt = true;
  serialConnected = correctConnection = false;
  int maxAttempts = (isBuilt)? 1:1;  //что такое isBuilt ?
  print(Serial.list());
  
  if (isBuilt) { 
    WcomPort.clear(); //вот тут получается не блютуз-компорт нужен, а просто компорт? Потому что проводками в компьютер вставляем
    WcomPort.stop();
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

void serialEvent(Serial WcomPort) { // и тут заменить порт
  String inputData = BTcomPort.readStringUntil(linefeed); // и тут заменить порт
  
  if (inputData != null) {
    if (!correctConnection) correctConnection = true;
    inputData = trim(inputData); 
    sensorsData = float(split(inputData, ',')); // во-во-во, тут мы делим по запятым то, что прописывали в ардуине с запятыми
  }
}
void serialConnect(boolean debug) {
  boolean lSerialConnected = serialConnected;
  try {
    try {
      WcomPort = null; // и тут заменить порт
      WcomPort = new Serial(this, Serial.list()[0], 57600); // тут заменить название порта и частоту, наверное
      lSerialConnected = true;
    }
    catch (RuntimeException ex) {
      WcomPort = null; // и тут заменить порт
      lSerialConnected = false;
      if (debug) {
      print("COM Port busy >> ");
      println(ex);
      }
    }
  }
  catch (ArrayIndexOutOfBoundsException ex) {
    WcomPort = null;
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
