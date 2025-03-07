#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define bUP 25
#define bOK 26
#define bDN 27
#define PIN_RELAY 23
#define BOUNCE 250

int selectedDigit = 0;
bool isHandleBacasdgnExecuted = false;
bool isHandleBacaKHExecuted = false;
bool isHandleWritesdgnExecuted = false;
bool isHandleWritekhExecuted = false;
bool shindengen = false;
bool keihin = false;
/////////////////////   KLINE   //////////////////////////////
#define PACKET_BUFFER_SIZE (256)
#define TX_PIN 17
#define RX_PIN 16
#define debug Serial
#define bike Serial2
uint8_t eepromHONDA[1024];
char number[10] = "";
int eepromIndex = 0;
byte ECU_WAKEUP_MESSAGE[] = { 254, 4, 114, 140 };   //  FE,04,72,8C
byte ECU_INIT_MESSAGE[] = { 114, 5, 0, 240, 153 };  //72,5,0,F0,99
int ECU_SUCCESS_CHECKSUM = 0x6FB;
int ECU_SUCCESS;
byte INIT1EPROM[] = { 0x91, 0x91, 0x0D, 0xDF, 0x9E, 0x8D, 0x9A, 0x86, 0x90, 0x8A, 0x8C, 0x9B, 0x88 };
byte INIT2EPROM[] = { 0x91, 0x91, 0x0D, 0xDF, 0x92, 0x9E, 0x86, 0x96, 0x8B, 0x8D, 0x86, 0xC0, 0x6A };
byte READ[] = { 0x91, 0x91, 0x07, 0x40 };
byte array1[] = { 0x27, 0x0B, 0xE0, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x48, 0x6F, 0x43 };
byte array2[] = { 0x27, 0x0B, 0xE0, 0x77, 0x41, 0x72, 0x65, 0x59, 0x6F, 0x75, 0x22 };
byte array7[] = { 130, 130, 16, 6, 0, 230 };
byte array8[] = { 130, 130, 16, 6, 1, 229 };
byte read1KH[] = { 0x82, 0x82, 0x10, 0x06 };

byte ECM_ID[] = { 0x72, 0x05, 0x71, 0x00, 0x18 };


///////////////////////  alamat   //////////////
uint8_t ADDRESS_11;
uint8_t ADDRESS_22;
uint8_t ADDRESS_33;
uint8_t ADDRESS_44;

uint8_t ALAMAT1;
uint8_t ALAMAT2;
uint8_t ALAMAT3;
uint8_t ALAMAT4;
uint8_t ALAMAT5;
uint8_t ALAMAT6;
uint8_t ALAMAT7;
uint8_t ALAMAT8;
uint8_t ALAMAT9;
uint8_t ALAMAT10;
uint8_t ALAMAT11;
uint8_t ALAMAT12;
uint8_t ALAMAT13;
uint8_t ALAMAT14;
uint8_t ALAMAT15;
uint8_t ALAMAT16;
uint8_t ALAMAT17;
uint8_t ALAMAT18;
uint8_t ALAMAT81;
uint8_t ALAMAT82;
uint8_t ALAMAT83;
uint8_t ALAMAT84;
uint8_t ALAMAT19;
uint8_t ALAMAT20;

