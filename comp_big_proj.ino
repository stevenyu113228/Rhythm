#include <Wire.h> //三軸要用ㄉ
#include <Vector> //心跳要平均
#include <LBattery.h> //電池
#include <LGPS.h> //GPS
#include <LSD.h> //SD卡
#include <LAudio.h> //聲音

#include <LWiFi.h> // Wifi
#include <LWiFiClient.h> // Wifi

////////////////////////////////下面是Wifi
#define WIFI_AP "SuperPig"
#define WIFI_PASSWORD "11111111"
#define WIFI_AUTH LWIFI_WPA 
#define SITE_URL "140.118.170.37"

LWiFiClient c;
void Connect_to_AP()
{
    // keep retrying until connected to AP
    Serial.println("Connecting to AP");
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
    {
        Serial.println("rrrrrrrrrrr");
        delay(1000);
    }
}

void Connect_to_Website()
{
    Serial.println("Connecting to WebSite");
    while (0 == c.connect(SITE_URL, 8891))
    {
        Serial.println("Re-Connecting to WebSite");
        delay(100);
    }
    Serial.println("Connect done");
}


void Send_request(String payload)
{
  
    char str[1000];
    // String payload = "heart=" + String(heart) + "&"
    // + "step=" + String(step) + "&"
    // + "battery=" + String(battery) + "&"
    // + "charging=" + String((int)charging) + "&"
    // + "latitude=" + String(latitude)+ "&"
    // + "longitude=" + String(longitude)+ "&"
    // + "height=" + String(height);

//    sprintf(str, "heart=%d&step=%d&battery=%d&charging=%d&latitude=%lf&longitude=%lf&height=%lf", heart, step, battery, charging, latitude, longitude, height);
//    String payload = str;
    Serial.println(payload);
    int content_len = payload.length();

    // send HTTP request, ends with 2 CR/LF
    Serial.println("send HTTP POST request");
    c.println("POST /post_data HTTP/1.1");
    c.println("Host: " SITE_URL);
    c.println("Content-Type: application/x-www-form-urlencoded");
    c.println("content-length: " + String(content_len));
    c.println("Connection: close");
    c.println("\n" + payload);
    c.println();
}


void Waiting_for_response()
{
    String response = "";
    Serial.println("waiting HTTP response:");
    while (!c.available())
    {
        delay(10);
    }

    while (c)
    {
        int v = c.read();
        if (v != -1)
        {
            // Serial.print((char)v);
            response += (char)v;
        }
        else
        {
            Serial.println("no more content, disconnect");
            c.stop();
        }
    }
    Serial.print(response + '\n');
}




////////////////////////////////下面是聲音

unsigned char vol = 6; // 音量，0到6（最大聲） 
boolean soft = 1;

// 此函式可取得下一首歌曲的路徑，如果副檔名是.mp3的話
String get_next(){
  /*
  LFile f = dir.openNextFile(FILE_READ);
  String song = String("\\mp3\\hard\\") + f.name();
  
  while(!song.endsWith(String(".mp3")) || f.name()[0] == '.'){
    f.close();
    f = dir.openNextFile(FILE_READ);
    song = String("\\mp3\\hard\\") + f.name();
    
  }
  f.close();*/
  String song;
  if(soft == 0){
      song = String("\\mp3\\hard\\") + String(random(1,4)) + ".mp3";
  }else{
      song = String("\\mp3\\soft\\") + String(random(1,4)) + ".mp3";
  }
  return song;
}

void change_style(){
  String song;
        soft = !soft;
        song = get_next();
        LAudio.playFile(storageSD, (char *)song.c_str());
        Serial.println(song.c_str());

}

////////////////////////////////下面是SD卡讀寫資料
void write_data(String s){
  LFile f;
  f = LSD.open("data.txt",FILE_WRITE);
  f.write(s.c_str());
  f.close();
}

String read_data(){
  String s;
  LFile f;
  f = LSD.open("data.txt",FILE_READ);
  while(f.available()){
    s += (char)f.read();
  }
  f.close();
  return s;
}

void delete_data(){
  LSD.remove("data.txt");
}

////////////////////////////////下面是GPS
gpsSentenceInfoStruct info;

static unsigned char getComma(unsigned char num, const char *str)
{
  unsigned char i, j = 0;
  int len = strlen(str);
  for (i = 0; i < len; i++)
  {
    if (str[i] == ',')
      j++;
    if (j == num)
      return i + 1;
  }
  return 0;
}

static double getDoubleNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;

  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev = atof(buf);
  return rev;
}

static double getIntNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;

  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev = atoi(buf);
  return rev;
}


