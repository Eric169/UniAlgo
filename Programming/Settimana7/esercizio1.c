#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

struct customer {
    char loanId[37];
    char customerId[37];
    bool loanStatus; // 1 Fully Paid, 0 Charged Off --> label che definisce la classe di appartenza
    int currentLoanAmount;
    bool term;// 1 Short Term, 0 Long Term
    int creditScore;
};

long double calcDist(struct customer *sample, struct customer *test){
    //euclidean distance = abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y) + (...) = dist^2
    long double weights[3] = {0.0001 * 0.0001, 100 * 100, 1};//squared because inserted in euclidean formula

    return (long double)abs(sample->currentLoanAmount - test->currentLoanAmount) * (long double)abs(sample->currentLoanAmount - test->currentLoanAmount) * weights[0] +
    (long double)abs(sample->term - test->term + 1) * (long double)abs(sample->term - test->term + 1) * weights[1] +
    (long double)abs(sample->creditScore - test->creditScore) * (long double)abs(sample->creditScore - test->creditScore) * weights[2];
}

struct customer *currentTest;
int cmp(const void* a, const void* b){//a è prima di b se la distanza dal custome corrente è minore di quella di b
    long double distA = calcDist(*((struct customer **)a), currentTest);
    long double distB = calcDist(*((struct customer **)b), currentTest);
    return distA - distB;
}

int partition(struct customer **arr, int low, int high) {
    struct customer* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (cmp(&arr[j], &pivot) <= 0) {
            i++;
            // Scambia arr[i] e arr[j]
            struct customer* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high] (put pivot in the right place)
    struct customer *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSelect(struct customer **arr, int low, int high, int k) {
    // Find pivot after partitioning
    int partitionIndex = partition(arr, low, high);
    // If the index is exactly k-1 we can return
    if (partitionIndex - low == k - 1) {
        return;
    }
    // If it's greater, look on the left side
    if (partitionIndex - low > k - 1) {
        return quickSelect(arr, low, partitionIndex - 1, k);
    }
    // Otherwise, look on the right side
    return quickSelect(arr, partitionIndex + 1, high, k - partitionIndex + low - 1);
}

void nthElement(struct customer **arr, int size, int n) {
    return quickSelect(arr, 0, size - 1, n);
}

bool predictLoanStatus(struct customer *training_samples, int samplesLen, struct customer *test, int K){
    struct customer *bestFound[samplesLen];
    currentTest = test;
    for(int i = 0; i < samplesLen; i++){
        bestFound[i] = &(training_samples[i]);
    }
    //I don't need to sort the array, I just need that the first K elements are the smallest
    nthElement(bestFound, samplesLen, K);
    //qsort(bestFound, samplesLen, sizeof(struct customer *), cmp);
    //count labels
    int countGoodCustomer = 0;
    for(int i = 0; i < K; i++){
        if(bestFound[i]->loanStatus){
            countGoodCustomer++;
        }
    }
    if(countGoodCustomer > K - countGoodCustomer){
        return true;//will refund the loan
    }else{
        return false; //wont refund the loan
    }
}

int main(){
    FILE *fp = fopen("credit.csv", "r");
    if (fp == NULL)
    {
        printf("Can not open file");
        exit(0);
    }
    const float percTrainingSet = 75.0;
    const int MAX_SAMPLES = 10000;
    char line[512]; char *s;
    fgets(line, 512, fp);//waste first line with columns name
    int samplesLen = percTrainingSet * MAX_SAMPLES / 100;
    int testLen = MAX_SAMPLES - samplesLen;
    struct customer training_samples[samplesLen];
    struct customer test_samples[testLen];
    int idx = 0;
    while(fgets(line, 512, fp) != NULL){
        struct customer *cust;
        if(idx < samplesLen){
            cust = &(training_samples[idx]);
        }else{
            cust = &(test_samples[idx - samplesLen]);
        }

        s = strtok(line, ",");
        strncpy(cust->loanId, s, 36); //loanId

        s = strtok(NULL, ","); //customerId
        strncpy(cust->customerId, s, 36);

        s = strtok(NULL, ","); //loanStatus
        if(strcmp(s, "Fully Paid") == 0){
            cust->loanStatus = 1;
        }else if(strcmp(s, "Charged Off") == 0){
            cust->loanStatus = 0;
        }else{
            printf("found unexpected value in loan status: %s", s);
        }

        s = strtok(NULL, ","); //currentLoanAmount
        cust->currentLoanAmount = atoi(s);

        s = strtok(NULL, ","); //term
        if(strcmp(s, "Short Term") == 0){
            cust->term = 1;
        }else if(strcmp(s, "Long Term") == 0){
            cust->term = 0;
        }else{
            printf("found unexpected value in term: %s\n", s);
        }

        s = strtok(NULL, ","); //creditScore
        cust->creditScore = atoi(s);
        
        idx++;
        if(idx >= MAX_SAMPLES){
            break;
        }
    }

    //test data
    printf("Each run takes about 5sec...\n");
    for(int k = 15; k <= 27; k += 2){
        clock_t start = clock();
        printf("K = %d\n", k);
        int rightGuess = 0;
        for(int i = 0; i < testLen; i++){
            bool predict = predictLoanStatus(training_samples, samplesLen, &test_samples[i], k);
            if(predict == test_samples[i].loanStatus){
                rightGuess++;
            }
        }
        printf("It took %ld.%ld seconds\n", (clock()-start)/CLOCKS_PER_SEC, ((clock()-start) * 1000 / CLOCKS_PER_SEC) % 1000);
        printf("Number of correct guesses: %d/%d\nPercentage of of correct guesses: %.2f%%\n", rightGuess, testLen, rightGuess * 100.0 / (float)testLen);
        if(k==27) continue;
        printf("Press any key to run with bigger K...\n");
        getchar();
    }

    return 0;
}