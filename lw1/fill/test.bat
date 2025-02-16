@echo off

set PROGRAM=%~1

::�������� ���������
%PROGRAM% test-data\input228.txt wrongAnswer.txt
if %ERRORLEVEL% EQU 0 goto err
echo Test 1 passed!

::�������� ������ � �����
%PROGRAM% test-data\input6.txt answer.txt
if %ERRORLEVEL% EQU 0 goto err
echo Test 2 passed!

::�������� � ������ ������
%PROGRAM% test-data\input0.txt answer.txt
if %ERRORLEVEL% EQU 1 goto err
fc answer.txt  test-data\output0.txt || goto err
echo Test 3 passed!

::�������� 1 ������� �� �������
%PROGRAM% test-data\input1.txt answer.txt
if %ERRORLEVEL% EQU 1 goto err
fc answer.txt  test-data\output1.txt || goto err
echo Test 4 passed!

::�������� 2 ������� �� �������
%PROGRAM% test-data\input2.txt answer.txt
if %ERRORLEVEL% EQU 1 goto err
fc answer.txt  test-data\output2.txt || goto err
echo Test 5 passed!

::�������� 3 ������� �� ������� - 2 ����� �������
%PROGRAM% test-data\input3.txt answer.txt
if %ERRORLEVEL% EQU 1 goto err
fc answer.txt  test-data\output3.txt || goto err
echo Test 6 passed!

::�������� ������� ����� ���� ������� 100 100
%PROGRAM% test-data\input4.txt answer.txt
if %ERRORLEVEL% EQU 1 goto err
fc answer.txt  test-data\output4.txt || goto err
echo Test 7 passed!

::�������� ������� ����� ���� ������� 0 0
%PROGRAM% test-data\input5.txt answer.txt
if %ERRORLEVEL% EQU 1 goto err
fc answer.txt  test-data\output5.txt || goto err
echo Test 8 passed!

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1