#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include<math.h>
#include <bitset>
using std::string, std::to_string;
using std::vector;
using std::cout, std::endl;
using std::ofstream;
using std::reverse;
using std::bitset;
using std::ifstream, std::getline;
using std::stringstream, std::hex, std::stol, std::dec, std::uppercase;

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

void printTable(const vector<vector<int>> &table){
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
            cout << table.at(i).at(j) << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void generateDDT(const int sbox[], vector<vector<int>> &table ){

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            table.at(i).push_back(0);
        }
    }

    int difference_x;
    int difference_y;
    for(int i = 0; i < 16; i++){
        for(int j = i+1; j < 16; j++){
            difference_x = i ^ j;
            difference_y = sbox[i]^sbox[j];
            table.at(difference_x).at(difference_y) += 2;
        }
    }
    table.at(0).at(0) = 16;
};

bitset<32> permute(string str_number){
    bitset<32> number = bitset<32>(str_number);
    str_number = number.to_string();
    int permTable[32] = { 16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25 };

    string permutedNumber = "";
    for(int i = 0; i < 32; i++){
        permutedNumber += str_number[permTable[i] - 1];
    }

    return bitset<32>(permutedNumber);
}

vector<vector<int>> findHighProbabilityPairs(vector<vector<vector<int>>> &ddtArray){
    vector<vector<int>> highProbabilityPairs = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

    for(int sboxNumber = 0; sboxNumber < 8; sboxNumber++){
        for(int i = 0; i < 16; i++){
            for(int j = 0; j < 16; j++){
                if(ddtArray.at(sboxNumber).at(i).at(j) == 16 && j != 0 && i != 0){
                    // Pushing sbox number and the pair with probability 16/16
                    highProbabilityPairs.at(sboxNumber).at(0) = i;
                    highProbabilityPairs.at(sboxNumber).at(1) = j;
                }
            }
        }
    }
    return highProbabilityPairs;
}

bitset<32> getDiffFromTable(const vector<vector<int>> &highProbabilityPairs, string type){
    string number = "";
    for(int i = 0; i < highProbabilityPairs.size(); i++){
        number += bitset<4>(highProbabilityPairs.at(i).at(type == "input" ? 0 : 1)).to_string();
    }
    return bitset<32>(number);
}

vector<vector<string>> getPlaintextCiphertextPairs(){
    ifstream f;
    f.open("../plaintext_ciphertext_pairs.txt");
    string line;
    vector<vector<string>> plaintext_ciphertext_pairs;
    int pairNumber = 0;
    string input;
    string output;
    if(f.is_open()){
        while(getline(f, line)){
            if(line[0] == '#'){
                pairNumber++;
                continue;
            } else {
                input = line.substr(0, 16);
                output = line.substr(17, line.size());
            }
            plaintext_ciphertext_pairs.push_back({to_string(pairNumber), input, output});
        }
    }
    f.close();
    return plaintext_ciphertext_pairs;
}

string binToHex(string input){
    stringstream ss;
    bitset<32> input_bin(input);
    ss << hex << uppercase << input_bin.to_ulong();
    return ss.str();
}

uint64_t binToDec(string input){
    cout << input << endl;
    uint32_t binary = static_cast<uint64_t>(stoul(input));
    uint32_t decimal = 0;
    int power = 1;
    uint64_t temp = binary;
    int last_digit = 0;
    while(temp){
        last_digit = temp % 10;
        decimal += last_digit*power;
        power = 2*power;
    }
    return decimal;
}

string hexToDec(char input){
    int dec_output;
    stringstream ss;
        ss << input;
        ss >> hex >> dec_output;
    return to_string(dec_output);
}

string hexToDec(string input){
    unsigned int input_dec = 0;
    int power = 1;
    int s = input.size();
    for(int i=s-1 ; i>=0 ; i--){
        if(input[i] >= '0' && input[i] <= '9'){
            input_dec += power*(input[i] - '0');
        } else if(input[i] >= 'A' && input[i] <= 'F'){
            input_dec += power*(input[i] - 'A' + 10);
        }
        power *= 16;
    }
    return to_string(input_dec);
}

