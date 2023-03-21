#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	int m = (l + r)/2;
	if (l < r)
	{
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
	}
	
	int a, b, c;
	int s1 = m - l + 1;
	int s2 = r - m; 

	//arrays for only temporary !Remember to free at end of fucntion
	int lA[s1], rA[s2];
	for(a = 0; a < s1; a++)
	{
		lA[a] = pData[l + a];
	}
	for (b = 0; b < s2; b++)
	{
		rA[b] = pData[m + 1 + b];
	}
	extraMemoryAllocated = sizeof(lA) + sizeof(rA);

	a = 0, b = 0;
	c = l;

	do 
	{
		if (lA[a] <= rA[b])
		{
			pData[c] = lA[a];
			a++;
		} else 
		{
			pData[c] = rA[b];
			b++;
		}
		c++;
	} while(a < s1 && b < s2);
	
	while (a < s1)
	{
		pData[c] = lA[a];
		a++;
		c++;
	}

	while (b < s2)
	{
		pData[c] = rA[b];
		b++;
		c++;
	}


}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	
	int a, b, item;
	for (a = 1; a < n; a++)
	{
		item = pData[a];
		b = a - 1; 

		while (b >= 0 && pData[b] > item)
		{
			pData[b + 1] = pData[b];
			b--; 
		}
		pData[b + 1] = item; 
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int a, b, temp;
	for (a = 0; a < n-1; a++)
	{
		for(b = 0; b < n-a-1; b++)
		{
			if (pData[b] > pData[b+1])
			{
				temp = pData[b];
				pData[b]= pData[b+1];
				pData[b+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int a, b, min_index, temp;
	for (a =0; a< n-1; a++)
	{
		min_index = a;
		for(b = a + 1; b < n; b++)
		{
			if (pData[b] < pData[min_index])
				min_index = b;
		}

		temp = pData[a];
		pData[a] = pData[min_index];
		pData[min_index] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		for(int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", &(*ppData)[i]);
		}
		// Implement parse data block
	}
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}