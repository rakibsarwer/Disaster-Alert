
#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7, 6);
int trigPin1=9;
int echoPin1=10;

int trigPin2=11;
int echoPin2=12;
int sensePin1=A0;
int sensePin2=A1;




String api_key = "KN4WH0QQK48KBCEL"; //Thinkspeak data write API KEY 


String field = "1"; 
String field = "2";
String field = "3";
String field = "4";
String field = "5";



void setup() //Setup Subprocedure
{  
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
   pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  mySerial.begin(9600);               // the GPRS baud rate   
 
  delay(1000);
}
 
void loop() // Main loop
{
  
 int valA1=analogRead(sensePin1);
int valA2=analogRead(sensePin2);
Serial.println(valA1);
Serial.println(valA2);
distanceir1= (valA1/2) / 29.1;
distanceir2= (valA2/2) / 29.1;
delay(200);

 
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

   if (distance1 >= 500 || distance1 <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print ( "Sensor1  ");
    Serial.print ( distance1);
    Serial.println("cm");
  }
  delay(2000);
long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;

   if (distance2 >= 500 || distance2 <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("Sensor2  ");
    Serial.print(distance2);
    Serial.println("cm");
  }
  delay(2000);


    int uls1 = distance1;
    String us1 = String(uls1);

    int uls2 = distance2;
    String us2 = String(uls2);

    int inf = distanceir1;
    String ir1 = String(inf);

    int inf2 = distanceir2;
    String ir2 = String(inf2);

    int itemp = 273;
    String temp = String(itemp);
    
    Serial.print(" iiuc bus ");
    Serial.print(x);
    Serial.println();
   Send2Pachube(us1,us2,ir1,ir2,temp);
    delay(2000);
   }
  delay(1000);
}


void Send2Pachube(String us1,String us2,String ir1,String ir2,String temp)       //send data with gsm
{
  mySerial.println("AT"); //check gsm
  delay(1000);

  mySerial.println("AT+CPIN?"); //Check if sim locked with pin
  delay(1000);

  mySerial.println("AT+CREG?"); //Check if gets registered to sim network
  delay(1000);

  mySerial.println("AT+CGATT?"); //Check if gets attached to registered network
  delay(1000);

  mySerial.println("AT+CIPSHUT"); //Close any previous active PDP (Packet data protocol) context
  delay(1000);

  mySerial.println("AT+CIPSTATUS"); //Check current connection status (bearer, TCP/UDP, IP, Port etc.)
  delay(2000);

  mySerial.println("AT+CIPMUX=0"); //Deactive any multi IP connections
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"INTERNET\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0"); //Set prompt if module is avail to send data
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  GET https://api.thingspeak.com/update?api_key=KN4WH0QQK48KBCEL&field1=0

  String str="GET https://api.thingspeak.com/update?api_key=KN4WH0QQK48KBCEL&field1="+ us1+"&field2=" + us2 + "&field3=" + ir1+"&field4=" + ir2 + "&field5=" + temp ;  
  
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waiting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}

void ShowSerialData() //Show serial data
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
    Serial.println();
}
