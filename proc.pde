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
  String inputData = WcomPort.readStringUntil(linefeed); // и тут заменить порт
  
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


void uartReceive() {
  unsigned long timer;
  unsigned int maxWait, loopCounter, maxLoops, multiplier;
  int incomingInt;
  int* currentStorage = 0;
  word numItems, storage;
  char incomingChar;
  bool transmitStart;

  maxWait = 100;
  maxLoops = 4;
  multiplier = 1;
  loopCounter = storage = numItems = 0;
  transmitStart = false;

  timer = millis();
  packageReceived = false;
  while (millis() - timer < maxWait && (storage < numItems || !transmitStart)) {
    if (uartSerial.available()) {
      incomingChar = uartSerial.read();
      incomingInt = (int)incomingChar;
      //Serial.println(incomingInt);

      if (incomingInt == -3) {
        if (transmitStart) {
          ++loopCounter;
          if (loopCounter == maxLoops) break;
        }
        else transmitStart = true;

        storage = 0;
        currentStorage = systemData;
        numItems = SYSTEM;

        clearData(true, true);
      }
      else if (incomingInt == -2) {
        if (transmitStart) break;
        else transmitStart = true;

        currentStorage = stateData;
        numItems = STATE;

        clearData(false, true);
      }
      else if (transmitStart) {
        if (incomingInt == -1) {
          ++storage;
          multiplier = 1;
        }
        else if (incomingInt >= 0) {
          if (currentStorage[storage] == -1) currentStorage[storage] = 0;
          currentStorage[storage] += incomingInt * multiplier;

          multiplier *= 100;
        }
      }
      timer = millis();
      packageReceived = true;
    }
  }
  if (storage < numItems && transmitStart) {
    for (int item = storage; item < numItems; ++item) currentStorage[item] = 0;
  }
  else if (!transmitStart) clearData(true, true);
}

//осталось сюда вставить блок с рисованием (а там используются какие-то углы, которые нужно взять откуда-то (возможно, создать кватернионы))
void drawCylinder(float topRadius, float bottomRadius, float tall, int sides) {
    float angle = 0;
    float angleIncrement = TWO_PI / sides;
    beginShape(QUAD_STRIP);
    for (int i = 0; i < sides + 1; ++i) {
        vertex(topRadius*cos(angle), 0, topRadius*sin(angle));
        vertex(bottomRadius*cos(angle), tall, bottomRadius*sin(angle));
        angle += angleIncrement;
    }
    endShape();
    
    // If it is not a cone, draw the circular top cap
    if (topRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
        
        // Center point
        vertex(0, 0, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }
  
    // If it is not a cone, draw the circular bottom cap
    if (bottomRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);
    
        // Center point
        vertex(0, tall, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }

//Осталось получить данные с датчиков, потом их превратить в кват.

