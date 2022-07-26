$LAB = $args[0]
$BUILD_DIR = "build_$LAB"
$STATUS = 0

if (Test-Path -Path $BUILD_DIR) { Remove-Item $BUILD_DIR -Force -Recurse 2>&1 > $null }
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

New-Item -Path "Test1" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test1"
cmake -DUNLIMITED=ON ../../$LAB
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure || ($STATUS = 1)
if ($STATUS -eq 1) { PrintInOut }
Set-Location ../

New-Item -Path "Test2" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test2"
cmake -DUNLIMITED=OFF ../../$LAB
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure || ($STATUS = 2)
if ($STATUS -eq 2) { PrintInOut }
Set-Location ../

New-Item -Path "Test3" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test3"
cmake ../../$LAB -DENABLE_ASAN=true -DUNLIMITED=ON
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure || ($STATUS = 3)
if ($STATUS -eq 3) { PrintInOut }
Set-Location ../

New-Item -Path "Test4" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test4"
cmake ../../$LAB -DENABLE_USAN=true -DUNLIMITED=ON
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure || ($STATUS = 4)
if ($STATUS -eq 4) { PrintInOut }
Set-Location ../../

exit $STATUS