#include <MFRC522v2.h>
#include <MFRC522DriverI2C.h>
#include <MFRC522Debug.h>
// Made as an example in C for using the PiicoDev RFID Module because the reference version is in micropython
 
const uint8_t customAddress = 0x2C; // by default the rfid sensor will be 0x2C, unless someone has touched the dip switches

// In reader mode scanning a card will output something in the form: for example Card UID: 04 AE 43 FA 3F 74 80 | UID_Size: 7
// now update allowed_uid_size and write each bit of the UID with the prefix 0x in a comma seperated list so 04 becomes 0x04
// then you can turn reader mode off and the code in the below labelled block where you see "access granted" will run or not run everytime a card is swiped
bool read_uid_mode = false;

int allowed_uid_size = 7;
byte allowed_uid[] = {0x04,0xAE,0x43,0xFA,0x3F,0x74,0x80};

TwoWire &customI2C = Wire;
MFRC522DriverI2C driver{customAddress, customI2C}; // Create I2C driver.
MFRC522 mfrc522{driver}; // Create MFRC522 instance.

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC for debugging.
  mfrc522.PCD_Init();   // Init MFRC522 board.
}

void loop() {
  rfid_authentication();
  delay(100);
}

void rfid_authentication(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    if (read_uid_mode) {
      // This will print out the uid and uid size of the scanned rfid card if in reader mode
      Serial.print(F("Card UID:"));
      MFRC522Debug::PrintUID(Serial, mfrc522.uid);
      Serial.print(" | UID_Size: ");
      Serial.print(mfrc522.uid.size);
      Serial.println();
      return;
    }
    // not in reader mode so check if the correct card is presented
    bool correct_uid = true;
    if (mfrc522.uid.size == allowed_uid_size) {
      for(int i = 0; i < mfrc522.uid.size; i++){
        if (mfrc522.uid.uidByte[i] != allowed_uid[i]){
          correct_uid = false;
        } 
      }
    } else {
      correct_uid = false;
    }
    
    // now we can write our own code here
    if(correct_uid) {
      Serial.println("Access Granted");
      // write code for when access is granted eg for motors or leds
    } else {
      Serial.println("Access Denied");
      // write code for when access is denied eg for buzzer noise and a red led or something else
    } 
  } 
}