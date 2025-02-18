@echo off

set PROGRAM=%~1

::Замена ma на pa
%PROGRAM% test-data\inp1.txt test-data\output.txt ma pa
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\mamaToPapa.txt || goto err
echo Test 1 passed!

::Замена пустой строки
%PROGRAM% test-data\inp1.txt test-data\output.txt "" pa
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\inp1.txt || goto err
echo Test 2 passed!

::Тест с цифрами
%PROGRAM% test-data\inp2.txt test-data\output.txt 1231234 ""
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\DefNumbers.txt|| goto err
echo Test 3 passed!

::Нечего заменять
%PROGRAM% test-data\Empty.txt test-data\output.txt 1231234 ""
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\Empty.txt|| goto err
echo Test 4 passed!

::Неверное кол-во параметров
%PROGRAM% test-data\Empty.txt test-data\output.txt ""
if %ERRORLEVEL% EQU 0 goto err
echo Test 5 passed!

::Открытие не сущесвующих файлов
%PROGRAM% NotExisitingFile.txt test-data\output.txt 1231234 ""
if %ERRORLEVEL% EQU 0 goto err
echo Test 6 passed!

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1