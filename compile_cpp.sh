#Compile the code
# if the file HW2 exits then remove it
if [ -f HW2 ]; then
    rm HW2
fi
g++ HW2.cpp -o HW2
# if the file HW2 does not exit then exit the test
if [ ! -f HW2 ]; then
    echo   "\033[1;91mCompile FAILED.\033[0m"
    exit
fi