/*
 * Copyright (c) 2014, Amit Kumar Vijay
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *******************************************************************
 * Author       : AMIT KUMAR VIJAY
 * Problem Ref. : http://en.wikipedia.org/wiki/100_prisoners_problem
 * Date         : 17 OCT 2014
 *******************************************************************/

 // Comments     : As per maths, the probablity of best strategy is 31 %
 //                while this probgram has roughly 50% success rate. Not
 //                sure if I have missed anything in the implementation.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_RANGE(N)       rand()/(RAND_MAX/(N) + 1)
#define log                 printf

#define NO_OF_PRISIONERS    100
#define NO_OF_DRAWERS       NO_OF_PRISIONERS

#define MAX_ATTEMPT         50

int cupboard [NO_OF_DRAWERS];

typedef int ATTEMPT [MAX_ATTEMPT];
ATTEMPT prisoners [NO_OF_PRISIONERS] = {0};


/*******************************************************************
 * Jailer distributing prisoner number's in drawer randomly
 ******************************************************************/
int init_cupboard (void)
{
   int i = 0;
   int r = 0;
   int temp = 0;

   for (i = 0; i < NO_OF_DRAWERS; i++) {
      cupboard [i] = i;
   }

   for (i = 0; i < NO_OF_DRAWERS - 1; i++) {
      r = RAND_RANGE (NO_OF_DRAWERS - i);
      /* swap positions */
      temp = cupboard [i];
      cupboard [i] = cupboard [i + r];
      cupboard [i + r] = temp;
   }

   for (i = 0; i < NO_OF_DRAWERS; i++) {
      cupboard [i] += 1;
   }

   return 0;
}

/*******************************************************************
 * Prints cupboard with contents (i.e. randomise prisoner's number)
 ******************************************************************/
void print_cupboard (void)
{
   int i;
   log ("\n                          D  R  A  W  E  R  S");
   log ("\n    +  1  ++  2  ++  3  ++  4  ++  5  ++  6  ++  7  ++  8  ++  9  ++  0  +");
   for (i = 0; i < NO_OF_DRAWERS; i++) {
      if (i%10 == 0) {
         log ("\n    +-----++-----++-----++-----++-----++-----++-----++-----++-----++-----+\n");
         log ("%3d ", (i/10) * 10);
      }
      log ("| %3d |", cupboard[i]);
   }
   log ("\n    +-----++-----++-----++-----++-----++-----++-----++-----++-----++-----+\n");
   return;
}


/*******************************************************************
 * Traces a prisioners attempt to find his number in the drawers
 ******************************************************************/
void print_attempt_for_a_prisoner (int prisoner, ATTEMPT attempt)
{
   int i = 0;
   log ("\nprisoner %3d : ", prisoner);
   for (i = 0; (i < MAX_ATTEMPT) && (attempt[i] != 0); i++) {
      log ("--> %d ", attempt [i]);
   }
   log ("\n");
}

/*******************************************************************
 * All prisioner take their chance with the agreement that
 * 1. all of them will start first with drawer number which maches
 *    their number.
 * 2. if they don't find their number, they will jump to the drawer
 *    number as found on the slip of the drawer just opened.
 ******************************************************************/
int attemp_to_survive (void)
{
   int i = 0;
   int j = 0;
   int k = 0;
   int found = 0;

   for (i = 0; i < NO_OF_PRISIONERS; i++) {
      found = 0;
      k = i; // <== Strategy Rule 1
      for (j = 0; (j < MAX_ATTEMPT) && (found == 0); j++) {
         prisoners [i][j] = cupboard [k];
         if (cupboard [k] == i+1) {
            found = 1; // <== found the number, stop
         }
         else {
            k = cupboard [k] - 1; // <== Strategy Rule 2
         }
      }
   }
   //log ("attempt_to_service (%d)\n", found);
   return found;
}

/*******************************************************************
 * Does number of experiment as per "attemp_to_survive"
 * strategy and
 * returns the *percent* when they survived.
 ******************************************************************/
float check_probablity (int total_number_of_try)
{
   int i       = 0;
   int success = 0;

   for (i = 0; i < total_number_of_try; i++) {
      init_cupboard ();                // randomize cupboard
      //print_cupboard ();             // print cupboard if you fancy
      success += attemp_to_survive();  // keep on adding the success
   }

   // return the % of success rate
   return (((float)success / total_number_of_try) * 100);
}


int main ()
{
   int i = 0;

   // seed the randon number generator
   srand (time(NULL));

   //init_cupboard ();
   //print_cupboard ();
   //attemp_to_survive ();
   // trace their route
   //for (i = 0; i < NO_OF_PRISIONERS; i++) {
   //   print_attempt_for_a_prisoner (i+1, prisoners[i]);
   //}
   log ("probablity = %2f\%\n", check_probablity (32000));

   return 0;
}

  
