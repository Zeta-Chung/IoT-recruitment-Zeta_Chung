# 2025090908021-钟浩轩-IoT方向-第一期
## 学习笔记
### 面包板
* 两端连接电源正负极（红正蓝负），中间五个插孔互联互通，凹槽两侧孔不连通。  

* **注意**：  
  * 一定要形成闭合回路。    

  * 如果整块插入开发板，每一引脚所在行的其他插孔可看作引脚的延伸。
### BLink示例中的函数
- *pinMode()*：设置引脚的工作模式(输入INPUT/输出OUTPUT)  

- *digitalWrite()*：调节引脚的电压水平(HIGH/LOW)  

- *delay()*：使程序暂停执行一段时间(单位：ms)  

- **setup()**：外设配置，执行一次  

- **loop()**：主体，循环执行
### IP地址
* 作用：设备在网络中的位置（身份）标记，设备之间通过IP地址发送和接收数据包   

* ESP32在连接上手机热点后，会被分配一个局域网IP地址(IPv4)
### Web服务器
* 定义：某种驻留在因特网上的计算机程序，

* 功能：监听并响应用户的请求，存储、处理和传递网页给用户。传递内容一般是HTML文档、图像、样式表或脚本等，也可以放置网站文件以供浏览或下载  

* 严格来说Web服务器只负责处理Http协议请求，发送静态页面的内容
### HTTP协议
* 由**请求**和**响应**组成  

* GET请求：用户输入网址或点击连接后产生，请求获取服务器中指定的数据  

