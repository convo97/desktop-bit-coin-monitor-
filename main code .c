#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Credentials (STA Mode)
const char* ssid = ""; // Replace with your WiFi SSID
const char* password = ""; // Replace with your WiFi password

// CoinGecko API URL
const char* apiUrl = "YOUR API";

// Web Server
WiFiServer server(80);
String btcPrice = "Fetching...";

// Function to fetch Bitcoin data
void fetchBitcoinData() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected. Skipping API request.");
        return;
    }

    WiFiClient client;
    HTTPClient http;

    http.begin(client, apiUrl); // Use WiFiClient for ESP8266
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println(payload);

        DynamicJsonDocument doc(512);
        deserializeJson(doc, payload);
        
        float price = doc["bitcoin"]["usd"];
        price = price * 81; // Convert USD to INR (example conversion rate)
        btcPrice = "Bitcoin: INR " + String(price);
    } else {
        btcPrice = "Failed to fetch Bitcoin price.";
    }

    http.end();
}

// Function to return HTML for the Webserver
String getHTML() {
    return String(
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE html>"
        "<html lang='en'>"
        "<head>"
        "<meta charset='UTF-8'>"
        "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
        "<title>ESP8266 Bitcoin Price</title>"
        "<style>"
        "body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding: 20px; }"
        ".container { max-width: 400px; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); margin: auto; }"
        "h1 { color: #007bff; font-size: 24px; }"
        ".btc-price { font-size: 18px; margin: 15px 0; padding: 10px; background: #eee; border-radius: 8px; }"
        ".refresh-btn { background: #007bff; color: white; border: none; padding: 10px 20px; font-size: 16px; border-radius: 5px; cursor: pointer; }"
        ".refresh-btn:hover { background: #0056b3; }"
        "</style>"
        "</head>"
        "<body>"
        "<div class='container'>"
        "<h1>Bitcoin Price</h1>"
        "<div class='btc-price'>" + btcPrice + "</div>"
        "<button class='refresh-btn' onclick='window.location.reload();'>Refresh</button>"
        "</div>"
        "</body>"
        "</html>"
    );
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi (STA Mode)
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    int retries = 30;
    while (WiFi.status() != WL_CONNECTED && retries-- > 0) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWiFi Connection Failed!");
    }

    // Start Web Server
    server.begin();
    
    fetchBitcoinData();  // Initial API Call
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("New Client Connected!");
        while (client.available()) {
            client.readStringUntil('\r');
        }
        client.print(getHTML()); // Serve the HTML page
        client.stop();

        fetchBitcoinData(); // Update Bitcoin Data on Request
    }

    delay(60000); // Update every 60 seconds
}
