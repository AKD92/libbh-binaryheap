

/************************************************************************************
    Program Interface of Binary Heap Data Structure & Binary Heap Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BINARY_HEAP_DATA_STRUCTURE_H
#define BINARY_HEAP_DATA_STRUCTURE_H







/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************    DATA STRUCTURES    ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/




struct BinaryHeap_ {
    
    void *pArrayElem;                          /* Underlying memory blocks for the storage of elements  */
    
    unsigned int elemCount;                    /* Number of elements the heap is currently holding      */
    unsigned int elemWidth;                    /* The size of each element, in Bytes                    */
    
    int (*fpCompare)                           /* User specifed function for comparing array elements   */
            (const void *arg1, const void *arg2);
    
    void *pSwapMemory;                         /* Temporary memory used for faster swapping of elements */
                                               /* Size of this pSwapMemory must be equal to elemWidth   */
    
};
typedef struct BinaryHeap_ BiHeap;






/**********************************************************************************************/
/***********************************                       ************************************/
/***********************************   PUBLIC INTERFACES   ************************************/
/***********************************                       ************************************/
/**********************************************************************************************/




int biheap_init(BiHeap *heap, void *pArray, unsigned int nCount,
            unsigned int nWidth, int (*fpCompare) (const void *arg1, const void *arg2));

void biheap_destroy(BiHeap *heap);



#define biheap_array(heap)                  ((heap)->pArrayElem)

#define biheap_size(heap)                   ((heap)->elemCount)

#define biheap_width(heap)                  ((heap)->elemWidth)


#define biheap_parentIndex(uChild)          (((uChild) - 1) / 2)       /* Wikipedia - Binary Heap */

#define biheap_leftChildIndex(uParent)      (((uParent) * 2) + 1)

#define biheap_rightChildIndex(uParent)     (((uParent) * 2) + 2)




int biheap_sinkLightElement(BiHeap *heap, unsigned int index);        /* Algorithm for MAX HEAP */

int biheap_swimHeavyElement(BiHeap *heap, unsigned int index);        /* Algorithm for MAX HEAP */


int biheap_sinkHeavyElement(BiHeap *heap, unsigned int index);        /* Algorithm for MIN HEAP */

int biheap_swimLightElement(BiHeap *heap, unsigned int index);        /* Algorithm for MIN HEAP */



int biheap_buildBinaryMaxHeap(BiHeap *heap);                          /* Algorithm for MAX HEAP */

int biheap_buildBinaryMinHeap(BiHeap *heap);                          /* Algorithm for MIN HEAP */



int biheap_sort(void *pArray, unsigned int nCount, unsigned int nWidth,
                            int (*fpCompare) (const void *agr1, const void *arg2));

int biheap_sortAscending(void *pArray, unsigned int nCount, unsigned int nWidth,
                                     int (*fpCompare) (const void *agr1, const void *arg2));
                            
int biheap_sortDescending(void *pArray, unsigned int nCount, unsigned int nWidth,
                                      int (*fpCompare) (const void *agr1, const void *arg2));



int biheap_swapElements(unsigned int index1, unsigned int index2, BiHeap *heap);






#endif


