#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstring>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;
// make array heap
int heap[100];
// function to add a single number num
void addint(int num){
	int spot =0;
	bool done =false;
	while(spot<100 && done == false){
		if(heap[spot] < num){
			// put num at spot and move everything down recursively. Hey recursion is useful!
			int next = heap[spot];
			heap[spot] = num;
			if(next != 0){
				// for now I'm just having the other number added the same way, from the top, so it could end up anywhere
				addint(next);
			}
			done = true;
		}
		spot++;
	}
}
int main(){
	// set heap to all zero
	for(int i=0; i<100; i++){
	heap[i] = 0;
	}
	bool quit = false;
	while(quit == false){
	cout << "What do you want to do, Add (A), Remove (R), Print (P), or Quit (Q)" << endl;
	char input;
	cin >> input;
	// Add: gives user the option between inputting numbers manually or using a file
	if (input == 'A'){
		cout <<"How would you like to add? User input (U) or File (F)?" << endl;
		char input2;
		cin >> input2;
		cin.get();
		//User input: does addint for every number the user says, unless it's zero, then it ends the loop.
		if (input2 == 'U'){
			bool addquit = false;
			while(addquit == false){
			cout << "Number (say 0 if you are done adding): ";
			int usernum;
			cin >> usernum;
			if(usernum == 0){
			addquit = true;
			}
			else addint(usernum);
			}
		}
		//File: I took the idea for how to read in from Pranav 
		else if (input2 == 'F'){
			cout << "Enter the file you would like to open, in this program there is a file called 'Numbers.txt'\n";
        		char file[20];
        		cin.getline(file, 80, '\n');
        		FILE* pfile = NULL;
        		char line[1000];
        		// opens the file with the given name from user
        		pfile = fopen(file, "r");
        		// alerts if file is unreadable
        		if (pfile == NULL)
        		{
        		    cout << "Error in opening the file.";
        		    return 0;
        		}

        		// goes through each line, and stores whats beween the spaces in the integer array
        		int index = 0;
        		while (fgets(line, 1000, pfile)) {
        		    char* buffer = new char[20];
        		    memset(buffer, '\0', 20);
        		    int pos = 0;
        		    while (buffer != NULL) {                
        		        buffer = strchr(line + pos, ' ');
         		        if (buffer != NULL) {
                		    char lineBuffer[20];
                		    memset(lineBuffer, '\0', 20);
                		    strncpy(lineBuffer, line + pos, sizeof(line - buffer));
                		    addint(stoi(lineBuffer)); // thing gets added here
                		    pos = (buffer-line) + 1;
                		}
            			}
        		}
		}
	}
	// Remove: This is kind of interesting. Basically it takes the biggest number, which is heap[0], 
	// and then goes through a loop which replaces it by its largest child, then replaces the child 
	// in the same way, until both children don't exist.
	else if (input == 'R'){
		cout << "How many removed? (say 100 if you want all): ";
		int rnum;
		cin >> rnum;
		for(int i=0; i<rnum && heap[0] != 0; i++){
			cout << heap[0] << endl;
			int k = 0;
			while(k < 63 && (heap[2*k+1] != 0 || heap[2*k+2] != 0)){
				if(heap[2*k+1] > heap[2*k+2]){
					heap[k] = heap[2*k+1];
					k = 2*k+1;
				}
				else{
					heap[k] = heap[2*k+2];
					k = 2*k+2;
				};
			};
			heap[k] = 0;
		};
	}
	// Print: I did this in such an overly complicated way, but basically it does a spacing of 2^(7-row),
	// then halves it if it's the start of a line, then adjusts for the number of digits the number has,
	// and does two endlines when it gets to the end of the line. It doesn't look bad in my opinion.
	else if (input == 'P'){
		//get number of rows total
		int totalrows = 0;
		for(int k=0; k<100; k++){
			if(heap[k]!=0){
				totalrows = (int)floor(log2(k+1))+1;
			}
		}
		if(totalrows > 5){
			cout << "I can only print things with at most 5 rows, sorry";
		}
		else if(totalrows == 0){
			cout << "The heap is empty!";
		}
		else for(int i=0; i<100; i++){
			int rownum = (int)floor(log2(i+1));
			int width = ceil(exp2(totalrows+2-rownum));
			if(i == 0 || i==1||i==3||i==7||i==15||i==31||i==63){
				width = (int)ceil(width / 2);
			};
			width = width - (int)floor(log10(heap[i]+1));
			cout << string(width -1, ' ');
			if (heap[i] != 0){
			cout << heap[i] << " ";
			}
			if (heap[i] == 0){
			cout << "  ";
			} 
			if (i==0 || i==2 || i==6 || i==14 || i==30 || i==62){
			cout << endl << endl;
			}
		}
		cout << endl;
	}
	// Quit: quit
	else quit = true;
	}
	return 0;
}
