@echo off
ECHO Add CRC16  At the end of the document
ECHO -------------------------------------

SET SREC_PATH=C:\SREC

for /f %%i in ('dir /b ..\OBJ\RTC.bin') do (
set indexdx=%%~zi
)


ECHO --------------------------------------------
ECHO %indexdx%
ECHO 123456

ECHO %SREC_PATH%\srec_cat.exe ..\OBJ\RTC.bin -Binary -crop 0 %indexdx%  -crc16-b-e %indexdx%  -o gps_bass.bin -Binary
%SREC_PATH%\srec_cat.exe ..\OBJ\RTC.bin -Binary -crop 0 %indexdx%  -crc16-l-e %indexdx%  -o ..\OBJ\gps_bass.bin -Binary
