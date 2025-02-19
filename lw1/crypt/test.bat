@echo off

set PROGRAM=%~1

::�������� ������� ���������
%PROGRAM% ����� input.txt output.txt 29 
if %ERRORLEVEL% EQU 0 goto err
echo Test 1 passed!

::�������� �� ���� �� 0 �� 255
%PROGRAM% crypt test-data\input0.txt test-data\output.txt 259
if %ERRORLEVEL% EQU 0 goto err
echo Test 2 passed!

::�������� ���������� 255
%PROGRAM% crypt test-data\input0.txt test-data\output0.txt 255
if %ERRORLEVEL% EQU 1 goto err

::�������� ������������ 255
%PROGRAM% decrypt test-data\output0.txt test-data\decrpyted.txt 255
if %ERRORLEVEL% EQU 1 goto err
fc test-data\input0.txt test-data\decrpyted.txt || goto err
echo Test 3 passed!

::�������� ���������� 0
%PROGRAM% crypt test-data\input0.txt test-data\output0.txt 0
if %ERRORLEVEL% EQU 1 goto err

::�������� ������������ 0
%PROGRAM% decrypt test-data\output0.txt test-data\decrpyted.txt 0
if %ERRORLEVEL% EQU 1 goto err
fc test-data\input0.txt test-data\decrpyted.txt || goto err
echo Test 4 passed!

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1