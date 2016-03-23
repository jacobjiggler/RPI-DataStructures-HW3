HOMEWORK 3: JAGGED ARRAY


NAME:  Jacob Martin


TIME SPENT ON THIS ASSIGNMENT:  <20>


COLLABORATORS:  
(You must do this assignment on your own, as described in "Academic
Integrity for Homework" handout.  If you did discuss the problem or
errors messages, etc. with anyone, please list their names here. )

ms cutler + Multiple TA's



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked: n^0
 packed: n^0

numBins
 unpacked: b
 packed: b

numElementsInBin
 unpacked: n^0
 packed: n^0

getElement
 unpacked: n^0
 packed: n^ 0

isPacked
 unpacked: n^ 0
 packed: n^ 0

clear
 unpacked: 3b
 packed: 3b

addElement
 unpacked: 3k
 packed: not allowed

removeElement
 unpacked: 3k
 packed: 3k

pack
 unpacked: 5b + 3k
 packed: n^0

unpack
 unpacked: n ^ 0
 packed: 3b + e + k

print 
 unpacked: b + e * b
 packed: b + e

constructor w/ integer argument
 unpacked: 3 b + k
 packed: 3 b + k impossible?

copy constructor
 unpacked: b + e (and maybe k?)
 packed: 3 b + k + e

destructor
 unpacked: be + 2b + k
 packed:be + 2b + k

assignment operator
 unpacked: n^ 0
 packed: n ^0




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
!!READ ME!!!

I brought this to a grading TA, Nathan who could not fix my memory leak issues which I could only fix for my main file and not the teachers. 
I went to multiple Alac Tutoring sessions, and I tried to work on whitespace. 
All I can say is I tried. The teachers delete at the end of batch causes a seg fault for some reason and I don't know why. Please tell me in grading.
