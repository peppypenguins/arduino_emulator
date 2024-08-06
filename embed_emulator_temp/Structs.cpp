#include "Structs.hpp"


int selectTest(int input){
  switch (input){
    case 1: return INCREMENTTEST;
      break;
    case 2: return COARSEMODETEST;
      break;
    case 3: return STABLETEST;
      break;
    case 4: return FILLTEST;
      break;
    case 5: return DT124;
      break;
    case 6: return DT130;
      break;
    case 7: return DT138;
      break;
    case 8: return DT142;
      break;
    case 9: return BC2TEST;
      break;
    case 10: return DT145;
      break;
    case 11: return DT124;
      break; 
    case 12: return DT144;
      break;
    case 13: return DT122;
      break;
    case 14: return STABLEHIGH;
      break;
    case 15: return STABLELOW;
      break;
    case 16: return FILLPRECISION
      break;
    default: return STABLETEST;
      break;
  }
}

int requestInput(){
  Serial.println("Select your test, options include:");
Serial.println("1. INCREMENTTEST");
Serial.println("2. COARSEMODETEST");
Serial.println("3. STABLETEST");
Serial.println("4. FILLTEST");
Serial.println("5. DT124");
Serial.println("6. DT130");
Serial.println("7. DT138");
Serial.println("8. DT142");
Serial.println("9. BC2");
Serial.println("10. DT145");
Serial.println("11. DT124");
Serial.println("12. DT144");
Serial.println("13. DT122");
Serial.println("14. STABLEHIGH");
Serial.println("15. STABLELOW");
Serial.println("16. DT145-2");
while (Serial.available() == 0){
}
int testInt = Serial.parseInt();
testInt =  selectTest(testInt); 
return testInt;
}