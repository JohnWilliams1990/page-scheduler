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
nodePtr copy(nodePtr* head) 
{
  nodePtr copyHead = NULL; 
  nodePtr currentPage = calloc(1, sizeof( node));
  currentPage->page = calloc(1,sizeof(pagePtr));
  nodePtr curPtr = (*head);
  while (curPtr != NULL) // iterate through list
  {
   // printf("%d",curPtr->page->pageId);
    currentPage->page->pageId = curPtr->page->pageId;;
    push_back(&copyHead, currentPage); 

    curPtr = curPtr->next;
  }
  return copyHead; // return pid of smallest burst time
}


long compare(nodePtr head, nodePtr frame) 
{
  long least = 0;
  int leastPageId = 0;
  nodePtr HeadStart = head;
  nodePtr frameStart = frame; 
  nodePtr curHeadPtr = head;
  nodePtr curFramePtr = frame;
  while (curFramePtr != NULL) // iterate through list
  {
    curFramePtr->page->count = 0;
    curFramePtr = curFramePtr->next;
  }

  curHeadPtr = head;
  curFramePtr = frame;

  while (curFramePtr != NULL) // iterate through frame
  {
    while (curHeadPtr != NULL) // iterate through head
    { 
      if (curFramePtr->page->pageId == curHeadPtr->page->pageId)
      {
        curFramePtr->page->count += 1;
        //printf("frame %d with %d\n",curFramePtr->page->pageId, curFramePtr->page->count);
      }
      //curFramePtr = curFramePtr->next;
      curHeadPtr = curHeadPtr->next;
    }
      curHeadPtr = HeadStart;
      curFramePtr = curFramePtr->next;
  }
    
  curHeadPtr = HeadStart;
  curFramePtr = frameStart;

  least = curFramePtr->page->count;
  leastPageId = curFramePtr->page->pageId;
  while (curFramePtr != NULL) // iterate through list
  {
    //printf("%d\n",curHeadPtr->page->pageId);
//    printf("frame %d with %d\n",curFramePtr->page->pageId, curFramePtr->page->count);
    if (curFramePtr->page->count < least)
    {
    //printf("%d\n",curFramePtr->page->pageId);
      least = curFramePtr->page->count;
      leastPageId = curFramePtr->page->pageId;
    }
    curFramePtr = curFramePtr->next;
  }


  return leastPageId; // return pid of smallest burst time
}

// reads file into the linked list or queue
// function assumes that correct input is given
nodePtr read_in_file(FILE* file, nodePtr head){
  nodePtr currentPage; // = calloc(1, sizeof(node));
  currentPage->page->lastTime = 0;
  currentPage->page->timesUsed = 0;
  //currentPage->page = calloc(1, sizeof(pagePtr));
  int index = 0;
  while (!feof (file)){ // go length of file
    index = -99;
    fscanf (file, "%d", &index); // scan and input values   
    if (index != -99) 
    { 
      currentPage->page->pageId = index;
      push_back(&head, currentPage); 
    }
  }
  		//freeNode(&currentPage); // free the node used and return the linked list
  return head;
}


// check the frame to see if its in there 
bool check(nodePtr head, int value, int time)
{
  int sum = 0;
  nodePtr curPtr = head;
  while (curPtr != NULL)
  { 
    if (curPtr->page->pageId == value)
    {
      curPtr->page->lastTime = time; 
      return true;
    }
    curPtr = curPtr->next;
  }
  return false; 
}



statPtr FCFS(nodePtr head, int frameSize) {
  statPtr stats = calloc(1, sizeof(struct stat_t));
  stats->interval = count(head) / 5;
  stats->name = "FCFS";
  stats->avg = calloc(5, sizeof(float));;

  nodePtr frame = NULL;
  nodePtr tempIN = calloc(1, sizeof(node));
  int fault = 0;
  bool checklist = false;
  long int time = 0; 
  float stuff[5];
  while (count(head)) {
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, 0);

    if (checklist) // check frame for page id to see if its already there
    { // page exists in frame so delete
      free(tempIN);
      //printf("~~Time: %d\n", time) ;
      //print(&frame);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        //printf("POP here\n");
        free(pop(&frame, 0));
      } 
      fault++;
      //printf("~~~~~~~~Fault @ pageId: %d\n", tempIN->page->pageId);
      push_back(&frame, tempIN);
      //printf("~~Time: %d\n", time) ;
      
      //print(&frame);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
      //printf("faults %d, Time %d val = %10.5f\n",fault,time, stats->avg[ ((time/stats->interval) -1 ) ]);
    }
  }
  stats->totalFault = fault; 
  freeQueue(&frame);
  freeQueue(&head);
  return stats;
}




statPtr LRU(nodePtr head, int frameSize) {
  statPtr stats = calloc(1, sizeof(struct stat_t));
  stats->interval = count(head) / 5;
  stats->avg = calloc(5, sizeof(float));;
  stats->name = "LRU";
  nodePtr frame = NULL;
  nodePtr tempIN = calloc(1, sizeof(node));
  nodePtr tempOUT = calloc(1, sizeof(node));
  int fault = 0;
  bool checklist = false;
  long int time = 0; 
  int pageId = -99;
  while (count(head)) {
    //printf("~~Time: %d\n", time) ;
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, time);
    if (checklist) // check frame for page id to see if its already there
    { // page exists in frame so delete
      
      free(tempIN);
      //print(&frame);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        pageId = least(frame);
        //pop page Id 
        tempOUT = popPageId(&frame, pageId);
        //printf("POP here pid = %d\n", tempOUT->page->pageId);
        free(tempOUT);
        //free(pop(&frame, 0));
      }
      fault++;
      //printf("~~~~~~~~Fault @ pageId: %d", tempIN->page->pageId);
      tempIN->page->lastTime = time;
      //frame = push(&frame, tempIN, 1);
      push_back(&frame, tempIN);
      //print(&frame);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
    }
  }
  stats->totalFault = fault; 
  freeQueue(&frame);
  return stats;
}


