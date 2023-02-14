#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

uint8_t address[6] = {0xAC, 0x67, 0xB2, 0x3C, 0xA0, 0xD2};
String dat = "";
int bat = 0;
int a = 0;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("slave");

  //Power outputs for sensors
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);

  //Sensor Inputs
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  
  //Motor Outputs
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
}

void loop() {

  //Setting power for sensors
  digitalWrite(15,HIGH);
  digitalWrite(2,LOW);
  
  digitalWrite(5,HIGH);
  digitalWrite(18,LOW);
  
  digitalWrite(19,HIGH);
  digitalWrite(21,LOW);

  // Recieveing data
  if (SerialBT.available()) 
  {
    dat = SerialBT.readStringUntil('\n');
  }
  
  
  //checking sensors
  
  if ((digitalRead(34) == LOW)&&((digitalRead(35) == LOW))&&(digitalRead(33) == HIGH)&&((digitalRead(32) == HIGH)))
  {
    dat = "s";
  }
  else if ((digitalRead(32) == LOW)&&((digitalRead(33) == LOW))&&(digitalRead(34) == HIGH)&&((digitalRead(35) == HIGH)))
  {
    dat = "w";
  }
  else if ((digitalRead(34) == LOW)&&((digitalRead(33) == HIGH))&&(digitalRead(32) == HIGH)&&((digitalRead(35) == HIGH)))
  {
    dat = "c";
  }
  else if ((digitalRead(35) == LOW)&&((digitalRead(33) == HIGH))&&(digitalRead(34) == HIGH)&&((digitalRead(32) == HIGH)))
  {
    dat = "z";
  }
  else if ((digitalRead(32) == LOW)&&((digitalRead(33) == HIGH))&&(digitalRead(34) == HIGH)&&((digitalRead(35) == HIGH)))
  {
    dat = "q";
  }
  else if ((digitalRead(33) == LOW)&&((digitalRead(32) == HIGH))&&(digitalRead(34) == HIGH)&&((digitalRead(35) == HIGH)))
  {
    dat = "e";
  }
  
  bat = (int)((char)dat[0]); // converting to ascii values
  Serial.println(dat);
  //Running motors based on gyroscope recieved data or sensor manipulated
  if (bat == 119)//forward
  {
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(27, HIGH);
    digitalWrite(26, LOW);
  }
  else if (bat == 115)// back
  {
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(26, HIGH); 
  }
  else if (bat == 97)// left
  {
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    digitalWrite(27, HIGH);
    digitalWrite(26, LOW);
  }
  else if (bat == 100)// right
  {
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, HIGH);
  }
  else if (bat == 113)// front left
  {
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(27, HIGH);
    digitalWrite(26, LOW);
  }
  else if (bat == 101)// front right
  {
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
  }
  else if (bat == 122)// back left
  {
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, HIGH);
  }
  else if (bat == 99)// back right
  {
    digitalWrite(12, LOW);
    digitalWrite(14, HIGH);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
  }
  
  else  // stop
  {
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
  }
  
  a++;
  if (a == 150)
  {
    dat = "";
    a = 0;
  }
}
