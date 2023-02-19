#include "pitches.h"
#include "math.h"

#define COL1 7
#define COL2 6
#define COL3 5
#define COL4 4
//#define ROW21 3
//#define ROW22 6
//#define ROW7 7
//#define ROW8 6

#define ROW1 A1
#define ROW2 A2
#define ROW3 A3
#define ROW4 A4

const int row[] = {ROW1, ROW2, ROW3, ROW4};
const int col[] = {COL1,COL2, COL3, COL4};

int A[4][4] = {{1,1,1,1},
		       {1,1,1,1},
		       {1,1,1,1},
		       {1,1,1,1}};


int B[4][4] = {{0,0,0,0},
		       {1,1,1,1},
		       {1,1,1,1},
		       {1,1,1,1}};


int C[4][4] = {{0,0,0,0},
		       {0,0,0,0},
		       {1,1,1,1},
		       {1,1,1,1}};

int D[4][4] = {{0,0,0,0},
		       {0,0,0,0},
		       {0,0,0,0},
		       {1,1,1,1}};

int E[4][4] = {{0,0,0,0},
		       {0,0,0,0},
		       {0,0,0,0},
		       {0,0,0,0}};


int mode;
int mode2ind = 0;
int mode3ind = 0;
int mode4ind = 0;
int mode5ind = 0;
long previoustime = 0;
int ledinterval = 25;
int freeinterval = 100;
int mode2interval = 100;
int mode3interval = 100;
int mode4interval = 175;
long spitch;

const int speakerpin = 13;
const int trigpin = 11;
const int echopin = 10;

const int modepin = A0;



bool distchange = false;
int prevdist = 0;
int loops = 0;

float ping;
int dist;

int speakerpitch(int dist);

int mode2notes[] = {NOTE_CS2,NOTE_GS2, NOTE_CS3, NOTE_E3, NOTE_GS3,
NOTE_CS3, NOTE_E3, NOTE_GS3, NOTE_CS4, NOTE_E3, NOTE_GS3, NOTE_CS4,
NOTE_E4, NOTE_GS4, NOTE_CS4, NOTE_E4, NOTE_GS4, NOTE_CS4, NOTE_E4,
NOTE_GS4, NOTE_CS5, NOTE_E4, NOTE_GS4, NOTE_CS5, NOTE_E5, NOTE_GS4,
NOTE_CS5, NOTE_E5, NOTE_GS5, NOTE_GS5,
NOTE_C2, NOTE_GS2, NOTE_C3, NOTE_DS3, NOTE_GS3, NOTE_C3, NOTE_DS3,
NOTE_GS3, NOTE_C4, NOTE_DS3, NOTE_GS3, NOTE_C4, NOTE_DS4,
NOTE_GS4, NOTE_C4, NOTE_DS4, NOTE_GS4, NOTE_C4, NOTE_DS4, NOTE_GS4,
NOTE_C5, NOTE_DS4, NOTE_GS4, NOTE_C5, NOTE_DS5, NOTE_GS4, NOTE_C5,
NOTE_DS5, NOTE_GS5, NOTE_GS5,
NOTE_B1, NOTE_CS3, NOTE_F3, NOTE_GS3, NOTE_CS4, NOTE_F3, NOTE_GS3, NOTE_CS4,
NOTE_F4, NOTE_GS3, NOTE_CS4, NOTE_F4, NOTE_GS4, NOTE_CS4, NOTE_E4, NOTE_GS4,
NOTE_CS5, NOTE_F4, NOTE_GS4, NOTE_CS5, NOTE_F5, NOTE_GS4, NOTE_CS5, NOTE_F5,
NOTE_GS5, NOTE_CS5, NOTE_F5, NOTE_GS5, NOTE_CS6, NOTE_CS6,
NOTE_A1, NOTE_CS3, NOTE_FS3, NOTE_A3, NOTE_CS4, NOTE_CS4, NOTE_FS4, NOTE_A4,
NOTE_CS5, NOTE_CS5, NOTE_FS5, NOTE_A5, NOTE_CS6, NOTE_CS6,
NOTE_A1, NOTE_CS3, NOTE_E3, NOTE_G3, NOTE_CS4, NOTE_CS4, NOTE_E4, NOTE_G4,
NOTE_CS5, NOTE_CS5, NOTE_E5, NOTE_G5, NOTE_CS6, NOTE_CS6,
NOTE_C6, NOTE_GS4, NOTE_GS5, NOTE_GS4, NOTE_GS5, NOTE_AS4, NOTE_GS5, 
NOTE_C4, NOTE_GS5, NOTE_CS5, NOTE_GS5, NOTE_DS5, NOTE_GS5, NOTE_C4, NOTE_GS5,
NOTE_DS5, NOTE_GS5, NOTE_CS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_E5, NOTE_GS5,
NOTE_DS5, NOTE_GS5, NOTE_CS5, NOTE_GS5, NOTE_C5, NOTE_GS5, NOTE_A4, NOTE_G5,
NOTE_GS4, NOTE_GS5, NOTE_GS4, NOTE_GS5, NOTE_GS4, NOTE_GS5, NOTE_AS4, NOTE_GS5,
NOTE_C5, NOTE_GS5, NOTE_CS5, NOTE_GS5, NOTE_DS5, NOTE_GS5, NOTE_C5, NOTE_GS5,
NOTE_DS5, NOTE_GS5, NOTE_CS5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_E5, NOTE_GS5,
NOTE_DS5, NOTE_GS5, NOTE_CS5, NOTE_GS5, NOTE_C5, NOTE_GS5, NOTE_A4, NOTE_G5,
NOTE_GS4, NOTE_GS5, NOTE_A4, NOTE_G5, NOTE_GS4, NOTE_GS5, NOTE_A4, NOTE_G5,
NOTE_GS4, NOTE_GS5, NOTE_A4, NOTE_G5, NOTE_GS4, NOTE_GS5, NOTE_A4, NOTE_G5,
NOTE_G5, 0, NOTE_GS2
};

