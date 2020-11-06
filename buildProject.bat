@echo off
rd /s /q build
md build
cd build
cmake -G"Unix Makefiles" ../
make -j4
cd ..