# Smart Alarm project with ESP32 TTGO T-CALL module

## Used softwares for development
---
- VSCode (Extension's list in "Scripts/VSCodeExtensions" folder)
- Docker

### How to compile source code
1. Install VSCode
2. Install Docker
3. Compile ESP32 image:
    - In VSCode press `F1` or `Ctrl+Alt+P` to open <i>Command palette</i>
    - Select `Tasks: Run Task` option
    - Select `Build docker image`
    - <i>(With this command the VSCode will build an image for ESP32 development.)</i>
4. From `Command palette` select `Build ESP32 project` 
    - This command will create a container from the built image, mount folders and call the idf.py to build the source code

## Folder structure
---
```
│── .vscode
│   └── tasks.json
│── Code+
│   ├── CMakeLists.txt
│   ├── example_test.py            Python script used for automated example testing
│   ├── main
│   │  ├── CMakeLists.txt
│   │  ├── component.mk           Component make file
│   │  └── hello_world_main.c
│   ├── Makefile                   Makefile used by legacy GNU Make
│   └── README.md                  This is the file you are currently reading
│── Docker
│   ├── docker-compose.yml
│   ├── Dockerfile
│   └── entrypoint.sh
└── VSCodeExtensions
    ├── Export_VSCode_Extension_List.bat
    └── Import_VSCode_Extension_List.bat
```