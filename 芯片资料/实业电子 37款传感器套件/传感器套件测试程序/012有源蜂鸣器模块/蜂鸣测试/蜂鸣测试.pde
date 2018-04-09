int buzzer=11;//设置控制蜂鸣器的数字IO脚
void setup()
{
 pinMode(buzzer,OUTPUT);//设置数字IO脚模式，OUTPUT为输出
}
void loop()
{
 unsigned char i,j;//定义变量
 while(1)
 {
for(i=0;i<80;i++)//输出一个频率的声音
 {
  digitalWrite(buzzer,HIGH);//发声音
    delay(1);//延时1ms
  digitalWrite(buzzer,LOW);//不发声音
 delay(1);//延时ms
  }
   for(i=0;i<500;i++)//输出另一个频率的声音
    {
      digitalWrite(buzzer,HIGH);//发声音
      delay(2);//延时2ms
      digitalWrite(buzzer,LOW);//不发声音
      delay(2);//延时2ms
    }
  }
} 