char hexString2[11];
byte buff[14];
int buffCount = 0;
int hexIndex = 0;
void BACA_ID() {
  bike.write(ECM_ID, sizeof(ECM_ID));
  delay(50);
  buffCount = 0;
  while ((bike.available() > 0) && (buffCount < 21)) {
    buff[buffCount++] = bike.read();
  }
  buffCount = 0;
  memset(hexString2, 0, sizeof(hexString2));
  int buffStart = 9;
  int buffEnd = 13;
  int hexIndex = 0;
  for (int i = buffStart; i <= buffEnd; i++) {
    sprintf(&hexString2[hexIndex], "%02X", buff[i]);
    hexIndex += 2;
  }
  if (strcmp(hexString2, "0103060F01") == 0) {  ////////////////   ALAMAT K59
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = VARIO 150 30400-K59J-A71");
    ADDRESS_11 = 0x90;
    ADDRESS_22 = 0x91;
    ADDRESS_33 = 0x8E;
    ADDRESS_44 = 0x8F;

    ALAMAT1 = 0x90;
    ALAMAT2 = 0x91;
    ALAMAT3 = 0x94;
    ALAMAT4 = 0x95;
    ALAMAT5 = 0x98;
    ALAMAT6 = 0x99;
    ALAMAT7 = 0x9C;
    ALAMAT8 = 0x9D;
    ALAMAT9 = 0x8E;
    ALAMAT10 = 0x8F;
    ALAMAT11 = 0x92;
    ALAMAT12 = 0x93;
    ALAMAT13 = 0x96;
    ALAMAT14 = 0x97;
    ALAMAT15 = 0x9A;
    ALAMAT16 = 0x9B;
    ALAMAT17 = 0x9E;
    ALAMAT18 = 0x9F;
    ALAMAT81 = 0x00;
    ALAMAT82 = 0x00;
    ALAMAT83 = 0x00;
    ALAMAT84 = 0x00;
    ALAMAT19 = 0x00;
    ALAMAT20 = 0x00;
  } else if (strcmp(hexString2, "0104130F01") == 0) {  ////////////////   ALAMAT K2F 11
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = SCOOPY 110 30400-K2F-N11");
    ADDRESS_11 = 0x22;
    ADDRESS_22 = 0x23;
    ADDRESS_33 = 0x20;
    ADDRESS_44 = 0x21;

    ALAMAT1 = 0x22;
    ALAMAT2 = 0x23;
    ALAMAT9 = 0x20;
    ALAMAT10 = 0x21;
  } else if (strcmp(hexString2, "0104D80F01") == 0) {  ////////////////   VARIO K2VG
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = VARIO 125 30400-K2VG-N42");
    ADDRESS_11 = 0x90;
    ADDRESS_22 = 0x91;
    ADDRESS_33 = 0x8E;
    ADDRESS_44 = 0x8F;

    ALAMAT1 = 0x90;
    ALAMAT2 = 0x91;
    ALAMAT3 = 0x94;
    ALAMAT4 = 0x95;
    ALAMAT5 = 0x98;
    ALAMAT6 = 0x99;
    ALAMAT7 = 0x9C;
    ALAMAT8 = 0x9D;
    ALAMAT9 = 0x8E;
    ALAMAT10 = 0x8F;
    ALAMAT11 = 0x92;
    ALAMAT12 = 0x93;
    ALAMAT13 = 0x96;
    ALAMAT14 = 0x97;
    ALAMAT15 = 0x9A;
    ALAMAT16 = 0x9B;
    ALAMAT17 = 0x9E;
    ALAMAT18 = 0x9F;
    ALAMAT81 = 0x00;
    ALAMAT82 = 0x00;
    ALAMAT83 = 0x00;
    ALAMAT84 = 0x00;
    ALAMAT19 = 0x00;
    ALAMAT20 = 0x00;
  } else if (strcmp(hexString2, "01046B0F01") == 0) {  ////////////////   VARIO K2SA
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = VARIO 160 30400-K2SA-N02");
    ADDRESS_11 = 0x90;
    ADDRESS_22 = 0x91;
    ADDRESS_33 = 0x8E;
    ADDRESS_44 = 0x8F;

    ALAMAT1 = 0x90;
    ALAMAT2 = 0x91;
    ALAMAT3 = 0x94;
    ALAMAT4 = 0x95;
    ALAMAT5 = 0x98;
    ALAMAT6 = 0x99;
    ALAMAT7 = 0x9C;
    ALAMAT8 = 0x9D;
    ALAMAT9 = 0x8E;
    ALAMAT10 = 0x8F;
    ALAMAT11 = 0x92;
    ALAMAT12 = 0x93;
    ALAMAT13 = 0x96;
    ALAMAT14 = 0x97;
    ALAMAT15 = 0x9A;
    ALAMAT16 = 0x9B;
    ALAMAT17 = 0x9E;
    ALAMAT18 = 0x9F;
    ALAMAT81 = 0x00;
    ALAMAT82 = 0x00;
    ALAMAT83 = 0x00;
    ALAMAT84 = 0x00;
    ALAMAT19 = 0x00;
    ALAMAT20 = 0x00;
  } else if (strcmp(hexString2, "0104040F01") == 0) {  ////////////////   PCX K1ZG
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = PCX 160 30400-K1ZG-N21");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "0104030F01") == 0) {  ////////////////   PCX K1ZG
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = PCX 160 30400-K1ZG-N31");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "0105030F01") == 0) {  ////////////////   PCX K1ZN
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = PCX 160 30400-K1ZN-N41");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "0105020F01") == 0) {  ////////////////   PCX K1ZN
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = PCX 160 30400-K1ZN-N51");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "01037B0F01") == 0) {  ////////////////   ADV
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = ADV 150 30400-K0WA-N01");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x34;
    ADDRESS_44 = 0x35;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x34;  ///////////
    ALAMAT10 = 0x35;
    ALAMAT11 = 0x36;
    ALAMAT12 = 0x37;
    ALAMAT13 = 0x38;
    ALAMAT14 = 0x39;
    ALAMAT15 = 0x3A;
    ALAMAT16 = 0x3B;
    ALAMAT17 = 0x3C;
    ALAMAT18 = 0x3D;
    ALAMAT19 = 0x3E;
    ALAMAT20 = 0x3F;
  } else if (strcmp(hexString2, "01037B0F11") == 0) {  ////////////////   ADV
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = ADV 150 30400-K0WA-N11");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x34;
    ADDRESS_44 = 0x35;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x34;  ///////////
    ALAMAT10 = 0x35;
    ALAMAT11 = 0x36;
    ALAMAT12 = 0x37;
    ALAMAT13 = 0x38;
    ALAMAT14 = 0x39;
    ALAMAT15 = 0x3A;
    ALAMAT16 = 0x3B;
    ALAMAT17 = 0x3C;
    ALAMAT18 = 0x3D;
    ALAMAT19 = 0x3E;
    ALAMAT20 = 0x3F;
  } else if (strcmp(hexString2, "01048C0F01") == 0) {  ////////////////   ADV
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = ADV 160 30400-K0WL-NA1");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "01048D0F01") == 0) {  ////////////////   ADV
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = ADV 160 30400-K0WL-NB1-IN01");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "01048D0F11") == 0) {  ////////////////   ADV
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = ADV 160 30400-K0WL-NB1-IN11");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "0102C70F01") == 0) {  ////////////////   PCX
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = PCX-150 30400-K97G-N01");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "0103470F01") == 0) {  ////////////////   PCX
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = PCX-150 30400-K97G-N31");
    ADDRESS_11 = 0x40;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x41;
    ADDRESS_33 = 0x4C;
    ADDRESS_44 = 0x4D;



    ALAMAT1 = 0x40;
    ALAMAT2 = 0x41;
    ALAMAT3 = 0x42;
    ALAMAT4 = 0x43;
    ALAMAT5 = 0x44;
    ALAMAT6 = 0x45;
    ALAMAT7 = 0x46;
    ALAMAT8 = 0x47;
    ALAMAT81 = 0x48;
    ALAMAT82 = 0x49;
    ALAMAT83 = 0x4A;
    ALAMAT84 = 0x4B;

    ALAMAT9 = 0x4C;  ///////////
    ALAMAT10 = 0x4D;
    ALAMAT11 = 0x4E;
    ALAMAT12 = 0x4F;
    ALAMAT13 = 0x50;
    ALAMAT14 = 0x51;
    ALAMAT15 = 0x52;
    ALAMAT16 = 0x53;
    ALAMAT17 = 0x54;
    ALAMAT18 = 0x55;
    ALAMAT19 = 0x56;
    ALAMAT20 = 0x57;
  } else if (strcmp(hexString2, "0105770F01") == 0) {  ////////////////   STYLO
    Serial.println();
    Serial.println();
    Serial.print("ECM CODE = ");
    Serial.println(hexString2);
    Serial.println("ECM PART = K3VA");
    ADDRESS_11 = 0x3C;  // Ubah sesuai dengan nilai yang diinginkan
    ADDRESS_22 = 0x3D;
    ADDRESS_33 = 0x3E;
    ADDRESS_44 = 0x3F;

    ALAMAT1 = 0x3C;
    ALAMAT2 = 0x3D;
    ALAMAT9 = 0x3E;
    ALAMAT10 = 0x3F;
  }
  int strLength = strlen(hexString2);
  int padding = (16 - strLength) / 2;
  if (strLength > 16) {
    hexString2[16] = '\0';
    padding = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" ==>ECM CODE<== ");
  lcd.setCursor(padding, 1);
  lcd.print(hexString2);
}

