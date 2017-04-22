I tried to multithread the program by exploiting parallelism in the nested for loops that process the rows and columns of the image. 

The main issue was that pthread_create only takes in one function to create and only one argument can be passed into the function. I had to overcome the issue by creating a new
 function with the entire code in the for loops. This function only takes in one argument so I had to declare many variables within the function. I also declared a scene variable
 in the global scope since it is needed before the threads are created. 

I used the function’s argument to pass in the number of the thread that’s running it. I created an array of numbers in the main function and passed a reference to the thread
 number into the function when I created the thread using pthread_create. 

The next issue was how to partition the work the for loops have to do between the threads. I decided that I could break up the rows of the image into sections that each thread 
could work on by starting each thread’s for loop at the number of the thread and incrementing by the number of threads. 

I then needed to properly print the color values for each pixel. I created a 3D array with width, height, and color for each thread to facilitate printing the color values in the main function.

After solving the above issues, I was able to fix some minor bugs and have the program work correctly. The most major bug I had was that I forgot to have the program print 
a newline in the for loop that prints out the color values so the diff file showed that every 131 lines, my color values were wrong. 

Running make clean check showed that multithreading greatly improved the performance of the program. With more threads, the real time significantly decreased since 
the multithreaded program exploited the parallelism of the code to run on many CPU cores at the same time. It appears that the program runs twice as fast with each 
doubling of threads, up to 8 threads. 