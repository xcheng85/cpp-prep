# cpp-prep
cpp prep

## project scaffolding
```shell
mkdir -p cmake src test

touch CMakeLists.txt
touch build.sh

cd cmake && touch CHECK_INSOURCE_BUILD.cmake && cd ..

cd test && touch CMakeLists.txt && cd ..

cd src && touch CMakeLists.txt && cd ..
```

## for windows
cuda issues

copying the 4 VS integration files (from C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.2\extras\visual_studio_integration\MSBuildExtensions) to both:

C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Microsoft\VC\v170\BuildCustomizations
and C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Microsoft\VC\v170\BuildCustomizations
