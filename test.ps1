$LAB = $args[0]
$BUILD_TEST_DIR = "build_$LAB"
$STATUS = 0

<<<<<<< HEAD
if (-not (Test-Path $LAB))
=======
if (-not (Test-Path -Path $LAB))
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb
{
    $STATUS = 1
    Write-Host -ForegroundColor Red "No such file or directory"
}

<<<<<<< HEAD
if (Test-Path -Path $BUILD_DIR) 
{ 
    Remove-Item $BUILD_DIR -Force -Recurse 2>&1 > $null 
}
New-Item -Path $BUILD_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_DIR
=======
if (Test-Path -Path $BUILD_TEST_DIR) 
{ 
    Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 
}
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb

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
<<<<<<< HEAD
New-Item -Path "Test1" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test1"
cmake -DUNLIMITED=ON ../../$LAB
=======
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake -DUNLIMITED=ON ../$LAB
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb
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
<<<<<<< HEAD
New-Item -Path "Test2" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test2"
cmake -DUNLIMITED=OFF ../../$LAB
=======
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake -DUNLIMITED=OFF ../$LAB
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb
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
<<<<<<< HEAD
New-Item -Path "Test3" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test3"
cmake ../../$LAB -DENABLE_ASAN=true -DUNLIMITED=ON
=======
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake ../$LAB -DCMAKE_C_COMPILER=clang -DENABLE_ASAN=true -DUNLIMITED=ON
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb
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
<<<<<<< HEAD
New-Item -Path "Test4" -ItemType "directory" 2>&1 > $null
Set-Location -Path "Test4"
cmake ../../$LAB -DENABLE_USAN=true -DUNLIMITED=ON
=======
New-Item -Path $BUILD_TEST_DIR -ItemType "directory" 2>&1 > $null
Set-Location -Path $BUILD_TEST_DIR
cmake ../$LAB -DCMAKE_C_COMPILER=clang -DENABLE_USAN=true -DUNLIMITED=ON
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb
cmake --build . --config Debug
ctest -C Debug --rerun-failed --output-on-failure
if (Test-Path ./Testing/Temporary/LastTestsFailed.log) 
{ 
    $STATUS = 5
    PrintInOut 
}
<<<<<<< HEAD
Set-Location ../../

=======
Set-Location ../
Remove-Item $BUILD_TEST_DIR -Force -Recurse 2>&1 > $null 

Write-Output $STATUS
>>>>>>> 83245f5c961f5315a8028a2636d1266ea89edbfb
exit $STATUS