* URL
  * 统一资源定位器，通俗理解就是网址。  

  * 标准格式:  
  协议类型:[//服务器地址[:端口号]][/资源层级 UNIX 文件路径]文件名[?查询字符串][#片段标识符]  

  * URL中有些参数可以省略(服务器地址、端口号、资源层级 UNIX 文件路径、查询字符串、片段标识符)，文件名不能省略
* 响应：服务器找到所需资源并返回给用户

* 当Web浏览器访问网站时，服务器会根据不同的情况返回相应的HTTP状态码。这些状态码被划分为五个类别:  

  * 1xx: 成功接收请求，要求客户端继续提交下一次请求才能完成整个处理过程

  * 2xx: 成功接收请求并已完成整个处理过程。常用200

  * 3xx: 完成请求，客户需进一步细化请求

  * 4xx: 客户端的请求有错误，常用404和403（403含义是权限不够，服务器拒绝访问）

  * 5xx: 服务器端出现错误，常用500
### HTML基础
* HTML 文档由 HTML 标签以及文本内容组成。

* HTML 标签是由尖括号及包围的关键词组成，比如< html>。

* HTML 标签
  * 通常是成对出现的，标签对中的第一个标签是开始标签，第二个标签是结束标签。结束标签比开始标签多一个斜杠“/”。
  
  * < html> < /html>标签标识网页的开始和结尾，网页的结构处于两者之间。

  * < head>和< /head>标记头部， < body>和< /body>标记主体。

  * <!–内容–>为注释标签，用于在 HTML 插入注释。
  
  其他常用标签  
  |标记|作用|用法|位置|  
  | :--- | :--- | :--- |:--- |
  |title|页面标题，显示在浏览器选项卡中|< title>标题< /title>|头部|
  |h1-h6|文本标题，数字越大字体越小|< h1>标题< /h1>|主体|
  |p|段落，用于放置文本|< p>段落文本< /p>|主体|
  |button|按钮|< button>按钮< /button>|主体|
  |br|插入一个简单的换行符|< br>|主体|
  |a|向文本/图像/按钮类文本添加超链接|<a -href>="url">链接< /a>|主体|
  
* HTML 文档分为两个主要部分：头部和主体。

  * 头部包含有关 HTML 文档的属性数据，这些数据对最终用户不可见，但会向网页添加标题、脚本、样式甚至更多，这称为元数据。

  * 主体是包括类似文本、按钮、表格等页面内容。

### ESP32 WebServer库
|函数|作用|备注|
|:--|:--|:--|
|WebServer server()|创建WebServer对象|括号内填端口号，常用80|
|server.on("路径","函数")|用户访问路径时，调用函数|/|
|server.begin()|启动监听请求|/|
|server.handleClient()|处理来自客户端的请求|放在loop()中循环执行|
|server.send(状态码,响应内容类型,响应内容)|向客户端发送响应信息|后两个参数可为空|

## 实现过程
### 环境搭建
1. 在Arduino官网上找到并安装IDE  
2. CSDN上寻找ESP32管理器地址，添加到IDE中  
3. 官网上找到并安装CP2102转串口驱动器  
### 点亮第一盏灯
1. 数据线连接开发板与电脑  
2. 在Arduino中找到并连接开发板(ESP32 Dev Module)  
3. 打开文件-示例-Basics-Blink  
4. 修改引脚号，使其能匹配实际连接的引脚  
5. 选择上传，成功运行，板载LED开始闪烁  
6. 将开发板、电阻、发光二极管在面包板上连接，成功使外接LED开始闪烁
### 连接到互联网
1. 在B站上找到相关学习资源（关键词：物联网入门、ESP32 Arduino教程，并选择性学习相关知识（TCP/IP协议、串口通信、WiFi库函数）  
2. 在Arduino上编写代码，上传  
3. 打开手机热点显示esp32已连接，在串口监视器中成功打印出IP地址
### 构建Web遥控器
1. 在上一步找到的学习资源中学习WebServer库内容，并以WebServer示例中的HelloServer作参考  
2. 学习最基础的HTML知识以搭建网页  
3. 在面包板上连接开发板、LED与电阻 
4. 编写代码，上传至开发板  
5. 将开发板与手机连上同一热点，打印出IP地址  
6. 手机浏览器输入IP地址进入网页，点击网页中的开关按钮，实现LED的亮灭
## 遇到的问题和解决方法
|遇到的问题|原因分析|解决方法|
| :---: | :---:| :---:|
|开发板无法与Arduino连接|未正确安装驱动|将CH340改为CP2102|
|连接后无法编译Blink程序|示例程序中引脚号不匹配|将示例中LED_BUILTIN替换为2|
|外接LED的两引脚插在面包板同一行时，无法点亮|可能是LED被面包板内金属条短路|改为插在同一列不同行|
|串口监视器无法打印出IP地址|代码中不含等待WiFi连接部分，没连上便打印，自然没有IP地址|修改代码，增加判断WiFi是否连接的语句|
|浏览器输入IP地址后无法进入网页|配置网页的函数中没有send语句，无法响应|函数末尾加上server.send(200,"text/html",html);
## 最终代码
### 开发板连接WiFi
```c
#include<WiFi.h>

const char * ssid = "blablabla"; 
const char * password = "blablabla";


void setup()
{
  Serial.begin(115200);

  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);

  while(WiFi.status!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("connected");
  Serial.print("the IP is:");
  Serial.println(WiFi.localIP());
}

void loop()
{
//这次一定行
}
```
### 网页控制LED开关
```c
#include<WiFi.h>
#include<WebServer.h>

const char * ssid = "blablabla";
const char * password = "blablabla";

WebServer server(80);

const int led = 4;//设置引脚为GPIO4

void handleroot()//配置网页
{
  String html = "<html><body><h1>Control the LED!</h1>";
  html += "<p><a href = \"/on\"><button>ON</button></a></p>";
  html += "<p><a href = \"/off\"><button>OFF</button></a></p>";
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

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200);

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

  server.on("/",handleroot);//路径与函数建立关联
  server.on("/on",ledon);
  server.on("/off",ledoff);

  server.begin();//启动服务器
}

void loop() {
  server.handleClient();//持续处理请求
}

```

## 附加题猜想
使用互联网中的云服务器，当朋友发出请求后，数据包进入互联网，经过云服务器处理转入我的局域网，使开发板能接收请求数据并做出响应。
