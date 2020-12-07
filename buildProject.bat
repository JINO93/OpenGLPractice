@echo off
rd /s /q build
md build
cd build
cmake -G"MinGW Makefiles" ../
make -j4
cd ..