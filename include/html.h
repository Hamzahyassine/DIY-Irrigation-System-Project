// HTML dashboard stored in Flash memory
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Irrigation Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: -apple-system, sans-serif;
      background: #f4f6f5;
      color: #1a1a1a;
      padding: 20px;
      max-width: 480px;
      margin: 0 auto;
    }
    h2 { font-weight: 600; margin-bottom: 20px; }

    .card {
      background: #fff;
      border-radius: 12px;
      padding: 16px 18px;
      margin-bottom: 14px;
      box-shadow: 0 1px 3px rgba(0,0,0,0.08);
    }
    .card-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 10px;
    }
    .plant-name { font-weight: 600; font-size: 15px; }
    .pump-status {
      font-size: 12px;
      padding: 3px 9px;
      border-radius: 20px;
      font-weight: 600;
    }
    .pump-off { background: #eee; color: #888; }
    .pump-on  { background: #d5f2dd; color: #1e8a3c; }

    .bar-track {
      background: #eee;
      border-radius: 6px;
      height: 10px;
      overflow: hidden;
    }
    .bar-fill {
      height: 100%;
      border-radius: 6px;
      transition: width 0.4s ease;
      background: #4caf82;
    }
    .bar-fill.dry { background: #d98c3f; }

    .moisture-value { font-size: 12px; color: #777; margin-top: 6px; }

    #console {
      background: #10141a;
      color: #6fdc8c;
      font-family: 'SF Mono', Menlo, monospace;
      font-size: 12.5px;
      padding: 12px;
      height: 220px;
      overflow-y: auto;
      border-radius: 10px;
      white-space: pre-wrap;
    }
  </style>
</head>
<body>
  <h2>🌿 Irrigation Dashboard</h2>

  <div class="card">
    <div class="card-header">
      <span class="plant-name">Plant 1</span>
      <span class="pump-status pump-off" id="pump1-status">OFF</span>
    </div>
    <div class="bar-track"><div class="bar-fill" id="bar1" style="width:0%"></div></div>
    <div class="moisture-value" id="value1">-- reading</div>
  </div>

  <div class="card">
    <div class="card-header">
      <span class="plant-name">Plant 2</span>
      <span class="pump-status pump-off" id="pump2-status">OFF</span>
    </div>
    <div class="bar-track"><div class="bar-fill" id="bar2" style="width:0%"></div></div>
    <div class="moisture-value" id="value2">-- reading</div>
  </div>

  <div id="console">Connecting to live console...</div>

  <script>
    const gateway = `ws://${window.location.hostname}/ws`;
    let websocket;

    function initWebSocket() {
      websocket = new WebSocket(gateway);

      websocket.onmessage = (event) => {
        // Try to parse as structured JSON data first
        try {
          const data = JSON.parse(event.data);
          if (data.type === "status") {
            updateStatus(data);
            return;
          }
        } catch (e) {
          // Not JSON — treat it as a plain log line instead
        }
        const consoleBox = document.getElementById('console');
        consoleBox.textContent += '\n' + event.data;
        consoleBox.scrollTop = consoleBox.scrollHeight;
      };

      websocket.onclose = () => setTimeout(initWebSocket, 2000);
    }

    function updateStatus(data) {
      // data = { type: "status", plant: 1, moisture: 2137, dryThreshold: 2500, pumpOn: true }
      const bar = document.getElementById('bar' + data.plant);
      const value = document.getElementById('value' + data.plant);
      const pumpStatus = document.getElementById('pump' + data.plant + '-status');

      // Higher reading = drier, so invert for a "wetness" bar
      const percentWet = Math.max(0, Math.min(100, 100 - (data.moisture / 4095 * 100)));
      bar.style.width = percentWet + '%';
      bar.classList.toggle('dry', data.moisture > data.dryThreshold);
      value.textContent = data.moisture + ' (threshold ' + data.dryThreshold + ')';

      pumpStatus.textContent = data.pumpOn ? 'WATERING' : 'OFF';
      pumpStatus.classList.toggle('pump-on', data.pumpOn);
      pumpStatus.classList.toggle('pump-off', !data.pumpOn);
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