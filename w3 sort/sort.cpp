#include <iostream>
#include <chrono> // for the high_resolution_clock function

/* README
 *  In this week, we'll compare the performance of different search and sorting algorithms.
 *
 *  There is a random number generator function below which is useful for populating your structures with test data.
 *  I've also included code to time the duration of these functions, using the 'high_resolution_clock' function of the 'chrono' library.
 *  Like before, I've included the exercise function declarations for you to complete the definition for.
 *
 */

using namespace std;

#include <random>

int getRandomNumber()
{
    // from C++11 - more reliable than the older C-style srand() function:
    random_device rd;                                   // obtain a random seed from the hardware
    mt19937 eng(rd());                                  // Standard Mersenne Twister engine seeded with rd()
    uniform_int_distribution<int> distribution(1, 100); // distribution from 1 to 100

    int randomNumber = distribution(eng); // generate random number

    return randomNumber;
}

// below are the exercise function declarations

void initArray(int arr[], int size);                 // Exercise 1
void bubbleSort(int arr[], int size);                // Exercise 2
void mergeSort(int arr[], int left, int right);      // Exercise 3
void merge(int arr[], int left, int mid, int right); // Exercise 3
int linearSearch(int arr[], int size, int target);   // Exercise 4
int binarySearch(int arr[], int size, int target);   // Exercise 5
void printArray(int arr[], int len);

bool isSorted(int arr[], int len)
{
    int i = 0;
    for (i; i < len - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    cout << "C++ DS&A Big O + Search and Sorting algorithms\n"
         << endl;

    /* Exercise 1 - Initialise the small and large arrays*/

    // initialise a constant for SIZE_S with the value 100
    const int SIZE_S = 100;
    const int SIZE_L = 10000;
    // initialise a constant for SIZE_L with the value 100000
    int *smallArray = (int *)malloc(32 * SIZE_S); // extend this statement so you point to an array of SIZE_S using the 'new' keyword
    int *largeArray = (int *)malloc(32 * SIZE_L); // extend this statement so you point to an array of SIZE_L using the 'new' keyword

    // uncomment below once ready
    initArray(smallArray, SIZE_S);

    // uncomment below once ready
    initArray(largeArray, SIZE_L);

    /* EXERCISE 2 - Bubble Sort */

    // START TIMER for the smallArray
    auto start = chrono::high_resolution_clock::now();
    mergeSort(largeArray, 0,SIZE_L);
    // END TIMER for the smallArray
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Elapsed for bubble sort small time: " << duration.count() << " seconds\n";



    cout<<"\n position of 34 = "<<binarySearch(largeArray, 1000, 34);


    // START TIMER
    // bubbleSort(largeArray, SIZE_L);
    // END TIMER

    /* Exercise 3 - Merge Sort */

    // START TIMER
    // cout<< "\nExercise 3: Merge Sort on an array of size " << SIZE_S << endl;
    // mergeSort(smallArray, 0, SIZE_S-1);
    // END TIMER

    // cout<< "\nExercise 3: Merge Sort on an array of size " << SIZE_L << endl;
    //  START TIMER
    // mergeSort(largeArray, 0, SIZE_L-1);
    //  END TIMER

    /* Exercise 4 - Linear Search */
    int target = 0;
    int index = 0;
    // START TIMER
    // linearSearch(largeArray, SIZE_L, target);
    // END TIMER

    /* Exercise 5 - Binary Search */

    // START TIMER
    // index = binarySearch(largeArray, SIZE_L, target);
    // END TIMER

    getchar();
    return 0;
}

/*
 * Exercise 1: Completing the initArray function below which takes a pointer to an array and the size to iterate through.
 * Write a loop which iterate through the array (being pointed to) and assign random values (using the getRandomNumber function above) for each element.
 * You should code the function in a way that can be reused for different array sizes.
 */

void initArray(int arr[], int size)
{
    cout << "\nExercise 1: Initialise an array of size " << size << endl;

    int i = 0;
    for (i; i < size; i++)
    {
        arr[i] = getRandomNumber();
    }
}

void printArray(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "\n"
             << to_string(arr[i]);
    }
}

/*
 * Exercise 2:
 * Implement a Bubble Sort algorithm in the function below.
 * Pass both the small and large arrays to this function and time how long each takes.
 *
 * Extension: are there any ways to optimise this bubble sort function?
 * Compare the time of the optimised against the unoptimised original algorithm
 */

void bubbleSort(int arr[], int size)
{
    cout << "\nExercise 2: Bubble Sort on an array of size " << size << endl;

    int i = 0;
    int j = 0;

    bool swapped;

    int n1 = 0;
    int n2 = 0;

    for (i = 0; i < size - 1; i++)
    {

        swapped = false;
        for (j = 0; j < size - i - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }

    /*
        while (isSorted(arr, size) == false)
        {
            for (i; i < size - 1; i++)
            {
                n1 = arr[i];
                n2 = arr[i + 1];
                if (n2 < n1)
                {
                    arr[i] = n2;
                    arr[i + 1] = n1;
                }
            }
        }
    */
    // implement your solution here
}

/*
 * Exercise 3: Provided the 'merge' logic below, complete the 'merge sort' function to complete the algorithm.
 * Once complete, comment out your 'exercise 2 bubble sort function calls' and instead call merge sort on the small and large arrays.
 *
 * Extension : If you have 'time', why not increase the size of the 'largeArray' by an appropriate interval (e.g. another 100000)
 * and observe the time difference between bubble sort and merge sort algorithms.
 * What do you notice?
 */

void mergeSort(int arr[], int left, int right)
{
    if(left>=right) return;
    int mid=left+(right-left)/2;
    mergeSort(arr,left,mid);
    mergeSort(arr,mid+1,right);
    merge(arr,left,mid,right);
}

// merge given here to save time
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

/*
 * Exercise 4: Implement the Linear Search algorithm below.
 * To start, just check that you can find a value that is in an array (positive case).
 * Also check the negative case - where a value isn't in the array.
 *
 * In the next exercise, we will compare the speed of linear and binary search for locating the same element.
 *
 */

int linearSearch(int arr[], int size, int target)
{
    cout << "\nExercise 4: Linear Search of array of size " << size << " to locate value " << target << endl;

    // implement your solution here.

    return 0; // think about return values for both positive and negative cases of finding the target
}

/* Exercise 5: Now implement the binary search function below.
 * For comparing the time taken to find values, find ensure the small and large arrays are sorted (either sort algorithm).
 * Then select values at the start, mid and end of the list to pass to both binary and linear search run on the SAME array.
 *
 * Note: You could modify the signature to pass in left and right,
 * but as left is usually initialised to 0, and right to size-1,
 * this can be infered from size being passed in.
 *
 * Extension : Can you modify the algorithm to not just return/print the first instance of a value,
 * but count (and/or index positions) of each instance of this value in the structure.
 */

int binarySearch(int arr[], int size, int target)
{
    cout << "Exercise 5: Binary Search of array of size " << size << " to locate value " << target << endl;

    int left = 0;
    int right = size - 1;

    int mid = left;

    while(left<=right){
        mid=right+left/2;
        if (arr[mid]==target){
            return mid;
        }else{
            if(mid<target){
                left=mid+1;
            }else{
                right=mid+1;
            }
        }
    }

    // whilst left is less than or equal to right
    // set mid
    // if mid is target
    // return index of mid
    // else if mid less than target
    // set left to mid + 1
    // else
    // set right to mid - 1

    return 0;
}
