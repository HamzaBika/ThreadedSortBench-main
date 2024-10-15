#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// Function declarations
int* generateRandomArray(int size);
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
void insertionSort(int arr[], int n);
void BubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void* mergeSortThread(void* args);
void* heapSortThread(void* args);
void* quickSortThread(void* args);
void* insertionSortThread(void* args);
void* BubblesortThread(void* args);
void* selectionSortThread(void* args);

// Struct to hold arguments for threading.
struct SortArgs {
    int* arr;
    int size;
};

clock_t start, end, total_start, total_end;
double cpu_time_used;

int main() {
    
    total_start = clock();

    int pas,choix; // Step size 
    FILE *file = fopen("execution_times.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    // Titre 
    printf("******* \t\t\tSort Alorithms Complexity\t\t\t *******\n");
    printf("1 . Quick\n");
    printf("2 . Merge\n");
    printf("3 . Heap\n");
    printf("4 . Insertion\n");
    printf("5 . Bubble\n");
    printf("6 . Selection\n");
    printf("7 . All Aboove\n");
    do{
    printf("Choose Sort Algorithm :");
    scanf("%d",&choix);
    }while(choix>7 || choix<1);
    
    printf("Enter the step size: ");
    scanf("%d", &pas);

    // Loop through sizes with step 'pas'
    for (int n = pas; n <= 100000; n += pas) {

        
        int* arr = generateRandomArray(n);   

        
       // ***********************************************************************
       printf("********** \t\t\t Taille : %d case (%d octets) \t\t\t*************\n",n,n*4);
       switch (choix){
            case 7 :
            case 1 :
            int* arrQuick = (int*)malloc(n * sizeof(int));
            pthread_t thread1;
            memcpy(arrQuick, arr, n * sizeof(int)); 
            struct SortArgs argsQuick = {arrQuick, n};
            // QuickSort
            start = clock();
            pthread_create(&thread1, NULL, quickSortThread, &argsQuick);
            pthread_join(thread1, NULL);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            if(choix == 1 )
            fprintf(file, "%d %f \n", n, cpu_time_used);
            else fprintf(file, "%d %f ", n, cpu_time_used);
            printf("Quick Sort : %f\n",cpu_time_used);
            
            free(arrQuick);
            if (choix == 1 ) break;


            case 2 :
            int* arrMerge = (int*)malloc(n * sizeof(int));
            pthread_t thread2;
            memcpy(arrMerge, arr, n * sizeof(int));
            struct SortArgs argsMerge = {arrMerge, n};
            // MergeSort
            start = clock();
            pthread_create(&thread2, NULL, mergeSortThread, &argsMerge);
            pthread_join(thread2, NULL);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            if (choix == 7)
            printf("Merge Sort : %f\n",cpu_time_used);
            if (choix == 2 ) fprintf(file, "%d %f \n",n,cpu_time_used);
            else fprintf(file, "%f ", cpu_time_used);
            free(arrMerge);
            if (choix == 2 ) break;

            case 3 :
            int* arrHeap = (int*)malloc(n * sizeof(int));
            pthread_t thread3;
            memcpy(arrHeap, arr, n * sizeof(int));
            struct SortArgs argsHeap = {arrHeap, n};
            // HeapSort
            start = clock();
            pthread_create(&thread3, NULL, heapSortThread, &argsHeap);
            pthread_join(thread3, NULL);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Heap Sort : %f\n",cpu_time_used);
            if (choix == 3 ) fprintf(file, "%d %f \n",n,cpu_time_used);
            else fprintf(file, "%f ", cpu_time_used);
            free(arrHeap);
            if (choix == 3 ) break;


            case 4 :
            int* arrInsert = (int*)malloc(n * sizeof(int));
            pthread_t thread4;
            memcpy(arrInsert, arr, n * sizeof(int));
            struct SortArgs argsInsert = {arrInsert, n};
            // InsertionSort
            start = clock();
            pthread_create(&thread4, NULL, insertionSortThread, &argsInsert);
            pthread_join(thread4, NULL);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Insertion Sort : %f\n",cpu_time_used);
            if (choix == 4 ) fprintf(file, "%d %f \n",n,cpu_time_used);
            else fprintf(file, "%f ", cpu_time_used);
            free(arrInsert);
            if (choix == 4 ) break;


            case 5:
            int* arrBubble = (int*)malloc(n * sizeof(int));
            pthread_t thread5;
            memcpy(arrBubble, arr, n * sizeof(int));
            struct SortArgs argsBubble = {arrBubble, n};
            // BubbleSort
            start = clock();
            pthread_create(&thread5, NULL, BubblesortThread, &argsBubble);
            pthread_join(thread5, NULL);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Bubble Sort : %f\n",cpu_time_used);
            if (choix == 5) fprintf(file, "%d %f \n",n,cpu_time_used);
            else fprintf(file, "%f ", cpu_time_used);
            free(arrBubble);
            if (choix == 5 ) break;

            case 6:
            int* arrSelection = (int*)malloc(n * sizeof(int));
            pthread_t thread6;
            memcpy(arrSelection, arr, n * sizeof(int));
            struct SortArgs argsSelection = {arrSelection, n};
            // SelectionSort
            start = clock();
            pthread_create(&thread6, NULL, selectionSortThread, &argsSelection);
            pthread_join(thread6, NULL);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Selection Sort : %f\n",cpu_time_used);
            if (choix == 6) fprintf(file, "%d %f \n",n,cpu_time_used);
            else fprintf(file, "%f \n", cpu_time_used);
            
            
            free(arrSelection);
            break;
        }
        // Free allocated arrays
        free(arr);
        
        
        
        
        
        
    }

    fclose(file);

    // Call GNUplot with the updated data and smoother graph configuration
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Error opening GNUplot.\n");
        return 1;
    }

    // GNUplot Commands
    fprintf(gnuplotPipe, "set title 'Sorting Algorithms Execution Time'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
    fprintf(gnuplotPipe, "set ylabel 'Execution Time (seconds)'\n");
    fprintf(gnuplotPipe, "set grid\n");

    // Smoother logarithmic graph for better visibility
    fprintf(gnuplotPipe, "set logscale xy\n");
    fprintf(gnuplotPipe, "set style data linespoints\n");
    switch(choix){
        case 1:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'QuickSort' with lines, \n");
        break;

        case 2:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'MergeSort' with lines, \n");
        break;

        case 3:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'HeapSort' with lines, \n");
        break;

        case 4:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'InsertionSort' with lines, \n");
        break;

        case 5:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'BubbleSort' with lines, \n");
        break;

        case 6:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'SelectionSort' with lines, \n");
        break;

        case 7:
        fprintf(gnuplotPipe, "plot 'execution_times.txt' using 1:2 title 'QuickSort' with lines, \\\n");
    fprintf(gnuplotPipe, "     '' using 1:3 title 'MergeSort' with lines, \\\n");
    fprintf(gnuplotPipe, "     '' using 1:4 title 'HeapSort' with lines, \\\n");
    fprintf(gnuplotPipe, "     '' using 1:5 title 'InsertionSort' with lines, \\\n");
    fprintf(gnuplotPipe, "     '' using 1:6 title 'BubbleSort' with lines, \\\n");
    fprintf(gnuplotPipe, "     '' using 1:7 title 'SelectionSort' with lines\n");
        break;

        


    }
    

    pclose(gnuplotPipe);

    total_end = clock();
    double total_time_used = ((double)(total_end - total_start)) / CLOCKS_PER_SEC;
    printf("Total execution time: %f seconds\n", total_time_used);

    return 0;
}







int* generateRandomArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le tableau.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; 
    }
    return arr;
}


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les tableaux temporaires.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}


void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void BubbleSort(int arr[],int size){
    for(int i=size-1;i>0;i--){
        for (int j=0;j<i;j++){
            if (arr[j]>arr[j+1]) swap(&arr[j],&arr[j+1]);
        }
    }
}

void selectionSort(int arr[],int n){
    for(int i=0 ; i<n-1 ; i++){
        int min = i;
        for (int j=i ; j<n ; j++){
            if (arr[j+1] < arr[j]) min = j;
        }
        swap(&arr[i], &arr[min]);
    }
}

void* quickSortThread(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    quickSort(args->arr, 0, args->size - 1);
    pthread_exit(NULL);
}

void* mergeSortThread(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    mergeSort(args->arr, 0, args->size - 1);
    pthread_exit(NULL);
}

void* heapSortThread(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    heapSort(args->arr, args->size);
    pthread_exit(NULL);
}

void* insertionSortThread(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    insertionSort(args->arr, args->size);
    pthread_exit(NULL);
}

void* BubblesortThread(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    BubbleSort(args->arr, args->size);
    pthread_exit(NULL);
}

void* selectionSortThread(void* arg) {
    struct SortArgs* args = (struct SortArgs*)arg;
    selectionSort(args->arr, args->size);
    pthread_exit(NULL);
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