string decToHex(string input){
    stringstream ss;
    ss << hex << static_cast<uint32_t>(stoul(input));
    return ss.str();
}

string hexToBin(string input){
    string binary = "";
    for(int i = 0; i < input.size(); i++){
        binary += bitset<4>(stoi(hexToDec(input[i]))).to_string();
    }
    return binary;
}

string getBoxOutput(string input){
    string dec_input;
    string sbox_output_hex = "";

    // getting sbox outputs
    for(int i = 0; i < input.size(); i++){
        dec_input = hexToDec(input[i]); // converting to dec
        sbox_output_hex += decToHex(to_string(sbox[i][stoi(dec_input)])); // getting output & converting back to hex
    }

    // converting [hex] sbox output to binary
    string sbox_output_binary;
    for(int i = 0; i < sbox_output_hex.size(); i++){
        sbox_output_binary += bitset<4>(stoi(hexToDec(sbox_output_hex[i]))).to_string();
    }

    return permute(sbox_output_binary).to_string();
}

string xorBinary(string input1, string input2){
    string res = "";
    for(int i = 0; i < 16; i++){
        if(input1[i] == input2[i]){
            res += "0";
        } else {
            res += "1";
        }
    }
    return res;
}

int main(){
    vector<vector<int>> s1_ddt(16);
    vector<vector<int>> s2_ddt(16);
    vector<vector<int>> s3_ddt(16);
    vector<vector<int>> s4_ddt(16);
    vector<vector<int>> s5_ddt(16);
    vector<vector<int>> s6_ddt(16);
    vector<vector<int>> s7_ddt(16);
    vector<vector<int>> s8_ddt(16);
    vector<vector<vector<int>>> ddtArray = { s1_ddt, s2_ddt, s3_ddt, s4_ddt, s5_ddt, s6_ddt, s7_ddt, s8_ddt };

    for(int i = 0; i < ddtArray.size(); i++){
        generateDDT(sbox[i], ddtArray[i]);
//        cout << "================= DDT for S-box " << i << "===================" << endl;
//        printTable(ddtArray[i]);
    }


    // Round 2
    vector<vector<int>> highProbabilityPairs = findHighProbabilityPairs(ddtArray);
    bitset<32> diff_input = getDiffFromTable(highProbabilityPairs, "input");
    string delta_z = permute(getDiffFromTable(highProbabilityPairs, "output").to_string()).to_string();
    cout << "delta z | " << delta_z << endl;

    vector<vector<string>> plaintext_ciphertext_pairs = getPlaintextCiphertextPairs();

    string cl_diff = xorBinary(hexToBin(plaintext_ciphertext_pairs[0][2].substr(0,8)), hexToBin(plaintext_ciphertext_pairs[1][2].substr(0,8)));

    int k4 = 0;
    uint32_t cr1, cr2, fbox_input_cr1, fbox_input_cr2;
    string fbox_output_cr1, fbox_output_cr2, fbox_output_diff;
    for(int32_t i = 0; i < INT32_MAX; i++){
        k4 = i;
        cr1 = static_cast<uint32_t>(stoul(hexToDec(plaintext_ciphertext_pairs[0][2].substr(8, 16))));
        cr2 = static_cast<uint32_t>(stoul(hexToDec(plaintext_ciphertext_pairs[1][2].substr(8, 16))));

        fbox_input_cr1 = cr1 ^ k4;
        fbox_input_cr2 = cr2 ^ k4;
        fbox_output_cr1 = getBoxOutput(decToHex(to_string(fbox_input_cr1)));
        fbox_output_cr2 = decToHex(to_string(fbox_input_cr2));
        fbox_output_diff = xorBinary(fbox_output_cr1, fbox_output_cr2);

        if(i%1000 == 0){
            cout << k4 << " ";
        }
        if(xorBinary(fbox_output_diff, delta_z) == cl_diff){
            cout << "found a candidate key" << endl;
            break;
        }
    }
    cout << "delta z | " << delta_z << endl;
    cout << "fbox_output | " << fbox_output_diff << endl;

    cout << "k4 | " << k4 << endl;

}
