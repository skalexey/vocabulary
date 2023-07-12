#!/bin/bash

adb shell am start "org.qtproject.example.QtGUIApp"
rm log.txt
adb logcat > log.txt

