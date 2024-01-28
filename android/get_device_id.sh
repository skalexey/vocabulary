#!/bin/bash

echo $(adb devices | awk 'NR==2 {print $1}')