SET argument1=%~1
@REM change directory to 'build.bat' file directory (project directory)
cd /D "%~dp0"
IF "%argument1%" == "" (
    GOTO :build
) 
IF "%argument1%" == "-t" (
    GOTO :tests
)
IF "%argument1%" == "--tests" (
    GOTO :tests
)
GOTO :eof
:tests
    @REM create sub-directory 'test' if it's not exists
    IF NOT EXIST .\build-tests (
        mkdir .\build-tests
    )
    @REM go to sub-directory 'tests'
    cd .\build-tests
    @REM make project using clang-cl compiler
    cmake -T ClangCL ..\tests
    @REM build project in Debug mode
    cmake --build .
    @REM go to project-directory
    cd ..
GOTO :eof
:build
    @REM create sub-directory 'test' if it's not exists
    IF NOT EXIST .\build (
        mkdir .\build
    )
    @REM go to sub-directory 'build'
    cd .\build
    @REM make project using clang-cl compiler
    cmake -T ClangCL ..
    @REM build project in Debug mode
    cmake --build .
    @REM go to project-directory
    cd ..
GOTO :eof
