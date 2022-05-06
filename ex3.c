/// Se da un fisier ce contine N numere intregi. Fie doua procese:
/// unu proces determina valoarea minima, iar al doilea determina
/// valoarea maxima dintr-un sir de numere. Sa se scrie un program
/// care determina cel de-al k-lea element (daca sirul ar fi
/// sortat crescator) dintr-un sir de numere intregi. N si k vor
/// fi furnizate de catre utilizator. Programul va folosi un numar
/// adecvat de procese pentru rezolvarea cerintei. In rezolvarea
/// problemei, NU se va folosi sortarea in prealabil a sirului.

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>

int find_minimum(const int* numbers, const int N) {
    int i = 0, index = 0, min = INT_MAX;
    for (i = 0; i < N; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
            index = i;
        }
    }

    return index;
}

int find_maximum(const int* numbers, const int N) {
    int i = 0, index = 0, max = INT_MIN;
    for (i = 0; i < N; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
            index = i;
        }    
    }

    return index;
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    int k = atoi(argv[2]);
    int minimum_index = 0, maximum_index = 0, l = 0, p = 0, status;

    // Allocating memory
    int* numbers = (int *) malloc(N * sizeof(int));

    if (numbers == NULL) {
        perror("malloc failed: ");
        exit(EXIT_FAILURE);
    }

    // Read numbers from file
    FILE* input_file = fopen("file.txt", "r");

    if (input_file == NULL) {
        perror("file opening failed: ");
        exit(EXIT_FAILURE);
    }

    for (l = 0; l < N; l++) {
        fscanf(input_file, "%d", &numbers[l]);
    }

    fclose(input_file);

    // Getting minimum / maximum from array
    int max_pid = fork();

    if (max_pid == -1) {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    } else if (max_pid == 0) {
        maximum_index = find_maximum(numbers, N);
        printf("[MAX] %d\n", numbers[maximum_index]);
        exit(maximum_index);
    }

    wait(&status);
    maximum_index = WEXITSTATUS(status);

    for (p = 0; p < k; p++) {
        int min_pid = fork();

        if (min_pid == -1) {
            perror("fork() error: ");
            exit(EXIT_FAILURE);
        } else if (min_pid == 0) {
            minimum_index = find_minimum(numbers, N);
            printf("[MIN] %d\n", numbers[minimum_index]);
            exit(minimum_index);
        }

        wait(&status);
        minimum_index = WEXITSTATUS(status);

        if (p == k - 1) {
            printf("Al %d-lea nr este: %d\n", k, numbers[minimum_index]);
        }

        numbers[minimum_index] = numbers[maximum_index];
    }
    
    // cleanup
    printf("\n");
    free(numbers);
    return 0;
}
