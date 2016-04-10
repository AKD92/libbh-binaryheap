

/************************************************************************************
	Program Interface of Binary Heap Data Structure & Associated Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BINARY_HEAP_DATA_STRUCTURE_H
#define BINARY_HEAP_DATA_STRUCTURE_H





#define binheap_elemSize(heap)     ((heap)->elemSize)
#define binheap_elemCount(heap)    ((heap)->elemCount)
#define binheap_array(heap)        ((heap)->pElemArray)







struct BinaryHeap_ {
	
	void *pElemArray;					/* Underlying memory blocks for the storage of elements	*/
	
	unsigned int elemCount;				/* Number of elements the heap is currently holding		*/
	unsigned int elemSize;				/* The size of each element, in Bytes					*/
	
	int (*compare)
			(const void *arg1, const void *arg2);

										/* User specifed function for comparing elements		*/
	void *tmpMemory;					/* Temporary memory used for faster swapping of elements */
										/* Size of this tmpMemory must be equal to elemSize */
	
};

typedef struct BinaryHeap_ BinHeap;








/*************************************************************************/
/*************************						**************************/
/*************************	PUBLIC INTERFACES	**************************/
/*************************						**************************/
/*************************************************************************/


int binheap_init(BinHeap *heap, void *array, unsigned int nCount,
			unsigned int nSize, int (*compare) (const void *arg1, const void *arg2));

void binheap_destroy(BinHeap *heap);




unsigned int binheap_parentIndex(unsigned int childIndex);

unsigned int binheap_leftChildIndex(unsigned int parentIndex);

unsigned int binheap_rightChildIndex(unsigned int parentIndex);




int binheap_sinkLightElement(BinHeap *heap, unsigned int index);		/* Algorithm for MAX HEAP */

int binheap_swimHeavyElement(BinHeap *heap, unsigned int index);		/* Algorithm for MAX HEAP */


int binheap_sinkHeavyElement(BinHeap *heap, unsigned int index);		/* Algorithm for MIN HEAP */

int binheap_swimLightElement(BinHeap *heap, unsigned int index);		/* Algorithm for MIN HEAP */




int binheap_buildMaxBinHeap(BinHeap *heap);								/* Algorithm for MAX HEAP */

int binheap_buildMinBinHeap(BinHeap *heap);								/* Algorithm for MIN HEAP */




int binheap_sort(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2));

int binheap_sortAscending(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2));
							
int binheap_sortDescending(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2));



int binheap_exchangeElement(unsigned int index1, unsigned int index2, BinHeap *heap);




#endif
