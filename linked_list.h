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

//typedef struct pcb_t { // pcb structure
//  int pid;
//  int arrivalTime;
//  int burstTime;
//  
//  float finishTime;
//  float waitTime;
//  float turnTime;
//  float respTime;
//  int contextCount;
//  
//  int timeMarker;
//  int firstRun;
//  bool ran;
//  int curRunningTime;
//
//} pcb,* pcbPtr ;


void freeNode(nodePtr * arg) {
  free((*arg)->page);
  free((*arg));
  return;
}

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



//// function that returns the pid for the pcb with the 
//// least ammount of burst time for the list of processes that it is passed
//int least(nodePtr head) 
//{
//  nodePtr curPtr = head;
//  int burst = curPtr->process->burstTime; 
//  int pid = curPtr->process->pid;
//  while (curPtr != NULL) // iterate through list
//  {
//    if (curPtr->process->burstTime < burst) // find smallees burts time
//    {
//      burst = curPtr->process->burstTime;
//      pid = curPtr->process->pid;
//    }
//    curPtr = curPtr->next;
//  }
//  return pid; // return pid of smallest burst time
//}
//
//// function that returns the pid for the pcb with the 
//// least ammount of remaining burst time for 
//// the list of processes that it is passed
//int leastleft(nodePtr head)
//{
//  nodePtr curPtr = head;
//  int burst = curPtr->process->burstTime - curPtr->process->curRunningTime;
//  int pid = curPtr->process->pid;
//  while (curPtr != NULL) // find least remaining time
//  {
//    if ((curPtr->process->burstTime - curPtr->process->curRunningTime) < burst)
//    {
//      burst = curPtr->process->burstTime - curPtr->process->curRunningTime;
//      pid = curPtr->process->pid;
//    }
//    curPtr = curPtr->next;
//  }
//  return pid;
//}


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
    (*arg)->page = calloc(1, sizeof( pagePtr));
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

  curPtr->next->page = calloc(1, sizeof( pagePtr));
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


void printHead( statPtr* args)
{
  statPtr arg = (*args);
  printf(" %50s\n","Page Fault Rates" );
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("| %10s | %10s | %6d | %6d | %6d | %6d | %6d |\n","Algorithm", "Total Faults", arg->interval, 2* arg->interval, 3* arg->interval, 4*arg->interval, 5*arg->interval );
}
void printStat( statPtr* args, char* name)
{

statPtr arg = (*args);
  if (arg == NULL)
  {
    return; 
  }
  //printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  //printf(" %50s\n","Page Fault Rates" );
  //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  //printf("| %10s | %10s | %6d | %6d | %6d | %6d | %6d |\n","Algorithm", "Total Faults", arg->interval, 2* arg->interval, 3* arg->interval, 4*arg->interval, 5*arg->interval );
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("| %10s | %12d | %6.3f | %6.3f | %6.3f | %6.3f | %6.3f |\n",name, arg->totalFault, arg->avg[0], arg->avg[1], arg->avg[2], arg->avg[3], arg->avg[4]);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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

#endif
