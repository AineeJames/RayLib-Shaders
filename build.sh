clang `pkg-config raylib --cflags` main.c -o main `pkg-config raylib --libs` 
if [ $? -eq 0 ]; then
  echo "Done compiling..."
  ./main
else
  echo "Compile error!"
fi
