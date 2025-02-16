# Lembang-Opcast

**Lembang-Opcast** is an open-source screen recording and live streaming application for Linux. It allows users to record their screen and stream content live to various platforms. Whether you're a content creator, gamer, or educator, Lembang-Opcast provides an easy and powerful way to capture your screen and share it with the world.

## Features
- High-quality screen recording with X11
- Audio capture using PulseAudio
- Video encoding with FFmpeg
- Live streaming support via RTMP
- GTK-based user interface
- Customizable settings for recording and streaming
- Lightweight and fast performance on Linux-based systems

## Prerequisites
- Linux-based operating system (e.g., Ubuntu, Fedora, etc.)
- Build dependencies:
  ```bash
  sudo apt-get update
  sudo apt-get install build-essential git
  sudo apt-get install libx11-dev libgtk-3-dev
  sudo apt-get install libavcodec-dev libavformat-dev libavutil-dev libswscale-dev
  sudo apt-get install libpulse-dev libpulse-simple0
  sudo apt-get install librtmp-dev
  ```

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/JiilanTj/Lembang-Opcast.git
   cd Lembang-Opcast
   ```

2. Build the application:
   ```bash
   make clean  # Clean any previous builds
   make        # Build the application
   ```

3. Run the application:
   ```bash
   ./build/lembang-opcast
   ```

## Project Structure
```
Lembang-Opcast/
├── src/
│   ├── main.c
│   ├── capture/          # Screen and audio capture
│   ├── encoder/          # Video/audio encoding
│   ├── gui/              # GTK user interface
│   ├── streaming/        # RTMP streaming
│   └── utils/            # Utilities and logging
├── include/              # Header files
├── build/               # Build output (generated)
└── docs/                # Documentation
```

## Usage

1. Launch the application from the terminal using `./build/lembang-opcast`
2. Configure your screen recording settings (resolution, frame rate, etc.)
3. Use the GUI controls to:
   - Start/Stop recording
   - Configure settings
   - Control streaming

## Contributing
We welcome contributions to **Lembang-Opcast**! To contribute:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Please make sure to follow our code of conduct and contribution guidelines.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- X11 for screen capture capabilities
- FFmpeg for video/audio encoding
- PulseAudio for audio capture
- GTK for the user interface
- RTMP for streaming functionality
- The open-source community for their invaluable tools and libraries
