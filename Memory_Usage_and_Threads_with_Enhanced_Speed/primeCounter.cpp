#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

#define BATCH_SIZE 1000

pthread_mutex_t count_mutex;
int total_counter = 0;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void *checkPrimesThread(void *arg)
{
    int nums[BATCH_SIZE];
    int local_counter = 0;

    while (true)
    {
        int count = 0;
        pthread_mutex_lock(&count_mutex);
        while (count < BATCH_SIZE && scanf("%d", &nums[count]) != EOF)
        {
            count++;
        }
        pthread_mutex_unlock(&count_mutex);

        if (count == 0)
            break;

        for (int i = 0; i < count; i++)
        {
            if (isPrime(nums[i]))
            {
                local_counter++;
            }
        }
    }

    pthread_mutex_lock(&count_mutex);
    total_counter += local_counter;
    pthread_mutex_unlock(&count_mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0)
    {
        printf("Number of threads must be positive .\n");
        return 1;
    }

    pthread_mutex_init(&count_mutex, NULL);

    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, checkPrimesThread, NULL);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&count_mutex);

    printf("%d total primes.\n", total_counter);

    return 0;
}
