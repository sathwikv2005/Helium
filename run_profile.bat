@echo off
gcc -pg -O2 src/*.c -o profiler.exe
profiler.exe %*                         
gprof profiler.exe gmon.out > report.txt