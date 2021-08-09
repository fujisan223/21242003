#include "mbed.h"
#include "hcsr04.h"
using namespace std;

Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);

//センサの値を受信するピンを定義
HCSR04 usensor1(D4, D5); // Trigger(DO), Echo(PWMIN)
HCSR04 usensor2(D2, D3);
HCSR04 usensor3(D6, D7);

class measure
{   
    public:
    static unsigned int dist;

    static int getdistance1(){
        //値をdist変数に格納
        dist = usensor1.get_dist_cm();
        pc.printf("dist1=%ldcm\r\n", dist);        
        myled = !myled;
        wait(1);
        
        return 0;
    }
    
    static int getdistance2(){
        //値をdist変数に格納
        dist = usensor2.get_dist_cm();
        pc.printf("dist1=%ldcm\r\n", dist);
        myled = !myled;
        wait(1);
        
        return 0;
    }
    
    static int getdistance3(){
        //値をdist変数に格納
        dist = usensor3.get_dist_cm();
        pc.printf("dist1=%ldcm\r\n", dist );
        myled = !myled;
        wait(1);
        
        return 0;
    }
};
