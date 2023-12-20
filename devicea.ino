//Coded by Nimmy K
//Amrita Vishwa Vidyapeetham, Amritapuri
#include <MD5.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
long int noncea;
const char *aID = "12345"; //ID of device A
const char *vID= "34567";//ID of Verifier
const char *Kav= "adfghijklm0095"; //Shared key between devce A and verifier

char msg[420];


char *sgav;
void setup() {
  const char *aTID, *vTID, *hkav;
  unsigned char* hash;
  char data[420];
  char hk[180];
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  randomSeed(analogRead(0));
  noncea=random(300);
  //ltoa(noncea,nonce,10);
  //prints time since program started
 
  //compute hkav
  strcpy(hk,Kav);
  strcat(hk,(char)noncea);
  Serial.println(hk);
  hash =MD5::make_hash(hk);
  hkav = MD5::make_digest(hash, 16);//hash in hexa decimal
  //Serial.println(hkav);
  free(hash);
   //compute TID_A and TID_V
   int iID=(int)aID;
   int ihk=(int)hkav;
   aTID=(char)iID^ihk;
   iID=(int)vID;
   ihk=(int)hkav;
   vTID=(char)iID^ihk;
     
  strcpy(data,aTID);
  strcat(data,vTID);
  strcat(data,hkav);
   
   
  hash =MD5::make_hash(data);
  sgav = MD5::make_digest(hash, 16);//hash in hexa decimal
  free(hash);
   
  //Message to be sent to Verifier
  strcpy(msg,aTID);
  //Serial.println("aTID:");
  //Serial.print(aTID);
  strcat(msg,":");
  //Serial.println("vTID:");
  //Serial.print(vTID);
  strcat(msg,vTID);
  strcat(msg,":");
  //Serial.println(vTID);
  strcat(msg,(char)noncea);
  strcat(msg,":");
  //Serial.println(noncea);
  strcat(msg,sgav);
  //strcat(msg,":");
  //Serial.println(sgav);
  //Serial.println(msg);
  //String now = new SimpleDateFormat("HH:mm:ss.SSS -> ").format(new Date());
}


void loop() {

  Serial.flush();
  //  Serial.write(msg); //Write the serial data
  Serial.println(msg);

  delay(1000);
  
  Serial.end();
}
