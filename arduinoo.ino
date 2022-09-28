/*Door lock system code
 * http://srituhobby.com
 */
 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
char UID[]  = "71 77 4C D3";
char UID2[] ="76 E3 EA 1F";
char data;
char data2;
String dataread;


Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  servo.write(70);
  lcd.init();
  lcd.backlight();
  servo.attach(3);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
 
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();
  
   if (ID.substring(1) == UID  )
   {

    Serial.write("71 77 4C D3");
    
   }
   else if(ID.substring(1) == UID2  )
   {
    Serial.write("76 E3 EA 1F");
   }
   if (Serial.available()){ 
     delay(3000);
data=Serial.read();
 lcd.clear();
lcd.setCursor(1, 0);
  lcd.print("cin = ");
  lcd.setCursor(7, 0);
  lcd.print(data);
 
 
  delay(3000);
  
      dataread=Serial.readStringUntil(data);
      


  lcd.setCursor(0, 1);
   lcd.print("points = ");
  lcd.setCursor(8, 1);
  lcd.println(dataread);
   delay(5000);
   lcd.clear();
   }

}
