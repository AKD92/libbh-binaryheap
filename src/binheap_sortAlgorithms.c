

/************************************************************************************
	Implementation of Algorithms
	For Sorting using Binary Heap Data Structure (Heap Sort)
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"







int binheap_sort(void *pArray, unsigned int nCount, unsigned int nWidth,
							int (*fpCompare) (const void *agr1, const void *arg2)) {
	
	return binheap_sortAscending(pArray, nCount, nWidth, fpCompare);
}




/************************************************************************************/
/************************************************************************************/


int binheap_sortAscending(void *pArray, unsigned int nCount, unsigned int nWidth,
							int (*fpCompare) (const void *agr1, const void *arg2)) {
	
	BinHeap heap;
	register unsigned int iElem;
	
	if (pArray == 0 || fpCompare == 0 || nWidth == 0)
		return -1;
	if (nCount < 2)
		return 0;
	
	binheap_init(&heap, pArray, nCount, nWidth, fpCompare);
	binheap_buildMaxBinHeap(&heap);
	
	iElem = nCount - 1;
	while (iElem >= 1) {
		
		binheap_exchangeElement (0, iElem, &heap);
		heap.elemCount = heap.elemCount - 1;
		binheap_sinkLightElement(&heap, 0);
		iElem = iElem - 1;
	}
	
	binheap_destroy(&heap);
	return 0;
}



int binheap_sortDescending(void *pArray, unsigned int nCount, unsigned int nWidth,
							int (*fpCompare) (const void *agr1, const void *arg2)) {
	
	BinHeap heap;
	register unsigned int iElem;
	
	if (pArray == 0 || fpCompare == 0 || nWidth == 0)
		return -1;
	if (nCount < 2)
		return 0;
	
	binheap_init(&heap, pArray, nCount, nWidth, fpCompare);
	binheap_buildMinBinHeap(&heap);
	
	iElem = nCount - 1;
	while (iElem >= 1) {
		
		binheap_exchangeElement (0, iElem, &heap);
		heap.elemCount = heap.elemCount - 1;
		binheap_sinkHeavyElement(&heap, 0);
		iElem = iElem - 1;
	}
	
	binheap_destroy(&heap);
	return 0;
}