byte initHonda() {
  int initSuccess = 0;
  debug.println("Starting up...");
  debug.println("Setting line low 70ms, high 120ms");
  initComms();
  bike.begin(10400, SERIAL_8N1, RX_PIN, TX_PIN);
  debug.println("Sending ECU Wakeup");
  bike.write(ECU_WAKEUP_MESSAGE, sizeof(ECU_WAKEUP_MESSAGE));
  delay(70);
  debug.println("Sending ECU Init String");
  bike.write(ECU_INIT_MESSAGE, sizeof(ECU_INIT_MESSAGE));
  bike.flush();
  delay(130);

  int initBuffCount = 0;
  byte initBuff[32];
  while (bike.available() > 0 && initBuffCount < 32) {
    initBuff[initBuffCount++] = bike.read();
  }

  int initSum = 0;
  debug.print("initSum: ");
  for (int i = 0; i < initBuffCount; i++) {
    initSum += initBuff[i];
    debug.print(initBuff[i], HEX);
    if (i != initBuffCount - 1) {
      debug.print(";");
    }
  }
  debug.println("14: ");
  if (initBuffCount > 14) {
    debug.println(initBuff[14], HEX);
    ECU_SUCCESS = initBuff[14];
  }
  debug.println();
  if (ECU_SUCCESS != 0) {
    debug.println("Successfully opened connection to ECU");
    initSuccess = 1;
    return 1;
  } else {
    debug.println("Failed to open connection to ECU, trying again in 2s");
  }
}

