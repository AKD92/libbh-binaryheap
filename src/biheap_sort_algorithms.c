

/************************************************************************************
    Implementation of Binary Heap Algorithms for Sorting arrays (Traditional Heap Sort)
    Using Binary Heap Data Structure
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "biheap.h"







/************************************************************************************/
/************************************************************************************/


int biheap_sort(void *pArray, unsigned int nCount, unsigned int nWidth,
                            int (*fpCompare) (const void *agr1, const void *arg2))
{
    
    return biheap_sortAscending(pArray, nCount, nWidth, fpCompare);
}




/************************************************************************************/
/************************************************************************************/


int biheap_sortAscending(void *pArray, unsigned int nCount, unsigned int nWidth,
                                     int (*fpCompare) (const void *agr1, const void *arg2))
{
    
    BiHeap heap;
    register unsigned int iElem;
    
    
    /* Check for invalid algorithm arguments */
    if (pArray == 0 || fpCompare == 0 || nWidth == 0)
        return -1;
    if (nCount < 2)
        return 0;
    
    
    /* Build a Binary MAX Heap on top of the pArray */
    biheap_init(&heap, pArray, nCount, nWidth, fpCompare);
    biheap_buildBinaryMaxHeap(&heap);
    
    
    /* SINK all lighter elements down the Binary MAX Heap (pArray) */
    iElem = nCount - 1;
    while (iElem >= 1) {
        
        biheap_swapElements (0, iElem, &heap);
        biheap_size(&heap) = biheap_size(&heap) - 1;
        biheap_sinkLightElement(&heap, 0);
        iElem = iElem - 1;
    }
    
    /* Destroy temporary Binary Heap wrapper object */
    biheap_destroy(&heap);
    return 0;
}



int biheap_sortDescending(void *pArray, unsigned int nCount, unsigned int nWidth,
                                      int (*fpCompare) (const void *agr1, const void *arg2))
{
    
    BiHeap heap;
    register unsigned int iElem;
    
    
    /* Check for invalid algorithm arguments */
    if (pArray == 0 || fpCompare == 0 || nWidth == 0)
        return -1;
    if (nCount < 2)
        return 0;
    
    
    /* Build a Binary MIN Heap on top of the pArray */
    biheap_init(&heap, pArray, nCount, nWidth, fpCompare);
    biheap_buildBinaryMinHeap(&heap);
    
    
    /* SINK all heavier elements down the Binary MIN Heap (pArray) */
    iElem = nCount - 1;
    while (iElem >= 1) {
        
        biheap_swapElements (0, iElem, &heap);
        biheap_size(&heap) = biheap_size(&heap) - 1;
        biheap_sinkHeavyElement(&heap, 0);
        iElem = iElem - 1;
    }
    
    /* Destroy temporary Binary Heap wrapper object */
    biheap_destroy(&heap);
    return 0;
}


