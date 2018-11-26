#!/usr/bin/python
#  John Williams
#  105201054
#  Date: Sat. Nov. 17, 2018
#  Program: graphing.py


import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')
import numpy as np
import pylab as p
import matplotlib.pyplot as plt

def work(pageNumbers, totalPages,  FCFS, LRU, MFU, OPTIMAL):
  #x = np.linspace(totalPages/5, totalPages, 5)
 
  x = [2000,4000,6000,8000,10000] 

  #plt.gca().invert_yaxis()
  p.plot(x,FCFS, label='FCFS')
  p.plot(x,LRU, label='LRU')
  p.plot(x,MFU, label='MFU')
  p.plot(x,OPTIMAL, label='OPTIMAL')
  p.legend()
  p.ylabel("Page Fault Rates", fontdict=None, labelpad=None)
  p.xlabel("Number of pages", fontdict=None, labelpad=None)
  p.title("Page Replacement Simulation: Frame Size {0}, Total Pages {1}".format( pageNumbers, totalPages))
  p.legend()
  p.show()
  plt.clf()
  plt.cla()
  plt.close()
  plt.gcf().clear()

count = 0
arr = [[],[],[],[],
       [],[],[],[],
       [],[],[],[],
       [],[],[],[]]

pageNumbers = []
totalPages = []


filename = "stuff"
file = open(filename, "r")
for line in file:
   if ("~" in line or "Number" in line or "Algorithm" in line):
     if ("Number" in line):
      
       pageNumbers.append(line.split(" ")[7])
       totalPages.append( line.split(" ")[3].split(":")[1])
       #print pageNumbers
       #print totalPages   
     else: 
       pass
   else:
     #if count %4 == 0:
       #print 
     for col in line.split(" "):  
       if ("|" in col or "." not in col):
         pass
       else: 
         #print col,
         arr[count].append(float(col))
         #print arr
     #print 
     count +=1




count = 0
x = [2000,4000,6000,8000,10000] 
for i in range(0,len(arr)/4):
  
  FCFS    =arr[4*count ]    
  LRU     =arr[4*count  + 1]   
  MFU     =arr[4*count  + 2]   
  OPTIMAL =arr[4*count  + 3] 
  count += 1;  
  work(int(pageNumbers[i]), int(totalPages[i]),  FCFS, LRU, MFU, OPTIMAL)
  

'''
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Number of pages:10000  Frame Size: 128               Page Fault Rates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|  Algorithm | Total Faults |   2000 |   4000 |   6000 |   8000 |  10000 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|       FCFS |         9653 |  0.965 |  0.966 |  0.966 |  0.966 |  0.965 |
|        LRU |         9651 |  0.966 |  0.966 |  0.965 |  0.966 |  0.965 |
|        MFU |         9686 |  0.972 |  0.969 |  0.968 |  0.968 |  0.969 |
|    OPTIMAL |         8868 |  0.941 |  0.926 |  0.919 |  0.908 |  0.887 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Number of pages:10000  Frame Size: 256               Page Fault Rates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|  Algorithm | Total Faults |   2000 |   4000 |   6000 |   8000 |  10000 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|       FCFS |         9334 |  0.935 |  0.935 |  0.934 |  0.934 |  0.933 |
|        LRU |         9331 |  0.936 |  0.935 |  0.933 |  0.934 |  0.933 |
|        MFU |         9408 |  0.953 |  0.944 |  0.944 |  0.941 |  0.941 |
|    OPTIMAL |         8075 |  0.895 |  0.872 |  0.854 |  0.838 |  0.808 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Number of pages:10000  Frame Size: 512               Page Fault Rates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|  Algorithm | Total Faults |   2000 |   4000 |   6000 |   8000 |  10000 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|       FCFS |         8752 |  0.894 |  0.885 |  0.877 |  0.878 |  0.875 |
|        LRU |         8752 |  0.891 |  0.883 |  0.877 |  0.877 |  0.875 |
|        MFU |         8761 |  0.893 |  0.877 |  0.879 |  0.876 |  0.876 |
|    OPTIMAL |         6899 |  0.841 |  0.792 |  0.757 |  0.730 |  0.690 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Number of pages:10000  Frame Size: 1024               Page Fault Rates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|  Algorithm | Total Faults |   2000 |   4000 |   6000 |   8000 |  10000 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|       FCFS |         7604 |  0.821 |  0.789 |  0.768 |  0.766 |  0.760 |
|        LRU |         7585 |  0.818 |  0.787 |  0.769 |  0.765 |  0.758 |
|        MFU |         7634 |  0.812 |  0.771 |  0.771 |  0.764 |  0.763 |
|    OPTIMAL |         5318 |  0.795 |  0.695 |  0.632 |  0.580 |  0.532 |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
'''
