//  John Williams
//  105201054
//  Date: Mon. Oct. 22, 2018
//  Program: linked_list.h
#ifndef LINKEDLIST_C
#define LINKEDLIST_C
#include<stdbool.h>
#include"linked_list.h"

typedef struct stat_t { // structure for statistics   
  char* name; 
  long totalFault;
  long interval; // interval used to determine when to get statistics
  float*avg;
} stat, * statPtr ;


typedef struct page_t { // pcb structure
  int pageId;   
  int lastTime;
  int timesUsed;
  long count; 
} page,* pagePtr ;

typedef struct node_t { // node type that contains the pcb structure
  struct node_t* next;
  struct node_t* prev;
  int data;
  pagePtr page;
} node, *nodePtr;


int least(nodePtr head) 
{
  nodePtr curPtr = head;
  int lastTime = curPtr->page->lastTime; 
  int pageId = curPtr->page->pageId;
  while (curPtr != NULL) // iterate through list
  {
    if (curPtr->page->lastTime < lastTime) // find smallees burts time
    {
      lastTime = curPtr->page->lastTime; 
      pageId = curPtr->page->pageId;
    }
    curPtr = curPtr->next;
  }
  return pageId; // return pid of smallest burst time
}


int most(nodePtr head) 
{
  nodePtr curPtr = head;
  int lastTime = curPtr->page->lastTime; 
  int pageId = curPtr->page->pageId;
  while (curPtr != NULL) // iterate through list
  {
    if (curPtr->page->lastTime > lastTime) // find smallees burts time
    {
      lastTime = curPtr->page->lastTime; 
      pageId = curPtr->page->pageId;
    }
    curPtr = curPtr->next;
  }
  return pageId; // return pid of smallest burst time
}


// function that pushed the element to back of list
// function uses iterative method to remove 
// limitations of recursion for large lists of processes
void push_back( nodePtr * arg, node* item)
{
  int counter = 1;
  nodePtr curPtr = (*arg);

  if ( curPtr == NULL) // if the linked list is empty
  {
    (*arg) = malloc( sizeof(node)); 
    (*arg)->prev = NULL; // assigne values based on object being pushed
    (*arg)->next = NULL;  
    //(*arg)->page = calloc(1, sizeof(page));
<<<<<<< HEAD
    (*arg)->page = calloc(1, sizeof(pagePtr));
=======
    (*arg)->page = calloc(1, sizeof(page*));
>>>>>>> f3c6c8e59df99c0155aa42d7be789e3e5cd0f26b
    (*arg)->page->pageId = item->page->pageId;
    (*arg)->page->lastTime = item->page->lastTime;
    (*arg)->page->timesUsed = item->page->timesUsed;
    (*arg)->data = 0;
    return;
  }
  // otherwise go to end and push back item
  while (curPtr->next != NULL)
  {
    curPtr = curPtr->next;
    counter +=1;
  }
  curPtr->next = calloc(1, sizeof(node));

  //curPtr->next->page = calloc(1, sizeof(page*));
  curPtr->next->page = calloc(1, sizeof(pagePtr));
  curPtr->next->page->pageId = item->page->pageId;
  curPtr->next->page->lastTime = item->page->lastTime;
  curPtr->next->page->timesUsed = item->page->timesUsed;


  curPtr->next->prev = curPtr;
  curPtr->next->data = counter;
  curPtr->next->next = NULL;
 return;
}

//function pops elememt from list at specific index
// function uses iterative method to remove 
// limitations of recursion for large lists of processes
nodePtr pop( nodePtr * arg, int index)
{

  node tmp;
  int counter = 0;
  nodePtr curPtr = (*arg);
  nodePtr prev = (*arg)->prev;
  if ((*arg) == NULL)  
  {
    return curPtr;
  }
  
  while (curPtr->next != NULL && counter < index) // iterate to point in linked list
  {
    prev = curPtr;
    curPtr = curPtr->next;
    counter +=1;
  }
  if(prev != NULL) // we are not at head of linked list
  {
    prev->next = curPtr->next;
  }
  else
  { // we are at head of list to pop front
    (*arg) = (*arg)->next;
    if ((*arg) != NULL) 
    { 
      (*arg)->prev = curPtr->prev;
    }
  }

  if (curPtr->next != NULL) // assigne previous if applicable
  {
    curPtr->next->prev = prev;
  }
    return curPtr; 
}

// function pops element off of end of list

nodePtr pop_back( nodePtr * arg)
{
  int counter = 0;
  nodePtr curPtr = (*arg);
  nodePtr prev = (*arg)->prev;

  if (curPtr == NULL) { exit(0);  } // return from function and program because list is empty
  if (curPtr->next == NULL && curPtr->prev == NULL) // if there is only one item in list
  {
    return curPtr;
  }

  while (curPtr->next != NULL)// iterate to item 
  {
    prev = curPtr;// reasign pointers
    curPtr = curPtr->next;
    counter +=1;
  }
  if (prev != NULL) {// reasigne list pointers
    prev->next = curPtr->next;
  }

  return curPtr; // return node
}


