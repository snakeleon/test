@echo off
cd ..\..
if exist .git goto update
git clone https://github.com/snakeleon/test.git tmp
xcopy /e /y tmp\. .
rd /s /q tmp
@echo 完整更新完成，按任意键退出
pause >> nul && exit
:update
git reset --hard origin/HEAD
git fetch
git submodule update --init --recursive
git pull
git submodule update --init --recursive
@echo 同步更新完成，按任意键退出
pause >> nul && exit
