

/************************************************************************************
	Implementation of Algorithms for Binary MIN Heap Creation & Manipulation
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "binheap.h"




int binheap_sinkHeavyElement(BinHeap *heap, unsigned int index) {					/* This is MIN-HEAPIFY operation */
	
	unsigned int smallest;
	unsigned int left, right;
	int stepCount;
	
	char *elemArray;
	char *elemLeft, *elemRight, *elemSmallest, *elemCurrent;

	if (index >= binheap_elemCount(heap)) {
		return -1;
	}
	stepCount = 0;
	
	/********************************************************************************
		Recursive call to binheap_sinkLightElement() with a different index 'smallest'
		For the sake of efficiency, an iterative approach might be helpful
		Utilizing simple GOTO statement as a way of iteration/looping.
	********************************************************************************/
	
	REPEAT:																/* Code in iterative approach */
	
	smallest = index;
	left = binheap_leftChildIndex(index);
	right = binheap_rightChildIndex(index);
	
	elemArray = (char *) binheap_array(heap);
	elemLeft = elemArray + (binheap_elemSize(heap) * left);
	elemRight = elemArray + (binheap_elemSize(heap) * right);
	elemCurrent = elemArray + (binheap_elemSize(heap) * index);
	elemSmallest = elemArray + (binheap_elemSize(heap) * smallest);
	
	if ( left < binheap_elemCount(heap)
		&& heap->compare((const void*) elemLeft, (const void*) elemCurrent) < 0 )
	{
		smallest = left;
		elemSmallest = elemArray + (binheap_elemSize(heap) * smallest);
	}
	if ( right < binheap_elemCount(heap)
		&& heap->compare((const void*) elemRight, (const void*) elemSmallest) < 0 )
	{
		smallest = right;
		elemSmallest = elemArray + (binheap_elemSize(heap) * smallest);
	}
	
	if ( smallest != index ) {
		
		binheap_exchangeElement (index, smallest, heap);
		stepCount = stepCount + 1;									/* Code in iterative approach */
		
		/********************************************************************************
			Recursive call to binheap_sinkLightElement() with a different index 'smallest'
			Can be done through an iterative approach (more efficient for computers)
			By stating 'index = smallest' and then repeat again. Revision required.
		********************************************************************************/
		
		/* stepCount = 1 + binheap_sinkHeavyElement(heap, smallest); */	/* Code in recursive approach */
		
		index = smallest;											/* Code in iterative approach */
		goto REPEAT;												/* Code in iterative approach */
	}
	
	return stepCount;
}



int binheap_swimLightElement(BinHeap *heap, unsigned int index) {				/* This is HEAP-SWIM operation		*/
	
	int cmpResult, stepCount;
	unsigned int iParent;
	char *elemParent, *elemCurrent, *elemArray;
	register unsigned int iCurrent;
	
	if (index >= binheap_elemCount(heap)) {						/* Check for invalid index argument */
		return -1;
	}
	
	iCurrent = index;
	cmpResult = -1;
	stepCount = 0;												/* Number of shifts/swaps needed so far */
	elemArray = (char *) binheap_array(heap);
	
	while (iCurrent > 0 && cmpResult < 0) {
		iParent = binheap_parentIndex(iCurrent);
		elemCurrent = elemArray + (binheap_elemSize(heap) * iCurrent);
		elemParent = elemArray + (binheap_elemSize(heap) * iParent);
		
		cmpResult = heap->compare((const void*) elemCurrent, (const void*) elemParent);
		
		if (cmpResult < 0) {
			binheap_exchangeElement(iParent, iCurrent, heap);
			iCurrent = binheap_parentIndex(iCurrent);
			stepCount = stepCount + 1;
		}
	}
	
	return stepCount;
}



int binheap_buildMinBinHeap(BinHeap *heap) {
	
	register unsigned int index;
	
	index = 1;
	while ( index < heap->elemCount ) {
		binheap_swimLightElement(heap, index);						/* Perform a HEAP-SWIM operation	*/
		index = index + 1;
	}
	
	/*************************************************************************************
		Or, we could also perform a MIN-HEAPIFY operation to achieve same goal
		
		index = (elemCount / 2);
		while (index >= 1) {
			binheap_sinkHeavyElement(heap, index - 1);			// Perform a MIN-HEAPIFY operation
			index = index - 1;
		}
	*************************************************************************************/
	
	return 0;
}

