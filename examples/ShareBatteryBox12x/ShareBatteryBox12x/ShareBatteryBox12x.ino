#include <Battery.h>

//定义12块电池的电压范围和采集口
//正常锂电的电压范围在标称电压的0.875~1.2倍之间？
Battery battery01(7200, 8400, A0);
Battery battery02(7200, 8400, A1);
Battery battery03(7200, 8400, A2);
Battery battery04(7200, 8400, A3);
Battery battery05(7200, 8400, A4);
Battery battery06(7200, 8400, A5);
Battery battery07(7200, 8400, A6);
Battery battery08(7200, 8400, A7);
Battery battery09(7200, 8400, A8);
Battery battery10(7200, 8400, A9);
Battery battery11(7200, 8400, A10);
Battery battery12(7200, 8400, A11);

//存放电池电压mv
int Vbatteries[12];
//存放电池剩余电量水平%
int Lbatteries[12];

//电池电量低于50%认为是坏电池，无法充电
#define BADBATTERYLEVEL 50
//电池充电的起点75%
#define LOWSTOPLEVEL 75
//电池满电，对应到电压上应该有给额度，一般是1.2倍
#define HIGHSTOPLEVEL 100

//定义电池真伪检查引脚
#define FAKEBATTERYTEST01 2
#define FAKEBATTERYTEST02 3
#define FAKEBATTERYTEST03 4
#define FAKEBATTERYTEST04 5
#define FAKEBATTERYTEST05 6
#define FAKEBATTERYTEST06 7
#define FAKEBATTERYTEST07 8
#define FAKEBATTERYTEST08 9
#define FAKEBATTERYTEST09 10
#define FAKEBATTERYTEST10 11
#define FAKEBATTERYTEST11 12
#define FAKEBATTERYTEST12 13

//定义电池柜门锁数字控制引脚
#define LOCKDIGITREADWRITE01 30
#define LOCKDIGITREADWRITE02 32
#define LOCKDIGITREADWRITE03 34
#define LOCKDIGITREADWRITE04 36
#define LOCKDIGITREADWRITE05 38
#define LOCKDIGITREADWRITE06 40
#define LOCKDIGITREADWRITE07 42
#define LOCKDIGITREADWRITE08 44
#define LOCKDIGITREADWRITE09 46
#define LOCKDIGITREADWRITE10 48
#define LOCKDIGITREADWRITE11 50
#define LOCKDIGITREADWRITE12 52
//定义充电线继电器数字控制引脚
#define INCHARGEREADWRITE01  31
#define INCHARGEREADWRITE02  33
#define INCHARGEREADWRITE03  35
#define INCHARGEREADWRITE04  37
#define INCHARGEREADWRITE05  39
#define INCHARGEREADWRITE06  41
#define INCHARGEREADWRITE07  43
#define INCHARGEREADWRITE08  45
#define INCHARGEREADWRITE09  47
#define INCHARGEREADWRITE10  49
#define INCHARGEREADWRITE11  51
#define INCHARGEREADWRITE12  53
/**
 * 电池电压高于5v，需要分压电路
 * 2 cells (2S1P) li-ion/li-poly battery wired to A0, continuous sensing
 * https://github.com/rlogiacco/BatterySense#higher-than-5v-with-internal-voltage-regulator
 *
 *   +--------+
 *   |        |
 *   |       +-+
 *   |       | | 33k
 *   |       | |
 * -----     +-+
 *  ---       |---------+ A0
 *   |       +-+
 *   |       | |
 *   |       | | 10k
 *   |       +-+
 *   |        |
 *   +--------+---------+ GND
 *
 **/

