💰 ESP8266 Bitcoin Price Tracker Web Server
This project uses an ESP8266 microcontroller to fetch the latest Bitcoin price (in USD) from the CoinGecko API, convert it to INR, and display it on a simple web interface hosted directly on the ESP8266.

🌐 Features
📡 Connects to Wi-Fi using STA mode

🔄 Fetches real-time Bitcoin price using CoinGecko API

₹ Converts USD price to INR (based on a fixed exchange rate)

🖥️ Hosts a responsive HTML web page from ESP8266

🔁 "Refresh" button to get latest price

🧠 Built using Arduino JSON, ESP8266 WiFi and HTTP libraries

🛠️ Hardware Requirements
ESP8266-based board (e.g., NodeMCU, Wemos D1 Mini)

USB Cable

Internet connection

📦 Software Requirements
Arduino IDE with:

ESP8266 Board Support

ESP8266WiFi.h

ESP8266HTTPClient.h

ArduinoJson.h

📁 Project Structure
bash
Copy
Edit
ESP8266-Bitcoin-Tracker/
│
├── src/
│   └── main.ino      # Main Arduino code
│
├── README.md         # You're here!
⚙️ Setup Instructions
Clone this repository:

bash
Copy
Edit
git clone https://github.com/your-username/ESP8266-Bitcoin-Tracker.git
Open the main.ino file in Arduino IDE.

Edit your WiFi credentials:

cpp
Copy
Edit
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
Replace CoinGecko API endpoint:

cpp
Copy
Edit
const char* apiUrl = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";
Upload the sketch to your ESP8266 board.

Open Serial Monitor at 115200 baud to get the ESP8266's IP address.

Access the IP address in your browser to view the Bitcoin price dashboard.

📸 Preview
<img src="https://user-images.githubusercontent.com/your-screenshot-url/esp8266-bitcoin-ui.png" alt="ESP8266 Bitcoin Price UI" width="400"/>
🧠 Notes
The conversion from USD to INR uses a hardcoded rate (USD * 81). You can use a more dynamic method if needed.

The webpage refreshes manually through the "Refresh" button.

CoinGecko allows free API usage but has request rate limits.
