##############################################
#  RANDOM DEVICES
##############################################

1) ndk-build
2) adb push libs/armeabi/randomdevs /data
3) adb shell
## Now on the phone's shell ##
4) cd /data
5) ./randomdevs <'u' for urandom and 'r' for random> 
    - urandom example: ./randomdevs u


