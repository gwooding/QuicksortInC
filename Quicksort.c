   #include <stdio.h>
   #include <stdlib.h>
   #include <errno.h>
   #include <string.h>


	void die(const char *message)
    {
        if (errno) {
            perror(message);
        } else {
            printf("ERROR: %s\n", message);
        }

        exit(1);
    }

    int* merge(int *sortedArray1, int sa1Size, int *sortedArray2, int sa2Size){

    	int *target = malloc((sa1Size + sa2Size) * sizeof(int));

    	int limit = sa1Size + sa2Size;
    	int counterOne = 0;
    	int counterTwo = 0;

    	for(int i = 0; i < limit; i++){

    		if(counterTwo > sa2Size - 1){
				target[counterOne + counterTwo] = sortedArray1[counterOne];
    			counterOne = counterOne + 1;
    		} 
    		else if(counterOne > sa1Size - 1){
    			target[counterOne + counterTwo] = sortedArray2[counterTwo];
    			counterTwo = counterTwo + 1;
    		}
    		else if(sortedArray1[counterOne]<sortedArray2[counterTwo]){
    			target[counterOne + counterTwo] = sortedArray1[counterOne];
    			counterOne = counterOne + 1;
    		} else {
    			target[counterOne + counterTwo] = sortedArray2[counterTwo];
    			counterTwo = counterTwo + 1;
    		}
    	}
    	free(sortedArray1);
    	free(sortedArray2);
    	return target;
    }


    int* quicksort(int *numbers, int count){

    	int *target = malloc(count * sizeof(int));
 
        if (!target)
             die("Memory error.");
 
        memcpy(target, numbers, count * sizeof(int));

        if(count==2){
        	if(target[0]>target[1]){
        		int temp = target[0];
        		target[0] = target[1];
        		target[1] = temp;
        		return target;
        	}
        	else {
        		return target;
        	}
        }
        else if(count == 1){
        	return target;
        }
        else{
        	int split = count/2;
        	int* result = merge(quicksort(target, split), split, quicksort(target + split, count - split), count - split);
            return result;
        }

    }

    int main(int argc, char *argv[])
    {
    	if (argc < 2)
            die("USAGE: Quicksort [integers]");

        int count = argc - 1;
        int i = 0;
        char **inputs = argv + 1;

        int *numbers = malloc(count * sizeof(int));
        if (!numbers) die("Memory error.");

        for (i = 0; i < count; i++) {
            numbers[i] = atoi(inputs[i]);
        }

        int *sorted = quicksort(numbers, count);

        if (!sorted)
            die("Failed to sort as requested.");

        for (i = 0; i < count; i++) {
            printf("%d ", sorted[i]);
        }
        printf("\n");

        free(sorted);

    	return 0;
    }