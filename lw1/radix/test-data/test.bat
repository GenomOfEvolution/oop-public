@echo off

set PROGRAM=%~1

::Перевод 1F из 16 в 10 сс
%PROGRAM% 16 10 1F > test-data\output.txt
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\From_16_To_10_1F.txt || goto err
echo Test 1 passed!

::Перевод MAX_INT из 10 в 36 сс
%PROGRAM% 10 36 2147483647 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\IntMax_From_10_To_36.txt || goto err
echo Test 2 passed!

::Перевод -ZIK0ZJ из 36 в 2 сс
%PROGRAM% 36 2 -ZIK0ZJ > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\-ZIK0ZJ_From_36_To_Bin.txt || goto err
echo Test 3 passed!

::Перевод 0 из 32 в 14 сс
%PROGRAM% 32 14 0 > test-data\output.txt 
if ERRORLEVEL 1 goto err
fc test-data\output.txt test-data\Zero_To_Any.txt || goto err
echo Test 4 passed!

::Выход из допустимой сс
%PROGRAM% 132 10 0
if %ERRORLEVEL% EQU 1 echo Test 5 passed! || goto err

::Неверный символ в сс
%PROGRAM% 16 10 1Z
if %ERRORLEVEL% EQU 1 echo Test 6 passed! || goto err

::Переполнение INT_MAX + 1
%POGRAM% 10 2 2147483648
if %ERRORLEVEL% EQU 0 goto err
echo Test 7 passed!

::Переполнение INT_MIN - 1
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