

/************************************************************************************
	Implementation of Algorithms
	For Sorting using Binary Heap Data Structure (Heap Sort)
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"





int binheap_sort(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2)) {
	
	return binheap_sortAscending(elemArray, nCount, nSize, compare);
}



int binheap_sortAscending(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2)) {
	
	BinHeap heap;
	register unsigned int iCurrent;
	
	binheap_init(&heap, elemArray, nCount, nSize, compare);
	binheap_buildMaxBinHeap(&heap);
	
	iCurrent = nCount - 1;
	while (iCurrent >= 1) {
		
		binheap_exchangeElement (0, iCurrent, &heap);
		heap.elemCount = heap.elemCount - 1;
		binheap_sinkLightElement(&heap, 0);
		iCurrent = iCurrent - 1;
	}
	binheap_destroy(&heap);
	
	return 0;
}



int binheap_sortDescending(void *elemArray, unsigned int nCount, unsigned int nSize,
							int (*compare) (const void *agr1, const void *arg2)) {
	
	BinHeap heap;
	register unsigned int iCurrent;
	
	binheap_init(&heap, elemArray, nCount, nSize, compare);
	binheap_buildMinBinHeap(&heap);
	
	iCurrent = nCount - 1;
	while (iCurrent >= 1) {
		
		binheap_exchangeElement (0, iCurrent, &heap);
		heap.elemCount = heap.elemCount - 1;
		binheap_sinkHeavyElement(&heap, 0);
		iCurrent = iCurrent - 1;
	}
	binheap_destroy(&heap);
	
	return 0;
}

