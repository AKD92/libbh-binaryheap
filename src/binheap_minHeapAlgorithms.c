

/************************************************************************************
	Implementation of Algorithms for Binary MIN Heap Creation & Manipulation
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"







int binheap_sinkHeavyElement(BinHeap *heap, unsigned int index) {			/* This is MIN-HEAPIFY operation */
	
	int iStepCount;
	unsigned int uiSmallest;
	unsigned int left, right;
	
	unsigned char *pArray;
	unsigned char *pCurrent, *pLeft, *pRight, *pSmallest;

	if (index >= binheap_elemCount(heap))
		return -1;
	if (index == binheap_elemCount(heap) - 1)
		return 0;
	
	iStepCount = 0;
	pArray = (unsigned char *) binheap_array(heap);
	
	/********************************************************************************
		Recursive call to binheap_sinkLightElement() with a different index 'uiSmallest'
		For the sake of efficiency, an iterative approach might be helpful
		Utilizing simple GOTO statement as a way of iteration/looping.
	********************************************************************************/
	
	REPEAT:																/* Code in iterative approach */
	uiSmallest = index;
	left = binheap_leftChildIndex(index);
	right = binheap_rightChildIndex(index);
	
	pLeft = pArray + (binheap_elemWidth(heap) * left);
	pRight = pArray + (binheap_elemWidth(heap) * right);
	pCurrent = pArray + (binheap_elemWidth(heap) * index);
	pSmallest = pArray + (binheap_elemWidth(heap) * uiSmallest);
	
	if ( left < binheap_elemCount(heap)
		&& heap->fpCompare((const void*) pLeft, (const void*) pCurrent) < 0 )
	{
		uiSmallest = left;
		pSmallest = pArray + (binheap_elemWidth(heap) * uiSmallest);
	}
	if ( right < binheap_elemCount(heap)
		&& heap->fpCompare((const void*) pRight, (const void*) pSmallest) < 0 )
	{
		uiSmallest = right;
		pSmallest = pArray + (binheap_elemWidth(heap) * uiSmallest);
	}
	
	if ( uiSmallest != index ) {
		
		binheap_exchangeElement (index, uiSmallest, heap);
		iStepCount = iStepCount + 1;									/* Code in iterative approach */
		
		/********************************************************************************
			Recursive call to binheap_sinkLightElement() with a different index 'uiSmallest'
			Can be done through an iterative approach (more efficient for computers)
			By stating 'index = uiSmallest' and then repeat again. Revision required.
		********************************************************************************/
		
		/* iStepCount = 1 + binheap_sinkHeavyElement(heap, uiSmallest); */	/* Code in recursive approach */
		
		index = uiSmallest;											/* Code in iterative approach */
		goto REPEAT;												/* Code in iterative approach */
	}
	
	return iStepCount;
}



int binheap_swimLightElement(BinHeap *heap, unsigned int index) {				/* This is HEAP-SWIM operation		*/
	
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
	
	if (iCompareVal > 0) {
		binheap_exchangeElement(iParent, iCurrent, heap);
		iCurrent = iParent;
		iStepCount = iStepCount + 1;
		
		if (iCurrent > 0)
			goto REPEAT;
	}
	
	return iStepCount;
}



int binheap_buildMinBinHeap(BinHeap *heap) {
	
	register unsigned int index;
	
	if (heap == 0)
		return -1;
	
	index = 1;
	while ( index < binheap_elemCount(heap) ) {
		binheap_swimLightElement(heap, index);						/* Perform a HEAP-SWIM operation	*/
		index = index + 1;
	}
	
	/*************************************************************************************
		Or, we could also perform a MIN-HEAPIFY operation to achieve same goal
		
		index = (binheap_elemCount(heap) / 2);
		while (index >= 1) {
			binheap_sinkHeavyElement(heap, index - 1);			// Perform a MIN-HEAPIFY operation
			index = index - 1;
		}
	*************************************************************************************/
	
	return 0;
}