void setup() {
  // 利用串口输出调试信息
	Serial.begin(9600);
	while (!Serial);
  Serial1.begin(9600);
  while (!Serial1);
	float ratio = (33 + 10) / 10;
	// 5V board, change to 3300 for a 3.3V board
  //启动电池电压采集
  battery01.begin(5000, ratio);
  battery02.begin(5000, ratio);
  battery03.begin(5000, ratio);
  battery04.begin(5000, ratio);
  battery05.begin(5000, ratio);
  battery06.begin(5000, ratio);
  battery07.begin(5000, ratio);
  battery08.begin(5000, ratio);
  battery09.begin(5000, ratio);
  battery10.begin(5000, ratio);
  battery11.begin(5000, ratio);
  battery12.begin(5000, ratio);

  // 定义真假电池检验引脚
  pinMode(FAKEBATTERYTEST01,INPUT);
  pinMode(FAKEBATTERYTEST02,INPUT);
  pinMode(FAKEBATTERYTEST03,INPUT);
  pinMode(FAKEBATTERYTEST04,INPUT);
  pinMode(FAKEBATTERYTEST05,INPUT);
  pinMode(FAKEBATTERYTEST06,INPUT);
  pinMode(FAKEBATTERYTEST07,INPUT);
  pinMode(FAKEBATTERYTEST08,INPUT);
  pinMode(FAKEBATTERYTEST09,INPUT);
  pinMode(FAKEBATTERYTEST10,INPUT);
  pinMode(FAKEBATTERYTEST11,INPUT);
  pinMode(FAKEBATTERYTEST12,INPUT);

  // 定义门锁状态继电器读写引脚
  pinMode(LOCKDIGITREADWRITE01,INPUT);
  pinMode(LOCKDIGITREADWRITE02,INPUT);
  pinMode(LOCKDIGITREADWRITE03,INPUT);
  pinMode(LOCKDIGITREADWRITE04,INPUT);
  pinMode(LOCKDIGITREADWRITE05,INPUT);
  pinMode(LOCKDIGITREADWRITE06,INPUT);
  pinMode(LOCKDIGITREADWRITE07,INPUT);
  pinMode(LOCKDIGITREADWRITE08,INPUT);
  pinMode(LOCKDIGITREADWRITE09,INPUT);
  pinMode(LOCKDIGITREADWRITE10,INPUT);
  pinMode(LOCKDIGITREADWRITE11,INPUT);
  pinMode(LOCKDIGITREADWRITE12,INPUT);

  pinMode(LOCKDIGITREADWRITE01,OUTPUT);
  pinMode(LOCKDIGITREADWRITE02,OUTPUT);
  pinMode(LOCKDIGITREADWRITE03,OUTPUT);
  pinMode(LOCKDIGITREADWRITE04,OUTPUT);
  pinMode(LOCKDIGITREADWRITE05,OUTPUT);
  pinMode(LOCKDIGITREADWRITE06,OUTPUT);
  pinMode(LOCKDIGITREADWRITE07,OUTPUT);
  pinMode(LOCKDIGITREADWRITE08,OUTPUT);
  pinMode(LOCKDIGITREADWRITE09,OUTPUT);
  pinMode(LOCKDIGITREADWRITE10,OUTPUT);
  pinMode(LOCKDIGITREADWRITE11,OUTPUT);
  pinMode(LOCKDIGITREADWRITE12,OUTPUT);

  
  // 定义充电线状态继电器读写引脚
  pinMode(INCHARGEREADWRITE01,INPUT);
  pinMode(INCHARGEREADWRITE02,INPUT);
  pinMode(INCHARGEREADWRITE03,INPUT);
  pinMode(INCHARGEREADWRITE04,INPUT);
  pinMode(INCHARGEREADWRITE05,INPUT);
  pinMode(INCHARGEREADWRITE06,INPUT);
  pinMode(INCHARGEREADWRITE07,INPUT);
  pinMode(INCHARGEREADWRITE08,INPUT);
  pinMode(INCHARGEREADWRITE09,INPUT);
  pinMode(INCHARGEREADWRITE10,INPUT);
  pinMode(INCHARGEREADWRITE11,INPUT);
  pinMode(INCHARGEREADWRITE12,INPUT);
  
  pinMode(INCHARGEREADWRITE01,OUTPUT);
  pinMode(INCHARGEREADWRITE02,OUTPUT);
  pinMode(INCHARGEREADWRITE03,OUTPUT);
  pinMode(INCHARGEREADWRITE04,OUTPUT);
  pinMode(INCHARGEREADWRITE05,OUTPUT);
  pinMode(INCHARGEREADWRITE06,OUTPUT);
  pinMode(INCHARGEREADWRITE07,OUTPUT);
  pinMode(INCHARGEREADWRITE08,OUTPUT);
  pinMode(INCHARGEREADWRITE09,OUTPUT);
  pinMode(INCHARGEREADWRITE10,OUTPUT);
  pinMode(INCHARGEREADWRITE11,OUTPUT);
  pinMode(INCHARGEREADWRITE12,OUTPUT);
  
}

