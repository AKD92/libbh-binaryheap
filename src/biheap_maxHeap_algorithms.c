

/************************************************************************************
    Implementation of Algorithms for Binary MAX Heap Creation & Manipulation
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "biheap.h"







int biheap_sinkLightElement(BiHeap *heap, unsigned int index) {     /* This is MAX-HEAPIFY operation */
    
    int nSwaps;
    unsigned int iLargest;
    unsigned int iLeft, iRight;
    
    unsigned char *pArray;
    unsigned char *pCurrent, *pLeft, *pRight, *pLargest;
    
    
    /* Check for invalid index arguments */
    if (index >= biheap_size(heap))
        return -1;
    if (index == biheap_size(heap) - 1)
        return 0;
    
    
    /* nSwaps = Number of shifts/swaps needed so far */
    nSwaps = 0;
    iLargest = index;
    pArray = (unsigned char *) biheap_array(heap);
    
    
    /********************************************************************************
        Recursive call to biheap_sinkLightElement() with a different index 'iLargest'
        For the sake of efficiency, an iterative approach might be helpful
        Utilizing simple GOTO statement as a way of iteration/looping.
    ********************************************************************************/
    
    
    /* Execution of SINK Algorithm begins now */
    REPEAT:                                                           /* Code in iterative approach */
    iLeft = biheap_leftChildIndex(index);
    iRight = biheap_rightChildIndex(index);
    
    pLeft = pArray + (biheap_width(heap) * iLeft);
    pRight = pArray + (biheap_width(heap) * iRight);
    pCurrent = pArray + (biheap_width(heap) * index);
    pLargest = pCurrent;
    
    if ( iLeft < biheap_size(heap)
        && heap->fpCompare((const void *) pLeft, (const void *) pCurrent) > 0 )
    {
        iLargest = iLeft;
        pLargest = pLeft;
    }
    if ( iRight < biheap_size(heap)
        && heap->fpCompare((const void *) pRight, (const void *) pLargest) > 0 )
    {
        iLargest = iRight;
        pLargest = pRight;
    }
    
    if ( iLargest != index ) {
        
        biheap_swapElements(index, iLargest, heap);
        nSwaps = nSwaps + 1;                                          /* Code in iterative approach */
        
        /********************************************************************************
            Recursive call to biheap_sinkLightElement() with a different index 'iLargest'
            Can be done through an iterative approach (more efficient for computers)
            By stating 'index = iLargest' and then repeat again. Revision required.
        ********************************************************************************/
        
        /* nSwaps = 1 + biheap_sinkLightElement(heap, iLargest); */  /* Code in recursive approach */
        
        index = iLargest;                                             /* Code in iterative approach */
        goto REPEAT;                                                  /* Code in iterative approach */
    }
    
    return nSwaps;
}



int biheap_swimHeavyElement(BiHeap *heap, unsigned int index) {     /* This is HEAP-SWIM operation */
    
    int iCompareVal, nSwaps;
    unsigned int iParent;
    register unsigned int iCurrent;
    unsigned char *pArray, *pParent, *pCurrent;
    
    
    /* Check for invalid index arguments */
    if (index >= biheap_size(heap))
        return -1;
    if (index == 0)
        return 0;
    
    
    /* nSwaps = Number of shifts/swaps needed so far */
    nSwaps = 0;
    iCompareVal = 0;
    iCurrent = index;
    pArray = (unsigned char *) biheap_array(heap);
    
    
    /* Execution of SWIM Algorithm begins now */
    REPEAT:
    iParent = biheap_parentIndex(iCurrent);
    pParent = pArray + (biheap_width(heap) * iParent);
    pCurrent = pArray + (biheap_width(heap) * iCurrent);
    iCompareVal = heap->fpCompare((const void *) pParent, (const void *) pCurrent);
    
    if (iCompareVal < 0) {
        
        biheap_swapElements(iParent, iCurrent, heap);
        nSwaps = nSwaps + 1;
        iCurrent = iParent;
        if (iCurrent > 0) goto REPEAT;
    }
    
    return nSwaps;
}



int biheap_buildBinaryMaxHeap(BiHeap *heap) {
    
    register unsigned int index;
    
    
    /* Check for invalid function argument */
    if (heap == 0)
        return -1;
    
    index = 1;
    while ( index < biheap_size(heap) ) {
        biheap_swimHeavyElement(heap, index);                        /* Perform a HEAP-SWIM operation */
        index = index + 1;
    }
    
    /*************************************************************************************
        Or, we could also perform a MAX-HEAPIFY operation to achieve same goal
        
        index = (biheap_size(heap) / 2);
        while (index >= 1) {
            biheap_sinkLightElement(heap, index - 1);      // Perform a MAX-HEAPIFY operation
            index = index - 1;
        }
    *************************************************************************************/
    
    return 0;
}


