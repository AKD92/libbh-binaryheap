

/************************************************************************************
	Program Interface of Heap Data Structure & Associated Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef HEAP_DATA_STRUCTURE_H
#define HEAP_DATA_STRUCTURE_H





#define heap_elemSize(heap)		((heap)->elemSize)
#define heap_elemCount(heap)	((heap)->elemCount)
#define heap_array(heap)		((heap)->pElemArray)







struct HeapDataStructure_ {
	
	void *pElemArray;					/* Underlying memory blocks for the storage of elements	*/
	
	unsigned int elemCount;				/* Number of elements the heap is currently holding		*/
	unsigned int elemSize;				/* The size of each element, in Bytes					*/
	
	int (*compare)
			(const void *arg1, const void *arg2);

										/* User specifed function for comparing elements		*/
	void *tmpMemory;					/* Temporary memory used for faster swapping of elements */
	
};

typedef struct HeapDataStructure_ Heap;








/*************************************************************************/
/*************************						**************************/
/*************************	PUBLIC INTERFACES	**************************/
/*************************						**************************/
/*************************************************************************/


int heap_init(Heap *heap, void *array, unsigned int nCount,
			unsigned int nSize, int (*compare) (const void *arg1, const void *arg2));

void heap_destroy(Heap *heap);



unsigned int heap_parentIndex(unsigned int childIndex);

unsigned int heap_leftChildIndex(unsigned int parentIndex);

unsigned int heap_rightChildIndex(unsigned int parentIndex);



int heap_sinkLightElement(Heap *heap, unsigned int index);

int heap_swimHeavyElement(Heap *heap, unsigned int index);


int heap_sinkHeavyElement(Heap *heap, unsigned int index);

int heap_swimLightElement(Heap *heap, unsigned int index);




int heap_buildMaxHeap(Heap *heap);

int heap_buildMinHeap(Heap *heap);



int heap_exchangeElement(unsigned int index1, unsigned int index2, Heap *heap);

int heap_sort(void *elemArray, unsigned int count, unsigned int size,
							int (*compare) (const void *agr1, const void *arg2));






#endif
