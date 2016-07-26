/**********************************************
 * Sweetness
 *********************************************/
#include <iostream>
#include <math.h>       /* floor & sqrt */
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

double findSDeviation(int rangeMin, int constant);
void evaluateConstant(char * argv[]);
void compareConstants(char * argv[]);
double findSweetness(int rangeMin, int constant);
bool isPrime(int number);
void solveForPrimes(int arraySize);
void findPrime(char * argv[]);
void learned();
void usage();
bool * numberArray;
/*********************************************
 * Main
 ********************************************/
int main(int argc, char* argv[])
{  
   if (argc == 1)
   {
      learned();
      usage();
      return 0;
   }
   else if (argc == 2 || argc == 3 || argc == 4)
   {
      cout << "Solving for primes - Please wait\n";
      int arraySize= 500000000;
      numberArray = new bool[arraySize];
      solveForPrimes(arraySize);
      
      if (argc == 3) // find one particular c
      {
         evaluateConstant(argv);
      }
      else if (argc == 4)   // find the greatest c
      {
         compareConstants(argv);
      }
      else // argc == 2 // find the nth prime
         findPrime(argv);
   }
   else
   {
      cout << "Oh bother! Those parameters are wrong!\n";
      return 0;
   }
   return 0;
}

/*********************************************
 * evaluateConstant
 ********************************************/
void evaluateConstant(char * argv[])
{
   int rangeMin = atoi(argv[1]);
   int constant = atoi(argv[2]);
   double sweetness = findSweetness(rangeMin, constant);
   double sDeviation = findSDeviation(rangeMin, constant);

   if (sweetness == 0)
      cout << "Sorry, that constant produces no primes. How sour!\n";
   else
      cout << "Sweetness for constant " << constant << ": " << sweetness << "%" << endl
           << "Standard Deviation of x's that produce primes: " << sDeviation << endl;
}

/*********************************************
 * compare Constants
 ********************************************/
void compareConstants(char * argv[])
{
   int rangeMin = atoi(argv[1]);
   int constantMin = atoi(argv[2]);
   int constantMax = atoi(argv[3]);
   int constantSweet = 0;
   double mostSweet = 0.0;
   double currentSweet = 0.0;
   double mostSweetDev = 0.0;
   double currentSweetDev = 0.0;

   cout << "Solving for sweetest constant - Please wait\n";
   for (int constantCurrent = constantMin; constantCurrent < constantMax; constantCurrent++)
   {
      currentSweet = findSweetness(rangeMin, constantCurrent);

      if (currentSweet > mostSweet) // if one sweetness score is higher simply switch them
      {
         mostSweet = currentSweet;
         constantSweet = constantCurrent;
      }
      else if (currentSweet == mostSweet) // if sweetness scores match judiciously compare the standard deviation. 
      {
         currentSweetDev = findSDeviation(rangeMin, constantCurrent);
         mostSweetDev = findSDeviation(rangeMin, constantSweet);
         if (mostSweetDev > currentSweetDev)
         {
            mostSweet = currentSweet;
            constantSweet = constantCurrent;
         }
      }
   }
   
   // Make sure we have the correct standard deviation
   mostSweetDev = findSDeviation(rangeMin, constantSweet);
   
   cout << "Sweetest constant: " << constantSweet << endl
        << "Percentage of sweetness: " << mostSweet << endl
        << "Standard deviation of x's that produce primes: " << mostSweetDev;
}

/*********************************************
 * find sweetness
 ********************************************/
double findSweetness(int rangeMin, int constant)
{
   int rangeMax = rangeMin + 10000; // YES
   int number; /// YES
   int numPrimes = 0; // YES

   for (int x = rangeMin; x < rangeMax; x++) // 10000's close to 0 
   {
      number = abs(x * x + x + constant);

      // check if x produces a prime
      if (isPrime(number))
      {
         numPrimes++; // increment number and primes (ie. x's that produce an x)
      }
   }
  
   double sweetness = (double)numPrimes / 100.0;

   return sweetness;
}

/********************************************
 * find SDeviation
 ********************************************/
