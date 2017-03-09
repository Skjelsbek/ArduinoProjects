// 22 - 28 is set connected to segment A - G
const int A = 22;
const int B = 23;
const int C = 24;
const int D = 25;
const int E = 26;
const int F = 27;
const int G = 28;

// 29 - 32 is set to display 4 - 1
const int D4 = 29;
const int D3 = 30;
const int D2 = 31;
const int D1 = 32;

// Storing what number that is displayed on each digit
int displayNumberD1 = 0;
int displayNumberD2 = 0;
int displayNumberD3 = 0;
int displayNumberD4 = 0;

// Timer variables
unsigned long startTime = 0;
unsigned long loopTime;

void setup() {
  // Setting up segments
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  // Setting up digits
  pinMode(D1, OUTPUT);
  digitalWrite(D1, 1);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, 1);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, 1);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, 1);
}

void loop() { 
    loopTime = millis() - startTime;
    if (loopTime <= 200) {
      displayDigits();
    }else {
      updateDigits();
      startTime = millis();
    } 
}

void displayDigits() {
  display(D4);
  delay(4);
  display(D3);
  delay(4);
  display(D2);
  delay(4);
  display(D1);
  delay(4);
}

void updateDigits() {  
  if (displayNumberD4 == 9) {           
    if (displayNumberD3 == 9) {
      displayNumberD3 = 0;
      if (displayNumberD2 == 9) {
        displayNumberD2 = 0;
        if (displayNumberD1 == 9) {
          setAllToZero();
        } else {
          displayNumberD1++;
        }
      } else {
        displayNumberD2++;
      }
    } else {
      displayNumberD3++;
    }
    displayNumberD4 = 0;
  } else {
    displayNumberD4++;
  }
}

void setAllToZero() {
  displayNumberD4 = 0;
  displayNumberD3 = 0;
  displayNumberD2 = 0;
  displayNumberD1 = 0;
}

void display(int toBeDisplayed) {
  // Enables the digit to be updated and sets displayNumber = the displayNumber of the one to be updated
  int displayNumber;
  if (toBeDisplayed == D4) {
    displayNumber = displayNumberD4;
    digitalWrite(D4, 0);
    digitalWrite(D3, 1);
    digitalWrite(D2, 1);
    digitalWrite(D1, 1);
  } else if (toBeDisplayed == D3) {
    displayNumber = displayNumberD3;
    digitalWrite(D4, 1);
    digitalWrite(D3, 0);
    digitalWrite(D2, 1);
    digitalWrite(D1, 1);
  } else if (toBeDisplayed == D2) {
    displayNumber = displayNumberD2;
    digitalWrite(D4, 1);
    digitalWrite(D3, 1);
    digitalWrite(D2, 0);
    digitalWrite(D1, 1);
  } else if (toBeDisplayed == D1) {
    displayNumber = displayNumberD1;
    digitalWrite(D4, 1);
    digitalWrite(D3, 1);
    digitalWrite(D2, 1);
    digitalWrite(D1, 0);
  }

  // Updates segments of the selected digit
  if (displayNumber == 0) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }
    digitalWrite(G, 0);     
  } else if (displayNumber == 1) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }    
    digitalWrite(B, 1);
    digitalWrite(C, 1);        
  } else if (displayNumber == 2) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);    
  } else if (displayNumber == 3) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);    
  } else if (displayNumber == 4) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);       
  } else if (displayNumber == 5) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);     
  } else if (displayNumber == 6) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    digitalWrite(C, 1);    
  } else if (displayNumber == 7) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);    
  } else if (displayNumber == 8) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }        
  } else if (displayNumber == 9) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    } 
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);     
  }
}
