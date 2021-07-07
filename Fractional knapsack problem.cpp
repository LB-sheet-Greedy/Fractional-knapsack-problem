/*
Approach 1: Brute force/Niave
			A brute-force solution would be to try all possible subset with all different 
			fraction but that will be too much time taking. 
			
Approach 2:  Use Greedy approach bcoz we have to maximize our number (profit).

			 Calculate the ratio value/weight for each item and sort the item on basis of this ratio.
			 
			 Then take the item with the highest ratio and add them until we can’t add the next item 
			 as a whole and at the end add the next item as much as we can. 
			
			TC => O(nlogn) for sorting
			 
____________________________What I learned new here:______________________________

C++ structure ke andar member function daal sakte.Structures in C cannot have member functions 
inside structure but Structures in C++ can have member functions along with data members.

EX:

struct marks {
    int num;
    void
    Set(int temp)   // Member function inside Structure to
                    // take input and store it in "num"
    {
        num = temp;
    }
    void display()  //  function used to display the values
    {
        printf("%d", num);
    }
};
// Driver Program
int main()
{
    struct marks m1;
    m1.Set(9); // calling function inside Struct to
               // initialize value to num
    m1.display(); // calling function inside struct to
                  // display value of Num
}

o/p => 9

Constructor creation in structure: Structures in C cannot 
have constructor inside structure but Structures in C++ can have Constructor creation.

EX:

struct Student {
    int roll;
    Student(int x)
    {
        roll = x;
    }
};
 
// Driver Program
int main()
{
    struct Student s(2);
    printf("%d", s.x);
    return 0;
}

o/p => 2

Third parameter in C++ STL function sort() (Its optional parameter)
It generally takes two parameters, the first one being the point of 
the array/vector from where the sorting needs to begin and the second 
parameter being the length up to which we want the array/vector to get sorted. 
The third parameter is optional and can be used in cases such as if we want to sort the elements lexicographically.

By default, the sort() function sorts the elements in ascending order.

How to sort in a particular order? 
We can also write our own comparator function and pass it as a third parameter. 
This “comparator” function returns a value; convertible to bool, which basically 
tells us whether the passed “first” argument should be placed before the passed “second” argument or not. 

For eg: (SORTING INTERVALS) In the code below, suppose intervals {6,8} and {1,9} are passed as arguments in the “compareInterval” 
function(comparator function). Now as i1.first (=6) > i2.first (=1), so our function returns “false”, which 
tells us that “first” argument should not be placed before “second” argument and so sorting will be done in 
order like {1,9} first and then {6,8} as next. 

// A C++ program to demonstrate
// STL sort() using
// our own comparator
#include <bits/stdc++.h>
using namespace std;
 
// An interval has a start
// time and end time
struct Interval {
    int start, end;
};
 
// Compares two intervals
// according to staring times.
bool compareInterval(Interval i1, Interval i2)
{
    return (i1.start < i2.start);
}
 
int main()
{
    Interval arr[]
        = { { 6, 8 }, { 1, 9 }, { 2, 4 }, { 4, 7 } };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    // sort the intervals in increasing order of
    // start time
    sort(arr, arr + n, compareInterval);
 
    cout << "Intervals sorted by start time : \n";
    for (int i = 0; i < n; i++)
        cout << "[" << arr[i].start << "," << arr[i].end
             << "] ";
 
    return 0;
}

Output: 

Intervals sorted by start time : 
[1,9] [2,4] [4,7] [6,8] 

*/

//___________________________________________________________________________________________________________________________
#include<iostream>
#include<algorithm> //to use sort()

using namespace std;

// Structure for an item which stores weight and corresponding value of Item
struct Item 
{
	//data members
    int value;
	int weight;
 
    // Constructor use kiya to automatixally initialise whenever class/struct is created
    Item(int v, int w)
    {
       value=v;
       weight=w;
    }
};

// Our own Comparison function to sort Item according to val/weight ratio in decreasing order i.e from hightest -> lowest ratio
bool cmp(struct Item a, struct Item b)
{
    double ratio_1 = (double)a.value / (double)a.weight;  //type cast kiya double me
    double ratio_2 = (double)b.value / (double)b.weight;  //type cast kiya double me
    
    //returns true if the condition holds
    return ratio_1>ratio_2;
}

//our important function that uses greedy approach
double fractionalKnapsack(int W, struct Item arr[], int n)
{
    //sorting Item on basis of ratio using 3rd argument in sort()
    sort(arr, arr + n, cmp);
 
    //check karne ke liye ki kaise sort kiya
    cout<<"\nValues sorted as per ratio\n";
    for (int i = 0; i < n; i++)
    {
    	cout<<"\n";
        cout << arr[i].value << "  " << arr[i].weight << " : "<< ((double)arr[i].value / arr[i].weight);
    }
    
 
    int curWeight = 0;       // Current weight in our knapsack
    double finalvalue = 0.0; // Result that will be our answer
 
    //Loop through all Items one by one
    for (int i=0;i<n;i++) 
	{
        // If adding Item won't overflow, add it completely
        if ((curWeight+arr[i].weight)<=W) 
		{
            curWeight=curWeight+arr[i].weight;
            finalvalue=finalvalue+arr[i].value;
        }
        // If we can't add full current Item, add fractional part of it
        else 
		{
			/*
			Ye compare karke likha means agar isse itna to usse kitna. Vo tha na ratio and proportion me unitary method
			Ex: Apna table >> value: 60 100 120
							  weight:10 20  30
							  ratio: 6   5  4   (sorted from highest to lowest in order to maximize number
							  
							  our final value => 60(10)+100(20)+120(20/30) = 240
							                                    ye 20 jo hai ye => 50(or W)-30(or curValue) hai.Bas code kiya
			
			*/
            int remaining=W-curWeight;
            //double isiliye liya taaki precision bana rahe and overflow na ho jo float agar lete to hota tha
            finalvalue+=arr[i].value*((double)remaining/(double)arr[i].weight);
            break;
        }
    }
 
// Returning final answer
return finalvalue;
}

int main()
{
	//static hi rakh raha hu inputs 
	
	int W = 50; //    Weight of our knapsack
	
    Item arr[] = { { 60, 10 }, { 100, 20 }, { 120, 30 } };  //constructor ke kaaran automatic value initialise hogi
 
    int n = sizeof(arr) / sizeof(arr[0]);
 
    // Function call
    cout << "\nMaximum value we can obtain = "
         << fractionalKnapsack(W, arr, n);
	
	return 0;
}
