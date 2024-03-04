/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1Gnome.h"
#include "IdEcoLab1Insertion.h"
#include <stdio.h>

int __cdecl compInts(const void *pa, const void *pb) {
    const int a = *(int *) pa;
    const int b = *(int *) pb;

    if (a > b) {
        return 1;
    } else if (a == b) {
        return 0;
    } else {
        return -1;
    }
}

int __cdecl compDoubles(const void *pa, const void *pb) {
    double a = *(double *) pa;
    double b = *(double *) pb;

    if (a > b) {
        return 1;
    } else if (a == b) {
        return 0;
    } else {
        return -1;
    }
}

int __cdecl compFloats(const void *pa, const void *pb) {
    float a = *(float *) pa;
    float b = *(float *) pb;

    if (a > b) {
        return 1;
    } else if (a == b) {
        return 0;
    } else {
        return -1;
    }
}

int __cdecl compChars(const void *pa, const void *pb) {
    char a = *(char *) pa;
    char b = *(char *) pb;

    if (a > b) {
        return 1;
    } else if (a == b) {
        return 0;
    } else {
        return -1;
    }
}

void *createIntArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));

    for (i = 1; i < size; i++) {
        arr[i] = (rand() % 10000) - 5000;
    }

    return arr;
}

void *createFloatArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    float *arr = (float *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(float));

    for (i = 0; i < size; i++) {
        arr[i] = ((float) (rand() %10000 - 5000)) / ((float) (rand() % 1000 + 1));
    }

    return arr;
}

void *createDoubleArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    double *arr = (double *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(double));

    for (i = 0; i < size; i++) {
        arr[i] = ((double) (rand() %10000 - 5000)) / ((double) (rand() % 1000 + 1));
    }

    return arr;
}

void *createCharArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    char *arr = (char *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(char));

    for (i = 1; i < size; i++) {
        arr[i] = rand() % 26 + 'a';
    }

    return arr;
}

void printIntArray(void *arr, size_t size) {
    int i;
    int *array = (int *) arr;

    for (i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printFloatArray(void *arr, size_t size) {
    int i;
    float *array = (float *) arr;

    for (i = 0; i < size; ++i) {
        printf("%f ", array[i]);
    }
    printf("\n");
}

void printDoubleArray(void *arr, size_t size) {
    int i;
    double *array = (double *) arr;

    for (i = 0; i < size; ++i) {
        printf("%lf ", array[i]);
    }
    printf("\n");
}

void printCharArray(void *arr, size_t size) {
    int i;
    char *array = (char *) arr;

    for (i = 0; i < size; ++i) {
        printf("%c ", array[i]);
    }
    printf("\n");
}

void run_tests(
    IEcoMemoryAllocator1 *pIMem,
    IEcoLab1 *pIEcoLab1Gnome,
    IEcoLab1 *pIEcoLab1Insertion,
    size_t elem_size,
    int (__cdecl *comp)(const void *, const void*),
    void *createArray(IEcoMemoryAllocator1 *, size_t),
    void printArray(void *, size_t),
    char *type,
    FILE *output_file
) {
    size_t size;
    void *data_v1;
    void *data_v2;
    void *data_v3;
    clock_t start, end;
    double sort_time;

    srand(time(0));

    fprintf(output_file, "%s\n", type);
    fprintf(output_file, "sort,size,time\n");

    /* Тестирование сортировок проходит на размерах от 2^10 до 2^16 включительно с увеличением в два раза */
    /* Тестирование Gnome Sort */
    for (size = 1024; size <= 65536; size *= 2) {
        data_v1 = createArray(pIMem, size);

        start = clock();
        pIEcoLab1Gnome->pVTbl->qsort(pIEcoLab1Gnome, data_v1, size, elem_size, comp);
        end = clock();
        sort_time = (double) (end - start) / CLOCKS_PER_SEC;
        printf("%6d GnomeSort time:     %lf\n", size, sort_time);
        fprintf(output_file, "%s,%d,%lf\n", "GnomeSort", size, sort_time);

        pIMem->pVTbl->Free(pIMem, data_v1);
    }

    printf("\n");
    fprintf(output_file, "\n");

    /* Тестирование Insertion Sort */
    for (size = 1024; size <= 65536; size *= 2) {
        data_v2 = createArray(pIMem, size);

        start = clock();
        pIEcoLab1Insertion->pVTbl->qsort(pIEcoLab1Insertion, data_v2, size, elem_size, comp);
        end = clock();
        sort_time = (double) (end - start) / CLOCKS_PER_SEC;
        printf("%6d InsertionSort time: %lf\n", size, sort_time);
        fprintf(output_file, "%s,%d,%lf\n", "InsertionSort", size, sort_time);

        pIMem->pVTbl->Free(pIMem, data_v2);
    }

    printf("\n");
    fprintf(output_file, "\n");

    /* Тестирование библиотечной qsort */
    for (size = 1024; size <= 65536; size *= 2) {
        data_v3 = createArray(pIMem, size);

        start = clock();
        qsort(data_v3, size, elem_size, comp);
        end = clock();
        sort_time = (double) (end - start) / CLOCKS_PER_SEC;
        printf("%6d std qsort time:     %lf\n", size, sort_time);
        fprintf(output_file, "%s,%d,%lf\n", "std qsort", size, sort_time);

        pIMem->pVTbl->Free(pIMem, data_v3);
    }

    printf("\n");
    fprintf(output_file, "\n");
}

// Функция EcoMain - точка входа
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1Gnome = 0;
    IEcoLab1* pIEcoLab1Insertion = 0;
    FILE *output_file;

    /* Проверка и создание системного интерфейса */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
    if (result != 0 && pISys == 0) {
        goto Release;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1Gnome, 0, &IID_IEcoLab1, (void**) &pIEcoLab1Gnome);
    if (result != 0 || pIEcoLab1Gnome == 0) {
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1Insertion, 0, &IID_IEcoLab1, (void**) &pIEcoLab1Insertion);
    if (result != 0 || pIEcoLab1Insertion == 0) {
        goto Release;
    }

    fopen_s(&output_file, "output.txt", "w");

    printf("Run test for int arrays\n");
    run_tests(pIMem, pIEcoLab1Gnome, pIEcoLab1Insertion, sizeof(int), compInts, createIntArray, printIntArray, "int", output_file);

    printf("Run test for float arrays\n");
    run_tests(pIMem, pIEcoLab1Gnome, pIEcoLab1Insertion, sizeof(float), compFloats, createFloatArray, printFloatArray, "float", output_file);

    printf("Run test for double arrays\n");
    run_tests(pIMem, pIEcoLab1Gnome, pIEcoLab1Insertion, sizeof(double), compDoubles, createDoubleArray, printDoubleArray, "double", output_file);

    printf("Run test for char arrays\n");
    run_tests(pIMem, pIEcoLab1Gnome, pIEcoLab1Insertion, sizeof(char), compChars, createCharArray, printCharArray, "char", output_file);

    fclose(output_file);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1Gnome != 0) {
        pIEcoLab1Gnome->pVTbl->Release(pIEcoLab1Gnome);
    }

    if (pIEcoLab1Insertion != 0) {
        pIEcoLab1Insertion->pVTbl->Release(pIEcoLab1Insertion);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

