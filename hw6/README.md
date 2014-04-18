## CSCI 104 HW 6

###Notes:
	+ Did not divide by Clock time per sec because that kept resulting in zero at some times and not others.
    + Had some trouble with time measurement code, not sure if completely correct but could not find any major issues
    + at office hours.
    + For the Heap time measurement, clock starts when generating numbers, but this is constant time so should not be
    + an issue for the timing. 
   ####Answers/Reasoning 

    + It makes sense that both add and remove have similar times considering the operations used to perform them. 
    + Adding is a simple push_back and a lookup, which is linear time and removing is similar in behavior time. Thus,
    + it makes sense that they take close to the same amount of time. 