int mode2tempo[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,2,2,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,2,2,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,2,2,
                    1,1,1,1,1,1,1,1,1,1,1,1,2,2,
                    1,1,1,1,1,1,1,1,1,1,1,1,2,2,
                    2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    3,1, 12
                    };


int mode3notes[] = {
NOTE_CS4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_GS4, NOTE_FS4, NOTE_CS4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_CS5, NOTE_CS4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_B4, NOTE_FS4, NOTE_CS5, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_FS4, NOTE_FS4,
};

int mode3tempo[] =
{3,3,3,4,3,5,3,3,3,4,2,1,3,3,3,3,3,4,1,1,2,1,1,2,2,2,1,1};


int mode4notes[] = {NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, 
NOTE_B4, NOTE_D5, NOTE_G4, NOTE_A4, NOTE_B4, 0, 
NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_B4, 
NOTE_B4, NOTE_B4, 
NOTE_B4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_D5};

int mode4tempo[] = {2,2,4,
                    2,2,4,
                    2,2,3,1,
                    4,4,
                    2,2,3,1,
                    2,2,2,1,1,
                    2,2,2,2,
                    4,4};


int matdisp = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

for (int i = 4; i <= 7; i++) {

     pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
 	pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);

 pinMode(A2, OUTPUT);
 digitalWrite(A2, LOW);

  	pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);

 pinMode(A4, OUTPUT);
 digitalWrite(A4, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currenttime = millis();
  if (matdisp > 4) matdisp = 0;
  

  if (currenttime - previoustime > ledinterval)
  {
    mode = analogRead(modepin);
    mode = findmode(map(mode, 0, 1023, 1, 100));
    switch(matdisp)
      {
        case 0:
          yaz(A);
          break;
        case 1: 
          yaz(B);
          break;
        case 2:
          yaz(C);
          break;
        case 3:
          yaz(D);
          break;
        case 4:
          yaz(E);
          break;
      }
    if (mode == 1)
    {
      if (currenttime - previoustime > freeinterval)
      {
        previoustime = currenttime;

        
        digitalWrite(trigpin,LOW);
        delayMicroseconds(10);
        digitalWrite(trigpin,HIGH);
        delayMicroseconds(15);
        digitalWrite(trigpin,LOW);
        delayMicroseconds(10);
        ping = pulseIn(echopin, HIGH);
        ping = ping/10000;
        ping = ping/2;
        dist = int(ping *343);

        spitch = speakerpitch(dist);
        tone(speakerpin, spitch, freeinterval);
      }
    }
    else if (mode == 2)
    {
      if (currenttime - previoustime > mode2interval * mode2tempo[mode2ind])
      {
        previoustime = currenttime;
        int mode3ind = 0;
        int mode4ind = 0;
        int mode5ind = 0;

        tone(speakerpin, mode2notes[mode2ind], mode2tempo[mode2ind] * mode2interval);
        mode2ind++;
        if (mode2ind > sizeof(mode2notes)/sizeof(mode2notes[0])-1) 
        {
          mode2ind = 0;
        }
      }
    }

    else if (mode == 3)
    {
      if (currenttime - previoustime > mode3interval * mode3tempo[mode3ind])
      {
        previoustime = currenttime;
        int mode2ind = 0;
        int mode4ind = 0;
        int mode5ind = 0;

        tone(speakerpin, mode3notes[mode3ind], mode3tempo[mode3ind] * mode3interval);
        mode3ind++;
        if (mode3ind > sizeof(mode3notes)/sizeof(mode3notes[0])-1) 
        {
          mode3ind = 0;
        }
      }
    }
    else if (mode == 4)
    {
      if (currenttime - previoustime > mode4interval * mode4tempo[mode4ind])
      {
        previoustime = currenttime;
        int mode2ind = 0;
        int mode3ind = 0;
        int mode5ind = 0;

        tone(speakerpin, mode4notes[mode4ind], mode4tempo[mode4ind] * mode4interval);
        mode4ind++;
        if (mode4ind > sizeof(mode4notes)/sizeof(mode4notes[0])-1) 
        {
          mode4ind = 0;
        }
      }
    }

  }  

  
  
}