int initComms() {

  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, LOW);  //TX Low for 70ms
  delay(70);
  digitalWrite(TX_PIN, HIGH);  //TX High for 120ms
  delay(130);
  return 1;
}

void Read() {
  int buffCount = 0;
  int byteCounter = 0;
  uint8_t buff[20];   // Buffer untuk menampung data masuk
  char hexString[3];  // Buffer untuk menyimpan byte dalam format hex
  for (int i = 0; i <= 255; i++) {
    // Kirim perintah membaca data
    bike.write(READ, sizeof(READ));
    bike.write(i);                                   // Kirim byte alamat
    bike.write((byte)0x0);                           // Data tambahan (0x00)
    bike.write((0x100 - (0x07 + 0x40 + i)) & 0xFF);  // Checksum
    delay(50);
    // Baca data dari perangkat
    buffCount = 0;
    while ((bike.available() > 0) && (buffCount < 20)) {
      buff[buffCount++] = bike.read();
    }
    // Pastikan buffer memiliki setidaknya 12 byte
    if (buffCount >= 12) {
      // Simpan byte ke EEPROM
      if (eepromIndex + 1 < sizeof(eepromHONDA)) {
        eepromHONDA[eepromIndex++] = buff[11];  // Byte ke-12 (indeks 11 dalam array)
        eepromHONDA[eepromIndex++] = buff[12];  // Byte ke-13 (indeks 12 dalam array)
      } else {
        Serial.println("EEPROM buffer penuh!");
        break;
      }
      // Debugging: Tampilkan hanya byte ke-12 dan ke-13 dalam format per 16 byte per baris
      sprintf(hexString, "%02X", buff[11]);  // Byte ke-12
      Serial.print(hexString);
      Serial.print(" ");
      byteCounter++;
      sprintf(hexString, "%02X", buff[12]);  // Byte ke-13
      Serial.print(hexString);
      Serial.print(" ");
      byteCounter++;
      // Baris baru setiap 16 byte
      if (byteCounter >= 16) {
        Serial.println();
        byteCounter = 0;
      }
    }
    // Kirim nilai progres melalui Serial Bluetooth
    int progress = (i * 100) / (256 - 1);  // Hitung progres dalam persen
    String progressMessage = "PROCECS: " + String(progress) + "%";
    //  // Kirim nilai progres dengan teks
    delay(10);
  }
  // Baris baru jika data terakhir tidak genap 16 byte
  if (byteCounter > 0) {
    Serial.println();
  }
  eepromIndex = 0;
  Serial.println("Selesai membaca data.");
}


