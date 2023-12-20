//Coded by Nimmy K
//Center for Cybersecurity Systems and Networks
//Amrita Vishwa Vidyapeetham, Amritapuri
//Implementation of Lightweight PUF based authentication protocol for IoT using Secret Sharing
#include <MD5.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>
#include <string.h>



char *sgav;
void setup() {
  char msg[420];

  long int noncea;
  char nonce[128];
  const char *aID = "99945"; //ID of device A
  const char *vID= "82567";//ID of Verifier
  const char *bID= "67890";//ID of device B
  const char *Kav= "adfghijklm0095"; //Shared key between devce A and verifier
  char aTID[50], vTID[50], bTID[50];
  const char *hkav;
  unsigned char* hash;
  
  char data[420];
  char hk[180];
  char res[7];
  char check[180];
  int i;
  // Begin the Serial at 9600 Baud
  Serial.begin(115200);
//  mySerial.begin(9600);

  randomSeed(analogRead(0));
  noncea=random(1000,50000);
  ltoa(noncea, nonce, 10);
  //ltoa(noncea,nonce,10);
  //prints time since program started
 
  //compute hkav
  strcpy(hk,Kav);
  strcat(hk,nonce);
  
  hash =MD5::make_hash(hk);
  hkav = MD5::make_digest(hash, 16);//hash in hexa decimal
  //Serial.println(hkav);
  free(hash);
  //Perform XOR operation to compute TD_A
   for(i=0;i<strlen(aID);i++)
   {
    char temp=(aID[i]^hkav[i]);
   res[i]=temp;
   }
   res[i]='\0';
  //test
  //for(i=0;i<strlen(res);i++)
   //{
    //char temp=(res[i]^hkav[i]);
   //check[i]=temp;
   //Serial.print(check[i]);
   //}
 
  Serial.println("Hello");
  strcpy(aTID,res);
  strcpy(data,res);
  
  //Perform XOR operation to compute TD_V
  for(i=0;i<strlen(vID);i++)
   {
    char temp=(vID[i]^hkav[i]);
   res[i]=temp;
   
   }
   res[i]='\0';
   //test
  //for(i=0;i<strlen(res);i++)
   //{
    //char temp=(res[i]^hkav[i]);
   //check[i]=temp;
   //Serial.print(check[i]);
   //}
 
  //Serial.println();
  strcpy(vTID,res);
  strcat(data,res);
 
  strcat(data,hkav);
   
   
  hash =MD5::make_hash(data);
  sgav = MD5::make_digest(hash, 16);//hash for integrity verification
  free(hash);
   
  //Message to be sent to Verifier
  strcpy(msg,aTID);
  strcat(msg,":");
  strcat(msg,vTID);
  strcat(msg,":");
  strcat(msg,nonce);
  strcat(msg,":");
  strcat(msg,sgav);
  Serial.flush();
  delay(1000);
  Serial.println(msg); //<TD_A,TD_V,N_A_1,SG_AV>

  
  delay(1000);
  //Serial.end();
}


void loop() {

 

  
}
