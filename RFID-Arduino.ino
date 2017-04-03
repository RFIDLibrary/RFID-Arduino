#include "rc522.h"

RFID rfid;
void setup()
{
    Serial.begin(9600);
    
}
 
void loop()
{
 
    uchar status;
    uchar str[MAX_LEN];
 
    // Search card, return card types
    status = rfid.MFRC522_Request(PICC_REQIDL, str);
    if (status != MI_OK)
    {
        return;
    }
 
    // Show card type
    rfid.ShowCardType(str);
 
    //Prevent conflict, return the 4 bytes Serial number of the card
    status = rfid.MFRC522_Anticoll(str);
 
    // str[0..3]: serial number of the card
    // str[4]: XOR checksum of the SN.
    if (status == MI_OK)
    {
        Serial.print("The card's number is: ");
        memcpy(rfid.serNum, str, 5);
        rfid.ShowCardID(rfid.serNum);
 
        // Check people associated with card ID
        uchar* id = rfid.serNum;
        Serial.print(id[0]);
        Serial.print(id[1]);
        Serial.print(id[2]);
        Serial.print(id[3]);
        Serial.print(id[4]);
        Serial.print('\n');
    }
 
    rfid.MFRC522_Halt(); //command the card into sleep mode
 
    delay(200);
}
 
