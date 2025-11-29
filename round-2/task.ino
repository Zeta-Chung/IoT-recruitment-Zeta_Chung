#include<WiFi.h>
#include<WebServer.h>
#include<DHT11.h> 
#include<HTTPClient.h>

DHT11 dht11(2);

const char * ssid = "XXX";
const char * password = "XXX";

WebServer server(80);

const int led = 4;//设置引脚为GPIO4

const unsigned long interval_re = 2000;//读取数据的时间间隔
const unsigned long interval_wr = 5000;//打印数据的时间间隔
unsigned long previoustime_dhtread = 0;
unsigned long previoustime_dhtwrite = 0;
int temp,humid;

const unsigned long interval_http = 30000;
unsigned long previoustime_http = 0;

void handleroot()//配置网页
{
  String html = "<html><body><h1>Control the LED!</h1>";
  html += "<p><a href = \"/on\"><button>ON</button></a></p>";
  html += "<p><a href = \"/off\"><button>OFF</button></a></p>";
  html += "<p><a href = \"/json\"><button>Status</button></a></p>";
  html += "</body></html>";
  server.send(200,"text/html",html);
}

void ledon()//开灯
{
  digitalWrite(led,HIGH);
  server.send(200,"The LED is ON");
}

void ledoff()//关灯
{
  digitalWrite(led,LOW);
  server.send(200,"The LED is OFF");
}

void json()
{ 
  int pinmode = digitalRead(4);
  String ledstate;
  if(pinmode == HIGH)
  {ledstate = "\"ON\"";}
  else
  {ledstate = "\"OFF\"";}

  String json = "{";
  json += "\"温度\":" + String(temp) + "°C,";
  json += "\"湿度\":" + String(humid) + "%,";
  json += "\"pinmode\":" + ledstate + "}";
  server.send(200,"application/json",json);
}
void Webprocess()
{
  server.on("/",handleroot);//路径与函数建立关联
  server.on("/on",ledon);
  server.on("/off",ledoff);
  server.on("/json",json);

  server.begin();//启动服务器
}

void Wifiprocess()
{
  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)//等待WiFi连接
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.println("connected");
  Serial.print("the IP is:");
  Serial.println(WiFi.localIP());//打印出IP地址
}

void httpprocess(int temp,int humid)
{ 
  String url = "https://api.thingspeak.com/update?api_key=3ABCV0OOLV6W54UF";
  url += "&field1=" + String(temp);
  url += "&field2=" + String(humid);
  HTTPClient http;
  http.begin(url);
  http.GET();
  http.end();
}
void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200);  
  Wifiprocess();
  Webprocess();
}

void loop() {
  server.handleClient();//ESP32服务器持续处理请求
  unsigned long currenttime = millis();

  if(currenttime-previoustime_dhtread >= interval_re)
  {
    dht11.readTemperatureHumidity(temp,humid);
    previoustime_dhtread = currenttime;
  }
  if(currenttime-previoustime_dhtwrite >= interval_wr)
  {
    Serial.print("humidity:");
    Serial.print(humid);
    Serial.println("%");
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.println("°C");
    previoustime_dhtwrite = currenttime;
  }
  if(currenttime-previoustime_http >= interval_http)
  {
    httpprocess(temp,humid);
    previoustime_http = currenttime;
  }
}
