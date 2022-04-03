Implemented a Priority Queue ADT using heap and applications in service sector simulation.

First, I took my implementation of a Queue ADT and made it into a Priority Queue. For more information on the base implementation of the queue and the 
format of the supported commands, please read the README.txt for the QueueADT in the main repository.

The simulator.c file in this program simulates random arrival of clients. The simulator will then process these clients using the queue and 
priority queue ADTs to schedule them based on appointment length. Then, I compare the two strategies and see how they would impact the average wait 
time of of each client and how that is tied to the time constraint. 
