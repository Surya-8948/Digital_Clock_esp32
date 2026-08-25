/*******************************************************
 | MAX7219 Pin | ESP32 Pin     |
| ----------- | -------------- |
| VCC         | 5V (VIN)       |
| GND         | GND            |
| DIN         | GPIO 23 (MOSI) |
| CS (LOAD)   | GPIO 5         |
| CLK         | GPIO 18 (SCK)  |

*******************************************************/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <DHT.h>
#include <WebServer.h>

/************** WiFi **************/
char ssid[] = "Vimal";
char pass[] = "1234567890";

/************** Matrix config **************/
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5
MD_Parola matrix = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

/************** DHT Sensor **************/
DHT dht(4, DHT11);
float lastTemp = 0;

/************** NTP Clock **************/
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);

unsigned long lastTick = 0;
bool calibrated = false;
bool printedIP = false;

int hr_, min_, sec_, day_, month_, year_, wday_;

/************** Quote via Web **************/
String quoteMsg = "Warmest congratulations on your wedding Sir - Mr. & Mrs. Singh! Wishing you both a lifetime filled with love, happiness, and beautiful moments together.— From me & the entire Mt team....";
WebServer server(80);

/************** Message Engine **************/
String msgs[20];
int reps[20];
int totalMsgs = 0;

int mIndex = 0;
int currentRepeat = 0;

bool makerShown = false;

