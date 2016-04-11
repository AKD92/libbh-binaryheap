

/************************************************************************************
    Program Interface of Binary Heap Data Structure & Associated Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef BINARY_HEAP_DATA_STRUCTURE_H
#define BINARY_HEAP_DATA_STRUCTURE_H







struct BinaryHeap_ {
    
    void *pArrayElem;                          /* Underlying memory blocks for the storage of elements  */
    
    unsigned int elemCount;                    /* Number of elements the heap is currently holding      */
    unsigned int elemWidth;                    /* The size of each element, in Bytes                    */
    
    int (*fpCompare)                           /* User specifed function for comparing array elements   */
            (const void *arg1, const void *arg2);

    void *pSwapMemory;                         /* Temporary memory used for faster swapping of elements */
                                               /* Size of this pSwapMemory must be equal to elemWidth   */
    
};
typedef struct BinaryHeap_ BinHeap;






/*************************************************************************/
/*************************                      **************************/
/*************************  PUBLIC INTERFACES   **************************/
/*************************                      **************************/
/*************************************************************************/




int binheap_init(BinHeap *heap, void *pArray, unsigned int nCount,
            unsigned int nWidth, int (*fpCompare) (const void *arg1, const void *arg2));

void binheap_destroy(BinHeap *heap);




#define binheap_size(heap)                   ((heap)->elemCount)

#define binheap_width(heap)                  ((heap)->elemWidth)

#define binheap_array(heap)                  ((heap)->pArrayElem)



#define binheap_parentIndex(uChild)          (((uChild) - 1) / 2)       /* Wikipedia - Binary Heap   */

#define binheap_leftChildIndex(uParent)      (((uParent) * 2) + 1)

#define binheap_rightChildIndex(uParent)     (((uParent) * 2) + 2)




int binheap_sinkLightElement(BinHeap *heap, unsigned int index);        /* Algorithm for MAX HEAP */

int binheap_swimHeavyElement(BinHeap *heap, unsigned int index);        /* Algorithm for MAX HEAP */


int binheap_sinkHeavyElement(BinHeap *heap, unsigned int index);        /* Algorithm for MIN HEAP */

int binheap_swimLightElement(BinHeap *heap, unsigned int index);        /* Algorithm for MIN HEAP */




int binheap_buildBinaryMaxHeap(BinHeap *heap);                          /* Algorithm for MAX HEAP */

int binheap_buildBinaryMinHeap(BinHeap *heap);                          /* Algorithm for MIN HEAP */




int binheap_sort(void *pArray, unsigned int nCount, unsigned int nWidth,
                            int (*fpCompare) (const void *agr1, const void *arg2));

int binheap_sortAscending(void *pArray, unsigned int nCount, unsigned int nWidth,
                                     int (*fpCompare) (const void *agr1, const void *arg2));
                            
int binheap_sortDescending(void *pArray, unsigned int nCount, unsigned int nWidth,
                                      int (*fpCompare) (const void *agr1, const void *arg2));



int binheap_swapElements(unsigned int index1, unsigned int index2, BinHeap *heap);






#endif


