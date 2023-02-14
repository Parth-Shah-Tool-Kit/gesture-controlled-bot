#include "BluetoothSerial.h"
#include "Wire.h" 

const int MPU_ADDR = 0x68; 
float ax=0,ay=0,az=0,ay2=0;
int16_t accelerometer_x, accelerometer_y, accelerometer_z; 
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


/* Check if Bluetooth configurations are enabled in the SDK */
/* If not, then you have to recompile the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
uint8_t address[6] = {0x3C, 0x61, 0x05, 0x12, 0xDE, 0x7E};
bool connected;


void setup() {
  //Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  SerialBT.begin("host", true);
  connected = SerialBT.connect(address);
  if(connected) 
  {
    //Serial.println("Connected Succesfully!");
  } 
  else 
  {
    while(!SerialBT.connected(10000)) {
      digitalWrite(LED_BUILTIN, HIGH);
      //Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) 
  {
    //Serial.println("Disconnected Succesfully!");
  }
  SerialBT.connect();
  digitalWrite(LED_BUILTIN, LOW); 
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(1);
  
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(0);
  //Wire.beginTransmission(MPU_ADDR);
  Wire.requestFrom(MPU_ADDR, 14, 1);

  
  accelerometer_x = Wire.read()<<8 | Wire.read();
  accelerometer_y = Wire.read()<<8 | Wire.read();
 
  ax=(float)(accelerometer_x);
  ay=(float)(accelerometer_y);
  
  //SerialBT.println("hi");
  if(((ax >= -12000)&&(ax <= -3000))&&((ay >= -2500)&&(ay <= 2500)))
  {
    SerialBT.println("w");
  }
  else if(((ax >= 3000)&&(ax <= 12000))&&((ay >= -2500)&&(ay <= 2500)))
  {
    SerialBT.println("s");
  }
  else if(((ax >= -2000)&&(ax <= 2000))&&((ay >= -14000)&&(ay <= -5000)))
  {
    SerialBT.println("a");
  }
  else if(((ax >= -2000)&&(ax <= 2000))&&((ay >= 5000)&&(ay <= 14000)))
  {
    SerialBT.println("d");
  }

  else if(((ax >= -12000)&&(ax <= -3000))&&((ay >= 5000)&&(ay <= 14000)))
  {
    SerialBT.println("q");
  }
  else if(((ax >= -12000)&&(ax <= -3000))&&((ay >= -14000)&&(ay <= -5000)))
  {
    SerialBT.println("e");
  }
  else if(((ax >= 3000)&&(ax <= 12000))&&((ay >= -14000)&&(ay <= -5000)))
  {
    SerialBT.println("z");
  }
  else if(((ax >= 3000)&&(ax <= 12000))&&((ay >= 5000)&&(ay <= 14000)))
  {
    SerialBT.println("c");
  }
 
  delay(20);
}
