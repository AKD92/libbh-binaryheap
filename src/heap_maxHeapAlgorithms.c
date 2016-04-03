

/************************************************************************************
	Implementation of Algorithms for MAX Heap Creation & Manipulation
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "heap.h"




int heap_sinkLightElement(Heap *heap, unsigned int index) {					/* This is MAX-HEAPIFY operation */
	
	unsigned int largest;
	unsigned int left, right;
	int stepCount;
	
	char *elemArray;
	char *elemLeft, *elemRight, *elemLargest, *elemCurrent;

	if (index >= heap_elemCount(heap)) {
		return -1;
	}
	stepCount = 0;
	
	/********************************************************************************
		Recursive call to heap_sinkLightElement() with a different index 'largest'
		For the sake of efficiency, an iterative approach might be helpful
		Utilizing simple GOTO statement as a way of iteration/looping.
	********************************************************************************/
	
	REPEAT:																/* Code in iterative approach */
	
	largest = index;
	left = heap_leftChildIndex(index);
	right = heap_rightChildIndex(index);
	
	elemArray = (char *) heap_array(heap);
	elemLeft = elemArray + (heap_elemSize(heap) * left);
	elemRight = elemArray + (heap_elemSize(heap) * right);
	elemCurrent = elemArray + (heap_elemSize(heap) * index);
	elemLargest = elemArray + (heap_elemSize(heap) * largest);
	
	if ( left < heap_elemCount(heap)
		&& heap->compare((const void*) elemLeft, (const void*) elemCurrent) > 0 )
	{
		largest = left;
		elemLargest = elemArray + (heap_elemSize(heap) * largest);
	}
	if ( right < heap_elemCount(heap)
		&& heap->compare((const void*) elemRight, (const void*) elemLargest) > 0 )
	{
		largest = right;
		elemLargest = elemArray + (heap_elemSize(heap) * largest);
	}
	
	if ( largest != index ) {
		
		heap_exchangeElement (index, largest, heap);
		stepCount = stepCount + 1;									/* Code in iterative approach */
		
		/********************************************************************************
			Recursive call to heap_sinkLightElement() with a different index 'largest'
			Can be done through an iterative approach (more efficient for computers)
			By stating 'index = largest' and then repeat again. Revision required.
		********************************************************************************/
		
		/* stepCount = 1 + heap_sinkLightElement(heap, largest); */	/* Code in recursive approach */
		
		index = largest;											/* Code in iterative approach */
		goto REPEAT;												/* Code in iterative approach */
	}
	
	return stepCount;
}



int heap_swimHeavyElement(Heap *heap, unsigned int index) {				/* This is HEAP-SWIM operation		*/
	
	int cmpResult, stepCount;
	unsigned int iParent;
	char *elemParent, *elemCurrent, *elemArray;
	register unsigned int iCurrent;
	
	if (index >= heap_elemCount(heap)) {						/* Check for invalid index argument */
		return -1;
	}
	
	iCurrent = index;
	cmpResult = 1;
	stepCount = 0;												/* Number of shifts/swaps needed so far */
	elemArray = (char *) heap_array(heap);
	
	while (iCurrent > 0 && cmpResult > 0) {
		iParent = heap_parentIndex(iCurrent);
		elemCurrent = elemArray + (heap_elemSize(heap) * iCurrent);
		elemParent = elemArray + (heap_elemSize(heap) * iParent);
		
		cmpResult = heap->compare((const void*) elemCurrent, (const void*) elemParent);
		
		if (cmpResult > 0) {
			heap_exchangeElement(iParent, iCurrent, heap);
			iCurrent = heap_parentIndex(iCurrent);
			stepCount = stepCount + 1;
		}
	}
	
	return stepCount;
}



int heap_buildMaxHeap(Heap *heap) {
	
	register unsigned int index;
	
	index = 1;
	while ( index < heap->elemCount ) {
		heap_swimHeavyElement(heap, index);						/* Perform a HEAP-SWIM operation	*/
		index = index + 1;
	}
	
	/*************************************************************************************
		Or, we could also perform a MAX-HEAPIFY operation to achieve same goal
		
		index = (elemCount / 2);
		while (index >= 1) {
			heap_sinkLightElement(heap, index - 1);			// Perform a MAX-HEAPIFY operation
			index = index - 1;
		}
	*************************************************************************************/
	
	return 0;
}

