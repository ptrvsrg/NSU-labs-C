$LAB = $args[0]
$BUILD_DIR = "build_$LAB"
$STATUS = 0

if (-not (Test-Path $LAB))
{
    $STATUS = 1
    Write-Host -ForegroundColor Red "No such file or directory"
}

if (Test-Path -Path $BUILD_DIR) 
{ 
    Remove-Item $BUILD_DIR -Force -Recurse 2>&1 > $null 
}
New-Item -Path $BUILD_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_DIR

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
New-Item -Path "Test1" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test1"
cmake -DUNLIMITED=ON ../../$LAB
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 2
    PrintInOut 
}
Set-Location ../

Write-Host -ForegroundColor Yellow "TEST 2"
New-Item -Path "Test2" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test2"
cmake -DUNLIMITED=OFF ../../$LAB
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 3
    PrintInOut 
}
Set-Location ../

Write-Host -ForegroundColor Yellow "TEST 3"
New-Item -Path "Test3" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test3"
cmake ../../$LAB -DENABLE_ASAN=true -DUNLIMITED=ON
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 4
    PrintInOut 
}
Set-Location ../

Write-Host -ForegroundColor Yellow "TEST 4"
New-Item -Path "Test4" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test4"
cmake ../../$LAB -DENABLE_USAN=true -DUNLIMITED=ON
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 5
    PrintInOut 
}
Set-Location ../../

exit $STATUS