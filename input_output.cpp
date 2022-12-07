#include <iostream>
#include <vector>
using std::vector;
using std::cout, std::endl;

void printTable(const int table[][16]){
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

void generateDDT(const vector<int> sbox_output, int table[][16] ){
    for(int i = 0; i < sbox_output.size(); i++){
        for(int j = 0; j < sbox_output.size(); j++){
            table[i][j] = 0;
        }
    }

    int difference_x;
    int difference_y;
    for(int i = 0; i < sbox_output.size(); i++){
        for(int j = i+1; j < sbox_output.size(); j++){
            difference_x = i ^ j;
            difference_y = sbox_output.at(i)^sbox_output.at(j);
            table[difference_x][difference_y] += 2;
        }
    }
    table[0][0] = 16;
};

int main(){
    vector<int> s1_output = { 6, 12, 3, 8, 14, 5, 11, 1, 2, 4, 13, 7, 0, 10, 15, 9 };
    vector<int> s2_output = { 10, 14, 15, 11, 6, 8, 3, 13, 7, 9, 2, 12, 1, 0, 4, 5 };
    vector<int> s3_output = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 };
    vector<int> s4_output = { 15, 9, 7, 0, 10, 13, 2, 4, 3, 6, 12, 5, 1, 8, 14, 11 };
    vector<int> s5_output = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 };
    vector<int> s6_output = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 };
    vector<int> s7_output = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 };
    vector<int> s8_output = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 };

    int s1_ddt[16][16];
    int s2_ddt[16][16];
    int s3_ddt[16][16];
    int s4_ddt[16][16];
    int s5_ddt[16][16];
    int s6_ddt[16][16];
    int s7_ddt[16][16];
    int s8_ddt[16][16];
    // populating the table with 0
    generateDDT(s1_output, s1_ddt);
    generateDDT(s2_output, s2_ddt);
    generateDDT(s3_output, s3_ddt);
    generateDDT(s4_output, s4_ddt);
    generateDDT(s5_output, s5_ddt);
    generateDDT(s6_output, s6_ddt);
    generateDDT(s7_output, s7_ddt);
    generateDDT(s8_output, s8_ddt);

    cout << "================= DDT for S-box 1 ===================" << endl;
    printTable(s1_ddt);
    cout << "================= DDT for S-box 2 ===================" << endl;
    printTable(s2_ddt);
    cout << "================= DDT for S-box 3 ===================" << endl;
    printTable(s3_ddt);
    cout << "================= DDT for S-box 4 ===================" << endl;
    printTable(s4_ddt);
    cout << "================= DDT for S-box 5 ===================" << endl;
    printTable(s5_ddt);
    cout << "================= DDT for S-box 6 ===================" << endl;
    printTable(s6_ddt);
    cout << "================= DDT for S-box 7 ===================" << endl;
    printTable(s7_ddt);
    cout << "================= DDT for S-box 8 ===================" << endl;
    printTable(s8_ddt);

}


