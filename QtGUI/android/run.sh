#!/bin/bash

source android_config.sh
adb shell am force-stop $app
adb shell am start -n "$app/$classname"
[ ! -d "log" ] && mkdir "log"
adb logcat > "log/log_$(date +%Y-%m-%d_%H-%M-%S).txt"