void parseGPGGA(const char *GPGGAstr, double &latitude, double &longitude, double &height, int &hour, int &minute, int &second, int &num)
{
  /* Refer to http://www.gpsinformation.org/dale/nmea.htm#GGA
   * Sample data: $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
   * Where:
   *  GGA          Global Positioning System Fix Data 
   *  123519       Fix taken at 12:35:19 UTC
   *  4807.038,N   Latitude 48 deg 07.038' N
   *  01131.000,E  Longitude 11 deg 31.000' E
   *  1            Fix quality: 0 = invalid
   *                            1 = GPS fix (SPS)
   *                            2 = DGPS fix
   *                            3 = PPS fix
   *                            4 = Real Time Kinematic
   *                            5 = Float RTK
   *                            6 = estimated (dead reckoning) (2.3 feature)
   *                            7 = Manual input mode
   *                            8 = Simulation mode
   *  08           Number of satellites being tracked
   *  0.9          Horizontal dilution of position
   *  545.4,M      Altitude, Meters, above mean sea level
   *  46.9,M       Height of geoid (mean sea level) above WGS84
   *                   ellipsoid
   *  (empty field) time in seconds since last DGPS update
   *  (empty field) DGPS station ID number
   *  *47          the checksum data, always begins with *
   */
  //  double latitude;
  //  double longitude;
  int tmp;

  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(1, GPGGAstr);
    hour = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');
    minute = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');
    second = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');

    //    sprintf(buff, "UTC timer %2d-%2d-%2d", hour, minute, second);
    //    Serial.println(buff);

    tmp = getComma(2, GPGGAstr);
    latitude = getDoubleNumber(&GPGGAstr[tmp]) / 100.0;
    int latitude_int = floor(latitude);
    double latitude_decimal = (latitude - latitude_int) * 100.0 / 60.0;
    latitude = latitude_int + latitude_decimal;
    tmp = getComma(4, GPGGAstr);
    longitude = getDoubleNumber(&GPGGAstr[tmp]) / 100.0;
    int longitude_int = floor(longitude);
    double longitude_decimal = (longitude - longitude_int) * 100.0 / 60.0;
    longitude = longitude_int + longitude_decimal;

    //    sprintf(buff, "latitude = %10.4f, longitude = %10.4f", latitude, longitude);
    //    Serial.println(buff);
    //
    tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);
    //    sprintf(buff, "satellites number = %d", num);
    tmp = getComma(11, GPGGAstr);
    height = getDoubleNumber(&GPGGAstr[tmp]);

    //    Serial.println("Height = " + String(height));
    //
    //    Serial.println(buff);
  }
  //  else
  //  {
  //    Serial.println("Not get data");
  //  }
}




////////////////////////////////下面是三軸

int I2C_Address = 0xA7 >> 1; // ADXL345 的 I2C 地址
/* setReg(reg,data)：寫入佔存器
   參數：
       reg → 指定佔存器位址
       data → 要寫入的資料
*/
void setReg(int reg, int data)
{
  Wire.beginTransmission(I2C_Address);
  Wire.write(reg);  // 指定佔存器
  Wire.write(data); // 寫入資料
  Wire.endTransmission();
}

/* getData(reg)：取得佔存器裡的資料
   參數：reg → 佔存器位址
*/
int getData(int reg)
{
  Wire.beginTransmission(I2C_Address);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(I2C_Address, 1);

  if (Wire.available() <= 1)
  {
    return Wire.read();
  }
}



int16_t X_log[3] = {0, 0, 0}, Y_log[3] = {0, 0, 0}, Z_log[3] = {0, 0, 0};

unsigned int getAcc()
{
  int16_t X0, X1, Y0, Y1, Z1, Z0;
  int16_t X, Y, Z;

  X0 = getData(0x32); // 取得 X 軸 低位元資料
  X1 = getData(0x33); // 取得 X 軸 高位元資料
  X = ((X1 << 8) | X0);

  Y0 = getData(0x34); // 取得 Y 軸 低位元資料
  Y1 = getData(0x35); // 取得 Y 軸 高位元資料
  Y = ((Y1 << 8) | Y0);

  Z0 = getData(0x36); // 取得 Z 軸 低位元資料
  Z1 = getData(0x37); // 取得 Y 軸 高位元資料
  Z = ((Z1 << 8) | Z0);

  for (uint8_t i = 0; i < 2; i++) // 0.9
  {
    X_log[i] = X_log[i + 1] * 0.9;
    Y_log[i] = Y_log[i + 1] * 0.9;
    Z_log[i] = Z_log[i + 1] * 0.9;
  }
  X_log[2] = X;
  Y_log[2] = Y;
  Z_log[2] = Z;

  X = (X_log[0] + X_log[1] + X_log[2]) / 3;
  Y = (Y_log[0] + Y_log[1] + Y_log[2]) / 3;
  Z = (Z_log[0] + Z_log[1] + Z_log[2]) / 3;

  unsigned int deltaX = abs(X_log[1] - X);
  unsigned int deltaY = abs(Y_log[1] - Y);
  unsigned int deltaZ = abs(Z_log[1] - Z);
  unsigned int total_delta = deltaX + deltaY + deltaZ;

  return total_delta;
}






