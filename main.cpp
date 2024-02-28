#include<iostream>
#include<fstream>

using namespace std;

template <typename T>
void print_arr(const T* array, int arr_length) {
    for (int i = 0; i < arr_length; i++) {
        cout << array[i] << ' ';
    }
    cout << endl;
}


int main(){
    ifstream inFile("customs.in");

    if (!inFile.is_open()){
        cerr << "Error opening file!";
        return 1;
    }


    // Read first 4 numbers into a int[]
    int first_data[4];

    for(int i=0; i<4;i++){
        inFile >> first_data[i];
    }

    int p_muitnieku_n = first_data[0];
    int n_mutnieku_n = first_data[1];
    int default_p_time = first_data[2];
    int default_n_time = first_data[3];

    print_arr<int>(first_data,4);


    return 0;
}