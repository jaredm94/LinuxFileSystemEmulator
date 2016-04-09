# Remove past executable
rm emulator

# Create executable from object files
gcc -w *.c *.h -o emulator

# Run emulator
./emulator
