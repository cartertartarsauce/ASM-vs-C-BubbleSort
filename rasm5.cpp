// Carter Froning, RASM5, last updated 5-16-24
// rasm5.cpp : Create a C++ driver that serves as a menu to call both your C++/ASM bubbleSort
// functions and the C++/ASM insertionSort functions. Upload input from a text file and use it
// to form an array of integers, to which we can select how to sort it. Each time we sort, we
// update the time displayed to the menu in the terminal.

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <chrono>
#include "c_bubbleSort.h"

using namespace std;
extern "C" void a_bubbleSort(long long*,int);

int main()
{
    //each time the program is run, the output text files will reset to be empty
    ifstream file;   // "input.txt"
    ofstream CBfile; // "c_bubblesort.txt"
    ofstream ABfile; // "a_bubblesort.txt"
    string line;     // temporary line variable
    int fileElemCount = 0;          //initialize file element number to 0
    int input = 0;                  //initialize user input to 0
    int CBTime = 0;                 //initialize C++ BubbleSort time
    int ABTime = 0;                 //initialize ASM BubbleSort time
    int CITime = 0;                 //initialize C++ InsertionSort time
    int AITime = 0;                 //initialize ASM InsertionSort time
    long long* quadArray = nullptr; //pointer to quadArray
    bool isArraySet = false;        //bool to see if the array is loaded


    //Loop to drive the menu
    while (input != 4)
    {
        std::cout << endl;
        std::cout << "               RASM 5: C vs Assembly" << endl;
        std::cout << "               File Element Count: " << fileElemCount << endl;
        std::cout << "------------------------------------------------------" << endl;
        std::cout << "C++ bubbleSort Time: " << CBTime << " ms" << endl;
        std::cout << "ASM bubbleSort Time: " << ABTime << " ms" << endl;
        std::cout << "------------------------------------------------------" << endl;
        std::cout << "<1> Load input file (quads/long long ints)" << endl;
        std::cout << "<2> Sort using C++ bubbleSort Algorithm" << endl;
        std::cout << "<3> Sort using Assembly bubbleSort Algorithm" << endl;
        std::cout << "<4> Quit" << endl << endl;

        //gather user input
        std::cout << "Enter a choice: ";
        cin >> input;

        //switch statement (1-4):
        switch (input)
        {
        case 1:
            std::cout << endl << "Loading input file..." << endl;

            if (isArraySet)
            {
                std::cout << "File already loaded.";
                break;
            }

            file.open("input.txt");

            if (!file.is_open())
                std::cout << "Error loading file.";
            else
            {
                fileElemCount = 0;    //reset fileElement Counter to 0

                //Count # of numbers in file
                while (getline(file, line))
                    fileElemCount++;

                //clear file flags and reset the file stream (after counting elements in file)
                file.clear();
                file.seekg(0, std::ios::beg);

                //Allocate an array to size of the element counter
                quadArray = new long long[fileElemCount];
                int i = 0;

                //For each line, convert to long long and add to allocated array
                while (getline(file, line))
                {
                    //Check i to ensure we dont overwrite buffer in quad array
                    if (i >= fileElemCount)
                        break;
                    else
                    {
                        //for each value in the file, convert to long long and copy to the array
                        long long value = std::stoll(line);
                        quadArray[i] = value;
                        i++;
                    }
                }
                file.close();
            }
            isArraySet = true;
            break;
    
        case 2: //CASE 2: C++ BUBBLESORT
            //ensure the array is not empty before proceeding to call a sort on it
            if (!isArraySet)
            {
                std::cout << "Error: No elements in the array." << endl;
                break;
            }
            else
            {
                std::cout << endl << "Sorting the array..." << endl;

                //Call and set timer for the C++ BubbleSort
                auto startTime = chrono::high_resolution_clock::now();
                c_bubbleSort(quadArray, fileElemCount);
                auto endTime = chrono::high_resolution_clock::now();

                //calculate the time save as milliseconds
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                CBTime = static_cast<int>(duration.count());

                std::cout << endl << "Done." << endl;
            }

            //CBfile is where the sorted C++ Bubblesort function result gets stored
            CBfile.open("c_bubblesort.txt");
            
            if (!CBfile.is_open())
            {
                std::cout << "Error loading c_bubblesort.txt" << endl;
            }
            else
            {
                std::cout << endl << "Saving sorted array to c_bubblesort.txt..." << endl;

                for (int i = 0; i < fileElemCount; ++i)
                    CBfile << quadArray[i] << endl;

                CBfile.close();

                std::cout << endl << "Done." << endl;
            }

            //DEALLOCATE ARRAY AFTER USING IT
            delete[] quadArray;
            quadArray = nullptr;
            isArraySet = false;
            fileElemCount = 0;

            break;

        case 3: //CASE 3: ASM BUBBLESORT
            //ensure the array is not empty before proceeding to call a sort on it
            if (!isArraySet)
            {
                std::cout << "Error: No elements in the array." << endl;
                break;
            }
            else
            {
                std::cout << endl << "Sorting the array..." << endl;

                //Call and set timer for the C++ BubbleSort
                auto startTime = chrono::high_resolution_clock::now();
                a_bubbleSort(quadArray, fileElemCount);
                auto endTime = chrono::high_resolution_clock::now();

                //calculate the time save as milliseconds
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                ABTime = static_cast<int>(duration.count());

                std::cout << endl << "Done." << endl;
            }

            //ABfile is where the sorted Assembly Bubblesort function result gets stored
            if (!ABfile.is_open())
            {
                std::cout << "Error loading a_bubblesort.txt" << endl;
            }
            else
            {
                std::cout << endl << "Saving sorted array to a_bubblesort.txt..." << endl;

                for (int i = 0; i < fileElemCount; ++i)
                    ABfile << quadArray[i] << endl;

                ABfile.close();

                std::cout << endl << "Done." << endl;
            }

            //DEALLOCATE ARRAY AFTER USING IT
            delete[] quadArray;
            quadArray = nullptr;
            isArraySet = false;
            fileElemCount = 0;

            break;

        case 4:
            //Code to quit program
            break;

        default:
            std::cout << "Please enter a valid number 1-4..." << endl;
            break;
        }

        //clear screen a bit each time before printing menu
        std::cout << endl << endl << endl << endl;
    }
    std::cout << "Quitting..." << endl;
}

