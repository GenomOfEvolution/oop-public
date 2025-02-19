@echo off

set PROGRAM=%~1

::������� 1F �� 16 � 10 ��
%PROGRAM% 16 10 1F > test-data\output.txt
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\From_16_To_10_1F.txt || goto err

::������� MAX_INT �� 10 � 36 ��
%PROGRAM% 10 36 2147483647 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\IntMax_From_10_To_36.txt || goto err

::������� -ZIK0ZJ �� 36 � 2 ��
%PROGRAM% 36 2 -ZIK0ZJ > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\-ZIK0ZJ_From_36_To_Bin.txt || goto err

::������� 0 �� 32 � 14 ��
%PROGRAM% 32 14 0 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\Zero_To_Any.txt || goto err

::����� �� ���������� ��
%PROGRAM% 132 10 0
if NOT ERRORLEVEL 1 goto err

::�������� ������ � ��
%PROGRAM% 16 10 1Z
if NOT ERRORLEVEL 1 goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1