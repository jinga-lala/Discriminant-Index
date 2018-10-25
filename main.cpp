//Written and developed by YASH JAIN
//IIT Bombay
#include <iostream>
#include <map>
#include<vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#define ln endl
using namespace std;

int students = 290;
int questions = 30;
int c = 78;
int starting_step = 2;
int ending_step = 29;
int randomness = 1;
int paper_type;
int help=0;
multimap< int , map< double , vector<int> > > ans;
vector < vector <float> > raw_data;
vector<int> selQ_number;
vector<float> subjQ;
void combinationUtil(int arr[], vector <int> data, int start, int end,
                     int index, int r, int iter);

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(int arr[], int n, int r, int iter)
{
    // A temporary array to store all combination one by one
    vector <int> data(r,0);

    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r , iter);
}

/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
bool compare(const pair<float, float>&i, const pair<float ,float>&j)
{
	// if(i.second == j.second){
	// 	//return i.first < j.first; //Ascending order for other cells (Excel use this)
	// }
    return i.second > j.second;
}
void combinationUtil(int arr[], vector <int> data, int start, int end,
                     int index, int r, int iter)
{
    // Current combination is ready to be printed, print it
    if (index == r )
    {

        int d = rand() % randomness;
        if (d >= randomness-1){
        double top_c = 0;
        double bottom_c = 0;
        vector < pair <float , float > >  req_sum;
        for(int i =0 ;i < students ; i++){
            req_sum.push_back( make_pair( raw_data[i][iter] , 0) ); //iter is the ques. no.
        }
        for (int i = 0; i < students; ++i)
        {
            for (int j  = 0; j < r; ++j)
            {
                req_sum[i].second += raw_data[i][data[j]];
            }
        }
        stable_sort (req_sum.begin() , req_sum.end() , compare);
        cout<<"QUESTIOn no. "<<iter<<ln;
//        for(auto i : req_sum){
//            cout<<i.second<<" ";
//        }cout<<ln;
        double DI;
        for (int i = 0; i < c; ++i)
        {
            top_c += req_sum[i].first;
            cout<<req_sum[i].first<<" ";
        }
        cout<<ln;
        for (int i = students - c ; i < students ; ++i)
        {
            bottom_c += req_sum[i].first;
            cout<<req_sum[i].first<<" ";
        }cout<<ln;
        cout<<top_c<<" "<<bottom_c<<ln;
        DI = (top_c - bottom_c)/(c*subjQ[iter]);
        const std::map< double , vector <int> > m1 ={{DI , data}};
        int q = iter;
        pair < int , map< double , vector<int> > > x;
        x.first = q;
        x.second = m1;
        ans.insert(x);
        return;
    }
        return;
    }

    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r ,iter);
    }
}

void PrintHelp(){
    cout<<ln<<ln;
	cout<< "              **********************HELP PAGE *******************              "<<ln;
	cout<< "Number of students : These are the number of students whose data is available  "<<ln;
	cout<< "                     to us in the file i.e., (number of rows -1) in the input "<<ln;
	cout<< "                     file"<<ln<<ln;
	cout<< "Number of questions: These are the number of questions on which test was based "<<ln;
	cout<< "                     on i.e., (number of columns)"<<ln<<ln;
	cout<< "c-value            : It is the number of students we consider from top and bottom"<<ln;
	cout<< "                     while calculating the Discriminant Index."<<ln;
	cout<< "                     It is usually taken as 27% of number of students."<<ln<<ln;
	cout<< "Nt                 : Sum of scores of top \"c\" students "<<ln<<ln;
	cout<< "Nb                 : Sum of scores of top \"c\" students "<<ln<<ln;
	cout<< "DI                 : Short form of Discriminant Index finding which is the goal "<<ln;
	cout<< "                     of the code."<<ln;
	cout<< "DI of question x   =  Nt - Nb /(c * (maximum marks for question x))"<<ln<<ln;
	cout<< "Including Self     : DI of question \"x\" calculated considering question \"x\" as a"<<ln;
	cout<< "                     differentiating factor along with other questions"<<ln<<ln;
	cout<< "Without Self       : DI of question \"x\" calculated WITHOUT considering question \"x\""<<ln;
	cout<< "                     as a differentiating factor along with other questions"<<ln<<ln;
 	cout<< "Step Size          : Size of the set of questions that have been used for calculating"<<ln;
 	cout<< "                     the DI value of question x"<<ln;
	cout<< "                   : Mathematically it's range is [Starting Step Size, Ending Step Size]"<<ln<<ln;
	cout<< "Starting Step      : Starting value of the \"Step Size\"."<<ln;
	cout<< "                     For \"Including Self\": Starting Step Size <= Number of questions"<<ln;
	cout<< "                     For \"Without Self\"  : Starting Step < Number of questions"<<ln<<ln;
	cout<< "Ending Step        : Ending value of the \"Step Size\"."<<ln;
	cout<< "                     For \"Including Self\": Ending Step Size <= Number of questions"<<ln;
	cout<< "                     For \"Without Self\"  : Ending Step < Number of questions"<<ln<<ln;
	cout<< "Input File Name    : All input files are by default to be of .txt format with data "<<ln;
	cout<< "                     separated by space or newline."<<ln;
	cout<< "                     The first line of Input File should be the Maximum Marks of"<<ln;
	cout<< "                      each question. "<<ln<<ln;
	cout<< "Output File Name   : Output File will be in .csv format to make it compatible with"<<ln;
    cout<< "                     Microsoft Excel and other popular softwares."<<ln<<ln;
	cout<< "Selective Q. List  : The Selective question list should be in .txt format and "<<ln;
	cout<< "                     should only contain the question numbers whose DI's has to "<<ln;
	cout<< "                     be calculated among each other."<<ln<<ln;
	cout<< "              *******************************************************************"<<ln;
}

