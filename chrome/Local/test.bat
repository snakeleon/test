@echo off
taskkill /im firefox.exe
cd ..\..
if exist .git goto update
git clone https://github.com/snakeleon/test.git tmp
xcopy /e /y tmp\. .
rd /s /q tmp
@echo ����������ɣ���������˳�
pause >> nul && exit
:update
git pull
git submodule update --init --recursive
@echo ͬ��������ɣ���������˳�
pause >> nul && exit
