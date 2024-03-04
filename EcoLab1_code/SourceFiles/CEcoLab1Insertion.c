#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1Insertion.h"


// Функция QueryInterface для интерфейса IEcoLab1
int16_t ECOCALLMETHOD CEcoLab1Insertion_QueryInterface(/* in */ struct IEcoLab1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1Insertion* pCMe = (CEcoLab1Insertion*)me;
    if (me == 0 || ppv == 0) {
        return -1;
    }
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

// Функция AddRef для интерфейса IEcoLab1
uint32_t ECOCALLMETHOD CEcoLab1Insertion_AddRef(/* in */ struct IEcoLab1* me) {
    CEcoLab1Insertion* pCMe = (CEcoLab1Insertion*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

// Функция Release для интерфейса IEcoLab1
uint32_t ECOCALLMETHOD CEcoLab1Insertion_Release(/* in */ struct IEcoLab1* me) {
    CEcoLab1Insertion* pCMe = (CEcoLab1Insertion*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1Insertion((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

void copy_bytes(char *src, char *dst, size_t count) {
    char *end = src + count;
    while (src < end) {
        *(dst++) = *(src++);
    }
}

void insertion_sort(
    char *start_ptr,
    size_t elem_count,
    size_t elem_size,
    char *key,
    int (__cdecl *comp)(const void *, const void*)
) {
    size_t i;
    char *current;

    for (i = 1; i < elem_count; i++) {
        copy_bytes(start_ptr + (i * elem_size), key, elem_size  );
        current = start_ptr + ((i - 1) * elem_size);

        /* Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
        while (current >= start_ptr && comp(current, key) == 1) {
            copy_bytes(current, current + elem_size, elem_size);
            current -= elem_size;
        }

        copy_bytes(key, current + elem_size, elem_size);
    }
}

/* Реализация функции qsort */
int16_t ECOCALLMETHOD CEcoLab1Insertion_qsort(
        struct IEcoLab1* me,
        void* pData,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *comp)(const void *, const void*)
) {
    CEcoLab1Insertion *pCMe = (CEcoLab1Insertion*) me;
    int16_t index;
    char* temp = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, elem_size);

    /* Проверка указателей */
    if (me == 0 || pData == 0) {
        return -1;
    }

    /* Запуск сортировки */
    insertion_sort(pData, elem_count, elem_size, temp, comp);

    /* Освобождение памяти */
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, temp);
    return 0;
}


// Виртуальная таблица методов для IEcoLab1
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
        CEcoLab1Insertion_QueryInterface,
        CEcoLab1Insertion_AddRef,
        CEcoLab1Insertion_Release,
        CEcoLab1Insertion_qsort
};


// Функция инициализации экземпляра
int16_t ECOCALLMETHOD initCEcoLab1Insertion(/*in*/ struct IEcoLab1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1Insertion* pCMe = (CEcoLab1Insertion*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

//  Функция создания экземпляра
int16_t ECOCALLMETHOD createCEcoLab1Insertion(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1Insertion* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1Insertion*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Insertion));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

//  Функция освобождения экземпляра
void ECOCALLMETHOD deleteCEcoLab1Insertion(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1Insertion* pCMe = (CEcoLab1Insertion*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}