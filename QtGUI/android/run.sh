#!/bin/bash

adb shell am start "org.qtproject.example.vocabulary"
rm log.txt
adb logcat > log.txt

