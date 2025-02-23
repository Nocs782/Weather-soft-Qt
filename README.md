# WeatherApp - Qt 6 GUI Application  

This is a simple Qt 6 GUI weather application that fetches real-time weather data from OpenWeatherMap API and displays temperature, weather conditions, wind speed, humidity, and other details. The app features a modern UI with a light blue gradient background and semi-transparent weather details.

---

## Features
- Fetches weather data dynamically based on user input.  
- Displays weather details including temperature, feels like, humidity, wind speed, pressure, sunrise/sunset time, and local time.  
- Weather icons update automatically based on API response.  
- Modern UI design with rounded buttons, bold labels, and a smooth gradient background.  
- Runs on Windows and Linux (cross-platform support).  

---

## Setup & Installation

### 1. Install Qt 6 (if not installed)
You need Qt 6.x with Qt Creator. If you haven’t installed it yet:  
[Download Qt 6](https://www.qt.io/download)  

Make sure the Qt Network Module is installed.

---

### 2. Clone the Repository
```sh
git clone https://github.com/yourusername/WeatherApp.git
cd WeatherApp
```

---

### 3. Add `.env` File with Your API Key
The app requires an OpenWeatherMap API key to function.  
1. Create a new file named `.env` inside the `build/` directory.  
2. Add your API key like this:  
   ```
   API_KEY=your_openweathermap_api_key
   ```
   Replace `your_openweathermap_api_key` with your actual API key from [OpenWeatherMap](https://home.openweathermap.org/api_keys).

---

### 4. Add Weather Icons
The app loads weather icons from a local folder instead of fetching them online.  
1. Create a folder named `icons/` inside `build/`.  
2. Download the OpenWeatherMap weather icons from [OpenWeatherMap Icons](https://openweathermap.org/weather-conditions).  
3. Make sure the filenames match OpenWeatherMap icon codes.  
   Example file names:
   ```
   01d@2x.png  // Clear sky (day)
   01n@2x.png  // Clear sky (night)
   02d@2x.png  // Few clouds (day)
   02n@2x.png  // Few clouds (night)
   ```
4. Final Folder Structure:
   ```
   /WeatherApp
   ├── main.cpp
   ├── mainwindow.cpp
   ├── mainwindow.h
   ├── mainwindow.ui
   ├── CMakeLists.txt
   ├── build/
   │   ├── WeatherApp.exe
   │   ├── .env             (API Key File)
   │   ├── icons/           (Weather Icons)
   │   │   ├── 01d@2x.png
   │   │   ├── 01n@2x.png
   │   │   ├── 02d@2x.png
   ```
---

### 5. Build & Run the App
#### Using Qt Creator
1. Open `WeatherApp.pro` in Qt Creator.  
2. Click **Build → Run**.  

#### Using CMake & Terminal
```sh
mkdir build
cd build
cmake ..
make
./WeatherApp
```
The app should now be running.

---

## Notes
- The `.env` file is not included in the repository (you need to create it).  
- The weather icons must be stored locally in the `icons/` folder.  
- If you get an API key error (`401 Unauthorized`), check your OpenWeatherMap API key and ensure it's active.  

---

## Future Improvements
- Add 5-day weather forecast.  
- Include automatic location detection.  
- Improve error handling and UI responsiveness.  