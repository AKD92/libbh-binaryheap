

/************************************************************************************
	Implementation of Algorithms for MIN Heap Creation & Manipulation
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "heap.h"




int heap_sinkHeavyElement(Heap *heap, unsigned int index) {					/* This is MIN-HEAPIFY operation */
	
	unsigned int smallest;
	unsigned int left, right;
	int stepCount;
	
	char *elemArray;
	char *elemLeft, *elemRight, *elemSmallest, *elemCurrent;

	if (index >= heap_elemCount(heap)) {
		return -1;
	}
	stepCount = 0;
	
	/********************************************************************************
		Recursive call to heap_sinkLightElement() with a different index 'smallest'
		For the sake of efficiency, an iterative approach might be helpful
		Utilizing simple GOTO statement as a way of iteration/looping.
	********************************************************************************/
	
	REPEAT:																/* Code in iterative approach */
	
	smallest = index;
	left = heap_leftChildIndex(index);
	right = heap_rightChildIndex(index);
	
	elemArray = (char *) heap_array(heap);
	elemLeft = elemArray + (heap_elemSize(heap) * left);
	elemRight = elemArray + (heap_elemSize(heap) * right);
	elemCurrent = elemArray + (heap_elemSize(heap) * index);
	elemSmallest = elemArray + (heap_elemSize(heap) * smallest);
	
	if ( left < heap_elemCount(heap)
		&& heap->compare((const void*) elemLeft, (const void*) elemCurrent) < 0 )
	{
		smallest = left;
		elemSmallest = elemArray + (heap_elemSize(heap) * smallest);
	}
	if ( right < heap_elemCount(heap)
		&& heap->compare((const void*) elemRight, (const void*) elemSmallest) < 0 )
	{
		smallest = right;
		elemSmallest = elemArray + (heap_elemSize(heap) * smallest);
	}
	
	if ( smallest != index ) {
		
		heap_exchangeElement (index, smallest, heap);
		stepCount = stepCount + 1;									/* Code in iterative approach */
		
		/********************************************************************************
			Recursive call to heap_sinkLightElement() with a different index 'smallest'
			Can be done through an iterative approach (more efficient for computers)
			By stating 'index = smallest' and then repeat again. Revision required.
		********************************************************************************/
		
		/* stepCount = 1 + heap_sinkHeavyElement(heap, smallest); */	/* Code in recursive approach */
		
		index = smallest;											/* Code in iterative approach */
		goto REPEAT;												/* Code in iterative approach */
	}
	
	return stepCount;
}



int heap_swimLightElement(Heap *heap, unsigned int index) {				/* This is HEAP-SWIM operation		*/
	
	int cmpResult, stepCount;
	unsigned int iParent;
	char *elemParent, *elemCurrent, *elemArray;
	register unsigned int iCurrent;
	
	if (index >= heap_elemCount(heap)) {						/* Check for invalid index argument */
		return -1;
	}
	
	iCurrent = index;
	cmpResult = -1;
	stepCount = 0;												/* Number of shifts/swaps needed so far */
	elemArray = (char *) heap_array(heap);
	
	while (iCurrent > 0 && cmpResult < 0) {
		iParent = heap_parentIndex(iCurrent);
		elemCurrent = elemArray + (heap_elemSize(heap) * iCurrent);
		elemParent = elemArray + (heap_elemSize(heap) * iParent);
		
		cmpResult = heap->compare((const void*) elemCurrent, (const void*) elemParent);
		
		if (cmpResult < 0) {
			heap_exchangeElement(iParent, iCurrent, heap);
			iCurrent = heap_parentIndex(iCurrent);
			stepCount = stepCount + 1;
		}
	}
	
	return stepCount;
}



int heap_buildMinHeap(Heap *heap) {
	
	register unsigned int index;
	
	index = 1;
	while ( index < heap->elemCount ) {
		heap_swimLightElement(heap, index);						/* Perform a HEAP-SWIM operation	*/
		index = index + 1;
	}
	
	/*************************************************************************************
		Or, we could also perform a MIN-HEAPIFY operation to achieve same goal
		
		index = (elemCount / 2);
		while (index >= 1) {
			heap_sinkHeavyElement(heap, index - 1);			// Perform a MIN-HEAPIFY operation
			index = index - 1;
		}
	*************************************************************************************/
	
	return 0;
}

