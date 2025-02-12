@echo off

set PROGRAM=%~1

::������ ma �� pa
%PROGRAM% test-data\inp1.txt test-data\output.txt ma pa
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\mamaToPapa.txt || goto err

::������ ������ ������
%PROGRAM% test-data\inp1.txt test-data\output.txt "" pa
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\inp1.txt || goto err

::���� � �������
%PROGRAM% test-data\inp2.txt test-data\output.txt 1231234 ""
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\DefNumbers.txt|| goto err

::������ ��������
%PROGRAM% test-data\Empty.txt test-data\output.txt 1231234 ""
if ERRORLEVEL 1 goto err
fc test-data\output.txt  test-data\Empty.txt|| goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1