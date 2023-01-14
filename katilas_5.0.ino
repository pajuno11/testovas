
//-----------Time------------//
uint32_t lastTime = 0;
//-----------LCD------------//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3f, 20, 4);

//-----------lan------------//

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {  0xD1, 0xAD, 0x7E, 0xEA, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 6);
//char server[] = "192.168.1.99"; // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie. "www.yourwebpage.com")
IPAddress server(192, 168, 1, 99);
EthernetClient client;

//EthernetServer server1(80);

//String HTTP_req;
int count;
int RED1 = 9;

//-----------DHT------------//

#include <dhtnew.h>
DHTNEW mySensor0(22);
DHTNEW mySensor1(23);
DHTNEW mySensor2(24);
DHTNEW mySensor3(25);

int dhtp1 = 2;   //temp[] = { 0, (1, 2), 3}; dhtp1 = 0; nuo 0,  
int dhtp2 = 4;   //temp[] = { , (1, 2), }; dhtp2 = 3; iki 3,
int lygis[] = { 150, 130, 185, 185}; //{ 0, 1, 2, 3}
int vostuvas[] = { 42, 43, 48, 49};  //{ 0, 1, 2, 3}
int skaicius[] = { 0, 0, 0, 0};
float temp[] = { 0, 0, 0, 0};
float hum[] = { 0, 0, 0, 0};
float tempdhtskaicius[] = { 0, 0, 0, 0};
float tempdhts[] = { 0, 0, 0, 0};
float tempdhta[] = { 0, 0, 0, 0};
float tempdhtb[] = { 0, 0, 0, 0};
int Vod2[] = { 0, 0, 0, 0};
int Vod3[] = { 0, 0, 0, 0};
int Vod4[] = { 0, 0, 0, 0};


//-----------Analog------------//
// NTC 100k,+20k, R11 = 570, T11 = 311.75
// NTC 10k,+1k, R12 = 1500, T12 = 318.7