// function iterates through the list and prints each node in their given order
void print( nodePtr * arg)
{
  nodePtr curPtr = (*arg);

  if (curPtr == NULL)
  {
    return; 
  }
 printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
printf("| %10s |  %10s | %10s |\n","Page Id", "last Time", "Times Used" );
 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  while (curPtr != NULL)
  {

  int lastTime;
  int timesUsed;

   printf("| %10d | %10d | %10d |\n",curPtr->page->pageId, curPtr->page->lastTime, curPtr->page->timesUsed);
   curPtr = curPtr->next;
  }
 printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("");
}


// function used to count the number fo nodes in linked list
// 
int count(nodePtr head)
{
  int sum = 0;
  nodePtr curPtr = head;
  while (curPtr != NULL)
  {
    sum += 1;
    curPtr = curPtr->next;
  }
  return sum; 
}


// function used to pop a specific node with a pid of a value specified
nodePtr popPageId( nodePtr * arg, int index)
{
  node tmp;
  int counter = 0;
  nodePtr curPtr = (*arg);
  nodePtr prev = (*arg)->prev;

  if ((*arg) == NULL)
  {
    return curPtr;
  } 
  while (curPtr->next != NULL && curPtr->page->pageId != index)
  {
    prev = curPtr;
    curPtr = curPtr->next;
    counter +=1;
  }
  if(prev != NULL) 
  {
    prev->next = curPtr->next;
  }
  else
  { // we are at head of list to pop front
    (*arg) = (*arg)->next;
    if ((*arg) != NULL) 
    { 
      (*arg)->prev = curPtr->prev;
    }
  }

  if (curPtr->next != NULL)
  {
    curPtr->next->prev = prev;
  }
    return curPtr; 
}

// function used to push node into list at specific point
nodePtr push( nodePtr * arg, node* item, int index)
{
  int counter = 1;
  nodePtr curPtr = (*arg);
  nodePtr tmpPtr = NULL;


  if ( curPtr == NULL)
  {
    (*arg) = calloc(1, sizeof( node));
    (*arg)->prev = NULL;
    (*arg)->next = NULL;  
    (*arg)->page = calloc(1, sizeof( pagePtr));
    (*arg)->page->pageId = item->page->pageId;
    (*arg)->page->lastTime = item->page->lastTime;
    (*arg)->page->timesUsed = item->page->timesUsed;
    return (*arg);
  }

  while (counter < index - 1 && curPtr->next != NULL)
  {
     curPtr = curPtr->next;
     counter += 1;
  }

  if (index == 1)
  {
    tmpPtr = calloc(1, sizeof( node));
    tmpPtr->prev = NULL;
    tmpPtr->next = NULL;
    tmpPtr->page = calloc(1,sizeof( pagePtr));
    tmpPtr->page->pageId = item->page->pageId;
    tmpPtr->page->lastTime = item->page->lastTime;
    tmpPtr->page->timesUsed = item->page->timesUsed;



    tmpPtr->prev = NULL;
    tmpPtr->next = curPtr;
    
    if (curPtr->prev != NULL)
    {
      curPtr->prev = tmpPtr;
    }

    return tmpPtr;
  }


  else {
  
  // grab item before overwriting it
    tmpPtr = curPtr->next;
    
  
    curPtr->next = calloc(1, sizeof(node));
    curPtr->next->page = calloc(1, sizeof( pagePtr));
    curPtr->next->page->pageId = item->page->pageId;
    curPtr->next->page->lastTime = item->page->lastTime;
    curPtr->next->page->timesUsed = item->page->timesUsed;

    curPtr->next->prev = curPtr;
    curPtr->next->data = counter;
   
    curPtr = curPtr->next;
    curPtr->next = tmpPtr; 
    
    if (curPtr->next != NULL)
    {
      curPtr->next->prev = curPtr;
    }
  }
  
  
  
  return (*arg);

}


// since we know the order then walk through list poping and pushing bach into specific place in line
//nodePtr sort(nodePtr header) {
//  nodePtr tmp = NULL;
//  nodePtr head = header;
//  int processes = count(head);
//  for (int i = 1; i < processes; i++)
//  {
//    tmp = popPid(&head, i);
//    head = push(&head, tmp, i);
//  }
//  return head;
//}
//
//
//
//
//// get total amount of time needed for all burst times
//int getTime(nodePtr head)
//{
//  int sum = 0;
//  nodePtr curPtr = head;
//  while (curPtr != NULL)
//  {
//    sum += curPtr->process->burstTime;
//    curPtr = curPtr->next;
//  }
//  return sum; 
//}
//
//// if user cannot provide correct parameters then give them these parameter lists
//void usage(){
//  printf("Usage:./processor {input_file} {schedling algorithm number} [time quantum size]\n\n");
//  printf("\t Available algorithms: \n");
//  printf("\t0: FCFS \n");
//  printf("\t1: SJF \n");
//  printf("\t2: SRTF \n");
//  printf("\t3: RR\n");
//  exit(0);
//}
//
//
//
// deallocate entire array for end of program

