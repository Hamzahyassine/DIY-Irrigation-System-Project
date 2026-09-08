// HTML dashboard stored in Flash memory
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Plant Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; background: #1a1a1a; color: #eee; padding: 20px; }
    #console { 
      background: #000; 
      color: #00ff66; 
      font-family: monospace; 
      padding: 12px; 
      height: 300px; 
      overflow-y: auto; 
      border-radius: 6px; 
      border: 1px solid #333;
      white-space: pre-wrap;
    }
  </style>
</head>
<body>
  <h2>🌿 Irrigation Monitor</h2>
  <div id="console">Connecting to live console...</div>

  <script>
    const gateway = `ws://${window.location.hostname}/ws`;
    let websocket;

    function initWebSocket() {
      websocket = new WebSocket(gateway);
      websocket.onmessage = (event) => {
        const consoleBox = document.getElementById('console');
        consoleBox.textContent += '\n' + event.data;
        consoleBox.scrollTop = consoleBox.scrollHeight;
      };
      websocket.onclose = () => {
        setTimeout(initWebSocket, 2000);
      };
    }

    window.addEventListener('load', initWebSocket);
  </script>
</body>
</html>
)rawliteral";


// Create the web server on standard HTTP port 80
AsyncWebServer server(80);

// Create the WebSocket endpoint at URL path "/ws"
AsyncWebSocket ws("/ws");