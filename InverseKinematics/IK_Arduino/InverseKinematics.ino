#include<math.h>
#include<Servo.h>

//ENTER THE VALUE OF BASE, ARM1, ARM2: 
int lenBase = 25;
int lenArm1 = 25;
int lenArm2 = 25;

//ENTER THE VALUE OF X Y Z HERE:
int x = 25;
int y = 25;
int z = 25;

#define RAD2DEG 180/3.1415

#define joyX1 A0
#define joyY1 A1
#define joyX2 A2
#define joyY2 A3

#define pinBase 5
#define pinArm1 6
#define pinArm2 7

Servo base, arm1, arm2;

int prevPosBase, prevPosArm1, prevPosArm2;
int newPosBase, newPosArm1, newPosArm2;

int iniXaxis1, iniYaxis1;
int iniXaxis2, iniYaxis2;

int posXaxis1, posYaxis1;
int posXaxis2, posYaxis2;

double angle[3];
int alpha = 0, beta = 90, gamma = 90;

void getAngle(int x, int y, int z, int base, int arm1, int arm2){

  
  double d = sqrt(x*x + y*y + (z-base)*(z-base));
  
  if(x!=0){
    double p = y/x;
    angle[0] = atan(p);}
  else{
    angle[0] = PI/2;}
    
  double theta1 = asin((z-base)/d);
  double theta2 = acos((arm1*arm1 - arm2*arm2 + d*d)/(2*arm1*d));

  angle[1] = theta1 + theta2;

  angle[2] = acos((arm1*arm1 + arm2*arm2 - d*d)/(2*arm1*arm2));

  angle[0] = angle[0] * RAD2DEG;
  angle[1] = angle[1] * RAD2DEG;
  angle[2] = angle[2] * RAD2DEG;

  Serial.print("Angle of Base =  ");
  Serial.println(angle[0]);
  
  Serial.print("Angle of Arm1 =  ");
  Serial.println(angle[1]);
  
  Serial.print("Angle of Arm2 (w.r.t to Arm1) =  ");
  Serial.println(angle[2]);

  int angles[3];
  for(int i = 0; i<=3; i++){
    angles[i] = (int)angle[i];
  }
  
  return angles;
}

void moveToXYZ(int iniPos, int finPos, Servo servo){
  if(iniPos>finPos){
    for(int i = iniPos; i>=finPos; i--){
      servo.write(i);
      delay(25);
    }
  }
  else{
    for(int i = iniPos; i<=finPos; i++){
      servo.write(i);
      delay(25);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(joyX1, INPUT);
  pinMode(joyY1, INPUT);
  pinMode(joyY2, INPUT);
  pinMode(joyX2, INPUT);

  base.attach(pinBase);
  arm1.attach(pinArm1);
  arm2.attach(pinArm2);

  delay(5000);
  base.write(180);
  delay(2000);
  arm1.write(90);
  delay(2000);
  arm2.write(180);

  
  prevPosBase = 180;
  prevPosArm1 = 90;
  prevPosArm2 = 180;

  
  getAngle(x, y, z, lenBase, lenArm1, lenArm2);


  if(z<0){
    Serial.println("The arms hit the base, change point to z>=0" );
    }
  else{
    if( 0<=angle[0]<=180 && 0<=angle[2]<=180){
      alpha = 180 - angle[0];
      gamma = angle[2];
      moveToXYZ(prevPosBase, alpha, base);
      delay(2000);
      
      if(0<=angle[1]<=90){
      beta = 90 + angle[1];
      moveToXYZ(prevPosArm1, beta, arm1);
      delay(2000);
      moveToXYZ(prevPosArm2, gamma, arm2);
      delay(2000);
      }
    else{
       Serial.println("The point can't be reached by the current configeration");
    }  
   } 
 }
    newPosBase = alpha;
    newPosArm1 = beta;
    newPosArm2 = gamma;
    
    Serial.println(alpha);
    Serial.println(beta);
    Serial.println(gamma);
  
  iniXaxis1 = analogRead(joyX1);
  iniYaxis1 = analogRead(joyY1);
  iniXaxis2 = analogRead(joyX2);
  iniYaxis2 = analogRead(joyY2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int posX1 = analogRead(joyX1);
  int posY1 = analogRead(joyY1);
  int posY2 = analogRead(joyY2);
  int posX2 = analogRead(joyX2);

  if(posYaxis1 >= iniYaxis1 + 100){
    base.write(newPosBase++);
    delay(15);
  }
  else if(posYaxis1 <= iniYaxis1 - 100){
    base.write(newPosBase--);
    delay(15);
  }

  if(posXaxis1 >= iniXaxis1 + 100){
    arm1.write(newPosArm1++);
    delay(15);
  }
  else if(posXaxis1 <= iniXaxis1 - 100){
    arm1.write(newPosArm1--);
    delay(15);
  }  

  if(posXaxis2 >= iniXaxis2 + 100){
    arm2.write(newPosArm2++);
    delay(15);
  }
  else if(posXaxis2 <= iniXaxis2 - 100){
    arm2.write(newPosArm2--);
    delay(15);
  }
}
