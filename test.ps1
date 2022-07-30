$LAB = $args[0]
$BUILD_TEST_DIR = "build_$LAB"
$STATUS = 0

if (-not (Test-Path -Path $LAB))
{
    $STATUS = 1
    Write-Host -ForegroundColor Red "No such file or directory"
}

if (Test-Path -Path $BUILD_TEST_DIR) 
{ 
    Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 
}

function PrintInOut
{
    if ((Test-Path -Path "in.txt") -and (Test-Path -Path "out.txt"))
    {
        Write-Host -ForegroundColor Yellow "in.txt"
        -join [char[]](Get-Content -Path "in.txt" -AsByteStream -totalcount 256)
        Write-Host -ForegroundColor Yellow "out.txt"
        -join [char[]](Get-Content -Path "out.txt" -AsByteStream -totalcount 256)
        Write-Host ""
    }
}

Write-Host -ForegroundColor Yellow "TEST 1"
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake -DUNLIMITED=ON ../$LAB
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 2
    PrintInOut 
}
Set-Location ../
Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 

Write-Host -ForegroundColor Yellow "TEST 2"
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake -DUNLIMITED=OFF ../$LAB
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 3
    PrintInOut 
}
Set-Location ../
Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 

Write-Host -ForegroundColor Yellow "TEST 3"
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake ../$LAB -DCMAKE_C_COMPILER="C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" -DENABLE_ASAN=true -DUNLIMITED=ON
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 4
    PrintInOut 
}
Set-Location ../
Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 

Write-Host -ForegroundColor Yellow "TEST 4"
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake ../$LAB -DCMAKE_C_COMPILER="C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/bin/Hostx64/x64/cl.exe" -DENABLE_USAN=true -DUNLIMITED=ON
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 5
    PrintInOut 
}
Set-Location ../
Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 

exit $STATUS