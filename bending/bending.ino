#include <AccelStepper.h>
#include <Servo.h>

#define limitSwitch 11

#define DistanceConst (48) //mm與steps轉換常數
#define angleConst (18) //角度與steps轉換常數
#define posConst (42) //初始位置到餵線口需轉動角度
//以上參數皆須做出實品後微調

AccelStepper feederStepper(1, 5, 6);
AccelStepper zAxisStepper(1, 7, 8);
AccelStepper benderStepper(1, 9, 10);

Servo servo01;
String dataIn = "";
String manualStatus = "";
int count = 0;
int dist;

void setup() {
  Serial.begin(9600);
  pinMode(limitSwitch,INPUT_PULLUP);
  servo01.attach(2);
  servo01.write(40);

    feederStepper.setMaxSpeed(2000);
    zAxisStepper.setMaxSpeed(2000);
    benderStepper.setMaxSpeed(2000);

    while(digitalRead(limitSwitch != 0)){
      benderStepper.setSpeed(1200);
      benderStepper.runSpeed();
      benderStepper.setCurrentPosition(0);
    }
    delay(40);

    while(benderStepper.currentPosition() != -1400){
      benderStepper.setSpeed(-1200);
      benderStepper.run();         
    }
benderStepper.setCurrentPosition(0);
}

void loop() {
  String mode = Serial.readString();


}
void xAxisBending(int feed, int angle, bool direction){
    //如果direction為正->順摺,反之亦然
    int feedDistance = feed * DistanceConst;
    // turn feed(mm) to the appropriate steps for the stepper to move
    //數值需做出實品後進行微調,先估48
    while (feederStepper.currentPosition() != feedDistance) {
      feederStepper.setSpeed(1200);
      feederStepper.run();
    } //feed
    feederStepper.setCurrentPosition(0); // reset the current position to 0
     
    int state = (direction)? 40:130;
    int positionConstant = (direction)? angle:posConst;
    //從起始位置轉至線的另一邊所需角度，仍需實測
    servo01.write(state);
    while (benderStepper.currentPosition() != -positionConstant * angleConst) {
      benderStepper.setSpeed(-700);
      benderStepper.run();
    }
    benderStepper.setCurrentPosition(0);
    delay(200);
    if(direction){
      servo01.write(40); // Set the bender pin up
      delay(200);
    }

    while (benderStepper.currentPosition() != angle * angleConst) {
      benderStepper.setSpeed(1200);
      benderStepper.run();
    }
    benderStepper.setCurrentPosition(0);
    delay(50);
    if(!direction){
    while (benderStepper.currentPosition() != -(angle - state) * angleConst) {
      benderStepper.setSpeed(-1200);
      benderStepper.run();
    }
    benderStepper.setCurrentPosition(0);
    servo01.write(130);
    delay(100);
    }
}
void zAxisTurning(int feed, int angle, bool direction){
  xAxisBending(int feed, int angle, bool direction);
}
