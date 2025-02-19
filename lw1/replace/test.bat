@echo off

set PROGRAM=%~1

::������ ma �� pa
%PROGRAM% test-data\inp1.txt test-data\output.txt ma pa
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\mamaToPapa.txt || goto err
echo Test 1 passed!

::������ ������ ������
%PROGRAM% test-data\inp1.txt test-data\output.txt "" pa
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\inp1.txt || goto err
echo Test 2 passed!

::���� � �������
%PROGRAM% test-data\inp2.txt test-data\output.txt 1231234 ""
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\DefNumbers.txt|| goto err
echo Test 3 passed!

::������ ��������
%PROGRAM% test-data\Empty.txt test-data\output.txt 1231234 ""
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt  test-data\Empty.txt|| goto err
echo Test 4 passed!

::�������� ���-�� ����������
%PROGRAM% test-data\Empty.txt test-data\output.txt ""
if %ERRORLEVEL% EQU 0 goto err
echo Test 5 passed!

::�������� �� ����������� ������
%PROGRAM% NotExisitingFile.txt test-data\output.txt 1231234 ""
if %ERRORLEVEL% EQU 0 goto err
echo Test 6 passed!

echo All tests passed
exit /B 0

:err
echo Program testing failed!
exit /B 1