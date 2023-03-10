@REM change directory to 'build.bat' file directory (project directory)
cd /D "%~dp0"
@REM go to sub-directory 'build'
cd .\build
@REM make project using clang-cl compiler
cmake -T ClangCL ..
@REM build project in Debug mode
cmake --build .
@REM go to project-directory
cd ..