////////////////////////////////下面是心跳
float data[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// 心跳用20點ㄉFIR Filter

float log_data[3] = {0, 0, 0};
// 記錄最近三點ㄉ濾波後資料

unsigned int uptime;
// 上升時間
unsigned int delta_time[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// 紀錄最近10筆心跳資料

std::vector<uint8_t> heart_log;

uint8_t get_heart() {
  double tmp = 0;
  uint8_t ti;
  for (int i = 0; i < 19; i++) {
    data[i] = data[i + 1] * 0.9;
    tmp += data[i];
  }
  // 推移 + 紀錄資料

  data[19] = analogRead(A1);
  //放入新資料

  tmp += data[19];
  tmp /= 20;
  //平均

  log_data[0] = log_data[1];
  log_data[1] = log_data[2];
  log_data[2] = tmp;
  // 推移最新三筆資料

  if (log_data[0] <= log_data[1] && log_data[1] >= log_data[2]) {
    // 找波峰 記錄時間
    digitalWrite(10, 1);
    uptime = millis();
  } else if (log_data[0] >= log_data[1] && log_data[1] <= log_data[2]) {
    // 找波谷

    digitalWrite(10, 0);
    unsigned int t = 0;

    if (millis() - uptime > 250) {
      // 心跳<250毫秒是不合理ㄉ 過濾掉
      for (int i = 0; i < 9; i++) {
        delta_time[i] = delta_time[i + 1];
        t += delta_time[i];
      }
      // 最新ㄉ10筆資料，累加+推移

      delta_time[9] = millis() - uptime;
      t += delta_time[9];
      t /= 10;
      ti = 30000 / t;
      // 半波時間，所以週期/2
      
      heart_log.push_back(ti);
      Serial.println(ti);
    }
  }
  return ti;
}




/////////////////////////主程式

void setup() {
  pinMode(A1, INPUT);  // 感測心跳ㄉ腳
  pinMode(10, OUTPUT); // 感測 
  Serial.begin(9600);

  Wire.begin(); // 三軸要用ㄉ
  setReg(0x2D, 0xA);//三軸要用ㄉ+1

  LSD.begin();
  LGPS.powerOn();
  LWiFi.begin();

  
  randomSeed(analogRead(A0)); //聲音需要一個rand放音樂
  LAudio.begin(); // 初始化聲音
  LAudio.setVolume(vol); // 設定音量

  
  if(LBattery.isCharging() == 0){ // 沒有在充電ㄉ話
  String song = get_next();
  LAudio.playFile(storageSD, (char *)song.c_str());
  Serial.println(song.c_str());
  }else{ //有在充電
    Connect_to_AP();
    

    // 處理讀取ㄉ東西
    String d = read_data();

    int start_  = 0;
    int end_  = d.indexOf("\n");
    while(end_ != -1){
      
      String payload = d.substring(start_, end_);

      
       start_ = end_ + 1;
       end_ = d.indexOf("\n", start_);
//       Serial.println(start_);
//       Serial.println(end_);
//       Serial.println(payload);
//      
      Connect_to_Website();
      Send_request(payload);
      Waiting_for_response();
    }

    delete_data();
  }
  
}


unsigned int get_heart_timer;


int step_count = 0;
unsigned int acc;
uint8_t heart;


double lat, lon, height;
int hour, minute, second, s_num;





unsigned int step_timer;
unsigned int get_acc_timer;
unsigned int write_data_timer;
unsigned int get_gps_timer;
void loop() {


if(LBattery.isCharging() == 0){
  // 取得GPS
  if(millis() - get_gps_timer > 3000){
    LGPS.getData(&info);
    parseGPGGA((const char *)info.GPGGA, lat, lon, height, hour, minute, second, s_num);
    if (s_num < 1)
        { // 沒訊號要防呆，不然程式碼會爆炸
            lon = 0;
            lat = 0;
            height = 0;
        }
  }

  
  // 心跳
  if (millis() - get_heart_timer > 10) {
    heart = get_heart();
//    heart_log.push_back(heart); 
    get_heart_timer = millis();
  }

  // 取得加速度
  if (millis() - get_acc_timer > 100) {
    acc = getAcc();
    get_acc_timer = millis();
  }


  // 計算步數
  if (acc > 150 && millis() - step_timer > 500)
  {
    Serial.println(++step_count);
    step_timer = millis();
  }

   
  if(millis()>10000 && millis()-write_data_timer > 10000){ //寫入資料
      char d[1000];
      float heart_average = 0;
      
      for(int i=0;i<heart_log.size();i++){
        heart_average += ((float)(heart_log[i]) / heart_log.size());
      }

      // 有時候會判斷不到，就先break
      if(heart_log.size() == 0){
        heart_average = 87;
      }

      
      sprintf(d,"heart=%f&step=%d&battery=%d&charging=%d&latitude=%lf&longitude=%lf&height=%lf&h=%d&m=%d&s=%d&s_num=%d\n",
                heart_average,step_count,LBattery.level(),LBattery.isCharging(),
                lat,lon,height,hour,minute,second,s_num
                );
      Serial.println(d);
      String str = String(d);
      write_data(d);

      
      if(heart_average > 100 || step_count > 15){ // 心跳>100 || 10秒內走超過15步
        //hard
        if(soft == 1){
          change_style();
        }
      }else{
        //soft
        if (soft == 0){
          change_style();
        }
      }
      
      heart_log.clear();
      step_count = 0;
      write_data_timer = millis();
  }
}
}