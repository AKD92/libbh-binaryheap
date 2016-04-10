

/************************************************************************************
	Implementation of Algorithms for Binary MAX Heap Creation & Manipulation
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"




int binheap_sinkLightElement(BinHeap *heap, unsigned int index) {					/* This is MAX-HEAPIFY operation */
	
	unsigned int largest;
	unsigned int left, right;
	int stepCount;
	
	char *elemArray;
	char *elemLeft, *elemRight, *elemLargest, *elemCurrent;

	if (index >= binheap_elemCount(heap)) {
		return -1;
	}
	stepCount = 0;
	
	/********************************************************************************
		Recursive call to binheap_sinkLightElement() with a different index 'largest'
		For the sake of efficiency, an iterative approach might be helpful
		Utilizing simple GOTO statement as a way of iteration/looping.
	********************************************************************************/
	
	REPEAT:																/* Code in iterative approach */
	
	largest = index;
	left = binheap_leftChildIndex(index);
	right = binheap_rightChildIndex(index);
	
	elemArray = (char *) binheap_array(heap);
	elemLeft = elemArray + (binheap_elemSize(heap) * left);
	elemRight = elemArray + (binheap_elemSize(heap) * right);
	elemCurrent = elemArray + (binheap_elemSize(heap) * index);
	elemLargest = elemArray + (binheap_elemSize(heap) * largest);
	
	if ( left < binheap_elemCount(heap)
		&& heap->compare((const void*) elemLeft, (const void*) elemCurrent) > 0 )
	{
		largest = left;
		elemLargest = elemArray + (binheap_elemSize(heap) * largest);
	}
	if ( right < binheap_elemCount(heap)
		&& heap->compare((const void*) elemRight, (const void*) elemLargest) > 0 )
	{
		largest = right;
		elemLargest = elemArray + (binheap_elemSize(heap) * largest);
	}
	
	if ( largest != index ) {
		
		binheap_exchangeElement (index, largest, heap);
		stepCount = stepCount + 1;									/* Code in iterative approach */
		
		/********************************************************************************
			Recursive call to binheap_sinkLightElement() with a different index 'largest'
			Can be done through an iterative approach (more efficient for computers)
			By stating 'index = largest' and then repeat again. Revision required.
		********************************************************************************/
		
		/* stepCount = 1 + binheap_sinkLightElement(heap, largest); */	/* Code in recursive approach */
		
		index = largest;											/* Code in iterative approach */
		goto REPEAT;												/* Code in iterative approach */
	}
	
	return stepCount;
}



int binheap_swimHeavyElement(BinHeap *heap, unsigned int index) {				/* This is HEAP-SWIM operation		*/
	
	int cmpResult, stepCount;
	unsigned int iParent;
	char *elemParent, *elemCurrent, *elemArray;
	register unsigned int iCurrent;
	
	if (index >= binheap_elemCount(heap)) {						/* Check for invalid index argument */
		return -1;
	}
	
	iCurrent = index;
	cmpResult = 1;
	stepCount = 0;												/* Number of shifts/swaps needed so far */
	elemArray = (char *) binheap_array(heap);
	
	while (iCurrent > 0 && cmpResult > 0) {
		iParent = binheap_parentIndex(iCurrent);
		elemCurrent = elemArray + (binheap_elemSize(heap) * iCurrent);
		elemParent = elemArray + (binheap_elemSize(heap) * iParent);
		
		cmpResult = heap->compare((const void*) elemCurrent, (const void*) elemParent);
		
		if (cmpResult > 0) {
			binheap_exchangeElement(iParent, iCurrent, heap);
			iCurrent = binheap_parentIndex(iCurrent);
			stepCount = stepCount + 1;
		}
	}
	
	return stepCount;
}



int binheap_buildMaxBinHeap(BinHeap *heap) {
	
	register unsigned int index;
	
	index = 1;
	while ( index < heap->elemCount ) {
		binheap_swimHeavyElement(heap, index);						/* Perform a HEAP-SWIM operation	*/
		index = index + 1;
	}
	
	/*************************************************************************************
		Or, we could also perform a MAX-HEAPIFY operation to achieve same goal
		
		index = (elemCount / 2);
		while (index >= 1) {
			binheap_sinkLightElement(heap, index - 1);			// Perform a MAX-HEAPIFY operation
			index = index - 1;
		}
	*************************************************************************************/
	
	return 0;
}