statPtr MRU(nodePtr head, int frameSize) {
  statPtr stats = calloc(1, sizeof(struct stat_t));
  stats->interval = count(head) / 5;
  stats->avg = calloc(5, sizeof(float));;
  stats->name = "MFU";
  nodePtr frame = NULL;
  nodePtr tempIN = calloc(1, sizeof(node));
  nodePtr tempOUT = calloc(1, sizeof(node));
  int fault = 0;
  bool checklist = false;
  long int time = 0; 
  int pageId = -99;
  while (count(head)) {
    //printf("~~Time: %d\n", time) ;
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, time);
    if (checklist) // check frame for page id to see if its already there
    { // page exists in frame so delete
      
      free(tempIN);
      //print(&frame);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        pageId = most(frame);
        //pop page Id 
        tempOUT = popPageId(&frame, pageId);
        //printf("POP here pid = %d\n", tempOUT->page->pageId);
        free(tempOUT);
        //free(pop(&frame, 0));
      }
      fault++;
      tempIN->page->lastTime = time;
      //frame = push(&frame, tempIN, 1);
      push_back(&frame, tempIN);
      //print(&frame);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
    }
  }
  stats->totalFault = fault; 
  //freeQueue(&frame);
  return stats;
}

statPtr OPTIMAL(nodePtr head, int frameSize) {
  statPtr stats = calloc(1, sizeof(struct stat_t));
  stats->interval = count(head) / 5;
  stats->avg = calloc(5, sizeof(float));;
  stats->name = "OPTIMAL";
  nodePtr frame = NULL;
  nodePtr tempIN = calloc(1, sizeof(node));
  nodePtr tempOUT = calloc(1, sizeof(node));
  int fault = 0;
  bool checklist = false;
  long int time = 0; 
  int pageId = -99;
  while (count(head)) {
    //printf("~~Time: %d\n", time) ;
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, time);
    if (checklist) // check frame for page id to see if its already there
    { // page exists in frame so delete
      
      free(tempIN);
      //print(&frame);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        pageId = compare( head, frame);
        //pop page Id 
        tempOUT = popPageId(&frame, pageId);
       // printf("POP here pid = %d\n", tempOUT->page->pageId);
        free(tempOUT);
        //free(pop(&frame, 0));
      }
      fault++;
      tempIN->page->lastTime = time;
      //frame = push(&frame, tempIN, 1);
      push_back(&frame, tempIN);
      //print(&frame);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
    }
  }
  stats->totalFault = fault; 
  freeQueue(&frame);
  return stats;
}


void printz(statPtr* stuff){
//statPtr item = (*stuff);
printf("HERE # PRINT\n\n");

//printf("%d", item[1]->totalFault);
  long value = stuff[0]->interval;
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(" %50s\n","Page Fault Rates" );
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("| %10s | %10s | %6d | %6d | %6d | %6d | %6d |\n","Algorithm", "Total Faults",value , 2* value, 3*value, 4*value, 5*value);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  for (int i = 0; i < 4 ; ++i)
  {
  
    printf("| %10s | %12d | %6.3f | %6.3f | %6.3f | %6.3f | %6.3f |\n",stuff[i]->name, stuff[i]->totalFault, stuff[i]->avg[0], stuff[i]->avg[1], stuff[i]->avg[2], stuff[i]->avg[3], stuff[i]->avg[4]);
  }

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


int main(int argc, char *argv[])
{
  int frameSize = 1024;
  FILE* file;
  //file = fopen ("sample.txt", "r");
  //file = fopen ("sample2.txt", "r");
  file = fopen ("pg-reference.txt", "r");
  //file = fopen ("random.txt", "r");
  nodePtr head = NULL;
  nodePtr copy1 = NULL;
  //nodePtr frame = NULL;
  //print (&frame);
  head = (nodePtr) read_in_file( file, head); // read in the file
  statPtr item = NULL;

 // print(&head) ;
//  print(&copy1) ;
  statPtr scores[4]; 


  //FCFS(head, 4);
  //FCFS(head, 1024);
  //FCFS(head, 3);
  //LRU(head, 1024);

  copy1 = copy(&head);
  scores[0] = FCFS(copy1, frameSize);
  //freeQueue(&copy1);
  //printf("HERE\n\n");
  copy1 = copy(&head);
  scores[1] = LRU(copy1, frameSize);
  //freeQueue(&copy1);
  //printf("HERE\n\n");
  copy1 = copy(&head);
  scores[2] = MRU(copy1, frameSize);
  //freeQueue(&copy1);
  copy1 = copy(&head);
  //printf("HERE\n\n");
  scores[3]= OPTIMAL(head, frameSize);
  //freeQueue(&copy1);
  printz(scores);
}