int main (){
    //vector < vector <int> > raw_data(students);
    cout<<"Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	string h;cin>>h;
	if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    PrintHelp();
    srand (time(0));
    ofstream fout;
    ifstream fin;
    cout<<"Enter number of students : ";
    cin>>students;
    cout<<"Enter number of questions : ";
    cin>>questions;
    cout<<"Enter c-value (27% of students) : ";
    cin>>c;
    cout<<"Do you want to calculate DI including \"self\"? (y/n) : ";
    string u;
    cin>>u;
    bool yash=0;
    while(u!="y" && u!="Y" && u!= "n" && u!="N" && u!="yes" && u!="Yes" && u!="YES" && u!="no" && u!="No" && u!="NO"){
    	help++;
    	if(help > 3){
    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
    		string h;cin>>h;
    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
    			PrintHelp();
    		help=0;
    	}
        cout<<"Invalid Input (should be \"y\" or \"n\"), Enter Again : ";
        cin>>u;
    }
    if(u=="y"||u=="Y"||u=="Yes"||u=="YES"||u=="yes"){
    	yash=1;
    }else{
        cout<<"Do you want to consider only selective questions? (y/n) : ";
        cin>>u;
         while(u!="y" && u!="Y" && u!= "n" && u!="N" && u!="yes" && u!="Yes" && u!="YES" && u!="no" && u!="No" && u!="NO"){
         	help++;
	    	if(help > 3){
	    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	    		string h;cin>>h;
	    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    			PrintHelp();
	    		help=0;
	    	}
            cout<<"Invalid Input (should be \"y\" or \"n\"), Enter Again : ";
            cin>>u;
        }
        if(u=="y"||u=="Y"||u=="Yes"||u=="YES"||u=="yes"){
            cout<<"Enter the text file name in which the questions to be considered are entered : ";
            string seQ;
            cin>>seQ;
            fin.open(seQ +".txt");
            int a;
            while(fin>>a){
            	selQ_number.push_back(a-1);
            }
            fin.close();
        }
	    cout<<"Enter Starting Step Size : ";
	    cin>>starting_step;
	   	while(selQ_number.size()!=0 && starting_step>= selQ_number.size()){
	   		help++;
	    	if(help > 3){
	    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	    		string h;cin>>h;
	    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    			PrintHelp();
	    		help=0;
	    	}
	    	cout<<"Invalid input (should be less than number of selective questions), Enter Again  : ";
	        cin>>starting_step;
	    }
	    while((yash==1 && starting_step > questions) || (yash==0 && starting_step>= questions) ){
         	help++;
	    	if(help > 3){
	    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	    		string h;cin>>h;
	    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    			PrintHelp();
	    		help=0;
	    	}
	        cout<<"Invalid input (should be less than (in without self) or less than or equal to (in including self) number of questions), Enter Again  : ";
	        cin>>starting_step;
	    }
	    cout<<"Ending Step Size : ";
	    cin>>ending_step;
	    while(selQ_number.size()!=0 && ending_step>= selQ_number.size()){
         	help++;
	    	if(help > 3){
	    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	    		string h;cin>>h;
	    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    			PrintHelp();
	    		help=0;
	    	}
	    	cout<<"Invalid input (should be less than number of selective questions), Enter Again  : ";
	        cin>>ending_step;
	    }
	    while((yash==1 && ending_step > questions) || (yash==0 && ending_step>= questions) ){
         	help++;
	    	if(help > 3){
	    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	    		string h;cin>>h;
	    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    			PrintHelp();
	    		help=0;
	    	}
	        cout<<"Invalid input (should be less than number of questions), Enter Again  : ";
	        cin>>ending_step;
	    }
	    while(ending_step < starting_step){
         	help++;
	    	if(help > 3){
	    		cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
	    		string h;cin>>h;
	    		if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
	    			PrintHelp();
	    		help=0;
	    	}
	        cout<<"Invalid input (ending step should be greater than starting step), Enter Again  :";
	        cin>>ending_step;
	    }
	    cout<<"Enter Randomness scale, i.e. 1 in how many to be considered(default: 1 in 10000) : ";
	    cin>>randomness;
	}
    cout<<"Enter input file : ";
    string input_file_name;
    cin>>input_file_name;
    cout<<"Enter output file identifier : ";
    string output_file_name;
    cin>>output_file_name;
    cout<< "Sit Back and Relax, leave the hardwork to the code."<<ln;
    fin.open(input_file_name + ".txt");
    vector < vector <float> > raw_data2(students);
    for(int i=0;i<questions;++i){ //update maximum marks for each question
    	int a;
        fin>>a;
        subjQ.push_back(a);
    }
    for (int i = 0; i < students; ++i){
        raw_data2[i] = std::vector<float> (questions);
        for(int j = 0; j < questions ; ++j){
            fin>>raw_data2[i][j];
        }
    }
    raw_data = raw_data2;
    //Data initialised into the 2d vector
    //QUESTIONS are numbered from zero
    if(yash==0){
	    if(selQ_number.size()==0){
	    	//Whether selective DI needed to be calculated or not
	    	for (int i = 0; i < questions; ++i)
	    	{
	    		selQ_number.push_back(i); // if not then continue with the normal way and initialise with all the question number
	    	}
	    }
	    for (int i = 0; i < selQ_number.size(); ++i){
	        srand(rand());
	        int temp [selQ_number.size()-1];
	        for (int j = 0,k =0; j < selQ_number.size()-1 ; ++j,++k){
	            if(k == selQ_number[i] ) {
	                k++;
	            }

	            temp[j] = selQ_number[k] ;
	        }
	        for(int k = starting_step; k <= ending_step ; ++k ){
	        printCombination(temp , selQ_number.size() - 1 , k , selQ_number[i]	);
	        }
	    }
	}else{
		int allquestions[questions];
        for (int i = 0; i < questions; ++i)
        {
        	allquestions[i]=i;
        }
        for (int i = 0; i < questions; ++i)
        {
        	printCombination(allquestions, questions, questions, i);
        }
	}
    auto m = ans.begin();
    int ques = m->first + 1;
    if(yash==1){
    	fout.open(output_file_name+".csv");
    	for (auto i = ans.begin(); i != ans.end(); ++i){
    		fout<< i->first+1 <<",";
	        auto j = i->second.begin();
	        fout << std::fixed;
	        fout << std::setprecision(6);
	        fout<< j->first <<",";
	        auto k = j->second;
	        for(int f = 0 ; f< k.size() ; f++)
	         fout<< k[f]+1<<",";
	        fout<<"\n";
    	}
    	return 0;
    }else{
    	fout.open(output_file_name + "_" + to_string(ques) + ".csv");
    }
    for (auto i = ans.begin(); i != ans.end(); ++i)
    {
        if(i -> first + 1 != ques){
            ques = i->first +1;
            fout.close();
            fout.open(output_file_name + "_" + to_string(ques) + ".csv");
        }
        fout<< i->first+1 <<",";
        auto j = i->second.begin();
        fout << std::fixed;
        fout << std::setprecision(6);
        fout<< j->first <<",";
        auto k = j->second;
        for(int f = 0 ; f< k.size() ; f++)
         fout<< k[f]+1<<",";
         fout<<"\n";
    }
}