void initsh1() {
  bike.write(INIT1EPROM, sizeof(INIT1EPROM));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("initsh1: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void ini1() {
  bike.write(ECU_WAKEUP_MESSAGE, sizeof(ECU_WAKEUP_MESSAGE));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("ini1: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void ini2() {
  bike.write(ECU_INIT_MESSAGE, sizeof(ECU_INIT_MESSAGE));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("ini2: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void initKh1() {
  bike.write(array1, sizeof(array1));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("initKh1: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void initsh2() {
  bike.write(INIT2EPROM, sizeof(INIT2EPROM));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("initsh2: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void initKh2() {
  bike.write(array2, sizeof(array2));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("initKh2: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void initKh7() {
  bike.write(array7, sizeof(array7));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("initKh7: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void initKh8() {
  bike.write(array8, sizeof(array8));
  delay(70);
  int buffCount = 0;
  byte buff[PACKET_BUFFER_SIZE];
  while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
    buff[buffCount++] = bike.read();
  }
  debug.print("initKh8: ");
  for (int i = 0; i < buffCount; i++) {
    debug.print(buff[i], HEX);
    if (i != buffCount - 1) {
      debug.print(";");
    }
  }
  debug.println();
}
void ReadKH() {
  int buffCount = 0;
  int byteCounter = 0;
  uint8_t buff[20];   // Buffer untuk menampung data masuk
  char hexString[3];  // Buffer untuk menyimpan byte dalam format hex
  for (int i = 0; i <= 255; i++) {
    byte command[] = { 0x82, 0x82, 0x10, 0x06, i, ((0x100 - ((0x82 + 0x82 + 0x10 + 0x06 + i) % 0x100)) & 0xFF) };
    bike.write(command, sizeof(command));

    delay(50);
    // Baca data dari perangkat
    buffCount = 0;
    while ((bike.available() > 0) && (buffCount < 20)) {
      buff[buffCount++] = bike.read();
    }
    // Pastikan buffer memiliki setidaknya 12 byte
    if (buffCount >= 10) {
      // Simpan byte ke EEPROM
      if (eepromIndex + 1 < sizeof(eepromHONDA)) {
        eepromHONDA[eepromIndex++] = buff[10];
        eepromHONDA[eepromIndex++] = buff[11];
      } else {
        Serial.println("EEPROM buffer penuh!");
        break;
      }
      // Debugging: Tampilkan hanya byte ke-12 dan ke-13 dalam format per 16 byte per baris
      sprintf(hexString, "%02X", buff[10]);  // Byte ke-12
      Serial.print(hexString);
      Serial.print(" ");
      byteCounter++;
      sprintf(hexString, "%02X", buff[11]);  // Byte ke-13
      Serial.print(hexString);
      Serial.print(" ");
      byteCounter++;
      // Baris baru setiap 16 byte
      if (byteCounter >= 16) {
        Serial.println();
        byteCounter = 0;
      }
    }
    int progress = (i * 100) / (256 - 1);  // Hitung progres dalam persen
    String progressMessage = "PROCECS: " + String(progress) + "%";
    //  // Kirim nilai progres dengan teks
  }
  // Baris baru jika data terakhir tidak genap 16 byte
  if (byteCounter > 0) {
    Serial.println();
  }
  eepromIndex = 0;
  Serial.println("Selesai membaca data.");
}

void WRITEReadKH() {
  uint8_t i, l;                      // Variabel untuk menyimpan pasangan byte
  uint8_t buff[PACKET_BUFFER_SIZE];  // Buffer untuk komunikasi dengan perangkat
  int buffCount = 0;
  int addr = 0;
  // Buat perintah dengan data i dan l
  for (int a = 0; a <= 255; a++) {
    // Ambil dua byte dari eepromHONDA berdasarkan alamat addr
    i = eepromHONDA[addr];
    l = eepromHONDA[addr + 1];

    uint8_t command[] = {
      0x82, 0x82, 0x14, 0x08, a, i, l,
      ((0x100 - ((0x82 + 0x82 + 0x14 + 0x08 + a + i + l) % 0x100)) & 0xFF)
    };

    // Kirim perintah ke perangkat
    bike.write(command, sizeof(command));
    delay(50);  // Beri waktu untuk perangkat memproses perintah

    // Baca respons perangkat
    buffCount = 0;
    while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
      buff[buffCount++] = bike.read();
    }

    // Debugging: Tampilkan respons yang diterima
    debug.print("Command: ");
    for (int c = 0; c < sizeof(command); c++) {
      debug.print(command[c], HEX);
      debug.print(" ");
    }
    debug.println();

    debug.print("Response: ");
    for (int j = 0; j < buffCount; j++) {
      debug.print(buff[j], HEX);
      if (j != buffCount - 1) {
        debug.print(";");
      }
    }
    debug.println();
    int progress = (a * 100) / (256 - 1);  // Hitung progres dalam persen
    String progressMessage = "PROCECS: " + String(progress) + "%";
    //  // Kirim nilai progres dengan teks
    // Update addr untuk mengakses alamat berikutnya di eepromHONDA
    addr += 2;  // Berpindah dua posisi dalam array untuk mengambil pasangan byte berikutnya
  }

  debug.println("Write Complete!");
}
void WRITESH() {
  uint8_t i, l;                      // Variabel untuk menyimpan pasangan byte
  uint8_t buff[PACKET_BUFFER_SIZE];  // Buffer untuk komunikasi dengan perangkat
  int buffCount = 0;
  int addr = 0;
  const int totalIterations = 256;
  // Buat perintah dengan data i dan l
  for (int a = 0; a <= 255; a++) {
    // Ambil dua byte dari eepromHONDA berdasarkan alamat addr
    i = eepromHONDA[addr];
    l = eepromHONDA[addr + 1];

    uint8_t command[] = { 0x91, 0x91, 0x09, 0x41, a, 0x00, i, l, (0x100 - (0x09 + 0x41 + a + 0x00 + i + l)) };

    // Kirim perintah ke perangkat
    bike.write(command, sizeof(command));
    delay(50);  // Beri waktu untuk perangkat memproses perintah

    // Baca respons perangkat
    buffCount = 0;
    while ((bike.available() > 0) && (buffCount < PACKET_BUFFER_SIZE)) {
      buff[buffCount++] = bike.read();
    }

    // Debugging: Tampilkan respons yang diterima
    debug.print("Command: ");
    for (int c = 0; c < sizeof(command); c++) {
      debug.print(command[c], HEX);
      debug.print(" ");
    }
    debug.println();

    debug.print("Response: ");
    for (int j = 0; j < buffCount; j++) {
      debug.print(buff[j], HEX);
      if (j != buffCount - 1) {
        debug.print(";");
      }
    }
    debug.println();

    // Kirim nilai progres melalui Serial Bluetooth
    int progress = (a * 100) / (256 - 1);  // Hitung progres dalam persen
    String progressMessage = "PROCECS: " + String(progress) + "%";
    // Update addr untuk mengakses alamat berikutnya di eepromHONDA
    addr += 2;  // Berpindah dua posisi dalam array untuk mengambil pasangan byte berikutnya
                // delay(10);
  }

  debug.println("Write Complete!");
}
void eeprom_show_data(uint8_t *data, uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    if (i % 16 == 0) {
      Serial.println();
    }
    if (data[i] < 16) {
      Serial.print("0");
    }
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
void Screenmenu() {
  lcd.setCursor(0, 0);
  lcd.print("SMART KEY HONDA");

  for (int i = 0; i < 9; i++) {
    lcd.setCursor(0, 1);
    lcd.print("Loading");
    for (int j = 0; j <= i; j++) {
      lcd.print(".");
    }
    delay(500);  // Kurangi delay agar lebih responsif
  }
}
void handlebacasdgn() {
  delay(100);  // Deboue
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Process......");
  Serial.println("ON OFF ECM");
  digitalWrite(PIN_RELAY, HIGH);
  delay(1000);
  digitalWrite(PIN_RELAY, LOW);
  delay(1000);
  digitalWrite(PIN_RELAY, HIGH);
  delay(1000);
  digitalWrite(PIN_RELAY, LOW);
  delay(1000);
  digitalWrite(PIN_RELAY, HIGH);
  delay(1000);
  initHonda();
  delay(50);
  BACA_ID();
  delay(50);
  initsh1();
  delay(100);
  initsh2();
  delay(100);
  Read();
  delay(50);
  eeprom_show_data(eepromHONDA, 1024);
  delay(50);
  BACAKEYHONDA();
}
void handlebacaKH() {
  delay(100);  // Deboue
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Process......");
  Serial.println("ON OFF ECM");
  digitalWrite(PIN_RELAY, HIGH);
  delay(1000);
  digitalWrite(PIN_RELAY, LOW);
  delay(1000);
  digitalWrite(PIN_RELAY, HIGH);
  delay(1000);
  initHonda();
  delay(50);
  BACA_ID();
  delay(50);
  ini1();
  delay(50);
  ini2();
  delay(50);
  initKh1();
  delay(50);
  initKh2();
  delay(50);
  initKh7();
  delay(50);
  initKh8();
  delay(50);
  ReadKH();
  delay(50);
  eeprom_show_data(eepromHONDA, 1024);
  delay(50);
  BACAKEYHONDA();
}


// Fungsi untuk menulis ke alamat dengan validasi
void writeToAddress(uint16_t address, uint8_t value) {
  if (address == 0x00 || address == 0) {  // Periksa jika alamat bernilai 0x00
    Serial.printf("Skipped writing to address 0x%02X\n", address);
    return;
  }
  if (address < sizeof(eepromHONDA)) {  // Validasi alamat
    eepromHONDA[address] = value;       // Tulis nilai ke alamat
    Serial.printf("Written 0x%02X to address 0x%02X\n", value, address);
  } else {
    Serial.printf("Invalid address: 0x%02X\n", address);
  }
}

void TULISKEYHONDA() {
  String inputKey = String(number);

  // Validasi input agar hanya terdiri dari 9 digit angka
  if (inputKey.length() != 9 || !inputKey.toInt()) {
    Serial.println("Input harus berupa 9 digit angka.");
    return;
  }

  // Konversi input menjadi long
  long ecmId = inputKey.toInt();

  // Pisahkan angka menjadi empat byte
  uint8_t value1 = (ecmId >> 16) & 0xFF;
  uint8_t value2 = (ecmId >> 24) & 0xFF;
  uint8_t value3 = ecmId & 0xFF;
  uint8_t value4 = (ecmId >> 8) & 0xFF;

  // Tulis ke alamat yang didefinisikan
  writeToAddress(ALAMAT1, value3);
  writeToAddress(ALAMAT2, value4);
  writeToAddress(ALAMAT3, value3);
  writeToAddress(ALAMAT4, value4);
  writeToAddress(ALAMAT5, value3);
  writeToAddress(ALAMAT6, value4);
  writeToAddress(ALAMAT7, value3);
  writeToAddress(ALAMAT8, value4);
  writeToAddress(ALAMAT81, value3);  // Akan dilewati jika alamat 0x00
  writeToAddress(ALAMAT82, value4);  // Akan dilewati jika alamat 0x00
  writeToAddress(ALAMAT83, value3);  // Akan dilewati jika alamat 0x00
  writeToAddress(ALAMAT84, value4);  // Akan dilewati jika alamat 0x00

  writeToAddress(ALAMAT9, value1);
  writeToAddress(ALAMAT10, value2);
  writeToAddress(ALAMAT11, value1);
  writeToAddress(ALAMAT12, value2);
  writeToAddress(ALAMAT13, value1);
  writeToAddress(ALAMAT14, value2);
  writeToAddress(ALAMAT15, value1);
  writeToAddress(ALAMAT16, value2);
  writeToAddress(ALAMAT17, value1);
  writeToAddress(ALAMAT18, value2);
  writeToAddress(ALAMAT19, value1);
  writeToAddress(ALAMAT20, value2);
}


void BACAKEYHONDA() {
  if (sizeof(eepromHONDA) >= 0x58) {  // Pastikan data EEPROM cukup
    // Baca dua byte dari alamat yang ditentukan
    uint8_t firstValue[2] = {
      eepromHONDA[ADDRESS_11],
      eepromHONDA[ADDRESS_22]
    };
    uint8_t secondValue[2] = {
      eepromHONDA[ADDRESS_33],
      eepromHONDA[ADDRESS_44]
    };
    // Proses nilai yang diambil
    process(firstValue, secondValue);
  } else {
    Serial.println("Insufficient data in EEPROM.");
  }
}

void process(uint8_t *firstValue, uint8_t *secondValue) {
  // Konversi byte ke string hexadecimal
  String firstHex = bytesToHex(firstValue, 2);
  String secondHex = bytesToHex(secondValue, 2);
  // Gabungkan data untuk diproses
  String inputData = secondHex + " " + firstHex;
  Serial.println("Input Data: " + inputData);
  // Pisahkan input menjadi byte
  char inputBuffer[20];
  inputData.toCharArray(inputBuffer, 20);
  char *token = strtok(inputBuffer, " ");
  uint8_t byteArray[4];
  int byteIndex = 0;
  while (token != NULL) {
    Serial.println("Token: " + String(token));
    if (strlen(token) == 4) {
      // Pecah token menjadi dua byte
      char subToken1[3] = { token[0], token[1], '\0' };
      char subToken2[3] = { token[2], token[3], '\0' };
      if (byteIndex < 4) {
        byteArray[byteIndex++] = convertInputToByte(subToken1);
      }
      if (byteIndex < 4) {
        byteArray[byteIndex++] = convertInputToByte(subToken2);
      }
    } else if (strlen(token) == 2) {
      if (byteIndex < 4) {
        byteArray[byteIndex++] = convertInputToByte(token);
      }
    }
    // Ambil token berikutnya
    token = strtok(NULL, " ");
  }

  // Jika array byte lengkap (4 byte)
  if (byteIndex == 4) {
    // Hitung ECM-ID
    int num2 = ((byteArray[3] & 0xFF) << 8) | (byteArray[2] & 0xFF);
    long ecmId = ((long)(byteArray[1] & 0xFF) << 24) | ((long)(byteArray[0] & 0xFF) << 16) | num2;


    snprintf(number, sizeof(number), "%09ld", ecmId);
    Serial.println("==> " + String(number) + " <==");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("==>Smart Key<==");
    lcd.setCursor(3, 1);
    lcd.print(number);
  }
}

String bytesToHex(uint8_t *bytes, size_t length) {
  String hexString = "";
  for (size_t i = 0; i < length; i++) {
    if (bytes[i] < 0x10) {
      hexString += "0";  // Tambahkan nol di depan jika kurang dari 0x10
    }
    hexString += String(bytes[i], HEX);
  }
  return hexString;
}

uint8_t convertInputToByte(const char *input) {
  return strtoul(input, NULL, 16);  // Konversi string hexadecimal menjadi byte
}







void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
  pinMode(bUP, INPUT_PULLUP);
  pinMode(bOK, INPUT_PULLUP);
  pinMode(bDN, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  Screenmenu();
  lcd.clear();
  // menuSeting();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    menuSeting();
  }
  lcd.setCursor(0, 0);
  lcd.print("SMART KEY HONDA");
}

void handleNumberEdit() {
  updateLCD();
  if (digitalRead(bUP) == LOW) {
    delay(100);  // Deboue
    number[selectedDigit]++;
    if (number[selectedDigit] > '9') {
      number[selectedDigit] = '0';  // Jika lebih dari 9, kembali ke 0
    }
    // updateLCD();
  }

  // Tombol SELECT: Pindah ke digit berikutnya
  if (digitalRead(bDN) == LOW) {
    delay(100);  // Deboue

    selectedDigit++;
    if (selectedDigit > 8) {
      selectedDigit = 0;  // Kembali ke digit pertama jika sudah di digit terakhir
    }
    //updateLCD();
  }
  delay(200);
}
void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("==> EDIT KEY <==");
  // Baris kedua: Tampilkan angka dan digit aktif
  lcd.setCursor(0, 1);
  lcd.print(number);

  // Tampilkan posisi digit yang dipilih
  lcd.setCursor(selectedDigit, 1);
  lcd.blink();  // Blink pada digit yang dipilih
}

void menuSeting() {
setMENU1:
  {
    if (digitalRead(bOK) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bOK) == LOW) {}
      lcd.clear();
      goto setSUBMENU1;
      //-------------------------
    } else if (digitalRead(bUP) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bUP) == LOW) {}
      lcd.clear();
      goto setMENUEXIT;
    } else if (digitalRead(bDN) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bDN) == LOW) {}
      lcd.clear();
      goto setMENU2;
    }

    lcd.setCursor(00, 00);
    lcd.print(">> Read Key SDG");
    lcd.setCursor(00, 01);
    lcd.print("   Read Key KH");
    goto setMENU1;

