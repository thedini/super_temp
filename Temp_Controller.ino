// written by C Macris with lots of help
// include the library code
// Goals - take temperature from oneWire digital sensor and display on LCD
//       - use funtion key to select between functions
//          +Select Temp Type (C, F, K)
//          +Select Heating or Cooling
//          +Select Temp spread (aka, turn on after it gets x degrees from desired temp
//          +select predefined temp functions (parm cheese, chedder cheese, cold process soap
//       - Buzzer to alert when temp is reached
// search arduino index

#include <EEPROM.h> //library for writing to EEPROM
#include <LiquidCrystal.h>// include the library code
#include <OneWire.h> // include temp sensor library code

//#define aref_voltage 3.3  // we tie 3.3V to ARef and measure it with a multimeter!
// above unneeded for oneWire sensor candidtate for removal

int DS18S20_Pin = 10; //DS18S20 is the the oneWire Signal pin on digital 2
int tvalue;           // temperature value
int led = 13;         // led is at pin is going to be the relay box!! to make things hotter or colder
float temp;           // make a variable called temp
float settemp;        // make a variable called temp
int swtu = 7;         // switch up is at pin 7
int swtd = 6;         // switch down is at pin 6
int swfn = 9;          //function switch at pin 9
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd is at 12,11,5,4,3,2

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 10


// initialize the library with the numbers of the interface pins
//------------------------------------------------------------\\


void setup() { 
  pinMode (led,1);  // make led or pin13 an output
  Serial.begin (9600); // set the serial monitor tx and rx speed
  // analogReference(EXTERNAL); //from analog sensor
  
  lcd.begin(16, 2); // set up all the "blocks" on the display
  lcd.setCursor(0,0); // set the cursor to colum 0 row 0
  lcd.print("MACRIS MADE"); // display hello world for 1 second
  //delay(1000)
  lcd.clear(); // clear the lcd
  //EPROM section doesn't work at all..
  EEPROM.read (1); // make the eeprom or atmega328 memory address 1

}

void loop() {
  //figure i should call up some functions here
  
}
/*
void mainMenu() {
  
  byte offset=0, loopcnt, whichkey,point=0;
  
  do {
    ClearLCD();
    PrintLCD_P(6); //"      Main Menu     "
    PrintLCDAt_P(offset, 0, 2);
    whichkey = PollKey();
    switch(whichkey) {
       case KeyUp:
          if (offset > 0) offset--;
          break;
       case KeyDown:
          if (offset < 5) offset++;
          break;
       case KeySel:
          switch (offset) {
             case 0: //Enroll
                enrollUser();
                break;
             case 1: //Edit users
                editUser();
                break;
             case 2: //Delete Users
                deleteUser(false);
                break;
             case 3: //Delete all users
                deleteUser(true);
                break;
             case 4: //List Users
                listUsers();
                break;
             case 5: //Set options
                optionsMenu();
                break;
          }
          break;
    }        
  } while (1 == 1);
}
*/
float tempC(){
  float temperature = getTemp();
  Serial.println(temperature);
  Serial.println(" degrees C");
  return temperature;
}

float tempF(){
  float temperatureF = (tempC() * 9.0 / 5.0) + 32.0;
  Serial.println(temperatureF); 
  Serial.println(" degrees F");
  return temperatureF;
}

float tempK(){
    float temperatureK = (tempC() + 273.15);
    Serial.println(temperatureK);
    Serial.println(" degrees K")

void heating(){
      if (temperatureF < settemp) // if the temperature is less than your chosen settemp
    {
  digitalWrite (led, 1); // turn on the relay
    }
      else // if that doesn't happen, then turn the led off
      {
      digitalWrite (led,0);
      }
}

void cooling(){
    if (temperatureF > settemp) //if the temperature is greater than
    {
   digitalWrite (led, 1); //turn relay on
    }
      else //if it is colder
    {
      digitalWrite (led, 0);
 }      
      
void buttons(){ 
  
  //int tvalue = analogRead(tempPin);  // make tvalue what ever we read on the tempPin
  //float temperature = getTemp();
  // Serial.println(temperature);
  // delay(100); //just here to slow down the output so it is easier to read
  
  //Serial.print("Temp reading = ");
  //Serial.print(tempReading);     // the raw analog reading
 
  // converting that reading to voltage, which is based off the reference voltage
  //float voltage = tvalue * aref_voltage;
  //voltage /= 1024.0; 
  //float temperature = getTemp();
   //Serial.println(temperature);
   //Serial.println(" degrees C");
  // delay(100);//slow down output
   
  // print out the voltage
  //Serial.print(" - ");
  //Serial.print(voltage); Serial.println(" volts");
 
  // now print out the temperature
  //float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((volatge - 500mV) times 100)
  //Serial.print(temperatureC); Serial.println(" degrees C");
 
  // now convert to Fahrenheight
 // float temperatureF = (temperature * 9.0 / 5.0) + 32.0;
  //Serial.print(temperatureF); Serial.println(" degrees F");
 
  // delay(1000);
  //-------------------------\\

  printtoscreen(tempF() + " F", tempC() + " C"); 
  //lcd.setCursor (0,0); // set the cursor to 0,0
  //lcd.print (temperatureF);  // Print the current temp in f
  //lcd.print ('F');
  //Serial.println (temp);  // print the temp it the serial monitor
  //settemp = EEPROM.read(1); // read the settemp on the eeprom

  //  delay (250); // wait for the lcd to refresh every 250 milliseconds
 
    if             // if we see the switch up pin reading on 1 or 5 volts
      (digitalRead(swtu)== 1 )
  {
    settemp ++;  // add one to the settemp, the settemp is the ideal temperature for you
 
  // EEPROM.write (1,settemp); /* write the most recent settemp in eeprom data stoage
 // so that if the power is disconnected, you settemp is saved!*/
  }

      else{// other wise do nothing

  }

    if
      (digitalRead (swtd) == 1)// if we detect a 1 on the minus switch pin
     {
  (settemp --);// subtract one fromm the settemp
  //EEPROM.write (1,settemp); /* write the most recent settemp in eeprom data stoage
  //so that if the power is disconnected, you settemp is saved!*/
 
      }
        else {
// else, do nothing
        }
        
    if
      (digitalRead (swfn) == 1)// if we detect a 1 on the function button
     {
 // some_fn();// go to this function
 
      }
        else { // else, do nothing
        }

/*    if (temperatureF < settemp) // if the temperature exceeds your chosen settemp
    {
  digitalWrite (led, 1); // turn on the led
    }
      else // if that doesn't happen, then turn the led off
      {
      digitalWrite (led,0);
      }
*/

  printtoscreen("", "Set To: " + settemp);
  //lcd.setCursor (0,1); // set the cursor to 0,1
//lcd.print ("Set To "); // Print set to and your ideal temperature in f
//lcd.print (settemp);
//lcd.print ('F');
//Serial.println(settemp);  // Print the settemp in the serial montior
//EEPROM.write (1,settemp);

 


//delay (250); // wait 250 milliseconds



} 

//--------------------------------------\\
//Get Temp from One Wire
float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}


void printtoscreen(String texttop, String textbottom){
  lcd.setCursor (0,0); // set the cursor to 0,0
  lcd.print (texttop);  // Print the current temp in f
  lcd.setCursor (0,1);
  lcd.print (textbottom); 
}
