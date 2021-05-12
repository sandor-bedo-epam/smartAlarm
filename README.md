# Smart Alarm project with ESP32 TTGO T-CALL module

## Used softwares for development
---
- VSCode (Extension's list in "Scripts/VSCodeExtensions" folder)
- Docker

### How to compile source code
1. Install [VSCode](https://code.visualstudio.com/download)
2. Install [Docker (for Windows)](https://hub.docker.com/editions/community/docker-ce-desktop-windows)
    - Registration is also needed
3. Compile ESP32 image (Only once needed)
    - In VSCode press `F1` or `Ctrl+Alt+P` to open `Command palette`
    - Select `Tasks: Run Task` option
    - Select `Docker Image Build`
    - <i>(With this command the VSCode is building an image for ESP32 development.)</i>
4. From `Command palette` select `ESP32 project - Build` 
    - This command will create a container from the built image, mount folders and call the idf.py to build the source code
5. From `Command palette` select `Mount COMx port to TCP`
    - Before this command edit the <b>COMx</b> and <b>IPaddress</b> in <i>.vscode/tasks.json</i> file
6. From `Command palette` select `ESP32 project - Flash`

## Folder structure
---
```
│── .vscode
│   └── tasks.json
│── Code
│   ├── CMakeLists.txt
│   ├── example_test.py                         Python script used for automated example testing
│   ├── main
│   │   ├── CMakeLists.txt
│   │   ├── component.mk                        Component make file
│   │   └── hello_world_main.c
│   ├── Makefile                                Makefile used by legacy GNU Make
│   └── README.md                               This is the file you are currently reading
│── Docker
│   ├── docker-compose.yml
│   ├── Dockerfile
│   └── entrypoint.sh
└── VSCodeExtensions
    └── Scripts
        ├── hub4com-2.1.0.0-386
        │   ├── com2tcp-rfc2217.bat             This batch file mount COMx port to localhost:5555 port to reach it from Docker container
        │   └── ...
        └── VSCodeExtensions
            ├── Export_VSCode_Extension_List.bat
            └── Import_VSCode_Extension_List.bat

```