const char ADDR[] = {22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52}; //char is one byte from -127 to 127
const char DATA[] = {39,41,43,45,47,49,51,53};
const char IOPORT[] = {13,12,11,10,9,8}; // para que el bit 7 el mas significativo quede primero en el shift de ioport

#define CLOCK 2
#define READ_WRITE 3


void setup() {
  for (int n=0;n<16;n++){
    pinMode(ADDR[n], INPUT);
  }
   for (int n=0;n<8;n++){
    pinMode(DATA[n], INPUT);
  }
     for (int n=0;n<6;n++){
    pinMode(IOPORT[n], INPUT);
  }
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);
  // each time that on pin 2 (clock) i receive a HIGH on the rising edge run the onClock function
  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING); 
  Serial.begin(9600);
}

void onClock (){
  char output[15];
  unsigned int address = 0;
  for (int n=0;n<16;n++){
    int bit = digitalRead(ADDR[n]) ? 1:0; //? ternary operator if TRUE then 1 else 0
    Serial.print(bit);
    address = (address << 1) + bit;
  }
  Serial.print("    ");
  unsigned int data = 0;
  for (int n=0;n<8;n++){
    int bit = digitalRead(DATA[n]) ? 1:0; //? ternary operator if TRUE then 1 else 0
    Serial.print(bit);
    data = (data << 1) + bit;
  }
    Serial.print("    ");
  unsigned int io = 0;
  for (int n=0;n<6;n++){
    int bit = digitalRead(IOPORT[n]) ? 1:0; //? ternary operator if TRUE then 1 else 0
    Serial.print(bit);
    io = (io << 1) + bit;
  } 
  sprintf(output, " %04x %04c %02x %02x",address,digitalRead(READ_WRITE)?'r':'W',data,io);
  Serial.println(output);
}

void loop() {
}
