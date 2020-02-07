#include <LiquidCrystal_I2C.h>

//---- Hardware LCD Setup ----//
LiquidCrystal_I2C lcd(0x27, 16, 2);
int x = 0;
// the 8 arrays that form each segment of the custom numbers
byte LT[8] = 
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte UMB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte LMB[8] =
{
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};



void setup()
{
  // assignes each segment a write number
  lcd.createChar(8,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,UMB);
  lcd.createChar(7,LMB);

  // Hardware LCD. SDA=4, SCL=5
  lcd.begin(4,5);
  lcd.backlight();
}

void custom0O()
{ // uses segments to build the number 0
  lcd.setCursor(x, 0); 
  lcd.write(8);  
  lcd.write(1); 
  lcd.write(2);
  lcd.setCursor(x, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);
}

void custom1()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x+1,1);
  lcd.write(255);
}

void custom2()
{
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}

void custom3()
{
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5); 
}

void custom4()
{
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
  lcd.setCursor(x+2, 1);
  lcd.write(255);
}

void custom5()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void custom6()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void custom7()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x+1, 1);
  lcd.write(8);
}

void custom8()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void custom9()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x+2, 1);
  lcd.write(255);
}

void customA()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(255);
}

void customB()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(5);
  lcd.setCursor(x, 1);
  lcd.write(255);
  lcd.write(7);
  lcd.write(2);
}

void customC()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(1);
  lcd.write(1);
  lcd.setCursor(x,1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(4);
}

void customD()
{
  lcd.setCursor(x, 0); 
  lcd.write(255);  
  lcd.write(1); 
  lcd.write(2);
  lcd.setCursor(x, 1); 
  lcd.write(255);  
  lcd.write(4);  
  lcd.write(5);
}

void customE()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(255);
  lcd.write(7);
  lcd.write(7); 
}

void customF()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(255);
}

void customG()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(1);
  lcd.write(1);
  lcd.setCursor(x,1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(2);
}

void customH()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(4);
  lcd.write(255);
  lcd.setCursor(x, 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(255); 
}

void customI()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(255);
  lcd.write(1);
  lcd.setCursor(x,1);
  lcd.write(4);
  lcd.write(255);
  lcd.write(4);
}

void customJ()
{
  lcd.setCursor(x+2,0);
  lcd.write(255);
  lcd.setCursor(x,1);
  lcd.write(4);
  lcd.write(4);
  lcd.write(5);
}

void customK()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(x,1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(2); 
}

void customL()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.setCursor(x,1);
  lcd.write(255);
  lcd.write(4);
  lcd.write(4);
}

void customM()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(3);
  lcd.write(5);
  lcd.write(2);
  lcd.setCursor(x,1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(254);
  lcd.write(255);
}

void customN()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(2);
  lcd.write(254);
  lcd.write(255);
  lcd.setCursor(x,1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(3);
  lcd.write(5);
}

void customP()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(255);
}

void customQ()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(255);
  lcd.write(4);
}

void customR()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x,1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(2); 
}

void customS()
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void customT()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(255);
  lcd.write(1);
  lcd.setCursor(x,1);
  lcd.write(254);
  lcd.write(255);
}

void customU()
{
  lcd.setCursor(x, 0); 
  lcd.write(255);  
  lcd.write(254); 
  lcd.write(255);
  lcd.setCursor(x, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);
}

void customV()
{
  lcd.setCursor(x, 0); 
  lcd.write(3);  
  lcd.write(254);
  lcd.write(254); 
  lcd.write(5);
  lcd.setCursor(x+1, 1); 
  lcd.write(2);  
  lcd.write(8);
}

void customW()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.write(254);
  lcd.write(254);
  lcd.write(255);
  lcd.setCursor(x,1);
  lcd.write(3);
  lcd.write(8);
  lcd.write(2);
  lcd.write(5);
}

void customX()
{
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(x,1);
  lcd.write(8);
  lcd.write(254);
  lcd.write(2); 
}

void customY()
{
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
  lcd.setCursor(x+1,1);
  lcd.write(255);
}

void customZ()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(6);
  lcd.write(5);
  lcd.setCursor(x, 1);
  lcd.write(8);
  lcd.write(7);
  lcd.write(4);
}

void customqm()
{
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(254);
  lcd.write(7);
}

void customsm()
{
  lcd.setCursor(x,0);
  lcd.write(255);
  lcd.setCursor(x, 1);
  lcd.write(7);
}

void letters1()
{
  customA();
  x = x + 4;
  customB();
  x = x + 4;
  customC();
  x = x + 4;
  customD();
  x = x + 4;
  customE();
  x = x + 4;
  customF();
  x = x + 4;
  customG();
  x = x + 4;
  customH();
  x = x + 4;
  customI();
  x = x + 4;
  customJ();
  delay(500);
}

void letters2()
{
  customK();
  x = x + 4;
  customL();
  x = x + 4;
  customM();
  x = x + 5;
  customN();
  x = x + 5;
  custom0O();
  x = x + 4;
  customP();
  x = x + 4;
  customQ();
  x = x + 5;
  customR();
  x = x + 4;
  customS();
  delay(500);
}

void letters3()
{
  customT();
  x = x + 4;
  customU();
  x = x + 4;
  customV();
  x = x + 5;
  customW();
  x = x + 5;
  customX();
  x = x + 4;
  customY();
  x = x + 4;
  customZ();
  x = x + 4;
  customqm();
  x = x + 4;
  customsm();
  delay(500);
}

void numbers()
{
  custom0O();    // displays custom 0 on the LCD
  x = x + 4;    // sifts cursor over 4 columns
  custom1();
  x = x + 4;
  custom2();
  x = x + 4;
  custom3();
  x = x + 4;
  custom4();
  x = x + 4;
  custom5();
  x = x + 4;
  custom6();
  x = x + 4;
  custom7();
  x = x + 4;
  custom8();
  x = x + 4;
  custom9();
  delay(500);
}

void loop() 
{
  lcd.setCursor(x,0);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(255);
  lcd.write(254);
  lcd.write(255);

  lcd.setCursor(4, 0); 
  lcd.write(8);  
  lcd.write(1); 
  lcd.write(2);
  lcd.setCursor(4, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);

  lcd.setCursor(8, 0); 
  lcd.write(8);  
  lcd.write(1); 
  lcd.write(2);
  lcd.setCursor(8, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);

  lcd.setCursor(12,0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(12+1,1);
  lcd.write(255);

  lcd.setCursor(16, 0); 
  lcd.write(8);  
  lcd.write(1); 
  lcd.write(2);
  lcd.setCursor(16, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);

  lcd.setCursor(20,0);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(20+1,1);
  lcd.write(255);

  
  lcd.setCursor(24,0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(24+1, 1);
  lcd.write(8);

  lcd.setCursor(28,0);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(28, 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);

  
  for (int positionCounter = 0; positionCounter < 27; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(100);
  }
}
