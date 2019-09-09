cmake -E make_directory "build-win" && cmake -E chdir "build-win" cmake -G "Visual Studio 15 Win64" ../ -DTHE_PROJECT_PREFIX=""
pause