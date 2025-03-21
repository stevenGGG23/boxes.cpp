
#include <iostream>
#include <fstream>
#include <cassert>
#include <iomanip>
using namespace std;

// function Prototypes
int ReadData(ifstream &myIn, string classNames[], int boxes[], int &numClasses, const int maxClasses);
string FindWinner(const string classNames[], const int boxes[], int numClasses);
void DisplayResults(const string classNames[], const int boxes[], int numClasses);
void SortData(string classNames[], int boxes[], int numClasses);

int main() {
    const int MAX_CLASSES = 10;  // Define the maximum number of classes in main()

    // open file 
    ifstream myIn;
    myIn.open("boxes.dat");
    assert(myIn); //make sure it's open correctly

    string classNames[MAX_CLASSES];  // Array to hold class names
    int boxes[MAX_CLASSES];  // Array to hold boxes sold for each class
    int numClasses = 0;  // Track number of distinct classes

    // Read the data and fill the arrays
    ReadData(myIn, classNames, boxes, numClasses, MAX_CLASSES);  // Pass MAX_CLASSES here

    // Sort the classes by the number of boxes sold in descending order
    SortData(classNames, boxes, numClasses);

    // Display the results in a table format
    DisplayResults(classNames, boxes, numClasses);

    // Find and display the winner
    string winner = FindWinner(classNames, boxes, numClasses); 
    int winnerScore = boxes[numClasses - 1];  // After sorting, the winner is at the last index
    cout << "The winner is " << winner << " with " << winnerScore << " boxes." << endl;

    myIn.close(); // Close the file
   
    return 0;
}

// reads the sales data and accumulates boxes sold for each class
int ReadData(ifstream &myIn, string classNames[], int boxes[], int &numClasses, const int maxClasses) {
    string className;
    int boxCount;

    // Read each sales record from the file
    while (myIn >> className >> boxCount) {
        bool found = false; // flag 

        // Check if the class already exists
        for (int i = 0; i < numClasses; i++) {
            if (classNames[i] == className) {
                boxes[i] += boxCount;  // Add boxes to class
                found = true;
                break;
            }
        }

        // Assert that we either found an existing class or we haven't reached the array limit
        assert(found || numClasses < maxClasses);  // Ensure we don't go over the array limit

        if (!found) {
            // If not found, add the new class to the array
            assert(numClasses < maxClasses);  // Ensure there is space to add a new class
            classNames[numClasses] = className;
            boxes[numClasses] = boxCount;
            numClasses++; // increment 
        }
    }

    return numClasses;  // Return number of distinct classes
}

// finds the class that sold the most boxes
string FindWinner(const string classNames[], const int boxes[], int numClasses) {
    int maxBoxes = boxes[0];  // Start with the first class as the max
    int winnerIndex = 0;

    // Scan through the boxes array to find the maximum value
    for (int i = 1; i < numClasses; i++) {
        if (boxes[i] > maxBoxes) {
            maxBoxes = boxes[i];
            winnerIndex = i;
        }
    }

    return classNames[winnerIndex];  // Return winner class name 
}

// prints the sales data in table format
void DisplayResults(const string classNames[], const int boxes[], int numClasses) {

    cout << "The final results are:" <<endl; 

    // Display each class and the number of boxes sold
    for (int i = 0; i < numClasses; i++) {
        cout << left << setw(18) << classNames[i] << setw(18) << boxes[i] << endl;
    }

    cout << endl;
}

// Sort the data using bubble sort (from least to greatest)
void SortData(string classNames[], int boxes[], int numClasses) {
    for (int i = 0; i < numClasses - 1; i++) {
        for (int j = 0; j < numClasses - 1 - i; j++) {
            if (boxes[j] > boxes[j + 1]) {  
                
                // Swap boxes
                int tempBox = boxes[j];
                boxes[j] = boxes[j + 1];
                boxes[j + 1] = tempBox;

                // Swap class names to match the swapped boxes
                string tempName = classNames[j];
                classNames[j] = classNames[j + 1];

                classNames[j + 1] = tempName;
            }
        }
    }
}
