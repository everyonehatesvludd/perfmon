#include <pdh.h>
#include <stdio.h>
#include "counters.h"

static PDH_HQUERY hQuery;
static PDH_HCOUNTER *counters = NULL;
static int counterCount = 0;

int pdh_init() {
    if (PdhOpenQuery(NULL, 0, &hQuery) != ERROR_SUCCESS) {
        printf("PdhOpenQuery failed\n");
        return -1;
    }
    return 0;
}

int add_counter(const char *counterPath){
    if (!hQuery) {
        printf("Query not initialized\n");
        return -1;
    }

    counters = realloc(counters, (counterCount + 1) * sizeof(PDH_HCOUNTER));
    if (!counters)
    {
        printf("Memory allocation failed\n");
        return -1;
    }

    if (PdhAddCounter(hQuery, counterPath, 0, &counters[counterCount]) != ERROR_SUCCESS) {
        printf("PdhAddCounter failed\n");
        return -1;
    }
    
    counterCount++;

    return 0;
}

int collect_data(){
    if (PdhCollectQueryData(hQuery) != ERROR_SUCCESS) {
        printf("PdhCollectQueryData failed\n");
        return -1;
    }

    Sleep(1000);

    if (PdhCollectQueryData(hQuery) != ERROR_SUCCESS) {
        printf("PdhCollectQueryData failed\n");
        return -1;
    }

    return 0;
}

int get_counter_data(int index, PDH_FMT_COUNTERVALUE *counterValue){
    if (index < 0 || index >= counterCount)
    {
        printf("Invalid index\n");
        return -1;
    }
    
    if(PdhGetFormattedCounterValue(counters[index], PDH_FMT_LONG, NULL, counterValue) != ERROR_SUCCESS){
        printf("PdhGetFormattedCounterValue failed\n");
        return -1;
    }


    // TODO

    return 0;
}