void loop() {
	int p;              // 定义整数型变量，保存接收的数据。
	//digitalWrite(13, HIGH);
	delay(500);
	delay(500);

  //采集电压存入全局数组
  Vbatteries[0]=battery01.voltage();
  Lbatteries[0]=battery01.level();
  Vbatteries[1]=battery02.voltage();
  Lbatteries[1]=battery02.level();
  Vbatteries[2]=battery03.voltage();
  Lbatteries[2]=battery03.level();
  Vbatteries[3]=battery04.voltage();
  Lbatteries[3]=battery04.level();
  Vbatteries[4]=battery05.voltage();
  Lbatteries[4]=battery05.level();
  Vbatteries[5]=battery06.voltage();
  Lbatteries[5]=battery06.level();
  Vbatteries[6]=battery07.voltage();
  Lbatteries[6]=battery07.level();
  Vbatteries[7]=battery08.voltage();
  Lbatteries[7]=battery08.level();
  Vbatteries[8]=battery09.voltage();
  Lbatteries[8]=battery09.level();
  Vbatteries[9]=battery10.voltage();
  Lbatteries[9]=battery10.level();
  Vbatteries[10]=battery11.voltage();
  Lbatteries[10]=battery11.level();
  Vbatteries[11]=battery12.voltage();
  Lbatteries[11]=battery12.level();

  //？打印电压、电量，在这里可以判断电量，
  //电量低于70%亮红灯，否则亮绿灯？需要额外的2个引脚，如果够用可以考虑。
//  for(int i=0;i<12;i++){
//    // 判断电压同时判断柜子状态、电池状态
//    // 并将柜子的状态写入EEPROM中
//    // 如果联网成功，则将状态上传服务器
//    if(! digitalRead(30+i*2)){
//            digitalWrite(30+i*2,HIGH);       // 点亮LED。
//            delay(1000);
//            digitalWrite(30+i*2,LOW); 
//            delay(1000);
//    }
//  	Serial.print("Battery ");
//  	Serial.print(i+1);
//  	Serial.print(" voltage is ");
//  	Serial.print(Vbatteries[i]);
//  	Serial.print("mV (");
//  	Serial.print(Lbatteries[i]);
//  	Serial.println("%)");
//   
//  }
  while (Serial1.available() > 0) {   // 串口收到字符数大于零。
  //？打印电压、电量，在这里可以判断电量，
  //电量低于70%亮红灯，否则亮绿灯？需要额外的2个引脚，如果够用可以考虑。
  for(int i=0;i<12;i++){
    // 判断电压同时判断柜子状态、电池状态
    // 并将柜子的状态写入EEPROM中
    // 如果联网成功，则将状态上传服务器
//    if(! digitalRead(30+i*2)){
//            digitalWrite(30+i*2,HIGH);       // 点亮LED。
//            delay(1000);
//            digitalWrite(30+i*2,LOW); 
//            delay(1000);
//    }
    Serial1.print("Battery ");
    Serial1.print(i+1);
    Serial1.print(" voltage is ");
    Serial1.print(Vbatteries[i]);
    Serial1.print("mV (");
    Serial1.print(Lbatteries[i]);
    Serial1.println("%)");
   
  }
    
    p = Serial1.parseInt();           // 在串口数据流中查找一个有效整数。
    if (Serial1.read() == '$') {      // 收到结束符后开始处理数据。
 
      switch (p) {                   // 判断数据内容。
      case 1:
        digitalWrite(LOCKDIGITREADWRITE01,HIGH);       // 点亮LED。
        break;
      case 2:
        digitalWrite(LOCKDIGITREADWRITE02,HIGH);       // 点亮LED。
        break;
      case 3:
        digitalWrite(LOCKDIGITREADWRITE03,HIGH);       // 点亮LED。
        break;
      case 4:
        digitalWrite(LOCKDIGITREADWRITE04,HIGH);       // 点亮LED。
        break;
      case 5:
        digitalWrite(LOCKDIGITREADWRITE05,HIGH);       // 点亮LED。
        break;
      case 6:
        digitalWrite(LOCKDIGITREADWRITE06,HIGH);       // 点亮LED。
        break;
      case 7:
        digitalWrite(LOCKDIGITREADWRITE07,HIGH);       // 点亮LED。
        break;
      case 8:
        digitalWrite(LOCKDIGITREADWRITE08 ,HIGH);       // 点亮LED。
        break;
      case 9:
        digitalWrite(LOCKDIGITREADWRITE09,HIGH);       // 点亮LED。
        break;
      case 10:
        digitalWrite(LOCKDIGITREADWRITE10,HIGH);       // 点亮LED。
        break;
      case 11:
        digitalWrite(LOCKDIGITREADWRITE11,HIGH);       // 点亮LED。
        break;
      case 12:
        digitalWrite(LOCKDIGITREADWRITE12,HIGH);       // 点亮LED。
        break;
        
//      case 2:
//        digitalWrite(11,LOW);        // 熄灭LED。
//        
//        Serial.println(p);           // 回传数据。
//        break;
//      default:
//        p = map(p,0,100,0,255);      // 转换数据范围到PWM输出值。
//        analogWrite(11,p);           // 调整LED亮度。（PWM）
      }
    }
  }
  
}
