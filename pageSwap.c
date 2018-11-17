//  John Williams
//  105201054
//  Date: Mon. Oct. 22, 2018
//  Program: Processor.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"


////////////////////////////////////////////////////////////////////////////////////
// use stats struct to make a count of total frames in list using count function  // 
// have a variable set aside for dividing total frames by 5                       //
// have an array of 4 arrays in five seperate varialbes for each method's rates   //
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// make copy function so copy the main queue and send copy to each individual function. In each function  //
// we should be destroying the queue at the end, being what is left in the frame.                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// make a list to hold totals and use list every time we have to page swap
// must update list as we go... :(
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// clean up each queue in each function once your done. via free //
///////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  // frameSize inputFile outputFile


  if (argc < 3){ // check for number of arguments from commandline
    usage();
  }

  int numberOfPages;
  nodePtr head = NULL;
  nodePtr copy1 = NULL;
  FILE* file;
  statPtr scores[4]; 
  file = fopen (argv[2], "r");
  FILE* outfile;
  outfile = fopen (argv[3], "a");

  if (file == NULL)// check that file opened correctly 
  {
    printf("Please check the file '%s' and try again....\n\n", argv[2]);
    exit(1);
  }
  if (outfile == NULL)// check that file opened correctly 
  {
    printf("Please check the file '%s' and try again....\n\n", argv[3]);
    exit(1);
  }
  
  long frameSize = atol(argv[1]);
  if (frameSize < 0 )
  {
    usage();
  }

  head = (nodePtr) read_in_file( file, head); // read in the file
  numberOfPages = count(head);

  //file = fopen ("sample.txt", "r");
  //file = fopen ("sample2.txt", "r");
  //file = fopen ("pg-reference.txt", "r");
  //file = fopen ("random.txt", "r");
  //nodePtr frame = NULL;
  //print (&frame);
  //head = (nodePtr) read_in_file( file, head); // read in the file

  //print(&head) ;
  //print(&copy1) ;



//  print(&head);
  copy1 = copy(&head);
  scores[0] = FCFS(copy1, frameSize);
  //freeQueue(&copy1);
  
  copy1 = copy(&head);
  scores[1] = LRU(copy1, frameSize);
  //freeQueue(&copy1);
  
  copy1 = copy(&head);
  scores[2] = MRU(copy1, frameSize);
  //freeQueue(&copy1);
  
  copy1 = copy(&head);
  scores[3]= OPTIMAL(head, frameSize);
  //freeQueue(&copy1);
 // freeQueue(&head);
  printz(scores, numberOfPages, frameSize, outfile);
 
}

