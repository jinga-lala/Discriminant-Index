//Written and developed by YASH JAIN
//IIT Bombay
#include<bits/stdc++.h>
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
#include<cmath>
#define ln endl
using namespace std;

long long students = 290;
long long questions = 30;
long long c = 78;
long long starting_step = 2;
long long ending_step = 29;
long long randomness = 1;
long long paper_type;
long long help=0;
multimap< long long , map< double , vector<long long> > > ans;
vector < vector <float> > raw_data;
vector<long long> selQ_number;
vector<float> subjQ;
void combinationUtil(long long arr[], vector <long long> data, long long start, long long end,
                     long long index, long long r, long long iter);

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(long long arr[], long long n, long long r, long long iter)
{
    // A temporary array to store all combination one by one
    vector <long long> data(r,0);

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
void combinationUtil(long long arr[], vector <long long> data, long long start, long long end,
                     long long index, long long r, long long iter)
{
    // Current combination is ready to be printed, print it
    if (index == r )
    {

        long long d = rand() % randomness;
        if (d >= randomness-1){
        double top_c = 0;
        double bottom_c = 0;
        vector < pair <float , float > >  req_sum;
        for(long long i =0 ;i < students ; i++){
            req_sum.push_back( make_pair( raw_data[i][iter] , 0) ); //iter is the ques. no.
        }
        for (long long i = 0; i < students; ++i)
        {
            for (long long j  = 0; j < r; ++j)
            {
                req_sum[i].second += raw_data[i][data[j]];
            }
        }
        stable_sort (req_sum.begin() , req_sum.end() , compare);
       // cout<<"QUESTIOn no. "<<iter<<ln;
//        for(auto i : req_sum){
//            cout<<i.second<<" ";
//        }cout<<ln;
        double DI;
        for (long long i = 0; i < c; ++i)
        {
            top_c += req_sum[i].first;
            //cout<<req_sum[i].first<<" ";
        }
        //cout<<ln;
        for (long long i = students - c ; i < students ; ++i)
        {
            bottom_c += req_sum[i].first;
            //cout<<req_sum[i].first<<" ";
        }//cout<<ln;
       // cout<<top_c<<" "<<bottom_c<<ln;
        DI = (top_c - bottom_c)/(c*subjQ[iter]);
        const std::map< double , vector <long long> > m1 ={{DI , data}};
        long long q = iter;
        pair < long long , map< double , vector<long long> > > x;
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
    for (long long i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r ,iter);
    }
}



string generateBitString(long long qset[], long long n, long long size){//flag=1 means including question
	vector<char> v;
	for (long long i = 0; i < size; ++i)
	{
		v.push_back('1');
	}
	for (long long i = 0; i < n -size; ++i)
	{
		v.push_back('0');
	}
	sort(qset, qset+n);
	srand(rand());
	string ans="";
	long long a=0;
	for (long long i = 0,j=0; i < questions ; ++i)
	{
		if(j<n && i==qset[j] && v.size()>0){ //probabilistically   may be this make q30 less probable!!
			/*a = rand()%2;
			if(a=='1') size--;
			ans += to_string(a);
			j++;*/
			long long a = rand()%v.size();
			ans += v[a];
			v.erase(v.begin()+a);
            ++j;
		}else{
			ans +='0'; continue;
		}
		/*if(i==iter && flag== 0){
			ans +='0'; continue;
		}else if (i==iter && flag ==1){
			ans +='1'; continue;	
		}*/
		
	}
	return ans;
}

void generateDIusingBitString(string Bitstring, long long iter){
        // cout<<"YASH "<<iter<<" "<<Bitstring<<ln;
		double top_c = 0;
        double bottom_c = 0;
        vector < pair <float , float > >  req_sum;
        vector<long long> data;
        for(long long i =0 ;i < students ; i++){
            req_sum.push_back( make_pair( raw_data[i][iter] , 0) ); //iter is the ques. no.
        }
        for (long long i = 0; i < students; ++i)
        {
            for (long long j  = 0; j < questions ; ++j)
            {
            	if ((Bitstring[j])=='1') {
                    // cout<<j<<" "<<raw_data[i][j]<<ln;
                    req_sum[i].second += raw_data[i][j];
                }
        
            }
        }
        for (long long j  = 0; j < questions ; ++j)
        {
            if ((Bitstring[j])=='1') data.push_back(j);
        }
        stable_sort (req_sum.begin() , req_sum.end() , compare);
       /*cout<<"QUESTIOn no. "<<iter<<ln;
       for(auto i : req_sum){
           cout<<i.second<<" ";
       }cout<<ln;*/
        double DI;
        for (long long i = 0; i < c; ++i)
        {
            top_c += req_sum[i].first;
            // cout<<req_sum[i].first<<" ";
        }
        // cout<<ln;
        for (long long i = students - c ; i < students ; ++i)
        {
            bottom_c += req_sum[i].first;
            //cout<<req_sum[i].first<<" ";
        }//cout<<ln;
       // cout<<top_c<<" "<<bottom_c<<" "<<data.size()<<  ln;
        DI = (top_c - bottom_c)/(c*subjQ[iter]);
        const std::map< double , vector <long long> > m1 ={{DI , data}};
        long long q = iter;
        pair < long long , map< double , vector<long long> > > x;
        x.first = q;
        x.second = m1;
        ans.insert(x);
        return;
}

long long binomialCoeff(long long n, long long k) 
{ 
    long long res = 1; 
  
    // Since C(n, k) = C(n, n-k) 
    if ( k > n - k ) 
        k = n - k; 
  
    // Calculate value of [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1] 
    for (long long i = 0; i < k; ++i) 
    { 
        res *= (n - i); 
        res /= (i + 1); 
    } 
  
    return res; 
} 


long long OrderOf10(long long n, long long k){
	long long num, den1, den2;
	num = (float)n*log10(n)-0.4342944819*(float)n + 0.39908993417 + 0.5*(float)log10(n);
	den1 = (float)k*log10(k)-0.4342944819*(float)k + 0.39908993417 + 0.5*(float)log10(k);
	den2 = (float)(n-k)*log10(n-k)-0.4342944819*(float)(n-k) + 0.39908993417 + 0.5*(float)log10(n-k);
	return num - den1 - den2;
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
    cout<<ln<<ln<<"The code has been developed by Mr. Yash Jain (B.Tech, IIT Bombay CSE) and Dr. P.K. Joshi (President IJSO, & TIFR)"<<ln;
    cout<< "For any further query the authors of this code can be reached at yash.jain3599@gmail.com or pkkjoshi@gmail.com"<<ln<<ln<<ln;

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
    bool yash=0, selfSelective=0;;
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
            long long a;
            while(fin>>a){
                selQ_number.push_back(a-1);
            }
            fin.close();
            selfSelective=1;
            cout<<"Enter Starting Step Size : ";
            cin>>starting_step;
            while(selQ_number.size()!=0 && (starting_step> selQ_number.size() || starting_step < 1)){
                help++;
                if(help > 3){
                    cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
                    string h;cin>>h;
                    if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
                        PrintHelp();
                    help=0;
                }
                cout<<"Invalid input (should be less than number of selective questions and greater than 0), Enter Again  : ";
                cin>>starting_step;
            }
            while((yash==1 && (starting_step > questions || starting_step < 1)) || (yash==0 && (starting_step>= questions || starting_step < 1)) ){
                help++;
                if(help > 3){
                    cout<<" Do you want help in running this code? Enter \"h\" for instructions otherwise \"s\" to skip : ";
                    string h;cin>>h;
                    if(h=="H"||h=="h"||h=="help"||h=="Help"||h=="HELP")
                        PrintHelp();
                    help=0;
                }
                cout<<"Invalid input (should be less than (in without self) or less than or equal to (in including self) number of questions and greater than 0), Enter Again  : ";
                cin>>starting_step;
            }
            cout<<"Ending Step Size : ";
            cin>>ending_step;
            while(selQ_number.size()!=0 && (ending_step> selQ_number.size()) )  {
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
        //Starting step ending step randomness missing -> fixed


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
            long long a;
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
    for(long long i=0;i<questions;++i){ //update maximum marks for each question
        float a;
        fin>>a;
        subjQ.push_back(a);
        //cout<<a<<" ";
    }
    for (long long i = 0; i < students; ++i){
        raw_data2[i] = std::vector<float> (questions);
        for(long long j = 0; j < questions ; ++j){
            fin>>raw_data2[i][j];
           // cout<<raw_data2[i][j]<<" ";
        }
        //cout<<ln;
    }
    raw_data = raw_data2;
//    for(long long i =0 ;i < students; ++i){
//        for(long long j=0;j< questions;++j){
//            cout<<raw_data[i][j]<<" ";
//        }
//        cout<<ln;
//    }
    //Data initialised into the 2d vector
    //QUESTIONS are numbered from zero
    if(yash==0){
	    if(selQ_number.size()==0){
	    	//Whether selective DI needed to be calculated or not
	    	for (long long i = 0; i < questions; ++i)
	    	{
	    		selQ_number.push_back(i); // if not then continue with the normal way and initialise with all the question number
	    	}
	    }
	    for (long long i = 0; i < selQ_number.size(); ++i){
	        srand(rand());
	        long long temp [selQ_number.size()-1];
	        for (long long j = 0,k =0; j < selQ_number.size()-1 ; ++j,++k){
	            if(k == selQ_number[i] ) {
	                k++;
	            }

	            temp[j] = selQ_number[k] ;
	        }
	        /*for(long long k = starting_step; k <= ending_step ; ++k ){
	        printCombination(temp , selQ_number.size() - 1 , k , selQ_number[i]	);
	        }*/
            // cout<<"DFs";
	        
	        set<string> VISITED;
		    for(long long j = starting_step ; j <= ending_step; ++j){
                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		    	long long no_of_datapts;
		    	if(randomness==1){
		    		long long estimate = OrderOf10(selQ_number.size(),j);
		    		if(estimate > 12){
		    			cout<<"Too less randomness, Please try again after increasing randomness"<<endl;
		    			return 0;
		    		}else{
		    			// no_of_datapts = binomialCoeff(questions-1,j); CHANGE
                        // cout<<questions<<" "<<selQ_number.size()<<ln;
                        no_of_datapts = binomialCoeff(selQ_number.size()-1,j);

                        // cout<<no_of_datapts<<ln;
		    		}
		    	}
		    	else{
		    		// no_of_datapts = r* (double)pow(10.0,(OrderOf10(questions,j)- log10(randomness))); CHANGE
                    no_of_datapts = r* (double)pow(10.0,(OrderOf10(selQ_number.size(),j)- log10(randomness)));
                    // cout<<no_of_datapts<<" "<<r<<" "<<(OrderOf10(selQ_number.size(),j)- log10(randomness))<<" "<<pow(10.0,(OrderOf10(selQ_number.size(),j)- log10(randomness)))<<ln;
                    // return 0; --> VERY sneaky bug! what if no_of_datapts becomes greater than max when randomness is small say 2!!

                    long long estimate = OrderOf10(selQ_number.size(),j);
                    long long no_of_datapts_buffer = INT_MAX;
                    if(estimate < 12 ){
                        no_of_datapts_buffer = binomialCoeff(selQ_number.size()-1,j);
                        // cout<<no_of_datapts<<ln;
                    }
                    if (no_of_datapts_buffer < no_of_datapts) no_of_datapts = no_of_datapts_buffer;

		    	}	
                cout<<"question no."<<i+1<<" | step size:"<<j<<" | number of data points: "<<no_of_datapts<<ln;    
		        for (long long k = 0; k < no_of_datapts; ++k)
		        {
                    srand(rand()+k*time(0));
		         	string a = generateBitString(temp, selQ_number.size()-1, j);
                    // cout<<j<<" "<<k<<" "<<no_of_datapts<<" "<<a<<ln;
		         	if(VISITED.find(a)!=VISITED.end()){
                        srand(rand()*rand()*rand());
		         		k--;continue;
		         	}else {
		         		VISITED.insert(a);
		         		generateDIusingBitString(a, selQ_number[i]);
		         	}
		        }
		    }	
	    }
	}else{
        if(selfSelective==0){ //All question including self
    		long long allquestions[questions];
            for (long long i = 0; i < questions; ++i)
            {
            	allquestions[i]=i;
            }
            for (long long i = 0; i < questions; ++i)
            {
            	// printCombination(allquestions, questions, questions, i);
            	srand(rand());

		        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		        
		        set<string> VISITED;
			   // for(long long j = starting_step ; j <= ending_step; ++j){
                long long j= questions;
		    	long long no_of_datapts;
		    	if(randomness==1){
		    		long long estimate = OrderOf10(questions,j);
		    		if(estimate > 12){
		    			cout<<"Too less randomness, Please try again after increasing randomness"<<endl;
		    			return 0;
		    		}else{
		    			no_of_datapts = binomialCoeff(questions,j);
		    		}
		    	}
		    	else{
		    		no_of_datapts = r*(double)pow(10,(OrderOf10(questions,j)- log10(randomness)));
		    	}	
		        
		        for (long long k = 0; k < no_of_datapts; ++k)
		        {
                    srand(rand()+k*time(0));
		         	string a = generateBitString(allquestions, questions, j);
		         	if(VISITED.find(a)!=VISITED.end()){
                        srand(rand()*rand()*rand());
		         		k--;continue;
		         	}else{
		         		VISITED.insert(a);
		         		generateDIusingBitString(a,i);
		         	}
		        }
		    }	

            
        }else{ //Selective questions including self

            // cout<<starting_step<<" "<<ending_step<<" "<<randomness<<ln;
            long long temp[selQ_number.size()];
            for (long long i = 0; i < selQ_number.size(); ++i)
            {
                temp[i]=selQ_number[i];
            }
            /*for (long long i = 0; i < selQ_number.size(); ++i)  
            {
                printCombination(temp, selQ_number.size(), selQ_number.size(), selQ_number[i]);
            }*/

            for (long long i = 0; i < selQ_number.size(); ++i){
		        srand(rand());
		        /*long long temp [selQ_number.size()-1];
		        for (long long j = 0,k =0; j < selQ_number.size()-1 ; ++j,++k){
		            if(k == selQ_number[i] ) {
		                k++;
		            }

		            temp[j] = selQ_number[k] ;
		        }*/
		        /*for(long long k = starting_step; k <= ending_step ; ++k ){
		        printCombination(temp , selQ_number.size() - 1 , k , selQ_number[i]	);
		        }*/

		        
		        set<string> VISITED;
			    for(long long j = starting_step ; j <= ending_step; ++j){
                    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			    	long long no_of_datapts;
			    	if(randomness==1){
                        //cout<<"2"<<ln;
			    		long long estimate = OrderOf10(selQ_number.size(),j);
			    		if(estimate > 12){
			    			cout<<"Too less randomness, Please try again after increasing randomness"<<endl;
			    			return 0;
			    		}else{
			    			no_of_datapts = binomialCoeff(selQ_number.size(),j);
			    		}
			    	}
			    	else{
			    		// no_of_datapts = r*(double)pow(10,(OrderOf10(questions,j)- log10(randomness))); CHANGE
                        no_of_datapts = r* (double)pow(10.0,(OrderOf10(selQ_number.size(),j)- log10(randomness)));

                        long long estimate = OrderOf10(selQ_number.size(),j);
                        long long no_of_datapts_buffer = INT_MAX;
                        if(estimate < 12 ){
                            no_of_datapts_buffer = binomialCoeff(selQ_number.size(),j);
                            // cout<<no_of_datapts<<ln;
                        }
                        if (no_of_datapts_buffer < no_of_datapts) no_of_datapts = no_of_datapts_buffer;

			    	}	
			    	// cout<<no_of_datapts<<ln;
                    cout<<"question no."<<i+1<<" | step size:"<<j<<" | number of data points: "<<no_of_datapts<<ln;    
			        for (long long k = 0; k < no_of_datapts; ++k)
			        {

			         	string a = generateBitString(temp, selQ_number.size(), j);
                        // cout<<k<<" "<<a<<ln
                        srand(rand()+k*time(0));
			         	if(VISITED.find(a)!=VISITED.end()){
                            // cout<<j<<" "<<k<<" "<<no_of_datapts<<" "<<a<<" "<<selQ_number.size()<<ln;
                            srand(rand()*rand()*rand());
			         		k--;continue;
			         	}else{
			         		VISITED.insert(a);
			         		generateDIusingBitString(a, selQ_number[i]);
			         	}
			        }
			    }	
		    }
        }
	}
    auto m = ans.begin();
    long long ques = m->first + 1;
    if(yash==1 && selfSelective==0){
    	fout.open(output_file_name+".csv");
    	for (auto i = ans.begin(); i != ans.end(); ++i){
    		fout<< i->first+1 <<",";
	        auto j = i->second.begin();
	        fout << std::fixed;
	        fout << std::setprecision(6);
	        fout<< j->first <<",";
	        auto k = j->second;
	        for(long long f = 0 ; f< k.size() ; f++)
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
        for(long long f = 0 ; f< k.size() ; f++)
         fout<< k[f]+1<<",";
         fout<<"\n";
    }
}
