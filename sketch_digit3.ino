const int PIN_PULL_RESET      = 2;      
const int PIN_TRIGGER_BUTTON  = 3;   
const int PIN_TRIGGER_Q       = 5;     
const int PIN_TRIGGER_NOT_Q   = 4;  
const int PIN_LED_FORBIDDEN   = 7;   

const int DELAY_MS       = 25;


void initPins() {
  pinMode(PIN_PULL_RESET, INPUT);      
  pinMode(PIN_TRIGGER_BUTTON, OUTPUT);
  digitalWrite(PIN_TRIGGER_BUTTON, LOW);
  
  pinMode(PIN_TRIGGER_Q, INPUT);
  pinMode(PIN_TRIGGER_NOT_Q, INPUT);

  pinMode(PIN_LED_FORBIDDEN, OUTPUT);
  digitalWrite(PIN_LED_FORBIDDEN, LOW);
}

void readInputs(int &resetButton, int &qState, int &notQState) {
  resetButton = digitalRead(PIN_PULL_RESET);
  qState = digitalRead(PIN_TRIGGER_Q);
  notQState = digitalRead(PIN_TRIGGER_NOT_Q);
}

void stateLogic(int resetButton, int qState, int notQState, bool &isForbidden) {
  if (resetButton == HIGH) {
    digitalWrite(PIN_TRIGGER_BUTTON, HIGH);
  } else {
    digitalWrite(PIN_TRIGGER_BUTTON, LOW);
  }

  if (qState == LOW && notQState == LOW) {
    isForbidden = true;
  } else {
    isForbidden = false;
  }
}

void setup() {
  Serial.begin(9600);
  initPins(); 
}


void updateOutputs(bool isForbidden, int qState, int notQState) {

  if (isForbidden) {
    digitalWrite(PIN_LED_FORBIDDEN, HIGH);
  } else {
    digitalWrite(PIN_LED_FORBIDDEN, LOW);
  }

  Serial.print("Q:");
  Serial.print(qState);
  Serial.print(" notQ:");
  Serial.print(notQState);
  Serial.print(" Forbidden:");
  Serial.println(isForbidden ? 1 : 0);
}


void loop() {
  int resetButton = LOW;
  int qState = LOW;
  int notQState = LOW;
  bool isForbidden = false;

  readInputs(resetButton, qState, notQState);
  stateLogic(resetButton, qState, notQState, isForbidden);
  updateOutputs(isForbidden, qState, notQState);

  delay(DELAY_MS);
}