@echo on
cd %~dp0..\..
if exist \.git
(
  git reset --hard origin/HEAD &&
  git fetch &&
  git submodule update --init --recursive
)
else
(
  git clone http://github.com/snakeleon/test.git .\tmp
  xcopy /e /y \tmp\. \.
  rd /s /q \tmp
)
@echo 更新完成，按任意键退出
pause >> nul & exit
