#include <Battery.h>

//定义12块电池的电压范围和采集口
Battery battery1(7200, 8400, A0);
Battery battery2(7200, 8400, A1);
Battery battery3(7200, 8400, A2);
Battery battery4(7200, 8400, A3);
Battery battery5(7200, 8400, A4);
Battery battery6(7200, 8400, A5);
Battery battery7(7200, 8400, A6);
Battery battery8(7200, 8400, A7);
Battery battery9(7200, 8400, A8);
Battery battery10(7200, 8400, A9);
Battery battery11(7200, 8400, A10);
Battery battery12(7200, 8400, A11);

//存放电池电压mv
int Vbatteries[12];
//存放电池剩余电量水平%
int Lbatteries[12];

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
	float ratio = (33 + 10) / 10;
	// 5V board, change to 3300 for a 3.3V board
  //启动电池电压采集
  battery1.begin(5000, ratio);
  battery2.begin(5000, ratio);
  battery3.begin(5000, ratio);
  battery4.begin(5000, ratio);
  battery5.begin(5000, ratio);
  battery6.begin(5000, ratio);
  battery7.begin(5000, ratio);
  battery8.begin(5000, ratio);
  battery9.begin(5000, ratio);
  battery10.begin(5000, ratio);
  battery11.begin(5000, ratio);
  battery12.begin(5000, ratio);
  
}

void loop() {
	digitalWrite(13, HIGH);
	delay(500);
	delay(500);

  //采集电压存入全局数组
  Vbatteries[0]=battery1.voltage();
  Lbatteries[0]=battery1.level();
  Vbatteries[1]=battery2.voltage();
  Lbatteries[1]=battery2.level();
  Vbatteries[2]=battery3.voltage();
  Lbatteries[2]=battery3.level();
  Vbatteries[3]=battery4.voltage();
  Lbatteries[3]=battery4.level();
  Vbatteries[4]=battery5.voltage();
  Lbatteries[4]=battery5.level();
  Vbatteries[5]=battery6.voltage();
  Lbatteries[5]=battery6.level();
  Vbatteries[6]=battery7.voltage();
  Lbatteries[6]=battery7.level();
  Vbatteries[7]=battery8.voltage();
  Lbatteries[7]=battery8.level();
  Vbatteries[8]=battery9.voltage();
  Lbatteries[8]=battery9.level();
  Vbatteries[9]=battery10.voltage();
  Lbatteries[9]=battery10.level();
  Vbatteries[10]=battery11.voltage();
  Lbatteries[10]=battery11.level();
  Vbatteries[11]=battery12.voltage();
  Lbatteries[11]=battery12.level();

  //？打印电压、电量，在这里可以判断电量，
  //电量低于70%亮红灯，否则亮绿灯？需要额外的2个引脚，如果够用可以考虑。
  for(int i=0;i<12;i++){
  	Serial.print("Battery voltage is ");
  	Serial.print(Vbatteries[i]);
  	Serial.print("mV (");
  	Serial.print(Lbatteries[i]);
  	Serial.println("%)");
  }
}
