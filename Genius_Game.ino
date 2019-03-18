#include <stdlib.h>
#include <time.h>
#define tempo 300

int cor[100];
int tom;
char recebido;
boolean newData = false;
int i = 0, j; //contador

int freq(){
    switch (cor[j]){
    case 4: 
      return 440;
      break;
    case 5: 
      return 550;
      break;
    case 6: 
      return 660;
      break;
  }
}

void pisca() {
  for (j = 0; j <= i; j ++) {
    digitalWrite(cor[j], HIGH);
    tom = freq();
    tone(3, tom, tempo);
    delay(tempo);
    digitalWrite(cor[j], LOW);
    delay(tempo);
  }
}

void recebeChar() {
  while (newData == false) {
    if (Serial.available() > 0) {
      recebido = Serial.read();
      newData = true;
    }
  }
  delay (tempo);
}

void compara(int index) {
  int cmp;
  switch (recebido) {
    case '1':
      cmp = 1;
      break;
    case '2':
      cmp = 2;
      break;
    case '3':
      cmp = 3;
      break; 
  }
  if (cmp != (cor[index] - 3)) {
    tone(3, 100, 2000);
    delay (3000);
    i = -1;
  }
  newData = false;
  delay(tempo);
}

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  srand(time(NULL));
  Serial.begin(9600);
  Serial.println("BEM VINDO AO GAME GENIUS");
}

void loop() {
  cor[i] = (rand() % 3) + 4;
  pisca ();
  for (j = 0; j <= i; j ++) {
    recebeChar();
    compara(j);
  }
  i ++;
}
