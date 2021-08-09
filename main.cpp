#include "mbed.h"
#include "hcsr04.h"
#include <vector>
#include "measure_distance.hpp"
using namespace std;

//各モータに指令を送るピンの設定
DigitalOut motorDir1(D10);
DigitalOut motorDir2(D11);
 
DigitalOut motorDir3(D8);
DigitalOut motorDir4(D9);

//モータの動作についての関数の定義
void motorForward(void);
void motorStop(void);
void motorReverse(void);
void motorLeft(void);
void motorRight(void);

int borderline = 10;//センサの閾値
vector<int> d(3);//センサの値を格納するvector
unsigned int measure::dist = 0;

int main()
{
    pc.baud(115200);
    pc.printf("Start!\r\n");
    
    while(1) {
        usensor1.start();
        usensor2.start();
        usensor3.start();
        wait_ms(100);
        
        //vectorの初期化
        d = {0, 0, 0};
        
        //センサの測距と値の収納
        measure::getdistance1();
        d[0] = measure::dist;
        measure::getdistance2();
        d[1] = measure::dist;
        measure::getdistance3();
        d[2] = measure::dist;

        //条件に沿ってモータの制御を行う
        if(*d.begin() <= borderline ){
            motorLeft();
        }
        
        else if(d[1] <= borderline ){
        motorForward();
        }  
        
        else if(d[2] <= borderline ){
        motorRight();
        }  
        
        else if(d[0] <= borderline/2 || d[1] <= borderline/2 || d[2] <= borderline/2){
        motorReverse();
        }  
        
        else{
         motorStop();
        }
        
        wait_ms(500);
        
    }
}

//モータを動作させる関数の詳細
void motorForward() {
    motorDir1 = 1;
    motorDir2 = 0;
    motorDir3 = 1;
    motorDir4 = 0;
}
 
void motorReverse() {
    motorDir1 = 0;
    motorDir2 = 1;
    motorDir3 = 0;
    motorDir4 = 1;
}
 
void motorStop() {
    motorDir1 = 0;
    motorDir2 = 0;
    motorDir3 = 0;
    motorDir4 = 0;
}

void motorRight() {
    motorDir1 = 1;
    motorDir2 = 0;
    motorDir3 = 0;
    motorDir4 = 1;
}

void motorLeft() {
    motorDir1 = 0;
    motorDir2 = 1;
    motorDir3 = 1;
    motorDir4 = 0;
}