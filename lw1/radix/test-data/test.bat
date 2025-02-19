@echo off

set PROGRAM=%~1

::Перевод 1F из 16 в 10 сс
%PROGRAM% 16 10 1F > test-data\output.txt
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\From_16_To_10_1F.txt || goto err

::Перевод MAX_INT из 10 в 36 сс
%PROGRAM% 10 36 2147483647 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\IntMax_From_10_To_36.txt || goto err

::Перевод -ZIK0ZJ из 36 в 2 сс
%PROGRAM% 36 2 -ZIK0ZJ > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\-ZIK0ZJ_From_36_To_Bin.txt || goto err

::Перевод 0 из 32 в 14 сс
%PROGRAM% 32 14 0 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\Zero_To_Any.txt || goto err

::Выход из допустимой сс
%PROGRAM% 132 10 0
if NOT ERRORLEVEL 1 goto err

::Неверный символ в сс
%PROGRAM% 16 10 1Z
if NOT ERRORLEVEL 1 goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1