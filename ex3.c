/// Se da un fisier ce contine N numere intregi. Fie doua procese:
/// unu proces determina valoarea minima, iar al doilea determina
/// valoarea maxima dintr-un sir de numere. Sa se scrie un program
/// care determina cel de-al k-lea element (daca sirul ar fi
/// sortat crescator) dintr-un sir de numere intregi. N si k vor
/// fi furnizate de catre utilizator. Programul va folosi un numar
/// adecvat de procese pentru rezolvarea cerintei. In rezolvarea
/// problemei, NU se va folosi sortarea in prealabil a sirului.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>

int find_minimum(int* numbers, int N) {
    int min = INT_MAX;
    for (int i = 0; i < N; i++) {
        if (numbers[i] < min) min = numbers[i];    
    }

    return min;
}

int main(int argc, char* argv[]) {
    int N = argv[1];
    int k = argv[2];

    int* numbers = (int *) malloc(N * sizeof(int));
    int minimum = 0, maximum = 0, status;

    // File handling
    FILE* input_file = fopen("file.txt", 'r');

    for (int l = 0; l < N; l++) {
        fscanf(input_file, "%d", &numbers[l])
    }

    fclose(input_file);

    // processes handling
    int pid = fork();
    switch (pid)
    {
        case -1:
            perror("fork() error: ");
            exit(EXIT_FAILURE);

        case 0:
            minimum = find_minimum(numbers, N));            
            exit(EXIT_SUCCESS);

        default:
            wait(&status);
            printf("[PARENT] %d\n", minimum);
    }

    // cleanup
    free(numbers);
    return 0;
}