int findmode(int x)
{
  if (x < 71)
  {
    return 1;
  }
  else if (x < 78)
  {
    return 2;
  }
  else if (x < 85)
  {
    return 3;
  }
  else if (x < 94)
  {
    return 4;
  }
  else if (x < 101)
  {
    return 5;
  }
}

int speakerpitch(int dist)
{
  if (dist < 10)
  {
    return NOTE_C4;
  }
  else if (dist < 12)
  {
    return NOTE_CS4;
  }
  else if (dist < 14)
  {
    return NOTE_D4;
  }
  else if (dist < 16)
  {
    return NOTE_DS4;
  }
  else if (dist < 18)
  {
    return NOTE_E4;
  }
  else if (dist < 20)
  {
    return NOTE_F4;
  }
  else if (dist < 22)
  {
    return NOTE_FS4;
  }
  else if (dist < 24)
  {
    return NOTE_G4;
  }
  else if (dist < 26)
  {
    return NOTE_GS4;
  }
  else if (dist < 28)
  {
    return NOTE_A4;
  }
  else if (dist < 30)
  {
    return NOTE_AS4;
  }
  else if (dist < 32)
  {
    return NOTE_B4;
  }
  else if (dist < 34)
  {
    return NOTE_C5;
  }
  else if (dist < 36)
  {
    return NOTE_CS5;
  }
  else if (dist < 38)
  {
    return NOTE_D5;
  }
  else if (dist < 40)
  {
    return NOTE_DS5;
  }
  else if (dist < 42)
  {
    return NOTE_E5;
  }
  else if (dist < 44)
  {
    return NOTE_F5;
  }
  else if (dist < 46)
  {
    return NOTE_FS5;
  }
  else if (dist < 48)
  {
    return NOTE_G5;
  }
  else if (dist < 50)
  {
    return NOTE_GS5;
  }
  else if (dist < 52)
  {
    return NOTE_A5;
  }
  else if (dist < 54)
  {
    return NOTE_AS5;
  }
  else if (dist < 56)
  {
    return NOTE_B5;
  }
  else if (dist < 58)
  {
    return NOTE_C6;
  }

}



int colNum = 1;
int rowNum = 0;
void  yaz(int matrix[4][4]){
  for (int c=0; c<4; c++){

    digitalWrite(col[c], HIGH);
    for (int r = 0; r < 4; r++){
      digitalWrite(row[r], 255*matrix[r][c]);
     delay(1);
    }
    for (int r = 0; r < 4; r++){
      digitalWrite(row[r], HIGH);
     delay(1);
    }
    digitalWrite(col[c], LOW);
  }
}

void  yazInvert(int matrix[4][4]){
  for (int c=0; c<4; c++){

    digitalWrite(col[c], HIGH);
    for (int r = 0; r < 4; r++){
      digitalWrite(row[r], 255*matrix[r][c]);
     delay(1);
    }
    for (int r = 0; r < 4; r++){
      digitalWrite(row[r], HIGH);
     delay(1);
    }
    digitalWrite(col[c], LOW);
  }
}


void test1()
{
  digitalWrite(col[colNum], HIGH);
      digitalWrite(row[rowNum],1);
  digitalWrite(col[colNum], LOW);
     delay(1);
}

void testMatrix()
{
  for (int c=0; c<5; c++)
  {
    digitalWrite(col[c], HIGH);
  }
  for (int r=0; r<5;r++)
  {
    digitalWrite(row[r], 1);
  }
  for (int cc=0; cc<5; cc++)
  {
    digitalWrite(col[cc], LOW);
  }
  delay(1);
}