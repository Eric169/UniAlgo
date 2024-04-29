#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Scambia arr[i] e arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Scambia arr[i + 1] e arr[high] (posiziona il pivot al posto corretto)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    for(int k = 0; k<7; k++) printf("%d ", arr[k]);
    printf("%c", '\n');
    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        // Trova l'indice del pivot dopo il partizionamento
        int partitionIndex = partition(arr, low, high);

        // Se l'indice del pivot è esattamente k-1, abbiamo trovato l'elemento alla k-esima posizione
        if (partitionIndex - low == k - 1) {
            return arr[partitionIndex];
        }

        // Se l'indice del pivot è maggiore di k-1, cerca nella parte sinistra
        if (partitionIndex - low > k - 1) {
            return quickSelect(arr, low, partitionIndex - 1, k);
        }

        // Altrimenti, cerca nella parte destra
        return quickSelect(arr, partitionIndex + 1, high, k - partitionIndex + low - 1);
    }

    // Restituisci un valore fuori intervallo se k è maggiore della dimensione dell'intervallo
    return -1;
}

int nthElement(int arr[], int size, int n) {
    if (n > 0 && n <= size) {
        return quickSelect(arr, 0, size - 1, n);
    }
    // Restituisci un valore fuori intervallo se n è maggiore della dimensione dell'array
    return -1;
}

int main() {
    int arr[] = {12, 3, 7, 5, 4, 6, 26};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 3;

    int result = nthElement(arr, size, n);

    if (result != -1) {
        printf("L'elemento alla %d-esima posizione è %d\n", n, result);
    } else {
        printf("Valore di n fuori intervallo\n");
    }
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("%c", '\n');
    return 0;
}
