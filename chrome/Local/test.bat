@echo off
cd ..\..
if exist .git goto update
git clone https://github.com/snakeleon/test.git tmp
xcopy /e /y tmp\. .
rd /s /q tmp
@echo ����������ɣ���������˳�
pause >> nul && exit
:update
git reset --hard origin/HEAD
git fetch
git submodule update --init --recursive
git pull
git submodule update --init --recursive
@echo ͬ��������ɣ���������˳�
pause >> nul && exit
