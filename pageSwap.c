//  John Williams
//  105201054
//  Date: Mon. Oct. 22, 2018
//  Program: Processor.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "linked_list.h"


int main(int argc, char *argv[])
{

  //argv[1] = "3";
  //argv[2] = "sample1.txt";
  //argv[3] = "stuff";
  //argc = 3;

  argv[1] = "256";
  argv[2] = "pg-reference.txt";
  argv[3] = "stuff";
  argc = 3;


  if (argc < 3){ // check for number of arguments from commandline
    usage();
  }

  FILE* file;
  FILE* outfile;
  file = fopen (argv[2], "r");
  if (file == NULL)// check that file opened correctly 
  {
    printf("Please check the file '%s' and try again....\n\n", argv[2]);
    exit(1);
  }

  outfile = fopen (argv[3], "a");
  if (outfile == NULL)// check that file opened correctly 
  {
    printf("Please check the file '%s' and try again....\n\n", argv[3]);
    exit(1);
  }
  
  int frameSize = atol(argv[1]);
  nodePtr head = NULL;
  nodePtr copy1 = NULL;
  statPtr item = NULL;
  head = (nodePtr) read_in_file( file, head); // read in the file
  int total = count(head);
  //file = fopen ("sample.txt", "r");
  //file = fopen ("sample2.txt", "r");
  //file = fopen ("pg-reference.txt", "r");
  //file = fopen ("random.txt", "r");
  //nodePtr frame = NULL;
  //print (&frame);

  statPtr scores[4]; 

  copy1 = copy(&head);
  scores[0] = FCFS(&copy1, frameSize);
  freeQueue(&copy1);
  print (&copy1);

  copy1 = copy(&head);
  scores[1] = LRU(&copy1, frameSize);
  freeQueue(&copy1);
  print (&copy1);

  copy1 = copy(&head);
  scores[2] = MRU(&copy1, frameSize);
  freeQueue(&copy1);
  print (&copy1);

  copy1 = copy(&head);
  scores[3]= OPTIMAL(&copy1, frameSize);
  freeQueue(&copy1);
  print (&copy1);

  freeQueue(&head);


  printz(scores, total,frameSize, outfile);
  
  
  for(int i = 0; i < 4 ; i++)
  {
    free(scores[i]->avg);
    free(scores[i]);
  }


}