void freeNode(nodePtr * arg) {
  free((*arg)->page);
  free((*arg));
  return;
}

void freeQueue(nodePtr*header)
{
  nodePtr head = *header;
  nodePtr temp = NULL;
  int processes = count(head);
  for (int i = 0; i < processes; i++)
  {
    temp = pop( &head, 0);
    //print(&temp);
    freeNode(&temp);
  } 
  (*header) = NULL;
}
<<<<<<< HEAD

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
    if (curFramePtr->page->count < least)
    {
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
  nodePtr currentPage = calloc(1, sizeof(node));
  currentPage->page = calloc(1, sizeof(pagePtr));
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
    { 
      free(tempIN); // page exists in frame so delete
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        free(pop(&frame, 0));
      } 
      fault++;
      push_back(&frame, tempIN);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
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
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, time);
    if (checklist) // check frame for page id to see if its already there
    { 
      // page exists in frame so delete
      free(tempIN);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        pageId = least(frame);
        //pop page Id 
        tempOUT = popPageId(&frame, pageId);
        free(tempOUT);
      }
      fault++;
      tempIN->page->lastTime = time;
      push_back(&frame, tempIN);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
    }
  }
  stats->totalFault = fault; 
  freeQueue(&frame);
  freeQueue(&head);
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
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, time);
    if (checklist) // check frame for page id to see if its already there
    { 
      // page exists in frame so delete
      free(tempIN);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        pageId = most(frame);
        //pop page Id 
        tempOUT = popPageId(&frame, pageId);
        free(tempOUT);
      }
      fault++;
      tempIN->page->lastTime = time;
      push_back(&frame, tempIN);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
    }
  }
  stats->totalFault = fault; 
  freeQueue(&frame);
  freeQueue(&head);
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
    tempIN = pop(&head, 0);
    checklist = check( frame, tempIN->page->pageId, time);
    if (checklist) // check frame for page id to see if its already there
    { 
      // page exists in frame so delete
      free(tempIN);
    }
    else
    {
      if (count(frame) == frameSize) // if fram is full then page swap
      {
        pageId = compare( head, frame);
        //pop page Id 
        tempOUT = popPageId(&frame, pageId);
        free(tempOUT);
      }
      fault++;
      tempIN->page->lastTime = time;
      push_back(&frame, tempIN);
    }
    time++;
    if (time != 0 && time % stats->interval == 0){
      stats->avg[ ((time/stats->interval) -1 ) ] = (float)fault/(float)time; 
    }
  }
  stats->totalFault = fault; 
  freeQueue(&frame); // clean up queues
  freeQueue(&head);
  return stats;
}


void printz(statPtr* stuff, int total, int frameSize, FILE * file){
  long value = stuff[0]->interval;
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(" Number of pages:%d  Frame Size: %d %30s\n", total, frameSize, "Page Fault Rates" );
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("| %10s | %10s | %6d | %6d | %6d | %6d | %6d |\n","Algorithm", "Total Faults",value , 2* value, 3*value, 4*value, 5*value);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  for (int i = 0; i < 4 ; ++i)
  {
  
    printf("| %10s | %12d | %6.3f | %6.3f | %6.3f | %6.3f | %6.3f |\n",stuff[i]->name, stuff[i]->totalFault, stuff[i]->avg[0], stuff[i]->avg[1], stuff[i]->avg[2], stuff[i]->avg[3], stuff[i]->avg[4]);
  }
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


  fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  fprintf(file, " Number of pages:%d  Frame Size: %d %30s\n", total, frameSize, "Page Fault Rates" );
  fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  fprintf(file, "| %10s | %10s | %6d | %6d | %6d | %6d | %6d |\n","Algorithm", "Total Faults",value , 2* value, 3*value, 4*value, 5*value);
  fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  for (int i = 0; i < 4 ; ++i)
  {
  
    fprintf(file, "| %10s | %12d | %6.3f | %6.3f | %6.3f | %6.3f | %6.3f |\n",stuff[i]->name, stuff[i]->totalFault, stuff[i]->avg[0], stuff[i]->avg[1], stuff[i]->avg[2], stuff[i]->avg[3], stuff[i]->avg[4]);
  }
  fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


}


void usage(){
  printf("Usage:./pageSwap {frameSize} {input file} {output file} \n\n");
  printf("\tframeSize must be greater than 0\n");
  exit(0);
}


=======
>>>>>>> f3c6c8e59df99c0155aa42d7be789e3e5cd0f26b
#endif