double findSDeviation(int rangeMin, int constant)
{
   int rangeMax = rangeMin + 10000; // YES     
   int number;
   int numPrimes = 0; // YES
   int upperValue; 
   int lowerValue;
   vector<int>spaces;
   int gap = 0;
   int totalGap = 0;
   double sum = 0;
   
   for (int x = rangeMin; x < rangeMax; x++) // 10000's close to 0 
   {
      number = abs(x * x + x + constant);

      if (isPrime(number))
      {
         numPrimes++; // increment number and primes (ie. x's that produce an x)
         if (numPrimes > 1)
         {
            upperValue = x;
            gap = upperValue - lowerValue;
            totalGap += gap;
            spaces.push_back(gap);
            lowerValue = upperValue;
         }
         else
            lowerValue = x;
      }
   }
   double average = (double)totalGap / ((double)numPrimes - 1.0);
   
   if (spaces.size() > 0)
   {
      for (int i = 0; i < numPrimes - 1; i++) 
      {
         sum += pow(spaces[i] - average, 2);
      }
   }
   
   double variance = sum / spaces.size();
   
   double sDeviation = sqrt(variance);

   return sDeviation;
}

/*********************************************
 *find Prime
 ********************************************/
void findPrime(char *argv[])
{
   int nthPrime = atoi(argv[1]);
   int checkPrime = 0;
   int i = 0;

   // if we want the 3rd prime (5)
   // prime = 3
   // 
   
   while (checkPrime != nthPrime)
   {
      if (isPrime(i) == 1)
         checkPrime++;
      i++;
   }

   cout << "The " << nthPrime << "th prime is: " << --i  << endl;  
}

/*********************************************
 * solve for primes
 ********************************************/
void solveForPrimes(int arraySize)
{
   numberArray[0] = 0; // set 0 and 1 to false, not primes
   numberArray[1] = 0;
   
   for (int i = 2; i < arraySize; i++)
   {
      numberArray[i] = i; // set all to true with their respective numbers
   }

   for (int i = 2; i < floor(sqrt(arraySize)); i++)
   {
      if (numberArray[i] != 0)
      {
         int j = i * i;
         while (j <= arraySize)
         {
            numberArray[j] = 0; // set constanents to false
            j = j + i;
         }
      }
   }
   cout << "Done solving for primes\n";
}

/*********************************************
 * check if prime
 ********************************************/
bool isPrime(int number)
{
   return (numberArray[number] == 1);   
}

/*********************************************
 * All the many wonderful things I learned
 ********************************************/
void learned()
{
   cout << "As I have come to expect from these explorations, I learned a lot. I defined \"sweetness\" as the probability of \n"
        << "producing a prime with the equation x^2 + x + c, where x ranges of 10000 numbers and c is a constant.\n"
        << "For c I went from -5000000 to 5000000. The sweetest c value by far was -1354363 with a percentage of 53.56% in the range of 0 - 10000.\n"
        << "After talking with classmates and Brother Neff it became clear that when using a range of x that crossing the origin would be bad\n"
        << "because of all the duplicate primes it generates. Also when calculating which x to use I deduced that there are more primes closer to\n"
        << "the origin so I studied mainly 0 < x < 10000 and -10000 < x < 0.\n"
        << "With regards to discrete probability we can say that, for example with a constant of -1354363 with a range of 0 - 10000 the\n"
        << "probability that x^2 + x + c produces a prime is 53.56%.\n"
        << "Being enrolled in CS306 was actually very helpful in approaching this problem and implementing a solution for it.\n"
        << "The first step in designing an algorithm, or I would say in solving any problem, is understanding the problem.\n"
        << "I spent the first couple of weeks reading the assignment, re-reading the assignment, talking to Brother Neff,\n"
        << "and talking to other students in the class by what they understood by it and how they were approaching it.\n"
        << "This method taught me through experience how to correctly approach a challenging problem,\n"
        << "because had I jumped right in in writing code I would have wasted a lot of time and probably\n"
        << "would have only succeeded in being frustrated. Although there were some parts I misunderstood and had to rewrite.\n"
        << "This was actually one of my favorite explorations, I wish they were all just as sweet.\n"
        << "Only please don't make us do the writeup this way again :(\n\n";
}

/*********************************************
 * How to use this program
 ********************************************/
void usage()
{
   cout << "\nUsage:\n"
        << "To get the best sweetness run \"a.out 0 -1354363\", this sets the range to 0 - 10000 and the constant to -1354363\n\n"
        << "There are 3 ways to run this program:\n\n"
        << "1)No commandline parameters: Displays what I learned and how to use this program\n\n"
        << "2)One commandline parameter: Finds the nth prime number\n\n"
        << "3)Two commandline parameters: Finds the sweetness given a constant and range.\n"
        << "The first argument is the constant and the second is the lower edge of the range of 1000.\n";
}
   
