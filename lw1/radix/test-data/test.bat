@echo off

set PROGRAM=%~1

::������� 1F �� 16 � 10 ��
%PROGRAM% 16 10 1F > test-data\output.txt
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\From_16_To_10_1F.txt || goto err
echo Test 1 passed!

::������� MAX_INT �� 10 � 36 ��
%PROGRAM% 10 36 2147483647 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\IntMax_From_10_To_36.txt || goto err
echo Test 2 passed!

::������� -ZIK0ZJ �� 36 � 2 ��
%PROGRAM% 36 2 -ZIK0ZJ > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\-ZIK0ZJ_From_36_To_Bin.txt || goto err
echo Test 3 passed!

::������� 0 �� 32 � 14 ��
%PROGRAM% 32 14 0 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\Zero_To_Any.txt || goto err
echo Test 4 passed!

::����� �� ���������� ��
%PROGRAM% 132 10 0
if %ERRORLEVEL% EQU 1 echo Test 5 passed! || goto err

::�������� ������ � ��
%PROGRAM% 16 10 1Z
if %ERRORLEVEL% EQU 1 echo Test 6 passed! || goto err

::������������ INT_MAX + 1
%POGRAM% 10 2 2147483648
if %ERRORLEVEL% EQU 0 goto err
echo Test 7 passed!

::������������ INT_MIN - 1
%POGRAM% 10 2 -2147483649
if %ERRORLEVEL% EQU 0 goto err
echo Test 8 passed!

::INT_MIN
%POGRAM% 10 2 -2147483648
if %ERRORLEVEL% EQU 1 goto err
echo Test 9 passed!


echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1