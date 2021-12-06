#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

void PrintMapElevations(const double terrain[][10], const unsigned rows, const unsigned columns);
void PrintMapFeatures(const double terrain[][10], const unsigned rows, const unsigned columns);

int main() {
    double elevationVal[20][10] = {0.0}; //terrain elevation values
    const unsigned int rows = sizeof(elevationVal)/sizeof(elevationVal[0]);         //num of rows in array
    const unsigned int columns = sizeof(elevationVal[0])/sizeof(elevationVal[0][0]);   //num of columns in array

    FILE *fp;
    fp = fopen("C:\\Users\\Leslie I\\Documents\\Visual Studio Code Workspace\\C C++\\terrainmap\\terraindata002.rfd", "rb");

    if (fp == NULL) {
        printf("Error: File failed to open.");
        return -1;
    }

    unsigned int count = fread(elevationVal, sizeof(double), (rows*columns), fp);
 
    if(count != rows*columns) {
        printf("Error: Incorrect number of elements read from file.");
        fclose(fp);
        return -1;
    }

    PrintMapElevations(elevationVal, rows, columns);
    PrintMapFeatures(elevationVal, rows, columns);

} //End of main function

void PrintMapElevations(const double terrain[][10], const unsigned rows, const unsigned columns)
{
    //This function prints out the contents of the terrain data array
    printf("Map Elevations (%i x %i):\n", rows, columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            printf("%7.1f\t", terrain[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintMapFeatures(const double terrain[][10], const unsigned rows, const unsigned columns)
{
    //This function analyzes the terrain array and displays information indicating areas of peaks, valleys and plains
    //The following strings are used to identify terrain features:      EDGE - "???????"
    //                                                                  PEAK - "^^^^^^^"
    //                                                                  VALLEY - "vvvvvvv"
    //                                                                  PLAIN - "_______"
    //                                                                  UNKNOWN - "......."
    //
    printf("Map Features (%i x %i):\n", rows, columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if((i == 0) || (i == rows - 1) || (j == 0) || (j == columns - 1)) {
                printf("???????\t");
            }
            else {
                int peakCount = 0;
                int valleyCount = 0;
                int plainCount = 0;

                for(int k = i - 1; k <= i + 1; k++) {
                    for(int l = j - 1; l <= j + 1; l++) {
                        
                        if ((terrain[i][j] == fmax(terrain[k][l], terrain[i][j]))) {
                            peakCount++;
                        }
                        if ((terrain[i][j] == fmin(terrain[k][l], terrain[i][j]))) {
                            valleyCount++;
                        }
                        if (abs(terrain[i][j] - terrain[k][l]) <= 4.5) {
                            plainCount++;
                        }
                    }
                }
                peakCount -= 1;
                valleyCount -= 1;
                plainCount -= 1;

                if((peakCount > 5) && (peakCount <= 8)) {
                    printf("^^^^^^^\t");
                }
                else if((valleyCount > 5) && (valleyCount <= 8)) {
                    printf("vvvvvvv\t");
                }
                else if(plainCount > 5) {
                    printf("_______\t");
                }
                else {
                    printf(".......\t");
                }
            }
        }
        printf("\n");
    }
    printf("\n");

}