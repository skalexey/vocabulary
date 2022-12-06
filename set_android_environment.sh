#!/bin/bash

echo "ANDROID_SDK_ROOT before: $ANDROID_SDK_ROOT"
echo "ANDROID_NDK_ROOT before: $ANDROID_NDK_ROOT"
echo "JAVA_HOME before: $JAVA_HOME"
export ANDROID_SDK_ROOT=~/bin/android/sdk
export ANDROID_NDK_ROOT=~/bin/android/sdk/ndk/25.1.8937393
export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.16.1.jdk/Contents/Home
echo "ANDROID_SDK_ROOT after: $ANDROID_SDK_ROOT"
echo "ANDROID_NDK_ROOT after: $ANDROID_NDK_ROOT"
echo "JAVA_HOME after: $JAVA_HOME"

