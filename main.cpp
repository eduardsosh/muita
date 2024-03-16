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
    int n_muitnieku_n = first_data[1];
    int default_p_time = first_data[2];
    int default_n_time = first_data[3];

    print_arr<int>(first_data,4);

    //Izveidosim muitniekus un ievadisim vinu laikus

    //char vaimuitnieks;
    char muitnieka_tips;
    int muitnieka_i;
    int muitnieka_laiks;
    
    int *p_muitnieku_laiki = new int[p_muitnieku_n];
    int *n_muitnieku_laiki = new int[n_muitnieku_n];

    int *p_punkti = new int[p_muitnieku_n];
    int *n_punkti = new int[n_muitnieku_n];

    for(int i = 0; i<p_muitnieku_n; i++){
        p_muitnieku_laiki[i] = default_p_time;
        p_punkti[i] = 0;
    }

    for(int i = 0; i<n_muitnieku_n; i++){
        n_muitnieku_laiki[i] = default_n_time;
        n_punkti[i] = 0;
    }
    // Muitnieki un vinu esosain klients
    // Pie katra muitnieka bus cilveka_id + muitnieka apkalposanas laiks
    // Ja nakama cilveka id parsniedz kadu no esosajiem laikiem, tad tas cilveks tiek izvadits faila
    // un tiek ievietots nakamais brivaja vieta.

    // Izveidojam 2 masivus kuri bus apkalposanas laiki


    char tips;
    int cilveka_id = 0;
    inFile >> tips;

    if(tips == 'T'){
        while(tips == 'T'){
            inFile >> muitnieka_tips >> muitnieka_i >> muitnieka_laiks;
            if(muitnieka_tips == 'P'){
                p_muitnieku_laiki[muitnieka_i - 1] = muitnieka_laiks;
            }
            if(muitnieka_tips == 'N'){
                n_muitnieku_laiki[muitnieka_i - 1] = muitnieka_laiks;
            }
            inFile >> tips;
        }
    }
    
    int min_laiks = 0;
    while(tips != 'X'){
        inFile >> cilveka_id;
        // tgd mums ir tips un cilveka id
        // sakas pats algoritms.
        
        // Ejam cauri tipa punktam un parbaudam vai nav kadam jau brivs

        if (tips == 'P'){
            for(int i=0;i<p_muitnieku_n;i++){
                if(cilveka_id > p_punkti[i]){
                    cout << p_punkti[i] - p_muitnieku_laiki[i] <<' ' <<p_punkti[i] << endl;
                    p_punkti[i] = cilveka_id + p_muitnieku_laiki[i];
                }
            }
        }


        inFile >> tips;
    }


    return 0;
}