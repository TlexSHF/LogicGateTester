/* LOGIC GATE TESTER
 * Tests if a logic gate is working,
 * Based on the type of gate
 * Change the gate variable to one of the defined gates
 */

//TODO: NEED SOME CONDITION FOR NOT GATES AS THEY ONLY HAVE ONE INPUT

#define NAND 0
#define NOR 2
#define NOT 4
#define AND 8
#define OR 32
#define XOR 86

unsigned gate = NOT;

unsigned pinA = 5;
unsigned pinB = 6;
unsigned pinY = 7;

void setup() {
  //Setting pin modes
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinY, INPUT);

  Serial.begin(9600);

  tester();
}
void loop(){}

void tester(){
  bool testY = 0;
  bool readY = 0;
  bool succeeded = true;
  
  for(int i=0; i < 2; i++){
    //Special case NOT
    if(gate == NOT){
      testY = notTest(i);
      digitalWrite(pinA, i);
      readY = digitalRead(pinY);
        Serial.println(readY);
        Serial.println(testY);
  
        if(testY != readY){
          succeeded = false;
        }
    } else {
      for(int j=0; j < 2; j++){
        digitalWrite(pinA, i);
        digitalWrite(pinB, j);
        Serial.print(i);
        Serial.println(j);
  
        if(gate == NAND) {
          testY = nandTest(i, j);
          
        } else if(gate == NOR) {
          testY = norTest(i, j);
          
        } else if(gate == AND){
          testY = andTest(i, j);
          
        } else if(gate == OR) {
          testY = orTest(i, j);
          
        } else if(gate == XOR) {
          testY = xorTest(i, j);
          
        } else {
          Serial.println("Unrecognized gate. Use one of the defined gates, and restart the program");
          return;
        }
        
        readY = digitalRead(pinY);
        Serial.println(readY);
        Serial.println(testY);
  
        if(testY != readY){
          succeeded = false;
        }
      }
    }
  }
  if(succeeded){
    Serial.print("The test succeeded. The gate is intact");
  } else {
    Serial.print("The test failed. The gate might be damaged, or the wrong gate was inputted into the program");
  }
}

bool nandTest(bool a, bool b){
  return !(a & b);
}
bool norTest(bool a, bool b){
  return !(a | b);
}
bool notTest(bool a){
  return !a;
}
bool andTest(bool a, bool b){
  return a & b;
}
bool orTest(bool a, bool b){
  return a | b;
}
bool xorTest(bool a, bool b){
  return a ^ b;
}
