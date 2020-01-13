unsigned long lastRefreshTime = 0;
int refreshInterval = 1;
unsigned long lastMoveTime = 0;
int moveInterval;

int shape[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

int rowPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int colPins[8] = {A3, A2, A1, A0, 13, 12, 11, 10};

unsigned long now = 0;
unsigned long overTime = 100000000;
int currentColumn = 0;
int ballX, ballY;
int player1Score, player2Score;
int player1Position, player2Position;
boolean ballMovingUp = true;
boolean ballMovingLeft = true;
boolean isGameOn = true;

void verificareLeduri(){

           digitalWrite(rowPins[0], HIGH);
           digitalWrite(rowPins[1], HIGH);
           digitalWrite(rowPins[2], HIGH); 
           digitalWrite(rowPins[3], HIGH);
           digitalWrite(rowPins[4], HIGH);
           digitalWrite(rowPins[5], HIGH);
           digitalWrite(rowPins[6], HIGH); 
           digitalWrite(rowPins[7], HIGH);

           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], LOW);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH);
}

void setup() {
  
  for(int i = 2; i <= 13; i++){
    pinMode(i, OUTPUT); 
  }
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  delay(2000);
  
  restartGame(); 
}

void loop() {

    now = millis();
   if(isGameOn){
     update();
   }
   else {
  updateScore();
  }
  draw();  

    // verificareLeduri();

}

void gameOver(){

  
    isGameOn = false;
    overTime = now;
    clearPins();
}

void clearPins(){

  delay(500);
  for (int i=0; i<8; i++){
    digitalWrite(rowPins[i], HIGH);
    digitalWrite(colPins[i], LOW);
  }
  delay(500);
}

void restartGame(){
  
  moveInterval = 600;
  ballX = 4;
  ballY = 6;
  ballMovingUp = true;
  ballMovingLeft = true;
  isGameOn = true;
}

void updateBall(){

  
  if(ballMovingLeft){
    ballX--;
  }
  else {
    ballX++;
  }

  if(ballX == 0){
    ballMovingLeft = false;
  }
  else if (ballX == 7){
    ballMovingLeft = true;
  }

  if (ballMovingUp){
    ballY--;
  }
  else{
    ballY++;
  }

  if(ballY == 0){
    player1Score++;
    gameOver();
  }
  else if (ballY == 7){
    player2Score++;
    gameOver();
  }

  if(ballY == 1 && ballX >= player2Position && ballX < player2Position + 3){
    ballMovingUp = false;
    moveInterval -= 20;
  }
  else if (ballY == 6 && ballX >= player1Position && ballX < player1Position + 3){
    ballMovingUp = true;
    moveInterval -= 20;
  }
}

void update(){
  
  if(now - lastMoveTime > moveInterval){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        shape[i][j] = 0;
      }
    }
    
    int PotentiometruPlayer1 = analogRead(A4);
    int PotentiometruPlayer2 = analogRead(A5);

    player1Position = 1023 - PotentiometruPlayer1 * 6 / 1024 - 1018;
    player2Position = PotentiometruPlayer2 * 6 / 1024;
    
    for(int i = 0; i < 8; i++){
      
      if(i > player1Position && i < player1Position + 3){
        shape[7][i] = 1;
      }
      else{
        shape[7][i] = 0;
      }
      
      if(i > player2Position && i < player2Position + 3){
        shape[0][i] = 1;
      }
      else{
        shape[0][i] = 0;
      }
    }
    
    updateBall();
    shape[ballY][ballX] = 1;    
    lastMoveTime = now;
  }
}

void draw(){

    for (int i = 0; i < 8; i++){
      digitalWrite(rowPins[i], shape[i][currentColumn] == 1 ? HIGH:LOW);
    }

     switch(currentColumn){
        case 0:
           digitalWrite(colPins[0], LOW);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH);
           break;
        case 1:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], LOW);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH); 
          break;
        case 2:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], LOW); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH);
          break;
        case 3:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], LOW);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH);
          break;
        case 4:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], LOW);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH); 
          break;
        case 5:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], LOW);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], HIGH);
          break;
        case 6:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], LOW); 
           digitalWrite(colPins[7], HIGH);
          break;
        case 7:
           digitalWrite(colPins[0], HIGH);
           digitalWrite(colPins[1], HIGH);
           digitalWrite(colPins[2], HIGH); 
           digitalWrite(colPins[3], HIGH);
           digitalWrite(colPins[4], HIGH);
           digitalWrite(colPins[5], HIGH);
           digitalWrite(colPins[6], HIGH); 
           digitalWrite(colPins[7], LOW); 
          break;
      }

      currentColumn++;
      currentColumn %= 8;
      lastRefreshTime = now;
}

void updateScore(){
  
  for (int i = 0; i < 8; i++){
    for (int j = 1; j < 8; j++){
      shape[i][j] = 0;
    }
  }
  
  if(now - overTime > 3000)
    restartGame();
}
