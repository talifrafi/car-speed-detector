#include <LiquidCrystal.h>
#include <SPI.h>        // Include SPI library (needed for the SD card)
#include <SD.h>         // Include SD library

File myFile;

int sen1=3;
int sen2=2;
int led = 0;
const int D4 = 7, D5 = 6, D6 = 5, D7 = 4, rs = 9, en = 8;
LiquidCrystal lcd(rs, en, D4, D5, D6, D7);
unsigned long t1=0;
unsigned long t2=0; 
float velocity;
float velocity_real;
float timeFirst;
float timeScnd;
float diff;
float jaraksensor=100;  //in cm.
float waktu;
int i = 0;
float speed;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Welcome To");
  lcd.setCursor(0,1);
  lcd.print("Speed Detector");
  delay(500);
  lcd.clear();
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
  pinMode(led,OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Speed Measurement");
  delay(10);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  Serial.print("Initializing SD card...");
 
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
//    if(led == HIGH){
//       myFile.println("LED : ON");
//    }
//    else if(led == LOW){
//      myFile.println("LED : OFF");
//    }
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
 
//  // re-open the file for reading:
//  myFile = SD.open("test.txt");
//  if (myFile) {
//    Serial.println("test.txt:");
// 
//    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
//    // close the file:
//    myFile.close();
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
//  }
}
  void loop()
  {
  velocity_real = 0; 
  if (digitalRead(sen1)==HIGH)
    {
      timeFirst = millis();
      //digitalWrite(ledPin, LOW);
      delay(30);
    }
 
  if (digitalRead(sen2)==HIGH)
  {
    timeScnd = millis();
    diff = timeScnd - timeFirst; 
    waktu = diff/1000;
    velocity = jaraksensor / waktu; //  cm/s 
    velocity_real = (velocity)/100;     //milliseconds to hours and centimetres to kilometeres.
    delay(30);
  }
  if(velocity_real > 30){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(50);
  }

  
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("object speed = ");
    lcd.setCursor(3,1);
    lcd.print(velocity_real);
     lcd.print(" m/s   ");
     delay(300);
     lcd.setCursor(3,1);
     lcd.print("            ");
     delay(300);
    lcd.clear();
  }

  myFile = SD.open("test.txt", FILE_WRITE);

  if(velocity_real > 30){
  Serial.println(velocity_real);
  Serial.println("LED : ON, BUZZER : ON");
  Serial.println("Kecepatan Melebihi Batas");
  myFile.println(velocity_real);
  myFile.println("LED : ON, BUZZER : ON");
  myFile.println("Kecepatan Melebihi Batas");
  delay (500);
  }
  else {
  Serial.println(velocity_real);
  Serial.println("LED : OFF, BUZZER : OFF");
  Serial.println("Kecepatan Normal");
  myFile.println(velocity_real);
  myFile.println("LED : OFF, BUZZER : OFF");
  myFile.println("Kecepatan Normal");
  delay (500);
  }
  myFile.close();

  /*else if(analogRead(sen2)<500 && analogRead(sen1)<500)       //uncomment if you want to write it.
  {
      Serial.print("\n Error:404/ the object is tooo big.");
  }*/
 /* else{Serial.print("\n error:404/no object detected ");}     //uncomment if you want to write it.*/
  }
