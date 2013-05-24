
call "H:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\amd64\vcvars64.bat"

pushd .\liblower\VC\liblower\
MSBuild /p:configuration=Release /p:platform=Win32
popd

pushd .\libloaders\VC\libloaders\
MSBuild /p:configuration=Release /p:platform=Win32
popd

pushd .\libseldom\VC\libseldom\
MSBuild /p:configuration=Release /p:platform=Win32
popd

copy .\liblower\VC\liblower\Release\liblower.lib .\lib\
copy .\libloaders\VC\libloaders\Release\libloaders.lib .\lib\
copy .\libseldom\VC\libseldom\Release\libseldom.lib .\lib\

pause

pushd .\VC\
MSBuild /p:configuration=Release /p:platform=Win32
copy .\Release\*.exe .\Final\
popd

pause
