@REM read arguments
SET argument1=%~1

@REM change directory to 'build.bat' file directory (project directory)
cd /D "%~dp0"

IF "%argument1%" == "" (
    GOTO :plain_build
)
IF "%argument1%" == "-t" SET build_type=build_tests
IF "%argument1%" == "--tests" SET build_type=build_tests
IF "%argument1%" == "-e" SET build_type=run_tests
IF "%argument1%" == "--exec-tests" SET build_type=run_tests

IF defined build_type (
    GOTO :build_tests
)

GOTO :eof

:build_tests
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
    @REM run tests if related option was set
    IF %errorlevel% == 0 if "%build_type%" == "run_tests" (
        ctest -C Debug --output-on-failure
    )
    @REM go to project-directory
    cd ..
GOTO :eof

:plain_build
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
