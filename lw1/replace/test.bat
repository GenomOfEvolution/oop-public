@echo off

set PROGRAM=%~1

::Замена ma на pa
%PROGRAM% test-data\inp1.txt test-data\output.txt ma pa
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\mamaToPapa.txt || goto err

::Замена пустой строки
%PROGRAM% test-data\inp1.txt test-data\output.txt "" pa
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\inp1.txt || goto err

::Тест с цифрами
%PROGRAM% test-data\inp2.txt test-data\output.txt 1231234 ""
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\DefNumbers.txt|| goto err

::Нечего заменять
%PROGRAM% test-data\Empty.txt test-data\output.txt 1231234 ""
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\Empty.txt|| goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1