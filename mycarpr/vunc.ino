

 void RMGO() { 
digitalWrite (EN3,HIGH);
digitalWrite (EN4,LOW);
}
void LMGO() { 
digitalWrite (EN1,LOW);
digitalWrite (EN2,HIGH );
}
void LMBACK() { 
digitalWrite (EN1,HIGH);
digitalWrite (EN2,LOW);
}
void RMBACK() { 
digitalWrite (EN3,LOW);
digitalWrite (EN4,HIGH);
}

void stopmotor() {  
digitalWrite (EN1,LOW);digitalWrite (EN2,LOW);
digitalWrite (EN3,LOW);digitalWrite (EN4,LOW);
}

void forwardmotor(){

RMGO();
LMBACK();
}  
void rightmotor(){
LMBACK();RMBACK();
}

void leftmotor(){
LMGO();RMGO();
}

void backmotor(){
 LMGO(); RMBACK();
}



int vHC_SR04() {
digitalWrite(A1, HIGH); // Подаем сигнал на выход микроконтроллера
delayMicroseconds(10); // Удерживаем 10 микросекунд
digitalWrite(A1, LOW); // Затем убираем
int vtime_us=pulseIn(A0, HIGH); // Замеряем длину импульса
int vdistance_sm=vtime_us/58; // Пересчитываем в сантиметры
return vdistance_sm; // Возвращаем значение
}


const int vmindistance = 30;
const int myservo_array[13]={0,15,30,45,60,75,90,105,120,135,150,165,180};
int disarr[13];
int vmaxarrayindex_int;
int vmaxarrayvalue_int;

void sensor(){
myservo.write(pos);  
delay(200);
 if (vHC_SR04() < vmindistance) {
// Останавливаем двигатели
stopmotor();
for (int i = 0; i < 13; i++) {
myservo.write(myservo_array[i]);
delay(200);
disarr[i] = vHC_SR04();
}

// Поиск в массиве позиции с максимальным значением
vmaxarrayindex_int = 0;
vmaxarrayvalue_int = 0;
for (int i = 0; i < 13; i++) {
if (disarr[i] > vmaxarrayvalue_int) {
vmaxarrayindex_int = i;
vmaxarrayvalue_int = disarr[i];
}

}


// Проверка - если максимальное значение массива меньше минимального расстояния, то едем назад
if (disarr[vmaxarrayindex_int] < vmindistance) {
backmotor();
delay(500);
}
 /*Проверка - если индекс максимального значения массива меньше 6 то поворачиваем вправо,
иначе влево */

if (vmaxarrayindex_int < 6) {
rightmotor();
delay(500);
}
else
{ 
leftmotor();
delay(500);

}

  }
else
{
  forwardmotor();
delay(500);
}}


  
void bluetoohsensor(){
   if (mySerial.available() > 0) { //если в буфере программного серийного порта есть данные

  int  command = mySerial.read();     //считываем их и запоминаем комманду
  Serial.println(command);       //выводим команду в монитор порта (используется для отладки)
  
switch(command){
case 70:{forwardmotor();break;}//вперед
//76-вперед 70-назад 66-налево
case 66:{backmotor();break;} //назад   
case 76:{leftmotor();break; } // налево  +
case 82:{rightmotor();break;}  // направо    +     
case 83:{
  stopmotor();break;
};}}
  
 }