/************** Utility **************/
String weekdayName[] = { "", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

String greeting() {
  if (hr_ < 4) return "Good Night";
  if (hr_ < 11) return "Good Morning";
  if (hr_ < 14) return "Good Noon";
  if (hr_ < 18) return "Good Afternoon";
  return "Good Evening";
}

String tf12() {
  int h12 = hr_ % 12;
  if (h12 == 0) h12 = 12;

  char buf[20];
  sprintf(buf, "%02d:%02d:%02d %s",
          h12, min_, sec_, (hr_ >= 12 ? "PM" : "AM"));
  return String(buf);
}

/************** Update NTP **************/
void updateClock() {
  if (timeClient.update()) {
    unsigned long ep = timeClient.getEpochTime();
    hr_ = hour(ep);
    min_ = minute(ep);
    sec_ = second(ep);
    day_ = day(ep);
    month_ = month(ep);
    year_ = year(ep);
    wday_ = weekday(ep);

    calibrated = true;
    lastTick = millis();
  }
}

/************** Offline tick **************/
void offlineTick() {
  if (millis() - lastTick >= 1000) {
    lastTick += 1000;
    sec_++;
    if (sec_ >= 60) { sec_ = 0; min_++; }
    if (min_ >= 60) { min_ = 0; hr_++; }
    if (hr_ >= 24) { hr_ = 0; }
  }
}

/************** BUILD QUEUE **************/
void buildQueue() {
  totalMsgs = 0;

  if (!calibrated) {
    msgs[totalMsgs] = "Connect WiFi To Calibrate Time And Other Funnctions once when Power is turned ON Thanks ...";
    reps[totalMsgs++] = 1;
    return;
  }

  msgs[totalMsgs] = greeting();
  reps[totalMsgs++] = 1;

  msgs[totalMsgs] = "Time " + tf12();
  reps[totalMsgs++] = 3;

  char d[20];
  sprintf(d, "%02d-%02d-%04d", day_, month_, year_);
  msgs[totalMsgs] = "Date " + String(d);
  reps[totalMsgs++] = 2;

  msgs[totalMsgs] = "Day " + weekdayName[wday_];
  reps[totalMsgs++] = 1;

  msgs[totalMsgs] = "Temp " + String((int)lastTemp) + "C";
  reps[totalMsgs++] = 1;

  msgs[totalMsgs] = "Quote: " + quoteMsg;
  reps[totalMsgs++] = 1;

  msgs[totalMsgs] = (WiFi.status() == WL_CONNECTED) ? "WiFi OK" : "WiFi OFF";
  reps[totalMsgs++] = 1;
}

/****************** NEW DASHBOARD UI HERE ******************/
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>ESP32 Dashboard</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<style>
:root {
  --bg: #050816;
  --card: #0f172a;
  --accent: #3b82f6;
  --accent-soft: rgba(59,130,246,0.15);
  --text: #e5e7eb;
  --muted: #9ca3af;
  --danger: #f97373;
  --success: #4ade80;
  --border: #1f2937;
  --preview-bg: #020617;
  --preview-led: #22c55e;
}

body {
  background: radial-gradient(circle at top, #1d2540 0, #020617 55%);
  font-family: Arial;
  color: var(--text);
  padding: 20px;
}

.app {
  max-width: 900px;
  margin: auto;
}

.tabs {
  display: flex;
  gap: 8px;
  margin-bottom: 16px;
}

.tab-btn {
  flex: 1;
  padding: 10px;
  background: #020617aa;
  border-radius: 25px;
  border: none;
  color: var(--muted);
  cursor: pointer;
}

.tab-btn.active {
  background: var(--accent);
  color: white;
  font-weight: 700;
}

.panel { display: none; }
.panel.active { display: block; }

.card {
  background: #0b1020;
  padding: 14px;
  border-radius: 12px;
  margin-bottom: 14px;
}

.preview-frame {
  background: #000;
  height: 45px;
  padding: 10px;
  border-radius: 8px;
  overflow: hidden;
}

.preview-text {
  color: var(--preview-led);
  white-space: nowrap;
  font-family: monospace;
  animation: scrollText 15s linear infinite;
}

@keyframes scrollText {
  from { transform: translateX(100%); }
  to { transform: translateX(-200%); }
}

textarea {
  width: 100%;
  height: 100px;
  border-radius: 8px;
}

button {
  width: 100%;
  margin-top: 10px;
  padding: 12px;
  background: var(--accent);
  border: none;
  border-radius: 8px;
  color: white;
  font-size: 16px;
}
</style>
</head>

<body>
<div class="app">

<h2>ESP32 MATRIX CLOCK DASHBOARD</h2>

<div class="tabs">
  <button class="tab-btn active" onclick="showTab('home')">Home</button>
  <button class="tab-btn" onclick="showTab('quote')">Quote</button>
  <button class="tab-btn" onclick="showTab('settings')">Settings</button>
</div>

<!-- HOME -->
<div id="home" class="panel active">
  <div class="card">
    <h3>Status</h3>
    <p><b>IP:</b> %IP%</p>
    <p><b>WiFi:</b> %WIFI%</p>
    <p><b>Temperature:</b> %TEMP%C</p>

    <p><b>Browser Time:</b></p>
    <h2 id="clock">--:--:--</h2>
  </div>

  <div class="card">
    <h3>Live Matrix Preview</h3>
    <div class="preview-frame">
      <span id="preview" class="preview-text">%QUOTE%</span>
    </div>
  </div>
</div>

<!-- QUOTE -->
<div id="quote" class="panel">
  <div class="card">
    <h3>Update Quote</h3>
    <form action="/quote" method="GET">
      <textarea name="msg">%QUOTE%</textarea>
      <button type="submit">Update Quote</button>
    </form>
  </div>
</div>

<!-- SETTINGS -->
<div id="settings" class="panel">
  <div class="card">
    <h3>Settings</h3>
    <p>Coming Soon...</p>
  </div>
</div>

</div>

<script>
function showTab(id){
  document.querySelectorAll('.panel').forEach(p=>p.classList.remove('active'));
  document.getElementById(id).classList.add('active');

  document.querySelectorAll('.tab-btn').forEach(b=>b.classList.remove('active'));
  event.target.classList.add('active');
}

function updateClock(){
  const d = new Date();
  document.getElementById('clock').innerText =
    d.toLocaleTimeString();
}
setInterval(updateClock, 1000);
</script>

</body>
</html>
)rawliteral";

  ///====== Replace values ======///
  html.replace("%IP%", WiFi.localIP().toString());
  html.replace("%WIFI%", (WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected"));
  html.replace("%TEMP%", String((int)lastTemp));
  html.replace("%QUOTE%", quoteMsg);

  server.send(200, "text/html", html);
}

/***************** Quote update *****************/
void handleQuote() {
  if (server.hasArg("msg")) {
    quoteMsg = server.arg("msg");
    buildQueue();
    server.send(200, "text/plain", "Quote Updated!");
  } else {
    server.send(400, "text/plain", "Missing msg");
  }
}

/************** SETUP **************/
void setup() {
  Serial.begin(115200);

  matrix.begin();
  matrix.setIntensity(3);
  matrix.displayClear();

  dht.begin();
  WiFi.begin(ssid, pass);
  timeClient.begin();

  server.on("/", handleRoot);
  server.on("/quote", handleQuote);
  server.begin();

  delay(200);

  matrix.displayText("Developed At- Mecatredz Softwares And Innovations Pvt Ltd Lucknow By - Surya Mani Bajpai & Mt Team ..",
                     PA_LEFT, 40, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  makerShown = true;
}

/************** LOOP **************/
void loop() {
  server.handleClient();

  if (WiFi.status() == WL_CONNECTED) {
    if (!printedIP) {
      char ipMsg[30];
      sprintf(ipMsg, "IP %s", WiFi.localIP().toString().c_str());
      matrix.displayText(ipMsg, PA_LEFT, 40, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      printedIP = true;
      delay(1500);
      buildQueue();
    }
    updateClock();
  } else {
    printedIP = false;
  }

  offlineTick();

  float t = dht.readTemperature();
  if (!isnan(t)) lastTemp = t;

  if (matrix.displayAnimate()) {
    currentRepeat++;

    if (currentRepeat >= reps[mIndex]) {
      currentRepeat = 0;
      mIndex++;
      if (mIndex >= totalMsgs) {
        buildQueue();
        mIndex = 0;
      }
    }

    matrix.displayText(msgs[mIndex].c_str(),
                       PA_LEFT, 40, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}
