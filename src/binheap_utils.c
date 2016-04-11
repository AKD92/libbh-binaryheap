

/************************************************************************************
	Implementation of Binary Heap Utility functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"
#include <string.h>
#include <stdlib.h>







int binheap_init(BinHeap *heap, void *array, unsigned int nCount,
			unsigned int nWidth, int (*fpCompare) (const void *arg1, const void *arg2))
{
	
	/* Check for invalid function argument */
	if (heap == 0 || array == 0 || nWidth == 0 || fpCompare == 0)
		return -1;
	
	heap->pArrayElem = array;
	heap->elemCount = nCount;
	heap->elemWidth = nWidth;
	heap->fpCompare = fpCompare;
	heap->pSwapMemory = (void *) malloc(nWidth);
	return 0;
}



void binheap_destroy(BinHeap *heap) {
	
	free((void *) heap->pSwapMemory);
	memset((void *) heap, 0, sizeof(BinHeap));
	return;
}





// unsigned int binheap_parentIndex(unsigned int childIndex) {
	
	// unsigned int parent;
	
	// parent = (childIndex - 1) / 2;										/* From Wikipedia - Binary Heap	*/
	// return parent;
// }



// unsigned int binheap_leftChildIndex(unsigned int parentIndex) {
	
	// unsigned int left;
	
	// left = (parentIndex * 2) + 1;
	// return left;
// }



// unsigned int binheap_rightChildIndex(unsigned int parentIndex) {
	
	// unsigned int right;
	
	// right = (parentIndex * 2) + 2;
	// return right;
// }





int binheap_swapElements(unsigned int index1, unsigned int index2, BinHeap *heap) {
	
	unsigned char *pElem1, *pElem2;
	
	pElem1 = ((unsigned char *) binheap_array(heap)) + (binheap_width(heap) * index1);
	pElem2 = ((unsigned char *) binheap_array(heap)) + (binheap_width(heap) * index2);
	
	memcpy((void*) heap->pSwapMemory, (const void*) pElem1,             binheap_width(heap));
	memcpy((void*) pElem1,            (const void*) pElem2,             binheap_width(heap));
	memcpy((void*) pElem2,            (const void*) heap->pSwapMemory,  binheap_width(heap));
	
	return 0;
}