setMENU2:
    if (digitalRead(bOK) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bOK) == LOW) {}
      lcd.clear();
      goto setSUBMENU2;
      //-------------------------
    } else if (digitalRead(bUP) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bUP) == LOW) {}
      lcd.clear();
      goto setMENU1;
    } else if (digitalRead(bDN) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bDN) == LOW) {}
      lcd.clear();
      goto setMENU3;
    }
    lcd.setCursor(00, 00);
    lcd.print("   Read Key SDG");
    lcd.setCursor(00, 01);
    lcd.print(">> Read Key KH");
    goto setMENU2;
setMENU3:
    if (digitalRead(bOK) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bOK) == LOW) {}
      lcd.clear();
      goto setSUBMENU3;
      //-------------------------
    } else if (digitalRead(bUP) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bUP) == LOW) {}
      lcd.clear();
      goto setMENU2;
    } else if (digitalRead(bDN) == LOW) {
      delay(BOUNCE);
      while (digitalRead(bDN) == LOW) {}
      lcd.clear();
      goto setMENU4;
    }
    lcd.setCursor(00, 00);
    lcd.print(">> EDIT KEY");
    lcd.setCursor(00, 01);
    lcd.print("   WRITE KEY");
    goto setMENU3;
  }
setMENU4:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    goto setSUBMENU4;
    //-------------------------
  } else if (digitalRead(bUP) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bUP) == LOW) {}
    lcd.clear();
    goto setMENU3;
  } else if (digitalRead(bDN) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bDN) == LOW) {}
    lcd.clear();
    goto setMENUEXIT;
  }
  lcd.setCursor(00, 00);
  lcd.print("   EDIT KEY");
  lcd.setCursor(00, 01);
  lcd.print(">> WRITE KEY");
  goto setMENU4;



