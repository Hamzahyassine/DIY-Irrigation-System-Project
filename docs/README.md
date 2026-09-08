# Dashboard Website

This folder contains the public dashboard for the irrigation project, hosted with GitHub Pages.

**Live site:** https://hamzahyassine.github.io/DIY-Irrigation-System-Project/

## What it does

The ESP32 sends each sensor reading to a Firebase Realtime Database over Wi-Fi. This page reads that data directly from Firebase and displays it as a dashboard, so the project's status is viewable from anywhere, not just on the home network.

- **Home tab** — current moisture level for each plant, shown as a water bar, plus placeholders for battery and tank level (not yet implemented in hardware).
- **History tab** — a full log of past readings and watering events for each plant.

## Known limitation

Readings are currently timestamped using the ESP32's `millis()` value (time since last boot), not real calendar time. This means the history table shows "minutes after boot" rather than an actual date/time, and "last watered" can't yet show an accurate "X hours ago." Adding NTP-based real timestamps is a planned improvement — see the main [PROGRESSION.md](../PROGRESSION.md) for details.