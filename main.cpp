#include<iostream>
#include<fstream>
#include<deque>
#include<vector>
#include<queue>

typedef unsigned int lint;

using namespace std;


struct lodzins
{
    lint beigu_laiks;
    lint id;

    lodzins(){
        beigu_laiks = 0;
        id = 0;
    }
};


struct CompareStruct {
    bool operator()(const lodzins& s1, const lodzins& s2) const {
        // Compare based on data field
        if (s1.beigu_laiks != s2.beigu_laiks)
            return s1.beigu_laiks < s2.beigu_laiks; // Change ">" to "<" for ascending order
        // If data field is equal, maintain original order
        // This ensures stable sorting
        // You can use any other criteria here if necessary
        return false;
    }
};

// Define SortedQueue class
template<typename T>
class SortedQueue {
private:
    priority_queue<T, vector<T>, CompareStruct> pq; // Min-heap
public:
    // Function to add an element to the sorted queue
    void push(const T& value) {
        pq.push(value);
    }

    // Function to get the front element of the sorted queue
    T top() {
        return pq.top();
    }

    // Function to remove the front element of the sorted queue
    void pop() {
        pq.pop();
    }

    // Function to check if the sorted queue is empty
    bool empty() const {
        return pq.empty();
    }
};

template <typename T>
void print_arr(const T* array, int arr_length) {
    for (int i = 0; i < arr_length; i++) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

void print_punkti(const lodzins* array, int arr_lenght){
    for (int i = 0; i < arr_lenght; i++){
        cout << array[i].id << " " << array[i].beigu_laiks << " | ";
    }
    cout << endl;
    
}

void printDeque(const deque<lint>& dq) {
    cout << "Deque: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main(){
    ifstream inFile("customs.in");
    ofstream outFile("customs.out");

    if (!inFile.is_open()){
        cerr << "Error opening file!";
        return 1;
    }


    // Read first 4 numbers into a int[]
    lint first_data[4];

    for(int i=0; i<4;i++){
        inFile >> first_data[i];
    }

    int p_muitnieku_n = first_data[0];
    int n_muitnieku_n = first_data[1];
    int default_p_time = first_data[2];
    int default_n_time = first_data[3];

    print_arr<lint>(first_data,4);

    //Izveidosim muitniekus un ievadisim vinu laikus

    //char vaimuitnieks;
    char muitnieka_tips;
    int muitnieka_i;
    int muitnieka_laiks;
    
    // muitnieki katram ir no 0..99]
    int *p_muitnieku_laiki = new int[p_muitnieku_n];
    int *n_muitnieku_laiki = new int[n_muitnieku_n];

    lodzins *p_punkti = new lodzins[p_muitnieku_n];
    lodzins *n_punkti = new lodzins[n_muitnieku_n];

    for(int i = 0; i<p_muitnieku_n; i++){
        p_muitnieku_laiki[i] = default_p_time;
    }

    for(int i = 0; i<n_muitnieku_n; i++){
        n_muitnieku_laiki[i] = default_n_time;
    }
    // Muitnieki un vinu esosain klients
    // Pie katra muitnieka bus cilveka_id + muitnieka apkalposanas laiks
    // Ja nakama cilveka id parsniedz kadu no esosajiem laikiem, tad tas cilveks tiek izvadits faila
    // un tiek ievietots nakamais brivaja vieta.

    // Izveidojam 2 masivus kuri bus apkalposanas laiki


    char tips;
    lint cilveka_id = 0;
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

    deque<lint> p_rinda;
    deque<lint> n_rinda;

    lint p_punkti_count = 0;
    lint n_punkti_count = 0;

    deque<lodzins> output_rinda;

    if(tips != 'P' && tips != 'N'){
        outFile<<"nothing";
        return 0;
    }
    while(tips != 'X'){
        // print_punkti(p_punkti,p_muitnieku_n);
        // print_punkti(n_punkti, n_muitnieku_n);
        // printDeque(p_rinda);
        // printDeque(n_rinda);
        // cout<<endl;
        inFile >> cilveka_id;
        
        //cout << "cehcking "<< cilveka_id << endl;
        //Add to output vector elements whose time has expired.

        //print_punkti(p_punkti, p_muitnieku_n);

        for(int i = 0; i<p_muitnieku_n;i++){
            if(p_punkti[i].id>0 && p_punkti[i].beigu_laiks <= cilveka_id){
                output_rinda.push_back(p_punkti[i]);
                p_punkti_count--;
                //p_punkti[i].beigu_laiks = 0;
                p_punkti[i].id = 0;
            }
        }

        for(int i = 0; i<n_muitnieku_n;i++){
            if(n_punkti[i].id>0 && n_punkti[i].beigu_laiks <= cilveka_id){
                output_rinda.push_back(n_punkti[i]);
                n_punkti_count--;
                //n_punkti[i].beigu_laiks = 0;
                n_punkti[i].id = 0;
            }
        }

        if(tips == 'P'){
            p_rinda.push_back(cilveka_id);
            //cout<< "Adding " << cilveka_id << " to p_rinda"<<endl;
        }else{
            n_rinda.push_back(cilveka_id);
            //cout<< "Adding " << cilveka_id << " to n_rinda"<<endl;
        }

        //Check if there are free windows and if are pop from queue to the window

        // vajag beigu laiku
        // zinam cilveka_id
        // zinam ieprieksejo beigu laiku
        // zinam apstrades laiku


        for(int i = 0; i<p_muitnieku_n;i++){
            if(p_punkti[i].id == 0 && !p_rinda.empty()){
                p_punkti[i].id = p_rinda.front();

                if(p_rinda.front() < p_punkti[i].beigu_laiks){
                    p_punkti[i].beigu_laiks = p_punkti[i].beigu_laiks + p_muitnieku_laiki[i];
                }else{
                    p_punkti[i].beigu_laiks = p_rinda.front() + p_muitnieku_laiki[i];
                }
                p_punkti_count++;

                p_rinda.pop_front();
            }
        }

        for(int i = 0; i<n_muitnieku_n;i++){
            if(n_punkti[i].id == 0 && !n_rinda.empty()){
                n_punkti[i].id = n_rinda.front();
                if(n_rinda.front() < n_punkti[i].beigu_laiks){
                    n_punkti[i].beigu_laiks = n_punkti[i].beigu_laiks + n_muitnieku_laiki[i];
                }else{
                    n_punkti[i].beigu_laiks = n_rinda.front() + n_muitnieku_laiki[i];
                }
                n_punkti_count++;

                n_rinda.pop_front();
            }
        }
        
        // for (int i = 0; i < output_rinda.size(); ++i) {
        //     std::cout << output_rinda[i].id << " " << output_rinda[i].beigu_laiks <<endl;
        // }

        // while (!output_rinda.empty()){
        //     output_rinda.pop_back();
        // }

        if(output_rinda.size() > 100050){
            outFile << output_rinda.front().id << " " << output_rinda.front().beigu_laiks <<endl;
        }
        

        inFile >> tips;
    }

    // We still need to finish processing remaining windows and emptying the queues.

    while(p_punkti_count > 0 || n_punkti_count > 0){
        // print_punkti(p_punkti,p_muitnieku_n);
        // print_punkti(n_punkti, n_muitnieku_n);
        // printDeque(p_rinda);
        // printDeque(n_rinda);
        //printf("Secondary loop");
        
        // Atrodam min laiku no punktiem un uztaisam to cilveka id
        // Pectam kad pievienojam vinu punktam, pieskaitam vina beigu
        // laikam minlaiks - cilveka id 

        lint minlaiks = 0;
        for(int i = 0; i < p_muitnieku_n; i++){
            if(p_punkti[i].beigu_laiks >0 && p_punkti[i].id >0){
                if(minlaiks == 0){
                    minlaiks = p_punkti[i].beigu_laiks;
                    //cout<<"setting default"<<endl;
                }else if(p_punkti[i].beigu_laiks <= minlaiks){
                    minlaiks = p_punkti[i].beigu_laiks;
                }
            }
        }

        for(int i = 0; i < n_muitnieku_n; i++){
            if(n_punkti[i].beigu_laiks >0 && n_punkti[i].id > 0){
                if(minlaiks == 0){
                    minlaiks = n_punkti[i].beigu_laiks;
                }else if(n_punkti[i].beigu_laiks <= minlaiks){
                    minlaiks = n_punkti[i].beigu_laiks;
                }
            }
        }

        //cout<<minlaiks<<endl;

        for(int i = 0; i<p_muitnieku_n;i++){
            if(p_punkti[i].id>0 && p_punkti[i].beigu_laiks <= minlaiks){
                output_rinda.push_back(p_punkti[i]);
                p_punkti_count--;
                p_punkti[i].beigu_laiks = 0;
                p_punkti[i].id = 0;
            }
        }

        for(int i = 0; i<n_muitnieku_n;i++){
            if(n_punkti[i].id>0 && n_punkti[i].beigu_laiks <= minlaiks){
                output_rinda.push_back(n_punkti[i]);
                n_punkti_count--;
                n_punkti[i].beigu_laiks = 0;
                n_punkti[i].id = 0;
            }
        }

        for(int i = 0; i<p_muitnieku_n;i++){
            if(p_punkti[i].id == 0 && !p_rinda.empty()){
                p_punkti[i].id = p_rinda.front();
                p_punkti[i].beigu_laiks = minlaiks + p_muitnieku_laiki[i] ;
                p_punkti_count++;

                p_rinda.pop_front();
            }
        }

        for(int i = 0; i<n_muitnieku_n;i++){
            if(n_punkti[i].id == 0 && !n_rinda.empty()){
                n_punkti[i].id = n_rinda.front();
                n_punkti[i].beigu_laiks = minlaiks + n_muitnieku_laiki[i];
                n_punkti_count++;

                n_rinda.pop_front();
            }
        }



        // while (!output_rinda.empty()){
        //     output_rinda.pop_back();
        // }

        if(output_rinda.size() > 100050){
            outFile << output_rinda.front().id << " " << output_rinda.front().beigu_laiks <<endl;
            output_rinda.pop_front();
        }
    }

    while (!output_rinda.empty()){
        outFile << output_rinda.front().id << " " << output_rinda.front().beigu_laiks <<endl;
        output_rinda.pop_front();
    }
    

    return 0;
}