setMENUEXIT:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    goto endSET;
    //-------------------------
  } else if (digitalRead(bUP) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bUP) == LOW) {}
    lcd.clear();
    goto setMENU4;
  } else if (digitalRead(bDN) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bDN) == LOW) {}
    lcd.clear();
    goto setMENU1;
  }
  lcd.setCursor(00, 00);
  lcd.print(">> EXIT");
  goto setMENUEXIT;

//-----------------
setSUBMENU1:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    goto setMENU1;
  }
  if (!isHandleBacasdgnExecuted) {
    handlebacasdgn();
    isHandleBacasdgnExecuted = true;
    shindengen = true;
  }
  goto setSUBMENU1;

setSUBMENU2:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    goto setMENU2;
  }
  //ISI.......
  if (!isHandleBacaKHExecuted) {
    handlebacaKH();
    isHandleBacaKHExecuted = true;
    keihin = true;
  }

  goto setSUBMENU2;

setSUBMENU3:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    goto setMENU3;
  }
  //ISI........
  handleNumberEdit();
  goto setSUBMENU3;

setSUBMENU4:
  if (digitalRead(bOK) == LOW) {
    delay(BOUNCE);
    while (digitalRead(bOK) == LOW) {}
    lcd.clear();
    goto setMENU4;
  }
  //ISIII
  if (!isHandleWritesdgnExecuted && shindengen) {
    lcd.setCursor(0, 0);
    lcd.print("Write Process...");
    TULISKEYHONDA();
    delay(10);
    WRITESH();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Write Process ok");
    lcd.setCursor(0, 1);
    lcd.print("Restar Modul");
    isHandleWritesdgnExecuted = true;
  } else if (!isHandleWritekhExecuted && keihin) {
    lcd.setCursor(0, 0);
    lcd.print("Write Process...");
    TULISKEYHONDA();
    delay(10);
    WRITEReadKH();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Write Process ok");
    lcd.setCursor(0, 1);
    lcd.print("Restar Modul");
    isHandleWritekhExecuted = true;
  }
  goto setSUBMENU4;



endSET:
  lcd.clear();
  delay(200);
}
