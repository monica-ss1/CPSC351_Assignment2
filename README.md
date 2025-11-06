# CPSC351_Assignment2

## Names and Emails:

- Josh Navarro/joshpatnav@csu.fullerton.edu
- Spencer Blunt/sblunt3@csu.fullerton.edu
- Matthew Estrada/mestrada145@csu.fullerton.edu
- Monica Soliman/msoliman14@csu.fullerton.edu
- Michelle Pineda/pinedama@csu.fullerton.edu
- Isaac Morrell/isaacmorrell13@csu.fullerton.edu


## The Programming Language:

 C++

## How to execute the code:

### Part 1: Shared Memory 

recv:

To compile code:
> gcc recv.cpp -o recv

To run code:
> ./recv

sender:

To compile code:
> gcc sender.cpp -o sender

To run code:
> ./sender *file name* *receiver pid*

### Part 2: Message Queues

recv:

To compile code:
> g++ -std=c++17 -O2 P2recv.cpp -o recv_mq -lrt 

To run code:
> ./recv_mq

sender:

To compile code:
> g++ -std=c++17 -O2 P2sender.cpp -o sender_mq -lrt  

To run code:
> ./sender_mq *file name*

### Part 3: Message Pipes

pipefile:

To compile code:
> gcc pipefile.cpp -o pipefile  

To run code:
> ./pipefile *file name*
