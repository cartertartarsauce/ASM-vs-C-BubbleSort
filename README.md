# ASM-vs-C-BubbleSort
Using both Assembly and C++, this program can input a file of 64-bit numbers, sort them with either the assembly or c++ bubblesort functions, output the results to their respective text files, and display the time in milliseconds that it took to run the sorting operations.
> g++ -c c_bubbleSort.cpp
> 
> as -g -o a_bubbleSort.o a_bubbleSort.s
> 
> g++ -c rasm5.cpp
> 
> g++ -o rasm5.out rasm5.o c_bubbleSort.o a_bubbleSort.o
