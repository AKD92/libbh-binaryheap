

/************************************************************************************
	Implementation of Algorithms for Binary MAX Heap Creation & Manipulation
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"







int binheap_sinkLightElement(BinHeap *heap, unsigned int index) {			/* This is MAX-HEAPIFY operation */
	
	int iStepCount;
	unsigned int uiLargest;
	unsigned int left, right;
	
	unsigned char *pArray;
	unsigned char *pCurrent, *pLeft, *pRight, *pLargest;

	if (index >= binheap_elemCount(heap))
		return -1;
	if (index == binheap_elemCount(heap) - 1)
		return 0;
	
	iStepCount = 0;
	pArray = (unsigned char *) binheap_array(heap);
	
	/********************************************************************************
		Recursive call to binheap_sinkLightElement() with a different index 'uiLargest'
		For the sake of efficiency, an iterative approach might be helpful
		Utilizing simple GOTO statement as a way of iteration/looping.
	********************************************************************************/
	
	REPEAT:																/* Code in iterative approach */
	uiLargest = index;
	left = binheap_leftChildIndex(index);
	right = binheap_rightChildIndex(index);
	
	pLeft = pArray + (binheap_elemWidth(heap) * left);
	pRight = pArray + (binheap_elemWidth(heap) * right);
	pCurrent = pArray + (binheap_elemWidth(heap) * index);
	pLargest = pArray + (binheap_elemWidth(heap) * uiLargest);
	
	if ( left < binheap_elemCount(heap)
		&& heap->fpCompare((const void*) pLeft, (const void*) pCurrent) > 0 )
	{
		uiLargest = left;
		pLargest = pArray + (binheap_elemWidth(heap) * uiLargest);
	}
	if ( right < binheap_elemCount(heap)
		&& heap->fpCompare((const void*) pRight, (const void*) pLargest) > 0 )
	{
		uiLargest = right;
		pLargest = pArray + (binheap_elemWidth(heap) * uiLargest);
	}
	
	if ( uiLargest != index ) {
		
		binheap_exchangeElement (index, uiLargest, heap);
		iStepCount = iStepCount + 1;									/* Code in iterative approach */
		
		/********************************************************************************
			Recursive call to binheap_sinkLightElement() with a different index 'uiLargest'
			Can be done through an iterative approach (more efficient for computers)
			By stating 'index = uiLargest' and then repeat again. Revision required.
		********************************************************************************/
		
		/* iStepCount = 1 + binheap_sinkLightElement(heap, uiLargest); */	/* Code in recursive approach */
		
		index = uiLargest;											/* Code in iterative approach */
		goto REPEAT;												/* Code in iterative approach */
	}
	
	return iStepCount;
}



int binheap_swimHeavyElement(BinHeap *heap, unsigned int index) {				/* This is HEAP-SWIM operation		*/
	
	int iCompareVal, iStepCount;
	unsigned int iParent;
	register unsigned int iCurrent;
	unsigned char *pArray, *pParent, *pCurrent;
	
	if (index >= binheap_elemCount(heap))						/* Check for invalid index argument */
		return -1;
	
	if (index == 0)
		return 0;
	
	iCurrent = index;
	iCompareVal = 0;
	iStepCount = 0;												/* Number of shifts/swaps needed so far */
	pArray = (unsigned char *) binheap_array(heap);
	
	REPEAT:
	iParent = binheap_parentIndex(iCurrent);
	pParent = pArray + (binheap_elemWidth(heap) * iParent);
	pCurrent = pArray + (binheap_elemWidth(heap) * iCurrent);
	iCompareVal = heap->fpCompare((const void*) pParent, (const void*) pCurrent);
	
	if (iCompareVal < 0) {
		binheap_exchangeElement(iParent, iCurrent, heap);
		iCurrent = iParent;
		iStepCount = iStepCount + 1;
		
		if (iCurrent > 0)
			goto REPEAT;
	}
	
	return iStepCount;
}



int binheap_buildMaxBinHeap(BinHeap *heap) {
	
	register unsigned int index;
	
	if (heap == 0)
		return -1;
	
	index = 1;
	while ( index < binheap_elemCount(heap) ) {
		binheap_swimHeavyElement(heap, index);						/* Perform a HEAP-SWIM operation	*/
		index = index + 1;
	}
	
	/*************************************************************************************
		Or, we could also perform a MAX-HEAPIFY operation to achieve same goal
		
		index = (binheap_elemCount(heap) / 2);
		while (index >= 1) {
			binheap_sinkLightElement(heap, index - 1);			// Perform a MAX-HEAPIFY operation
			index = index - 1;
		}
	*************************************************************************************/
	
	return 0;
}


