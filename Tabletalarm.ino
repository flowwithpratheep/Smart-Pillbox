#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
// Your blynk Template ID <Name ,Authondication Token
#define BLYNK_TEMPLATE_ID "*******"
#define BLYNK_TEMPLATE_NAME "-------------"
#define BLYNK_AUTH_TOKEN "t--------------"
#include <BlynkSimpleEsp8266.h>
const char *ssid     = "*******";//your ssid
const char *password = "****************";//your password
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 19800, 60000);
int box_1_o,box_1_c,box_2_o,box_2_c,h1o,m1o,h2o,m2o,h1c,m1c,h2c,m2c;
void setup()
{
  Serial.begin(115200);
  pinMode(D5,OUTPUT); 
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  pinMode(D4,OUTPUT);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  digitalWrite(D4,LOW);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password); 
  Blynk.virtualWrite(V5,"BOX 1,2 CLOSE");
}
BLYNK_WRITE(V0)
{
  box_1_o=param.asInt();
  h1o=box_1_o/3600;
  int r1=box_1_o%3600;
  m1o=r1/60;
}
BLYNK_WRITE(V1) 
{
  box_1_c=param.asInt();
  h1c=box_1_c/3600;
  int r2=box_1_c%3600;
  m1c=r2/60;
}
BLYNK_WRITE(V2)
{
  box_2_o=param.asInt();
  h2o=box_2_o/3600;
  int r3=box_2_o%3600;
  m2o=r3/60;
}
BLYNK_WRITE(V3) 
{
  box_2_c=param.asInt();
  h2c=box_2_c/3600;
  int r3=box_2_c%3600;
  m2c=r3/60;
}
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);    
  Blynk.syncVirtual(V1);  
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);  
  Blynk.syncVirtual(V4);  
  Blynk.syncVirtual(V5);  
}
void loop() 
{
  int h,m,s;
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
if(h1o==h && m1o==m)
  {
  digitalWrite(D4,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,LOW);
  delay(30000);
  Blynk.virtualWrite(V5,"BOX 1 OPEN");
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  int i=1;
  while(i)
{ 
  
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
  if(h1c==h && m1c==m)
  {
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,HIGH);
  delay(30000);
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
  Blynk.virtualWrite(V5,"BOX 1,2 CLOSE");
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  i=0;
}
}
}
if(h2o==h && m2o==m)
  {
  digitalWrite(D4,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,LOW);
  delay(30000);
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
  Blynk.virtualWrite(V5,"BOX 2 OPEN");
  Blynk.virtualWrite(V5,"");
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  int i=1;
  while(i)
  {
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
  if(h2c==h && m2c==m)
  {
  digitalWrite(D4,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,HIGH);
  delay(30000);
  timeClient.update();
  h=timeClient.getHours();
  m=timeClient.getMinutes();
  s=timeClient.getSeconds();
  Blynk.virtualWrite(V4,timeClient.getFormattedTime());
  Blynk.virtualWrite(V5,"BOX 1,2 CLOSE");
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  i=0;
}
}
}
delay(1000);
}