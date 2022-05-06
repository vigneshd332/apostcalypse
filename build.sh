echo "You are about to commence the build, after the build, an executable 'apost.exe' will be created."
echo "Make sure you have cmake and make installed."
echo "Press [ENTER] to continue..."
read

echo "Generating Makefile..."
cmake -G "Unix Makefiles" .

echo "Building..."
make

echo "Build Done."
echo "Cleaning up..."
rm -rf CMakeFiles
rm -rf CMakeCache.txt
rm -rf Makefile
rm -rf cmake_install.cmake
