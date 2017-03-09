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

int displayNumberD1 = 9;
int displayNumberD2 = 9;
int displayNumberD3 = 9;
int displayNumberD4 = 9;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

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
  updateAll();
  delay(200);
}

void updateAll() {  
  if (displayNumberD4 == 9) {
    updateD4();
    displayNumberD4 = 0;
    updateD3();
    if (displayNumberD3 == 9) {
      displayNumberD3 = 0;
    } else {
      displayNumberD3++;
    }
  } else if (displayNumberD3 == 9) {
    updateD3();
    displayNumberD3 = 0;
    updateD2();
    if (displayNumberD2 == 9) {
      displayNumberD2 = 0;
    } else {
      displayNumberD2++;
    }  
  } else if (displayNumberD2 == 9) {
    updateD2();
    displayNumberD2 = 0;
    updateD1();
    if (displayNumberD1 == 9) {
      displayNumberD1 = 0;
    } else {
      displayNumberD1++;
    }
  } else if (displayNumberD1 == 9) {
    setAllToZero();    
  } else if (displayNumberD4 != 9) {
    updateD4();
    displayNumberD4++;
  }
}

void setAllToZero() {
  displayNumberD4 = 9;
  displayNumberD3 = 9;
  displayNumberD2 = 9;
  displayNumberD1 = 9;
}

void updateD4() {  
  digitalWrite(D4, 0);
  digitalWrite(D3, 1);
  digitalWrite(D2, 1);
  digitalWrite(D1, 1);  
 
  if (displayNumberD4 == 0) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }    
    digitalWrite(B, 1);
    digitalWrite(C, 1);    
    
  } else if (displayNumberD4 == 1) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD4 == 2) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD4 == 3) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);   
    
  } else if (displayNumberD4 == 4) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1); 
    
  } else if (displayNumberD4 == 5) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD4 == 6) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD4 == 7) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }      
    
  } else if (displayNumberD4 == 8) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    } 
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
     
  } else if (displayNumberD4 == 9) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }
    digitalWrite(G, 0);     
  }
  
}

void updateD3() {  
  digitalWrite(D4, 1);
  digitalWrite(D3, 0);
  digitalWrite(D2, 1);
  digitalWrite(D1, 1);  
 
  if (displayNumberD3 == 0) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }    
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD3 == 1) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD3 == 2) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);  
    
  } else if (displayNumberD3 == 3) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD3 == 4) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD3 == 5) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD3 == 6) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD3 == 7) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }      
    
  } else if (displayNumberD3 == 8) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    } 
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
     
  } else if (displayNumberD3 == 9) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }
    digitalWrite(G, 0);     
  }    
}

void updateD2() {  
  digitalWrite(D4, 1);
  digitalWrite(D3, 1);
  digitalWrite(D2, 0);
  digitalWrite(D1, 1);  
 
  if (displayNumberD2 == 0) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }    
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD2 == 1) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD2 == 2) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);  
    
  } else if (displayNumberD2 == 3) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD2 == 4) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD2 == 5) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD2 == 6) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD2 == 7) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }      
    
  } else if (displayNumberD2 == 8) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    } 
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
     
  } else if (displayNumberD2 == 9) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }
    digitalWrite(G, 0);     
  }    
}

void updateD1() {  
  digitalWrite(D4, 1);
  digitalWrite(D3, 1);
  digitalWrite(D2, 1);
  digitalWrite(D1, 0);  
 
  if (displayNumberD1 == 0) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }    
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD1 == 1) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD1 == 2) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);  
    
  } else if (displayNumberD1 == 3) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD1 == 4) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(C, 1);
    digitalWrite(D, 1);
    
  } else if (displayNumberD1 == 5) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
    digitalWrite(E, 1);
    digitalWrite(D, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD1 == 6) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    }  
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    
  } else if (displayNumberD1 == 7) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }      
    
  } else if (displayNumberD1 == 8) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 0);
    } 
    digitalWrite(A, 1);
    digitalWrite(B, 1);
    digitalWrite(C, 1);
    digitalWrite(F, 1);
    digitalWrite(G, 1);
     
  } else if (displayNumberD1 == 9) {
    for (int i = 22; i <= 28; i++) {
      digitalWrite(i, 1);
    }
    digitalWrite(G, 0);     
  }    
}