int couna;
int analog[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
int Vanlog[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float Vanalogtem[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int Voh1[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Voh2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Voh3[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Voh4[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

float R11 = 570; // value of R1 on board
float logR21, R21, T1, T11;
float c11 = 0.001129148, c21 = 0.000234125, c31 = 0.0000000876741; //steinhart-hart coeficients for thermistor

float R12 = 1500; // value of R1 on board
float logR22, R22, T2, T12;
float c12 = 0.001129148, c22 = 0.000234125, c32 = 0.0000000876741; //steinhart-hart coeficients for thermistor


//-----------katilas_auto------------//

int counkat;
int  KatiloBendras = 100;
int  KatiloVirsus1 = 100;
int  KatiloVirsus2 = 100;
int  KatiloKaminas = 100;
int  KatiloApacia = 100;

int ORO_SKLENDE_START = 38;
int ORO_SKLENDE_STATUS = 37;
int SIUBLYS = 36;
int ORO_SKLENDE_MK = 29;

int START_LED = 44;
int STOP_LED = 45;
int STATUS_LED = 46;

int MK[] = { 26, 27};
int ECO = 28;










void setup() {

  Serial.begin(9600);
  
    //-----------lan------------//
    Serial.println("Ethernet configured via DHCP");
    Ethernet.begin(mac, ip);
  //  HTTP_req = "";
  //Set LED to output
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
  pinMode(RED1, OUTPUT);
  digitalWrite(RED1,LOW);

 //-----------DHT-----------//
  mySensor0.read();
  mySensor1.read();
  mySensor2.read();
  mySensor3.read();
  mySensor0.setHumOffset(0);
  mySensor1.setHumOffset(0);
  mySensor2.setHumOffset(0);
  mySensor3.setHumOffset(0);
  mySensor0.setTempOffset(-0.8);
  mySensor1.setTempOffset(-0.8);
  mySensor2.setTempOffset(-0.8);
  mySensor3.setTempOffset(-0.8);

 //----------Reles radiatoius------------//
  for (count = dhtp1; count < dhtp2; count++) {
    pinMode(vostuvas[count], OUTPUT);
  }
  
    //-----------LCD------------//
  lcd.init();
  lcd.backlight();
  lcd.print("labas");

   //-----------katilas_auto------------//

  pinMode(ORO_SKLENDE_START, OUTPUT);
  pinMode(ORO_SKLENDE_STATUS, OUTPUT);
  pinMode(SIUBLYS, OUTPUT);
  digitalWrite(ORO_SKLENDE_START,LOW);
  digitalWrite(ORO_SKLENDE_STATUS,LOW);
  digitalWrite(SIUBLYS,LOW);
  pinMode(ORO_SKLENDE_MK, INPUT);

  pinMode(START_LED, OUTPUT);
  pinMode(STOP_LED, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(START_LED,LOW);
  digitalWrite(STOP_LED,HIGH);
  digitalWrite(STATUS_LED,LOW);

  pinMode(MK[0], INPUT);
  pinMode(MK[1], INPUT);
  pinMode(ECO, INPUT);
  

}

void loop() {


  analogmy();
  dhtmy();
  ButtonDebounce();
  katilo_auto();
  lygismy();


    if (millis() - lastTime > 5000)
  {
     
    lastTime = millis();
    relesradiatoiusmy();
    serial();
    lcdmy();

  }


//  delay(1000);
}
//-----------LOOP pabaiga------------//
////////////////////////////////////////////////////////////////////////////////

  //-----------Temperaturos lygis------------//
  
void dhtmy(){  
  mySensor0.read();
  mySensor1.read();
  mySensor2.read();
  mySensor3.read();
  hum[0] = mySensor0.getHumidity(), 1;
  hum[1] = mySensor1.getHumidity(), 1;
  hum[2] = mySensor2.getHumidity(), 1;
  hum[3] = mySensor3.getHumidity(), 1;
  temp[0] = mySensor0.getTemperature(), 1;
  temp[1] = mySensor1.getTemperature(), 1;
  temp[2] = mySensor2.getTemperature(), 1;
  temp[3] = mySensor3.getTemperature(), 1;

    for (count = dhtp1; count < dhtp2; count++) {
    skaicius[count] = (temp[count] * 8);
    tempdhtskaicius[count] = skaicius[count];
    tempdhts[count] = (tempdhtskaicius[count] / 8);
    tempdhta[count] = lygis[count];
    tempdhtb[count] = (tempdhta[count] / 8);
    }
}

  //----------Reles radiatoius------------//

void relesradiatoiusmy(){

    for (count = dhtp1; count < dhtp2; count++) {
      Serial.print(count);
      
  //  dhtmy();
    if(skaicius[count] < lygis[count])
            { digitalWrite(vostuvas[count],HIGH);}
    if(skaicius[count] > lygis[count])
            {digitalWrite(vostuvas[count],LOW); }
  }
  lcdmy();

}

  //-----------Temperaturos lygis------------//

void lygismy(){
// dhtmy();
  
  for (couna = 8; couna < 12; couna++) { 
  //   Vo0 = analogRead(analog[couna]);
     Voh1[couna] = map(analogRead(analog[couna]), 0, 1023, 1023, 0);                       
     Voh3[couna] = (Voh1[couna] - 15); 
     Voh4[couna] = (Voh1[couna] + 15);  
     
  if(Voh2[couna] < Voh3[couna] || Voh2[couna] > Voh4[couna]){
    Voh2[couna] = Voh1[couna];
    send_php();  ////////////////////////////////////////////////////
    
    
  }
    
    }
/*
    for (count = dhtp1; count < dhtp2; count++) {
     Vod3[count] = (skaicius[count] - 1); 
     Vod4[count] = (skaicius[count] + 1);
    
  if(Vod2[count] < Vod3[count] || Vod2[count] > Vod4[count]){
    Vod2[count] = skaicius[count];
    send_php();   //////////////////////////////////////////////////////
  }
 }
 */
}







////////////////////////////////////////////////////////////////////////////////


//-----------Analog------------//

void analogmy(){
  
      for (couna = 0; couna < 2; couna++) { // A2 to A5

  Vanlog[couna] = map(analogRead(analog[couna]), 0, 1023, 1023, 0);
  R21 = R11 * (1023.0 / (float)Vanlog[couna] - 1.0); //calculate resistance on thermistor
  logR21 = log(R21);
  T11 = (1.0 / (c11 + c21*logR21 + c31*logR21*logR21*logR21)); // temperature in Kelvin
  T1 = T11 - 311.75; //convert Kelvin to Celcius
  Vanalogtem[couna] = T1;

    }

      for (couna = 2; couna < 12; couna++) { // A2 to A5

  Vanlog[couna] = map(analogRead(analog[couna]), 0, 1023, 1023, 0);
  R22 = R12 * (1023.0 / (float)Vanlog[couna] - 1.0); //calculate resistance on thermistor
  logR22 = log(R22);
  T12 = (1.0 / (c12 + c22*logR22 + c32*logR22*logR22*logR22)); // temperature in Kelvin
  T2 = T12 - 300.7; //convert Kelvin to Celcius
  Vanalogtem[couna] = T2;

    }
}

//-----------katilas_Mygtukai-----------//


void ButtonDebounce()
{
    static byte buttonState[2]     = {LOW, LOW}; 
    static byte lastButtonState[2] = {LOW, LOW};
   // static byte LED_state[3] = {HIGH, HIGH, HIGH};

    static long lastDebounceTime[2] = {0}; 
    long debounceDelay = 1000;  
  
    byte reading[2];
    
    reading[0] = digitalRead(MK[0]);
    reading[1] = digitalRead(MK[1]);

    
    for (int i = 0; i < 3; i++) {
        if (reading[i] != lastButtonState[i]) {
            // reset the debouncing timer
            lastDebounceTime[i] = millis();
        }
      
        if ((millis() - lastDebounceTime[i]) > debounceDelay) {
            if (reading[i] != buttonState[i]) {
                buttonState[i] = reading[i];
          
                // Mygtukas START_MK HIGH
                if (buttonState[0] == HIGH) {
                    digitalWrite(START_LED, LOW);
                    digitalWrite(STOP_LED, HIGH);
                }
               // Mygtukas STOP_MK HIGH
                if (buttonState[1] == HIGH) {
                    digitalWrite(START_LED, HIGH);
                    digitalWrite(STOP_LED, LOW);
                }
            }
        }
    }

   lastButtonState[0] = reading[0];
   lastButtonState[1] = reading[1];
}

//-----------katilas_auto------------//

void katilo_auto(){

// 20/170, 30/230, 35/265 40/295, 45/335, 50/370, 55/410, 60/450, 65/485, 70/530, 75/560, 80/600, 85/630, 90/665
// 0=0c-18c kazkas netaip, 1=18c-35c  STOP, 2=35c- 60c ECO, 3=60c-70c  OPEN, 4=70c-80c STOP, 5=80c-90c Karstis, 6=90c-150c FIRE //

        int Kat_temp[] = { 0, 150, 265, 450, 530, 600, 665, 1023};
          KatiloBendras = map(analogRead(analog[0]), 0, 1023, 1023, 0);

  for (counkat = 0; counkat < 12; counkat++) {

    if(KatiloBendras > Kat_temp[counkat] && KatiloBendras <= Kat_temp[counkat + 1 ]){
      
      if(counkat == 0 ){         // 0c-18c kazkas netaip 0-150
        Serial.println("kazkas netaip");
        if (digitalRead(START_LED) == HIGH) {
          digitalWrite(SIUBLYS,LOW);
          digitalWrite(STOP_LED,LOW);
          katilo_sklende_START();
          } else {
            katilo_sklende_STOP();
            digitalWrite(SIUBLYS,LOW);
            digitalWrite(STOP_LED,HIGH);
          }
      }
      
      else if (counkat == 1 ){   // 18c-35c  STOP   150-265
        Serial.println("18c-35c  STOP");
        if (digitalRead(START_LED) == HIGH) {
          digitalWrite(SIUBLYS,LOW);
          digitalWrite(STOP_LED,LOW);
          katilo_sklende_START();
          }
          else{
            katilo_sklende_STOP();
            digitalWrite(SIUBLYS,HIGH);
            digitalWrite(STOP_LED,HIGH);
          }
      }

      else if (counkat == 2 ){  // 35c- 60c ECO  265-450
        
        Serial.println("35c- 60c ECO");
          if (digitalRead(START_LED) == HIGH) {
            digitalWrite(SIUBLYS,LOW);
            katilo_sklende_START();
          }
          else if (digitalRead(STOP_LED) == HIGH) {
            digitalWrite(SIUBLYS,LOW);
            katilo_sklende_STOP();
          }
          else if (digitalRead(STATUS_LED) == HIGH) {
            digitalWrite(SIUBLYS,LOW);
            katilo_sklende_START(); 
          }
         else if (digitalRead(ECO) == HIGH) {
            if (KatiloBendras < 350){
              digitalWrite(STATUS_LED,HIGH);
            }
          }else{
            digitalWrite(STATUS_LED,HIGH);
          }
      }
 
      else if (counkat == 3 ){   // 60c-70c  OPEN  450-530
        Serial.println("60c-70c  OPEN");
        if (digitalRead(START_LED) == HIGH) {
            digitalWrite(SIUBLYS,LOW);
            katilo_sklende_START();
          }
          else if (digitalRead(STOP_LED) == HIGH) {
            digitalWrite(SIUBLYS,LOW);
            katilo_sklende_STOP();
          }
          else if (digitalRead(STATUS_LED) == HIGH) {
            digitalWrite(SIUBLYS,LOW);
            katilo_sklende_START(); 
          }else{
            katilo_sklende_STOP();
            digitalWrite(SIUBLYS,LOW);
          }
      }
      
      else if (counkat == 4 ){   // 70c-80c STOP ,530- 600
        Serial.println("70c-80c STOP");
        katilo_sklende_STOP();
        katilo_FIRE();
      }
      else if (counkat == 5 ){  // 80c-90c Karstis
        Serial.println("80c-90c Karstis");
        katilo_sklende_STOP();
        katilo_FIRE();
      }
      else if (counkat == 6 ){   // 90c-150c FIRE
        Serial.println("90c-150c FIRE");
        katilo_sklende_STOP();
        katilo_FIRE();
      }
    }     
  }  
}

//-----------katilas_FIRE-----------//

void katilo_FIRE(){
  Serial.println("KAZKAS NETAIP ");
  digitalWrite(SIUBLYS,LOW);
  digitalWrite(STATUS_LED,LOW);
  digitalWrite(START_LED,LOW);
}

//-----------katilas_Netaip-----------//

void katilo_netaip(){
  Serial.println("KAZKAS NETAIP ");
  digitalWrite(ORO_SKLENDE_STATUS,LOW);
  digitalWrite(SIUBLYS,LOW);
  digitalWrite(START_LED,LOW);
  digitalWrite(STOP_LED,HIGH);
  digitalWrite(STATUS_LED,LOW);
}


//-----------katilo_sklende_STOP-----------//

void katilo_sklende_STOP(){
  
  Serial.println("STOP");
  digitalWrite(ORO_SKLENDE_STATUS,LOW);
  digitalWrite(ORO_SKLENDE_START,LOW);
  digitalWrite(STATUS_LED,LOW);
}

//-----------katilo_sklende_START-----------//

void katilo_sklende_START(){
  Serial.println("START");

  
       if (digitalRead(ORO_SKLENDE_STATUS) == LOW){
      digitalWrite(ORO_SKLENDE_STATUS,HIGH);
      digitalWrite(ORO_SKLENDE_START,HIGH);
      delay(1000);
      digitalWrite(ORO_SKLENDE_STATUS,HIGH);
      digitalWrite(ORO_SKLENDE_START,LOW);
      
    } else {
      digitalWrite(ORO_SKLENDE_STATUS,HIGH);
      digitalWrite(ORO_SKLENDE_START,LOW);
      digitalWrite(STATUS_LED,HIGH);
    }
}


///////////////////////////////////////////////////////////////////////////////
















//-----------Serial------------//

void serial(){
  for (couna = 0; couna < 16; couna++) {
    Serial.print(" - ");
    Serial.print(Vanalogtem[couna]);   
  }
  Serial.println("  ");

}


 //-----------LCD------------//

void lcdmy(){

   lcd.setCursor(0,0);
   lcd.print("1a.                 ");
   lcd.setCursor(4,0);
   lcd.print(Vanalogtem[0]);
   lcd.setCursor(9,0);
   lcd.print(" - 2a");
   lcd.setCursor(15,0);
   lcd.print(Vanalogtem[1]);
   lcd.setCursor(0,1);
   lcd.print("2a.                 ");
   lcd.setCursor(4,1);
   lcd.print(temp[2]);
   lcd.print("c -");
   lcd.setCursor(13,1);
   lcd.print(Vanalogtem[3]);
   lcd.print(" r");
   lcd.setCursor(0,2);
   lcd.print("1a.                 ");
   lcd.setCursor(4,2);
   lcd.print(temp[3]);
   lcd.print("c -");
   lcd.setCursor(13,2);
   lcd.print(Vanalogtem[10]);
   lcd.print(" r");

   if (digitalRead(vostuvas[3]) == HIGH) {
          lcd.setCursor(0,3);
          lcd.print("        ");
          lcd.setCursor(1,3);
          lcd.print("1a.Syla");
  } else {
          lcd.setCursor(0,3);
          lcd.print("        ");

  }




  if (digitalRead(vostuvas[2]) == HIGH) {
          lcd.setCursor(9,3);
          lcd.print("         ");
          lcd.setCursor(9,3);
          lcd.print("-  2a.Syla");
  } else {
          lcd.setCursor(9,3);
          lcd.print("         ");

  }

  
}

 //----------send_php------------//

void send_php(){
  digitalWrite(RED1, HIGH);
  dhtmy();
//  Serial.println("Connecting...");
  if (client.connect(server, 80)) {
 //   Serial.println("--> Connected..write_radiatorius_min.php");
    client.print("GET /write_radiatorius_min.php?"); // This
    

    client.print("dht0=");
    client.print(temp[0]);
    client.print("&dht1=");
    client.print(temp[1]);
    client.print("&dht2=");
    client.print(temp[2]);
    client.print("&dht3=");
    client.print(temp[3]);

analogmy();

    for (couna = 0; couna < 10; couna++) {
      client.print("&ang0");
      client.print(couna);
      client.print("=");
      client.print(Vanalogtem[couna]);
      
    }
    for (couna = 10; couna < 16; couna++) {
      client.print("&ang");
      client.print(couna);
      client.print("=");
      client.print(Vanalogtem[couna]);
      
    }

//----------------------------//
/*
    client.print("&ang00=");
    client.print(Vo11);
    client.print("&ang01=");
    client.print(Ve1[1]);
    client.print("&ang02=");
    client.print(Ve1[2]);
    client.print("&ang03=");
    client.print(Ve1[3]);
    client.print("&ang04=");
    client.print(Ve1[4]);
    client.print("&ang05=");
    client.print(Ve1[5]);
    client.print("&ang06=");
    client.print(Ve1[6]);
    client.print("&ang07=");
    client.print(Ve1[7]);
    client.print("&ang08=");
    client.print(Ve1[8]);
    client.print("&ang09=");
    client.print(Ve1[9]);
    client.print("&ang10=");
    client.print(Ve1[1]);
    client.print("&ang11=");
    client.print(Ve1[1]);
    client.print("&ang12=");
    client.print(Ve1[1]);
    client.print("&ang13=");
    client.print(Ve1[1]);
    client.print("&ang14=");
    client.print(Ve1[1]);
    client.print("&ang15=");
    client.print(Ve1[1]);


*/


//-------------------------//
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.1.99");
    client.println( "Content-Type: application/x-www-form-urlencoded" );
    client.println("Connection: close");
    client.println();
    client.println();
  }
    else {
    // If Arduino can't connect to the server (your computer or web page)
    Serial.println("--> connection failed--write_min.php");
    Ethernet.begin(mac, ip);
  }
  client.flush();
  client.stop();
  digitalWrite(RED1, LOW);
  delay(100);
}
