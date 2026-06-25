# EEZ-Studio-Arduino-IDE-Template
A boilerplate template to start developing a LVGL based UI with EEZ studio program and flash it using Arduino IDE. The example used here is for the Waveshare esp32-s3 1.28inch no touch LCD dev board, but you may adapt it to your display and platform
I keep needing to start a new prototype project every now and then with these boards and I prefer using EEZ studios (other than Squareline) for the UI dev, and I wanted to make a template project for the same purpose. Feel free to clone and make necessary changes to base your EEZ studios project 

EEZ studio - https://www.envox.eu/studio/studio-introduction/

The board used- https://www.waveshare.com/esp32-s3-lcd-1.28.htm
https://www.waveshare.com/wiki/ESP32-S3-LCD-1.28 (please refer to the usage instructions for the specific esp32 board package version 2.0.12, board settings for the ide and the required libraries like lvgl and tft_espi if the instructions specifiy a non-standard version)

Download appimage of eez studio and run it with first chmod +x eez-studio.AppImage
./eez-studio.AppImage

After this code is running on your board, you can start developing the UI in EEZ studios

After you make a new project in eez studio, you can go into project settings, set display dimensions and the screen dimensions (in this board's case 240x240 and circular display enabled)

Set 'lvgl include path' to lvgl. (remove lvgl/)

Then set destination folder for ui files to the /libraries/ui folder (make sure to delete its old contents everytime you build the ui with eez studio)

Then just set Arduino path to the folder's root (which has libraries and ui folder) and flash your board


<img width="4096" height="3072" alt="IMG_20260626_033049389" src="https://github.com/user-attachments/assets/2617fbb0-2d84-4874-bc46-283a9b418828" />
