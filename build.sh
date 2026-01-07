g++ -o main main.cpp crypto_functions.cpp

if [ $? -eq 0 ]; then
    ./main
else
    echo "--- Compilation Failed! Check the errors printed above. ---"
    read -p "Press [Enter] key to continue..."
fi