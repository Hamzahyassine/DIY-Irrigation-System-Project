// ota_setup.h
    // ============================================================
    // ArduinoOTA already defines these four "slots" (onStart, onEnd,
    // onProgress, onError) — the library's authors built them in
    // advance, along with the logic (hidden inside ArduinoOTA.handle(),
    // in loop()) that watches the network and decides WHEN each one
    // should fire. That detection logic is the library's job, not ours.
    //
    // But each slot starts out EMPTY — like a labeled mailbox with
    // nothing inside it. Calling .onStart(...) here doesn't create
    // the trigger, it just puts OUR function inside that existing
    // slot, so something actually happens when the library fires it.
    //
    // We never call these functions ourselves. ArduinoOTA.handle()
    // calls them internally, at the exact real moment each event
    // truly happens (e.g. only onStart fires when a transfer begins —
    // not all four firing together just because handle() ran).
    // ============================================================
void setupOTACallbacks() {


    // Slot: fires the moment a real OTA upload attempt begins.
    // Our content: just log it, so we can see the invitation was received.
    ArduinoOTA.onStart([]() {
    logMessage("OTA update starting...");
    });

    // Slot: fires once, when the OTA transfer finishes successfully.
    // Our content: confirm success in the log.
    ArduinoOTA.onEnd([]() {
    logMessage("OTA update complete.");
    });

    // Slot: fires repeatedly WHILE data is actively being received.
    // Our content: turn the raw byte counts into a readable percentage.
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    logMessage("OTA progress: " + String((progress / (total / 100))) + "%");
    });

    // Slot: fires if anything goes wrong during the attempt.
    // Our content: translate the library's error code into a real
    // message, so a failure tells us WHY instead of just timing out silently.
    ArduinoOTA.onError([](ota_error_t error) {
    String errMsg = "OTA Error [" + String(error) + "]: ";
    if (error == OTA_AUTH_ERROR) errMsg += "Auth Failed";
    else if (error == OTA_BEGIN_ERROR) errMsg += "Begin Failed";
    else if (error == OTA_CONNECT_ERROR) errMsg += "Connect Failed";
    else if (error == OTA_RECEIVE_ERROR) errMsg += "Receive Failed";
    else if (error == OTA_END_ERROR) errMsg += "End Failed";
    logMessage(errMsg);
    });
  
}