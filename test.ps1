Param (
    [string]$Lab,
    [string]$Test
)

if($Lab)
{
    $BUILD_TEST_DIR = "build_$Lab"

    if (-not (Test-Path -Path $Lab))
    {
        Write-Host -ForegroundColor Red "No such file or directory"
        exit 1
    }
}
else
{
    $Lab = "."
    $BUILD_TEST_DIR = "build_all_labs"
}

if (Test-Path -Path $BUILD_TEST_DIR)
{
    Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null
}

New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null

if ((-not $Test) -or ($Test).Contains('Test1'))
{
    Write-Host -ForegroundColor Yellow "TEST 1"
    cmake -B $BUILD_TEST_DIR/Test1 -S $Lab -DUNLIMITED=ON -DCMAKE_BUILD_TYPE=Release
    cmake --build $BUILD_TEST_DIR/Test1 --config Release
    if ($IsWindows) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test1 --target RUN_TESTS}
    if ($IsLinux) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test1 --target test}
}

if ((-not $Test) -or ($Test).Contains('Test2'))
{
    Write-Host -ForegroundColor Yellow "TEST 2"
    cmake -B $BUILD_TEST_DIR/Test2 -S $Lab -DUNLIMITED=OFF -DCMAKE_BUILD_TYPE=Release
    cmake --build $BUILD_TEST_DIR/Test2 --config Release
    if ($IsWindows) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test2 --target RUN_TESTS}
    if ($IsLinux) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test2 --target test}
}

if ((-not $Test) -or ($Test).Contains('Test3'))
{
    Write-Host -ForegroundColor Yellow "TEST 3"
    cmake -B $BUILD_TEST_DIR/Test3 -S $Lab -DCMAKE_C_COMPILER=clang -DENABLE_ASAN=true -DUNLIMITED=ON  -DCMAKE_BUILD_TYPE=Debug
    cmake --build $BUILD_TEST_DIR/Test3 --config Debug
    if ($IsWindows) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test3 --target RUN_TESTS}
    if ($IsLinux) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test3 --target test}
}

if ((-not $Test) -or ($Test).Contains('Test4'))
{
    Write-Host -ForegroundColor Yellow "TEST 4"
    cmake -B $BUILD_TEST_DIR/Test4 -S $Lab -DCMAKE_C_COMPILER=clang -DENABLE_USAN=true -DUNLIMITED=ON -DCMAKE_BUILD_TYPE=Debug
    cmake --build $BUILD_TEST_DIR/Test4 --config Debug
    if ($IsWindows) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test4 --target RUN_TESTS}
    if ($IsLinux) {cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build $BUILD_TEST_DIR/Test4 --target test}
}