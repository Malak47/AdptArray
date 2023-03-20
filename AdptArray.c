//
// Created by malak on 3/17/23.
//

#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    PElement *pElem;
    int size;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray pAdp = (PAdptArray) malloc(sizeof(AdptArray));
    if (pAdp) {
        pAdp->pElem = NULL;
        pAdp->size = 0;
        pAdp->copyFunc = copyFunc;
        pAdp->delFunc = delFunc;
        pAdp->printFunc = printFunc;
        return pAdp;
    }
    return NULL;

}

void DeleteAdptArray(PAdptArray pAdp) {
    int i = 0;
    while (i < pAdp->size) {
        if (pAdp->pElem[i]) {
            pAdp->delFunc(pAdp->pElem[i]);
        }
        i++;
    }
    free(pAdp->pElem);
    free(pAdp);
}

Result SetAdptArrayAt(PAdptArray pAdp, int index, PElement newpElem) {
    if (!pAdp || index < 0 || !newpElem) {
        return FAIL;
    }


    if (index >= pAdp->size) {
        PElement newPElem = (PElement *) calloc(index + 1, sizeof(PElement));
        if (!newPElem) {
            return FAIL;
        }
        memcpy(newPElem, pAdp->pElem, pAdp->size * sizeof(newpElem));
        free(pAdp->pElem);
        pAdp->pElem = newPElem;
    }
    //CHECK
    if (pAdp->pElem[index]) {
        pAdp->delFunc(pAdp->pElem[index]);
    }

    pAdp->pElem[index] = pAdp->copyFunc(newpElem);
    if (pAdp->size <= index) {
        pAdp->size = index + 1;
    }
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAdp, int index) {
    if (!pAdp || index < 0 || pAdp->size < index) {
        return NULL;
    }
    if (pAdp->pElem[index]) {
        return pAdp->copyFunc(pAdp->pElem[index]);
    }
    return NULL;
}

int GetAdptArraySize(PAdptArray pAdp) {
    if (!pAdp || pAdp->size < 0) {
        return -1;
    }
    return pAdp->size;
}

void PrintDB(PAdptArray pAdp) {
    int i = 0;
    while (i < pAdp->size) {
        if (pAdp->pElem[i]) {
            pAdp->printFunc(pAdp->pElem[i]);
        }
        i++;
    }
}