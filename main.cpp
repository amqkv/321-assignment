#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;
using std::cout, std::endl;
using std::ofstream;
using std::reverse;

void printToCSV(const int table[][16], string name){
    cout << name << endl;
    cout << "diff y   ";
    for(int i = 0; i < 16; i++){
        cout << i;
        if(i < 10){
            cout << "  ";
        } else{
            cout << " ";
        }
    }
    cout << "\ndiff x -------------------------------------------------" << endl;

    for(int i = 0; i < 16; i++){
        cout << i;
        if(i < 10){
            cout << "    |   ";
        } else{
            cout << "   |   ";
        }
        for(int j = 0; j < 16; j++){
            cout << table[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void generateDDT(const int sbox[], int table[][16], string name ){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            table[i][j] = 0;
        }
    }

    int difference_x;
    int difference_y;
    for(int i = 0; i < 16; i++){
        for(int j = i+1; j < 16; j++){
            difference_x = i ^ j;
            difference_y = sbox[i]^sbox[j];
            table[difference_x][difference_y] += 2;
        }
    }
    table[0][0] = 16;
    printToCSV(table, name);
};

void permutation(int number){
    int permTable[32] = { 16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25 };
    vector<int> permutatedNumber;
    int digit = 0;
    // Adding number's digits to array
    while(number != 0){
        digit = number%10;
        number /= 10;
        permutatedNumber.push_back(digit);
    }
    std::reverse(permutatedNumber.begin(), permutatedNumber.end());
    for(int i = 0; i < permutatedNumber.size(); i++){
        cout << permutatedNumber.at(i);
    }


}

int main(){
    int sbox[8][16] = {
            /* 1 */
            { 6, 12, 3, 8, 14, 5, 11, 1, 2, 4, 13, 7, 0, 10, 15, 9},
            /* 2 */
            { 10, 14, 15, 11, 6, 8, 3, 13, 7, 9, 2, 12, 1, 0, 4, 5},
            /* 3 */
            { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
            /* 4 */
            { 15, 9, 7, 0, 10, 13, 2, 4, 3, 6, 12, 5, 1, 8, 14, 11},
            /* 5 */
            { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
            /* 6 */
            { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
            /* 7 */
            { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
            /* 8 */
            { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7}
    };

    int s1_ddt[16][16];
    int s2_ddt[16][16];
    int s3_ddt[16][16];
    int s4_ddt[16][16];
    int s5_ddt[16][16];
    int s6_ddt[16][16];
    int s7_ddt[16][16];
    int s8_ddt[16][16];

    generateDDT(sbox[0], s1_ddt,"================= DDT for S-box 1 ===================");
    generateDDT(sbox[1], s2_ddt,"================= DDT for S-box 2 ===================");
    generateDDT(sbox[2], s3_ddt,"================= DDT for S-box 3 ===================");
    generateDDT(sbox[3], s4_ddt,"================= DDT for S-box 4 ===================");
    generateDDT(sbox[4], s5_ddt,"================= DDT for S-box 5 ===================");
    generateDDT(sbox[5], s6_ddt,"================= DDT for S-box 6 ===================");
    generateDDT(sbox[6], s7_ddt,"================= DDT for S-box 7 ===================");
    generateDDT(sbox[7], s8_ddt,"================= DDT for S-box 8 ===================");

}


