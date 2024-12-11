/******************
Name:Ori Bahat-Petel
ID:331753830
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
int day = 0;

void printMenu()
{
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
//update one car brand
void UpdateOne(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int name, int sale1, int sale2, int sale3, int sale4)
{
    cube[day][name][0] = sale1;
    cube[day][name][1] = sale2;
    cube[day][name][2] = sale3;
    cube[day][name][3] = sale4;
}
//print missing car brands
void printMissing(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    printf("No data for brands");
    int hasMissing = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (cube[day][i][0] == -1) {
            printf(" %s", brands[i]);
            hasMissing = 1;
        }
    }
    if (hasMissing)
        printf("\nPlease complete the data.\n");
    else
        printf("\nAll brands have data for today.\n");
}
//check if a brand hasnt been inputed yet
int isBrandValid(int type, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    if (type < 0 || type >= NUM_OF_BRANDS || cube[day][type][0] != -1) {
        return 0;
    }
    return 1;
}

void printAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int total;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Sales for %s:\n", brands[i]);
        for (int j = 0; j < day; j++) {
            total = 0;
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                total += cube[j][i][k];
            }
            if (total == 0) {
                printf("Day %d: No sales\n", j);
            } else {
                printf("Day %d: %d sales\n", j, total);
            }
        }

        printf("*****************************************\n");
    }
}

void printDaily(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int userDate)
{
    int c1[NUM_OF_BRANDS] = {0};
    int c2[NUM_OF_TYPES] = {0};
    printf("In day number %d:\n", userDate);
    int sum = 0, Mb = 0, Mt = 0, MbIndex = 0, MtIndex = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            sum += cube[userDate][i][j];
            c1[i] += cube[userDate][i][j];
        }
        if (Mb < c1[i]) {
            Mb = c1[i];
            MbIndex = i;
        }
    }
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            c2[i] += cube[userDate][j][i];
        }
        if (Mt < c2[i]) {
            Mt = c2[i];
            MtIndex = i;
        }
    }
    printf("The sales total was %d\n", sum);
    printf("The best sold brand with %d sales was %s\n", Mb, brands[MbIndex]);
    printf("The best sold type with %d sales was %s\n", Mt, types[MtIndex]);
}

void printOverall(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int Mb = 0, Md = 0, Mt = 0, MbIndex = 0, MtIndex = 0, MdIndex = 0;
    int c1[DAYS_IN_YEAR] = {0};
    int c2[NUM_OF_BRANDS] = {0};
    int c3[NUM_OF_TYPES] = {0};
    for (int i = 0; i < day; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int m = 0; m < NUM_OF_TYPES; m++) {
                c1[i] += cube[i][j][m];
            }
        }
        if (Md < c1[i]) {
            Md = c1[i];
            MdIndex = i;
        }
    }
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < day; j++) {
            for (int m = 0; m < NUM_OF_TYPES; m++) {
                c2[i] += cube[j][i][m];
            }
        }
        if (Mb < c2[i]) {
            Mb = c2[i];
            MbIndex = i;
        }
    }
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int m = 0; m < day; m++) {
                c3[i] += cube[m][j][i];
            }
        }
        if (Mt < c3[i]) {
            Mt = c3[i];
            MtIndex = i;
        }
    }
    printf("The best-selling brand overall is %s with %d sales\n", brands[MbIndex], Mb);
    printf("The best-selling type of car is %s with %d sales\n", types[MtIndex], Mt);
    printf("The most profitable day was day number %d with %d sales\n", MdIndex, Md);
}

void printAvgDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    int c1[NUM_OF_BRANDS] = {0};
    int sum1, sum2;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < day - 1; j++) {
            sum1 = cube[j][i][0] + cube[j][i][1] + cube[j][i][2] + cube[j][i][3];
            sum2 = cube[j + 1][i][0] + cube[j + 1][i][1] + cube[j + 1][i][2] + cube[j + 1][i][3];
            c1[i] += sum2 - sum1;
        }
        printf("Brand: %s , Average Delta: %d\n", brands[i], c1[i]);
    }
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int type, S1, S2, S3, S4, counter, userDay;

    // start cube all -1 values
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int m = 0; m < NUM_OF_TYPES; m++) {
                cube[i][j][m] = -1;
            }
        }
    }

    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
            case addOne:
                do {
                    scanf("%d %d %d %d %d", &type, &S1, &S2, &S3, &S4);
                    if (type < 0 || type >= NUM_OF_BRANDS) {
                        printf("This brand is not valid\n");
                    } else {
                        UpdateOne(cube, type, S1, S2, S3, S4);
                        day++;
                    }
                } while (type < 0 || type >= NUM_OF_BRANDS);
                break;

            case addAll:
                counter = 0;
                while (counter < NUM_OF_BRANDS) {
                    printMissing(cube);
                    do{
                        scanf("%d %d %d %d %d", &type, &S1, &S2, &S3, &S4);
                        if (!isBrandValid(type, cube)) {
                            printf("This brand is not valid\n");
                        }
                    }while(!isBrandValid(type, cube));
                    UpdateOne(cube, type, S1, S2, S3, S4);
                    counter++;
                }
                day++;
                break;
            case stats:
                do {
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &userDay);
                    if (userDay < 0 || userDay >= DAYS_IN_YEAR || userDay >= day)
                        printf("Please enter a valid day.\n");
                } while (userDay < 0 || userDay >= DAYS_IN_YEAR || userDay >= day);
                printDaily(cube, userDay);
                break;
            case print:
                printAllData(cube);
                break;
            case insights:
                printOverall(cube);
                break;
            case deltas:
                printAvgDelta(cube);
                break;
            case done:
                break;    
            default:
                printf("Invalid input\n");
        }
    }while (choice != done);
    printf("Goodbye!\n");
    return 0;
}
