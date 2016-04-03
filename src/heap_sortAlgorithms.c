

/************************************************************************************
	Implementation of Algorithms for Sorting using Heap Data Structure (Heap Sort)
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "heap.h"





int heap_sort(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2)) {
	
	Heap heap;
	register unsigned int iCurrent;
	
	heap_init(&heap, elemArray, nCount, nSize, compare);
	heap_buildMaxHeap(&heap);
	
	iCurrent = nCount - 1;
	while (iCurrent >= 1) {
		
		heap_exchangeElement (0, iCurrent, &heap);
		heap.elemCount = heap.elemCount - 1;
		heap_sinkLightElement(&heap, 0);
		iCurrent = iCurrent - 1;
	}
	heap_destroy(&heap);
	
	return 0;
}

