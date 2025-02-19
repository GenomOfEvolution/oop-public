@echo off

set PROGRAM=%~1

::����������� ������� == 0
%PROGRAM% < test-data\input0.txt > out.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\Non-invertible.txt out.txt || goto err
echo Test 1 passed!

::������� ������� �������
%PROGRAM% < test-data\input1.txt > out.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\InvalidMatrixFormat.txt out.txt || goto err
echo Test 2 passed!

::������� ������� ���������
%PROGRAM% < test-data\input2.txt > out.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\InvalidMatrixFormat.txt out.txt || goto err
echo Test 3 passed!

::������ �� ���� 1
%PROGRAM% test-data\input3.txt out.txt
if %ERRORLEVEL% EQU 1 goto err
echo chis
fc test-data\output3.txt out.txt || goto err
echo Test 4 passed!

::������ �� ���� 2
%PROGRAM% test-data\input4.txt out.txt
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output4.txt out.txt || goto err
echo Test 5 passed!

::�������� ����. �������
%PROGRAM% < test-data\input5.txt > out.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\InvalidMatrix.txt out.txt || goto err
echo Test 6 passed!

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1