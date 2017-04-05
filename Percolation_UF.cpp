/*Percolation Problem*/
/*Created by: @noobprog_22*/
#include <iostream>

using namespace std;

class PercolationUF{
	private:
		int state[100], size[100];
		int num[100], i, j, length;
		
	public:
		int count;
		int root(int a){
			while(a != num[a]){
				num[a] = num[num[a]];
				a = num[a];
			}
			return a;
		}
		void open(int a){
			state[a] = 0;//Value zero indicates the site is open
			//So basically here I'm opening the site and connecting with all adjecent 
			//Opened sites.
			if(state[a+1] == 0)
				unite(a, a+1);
			else
				;
			if(state[a-1] == 0)
				unite(a - 1, a);
			else
				;
			if(state[a+length] == 0)
				unite(a, a+length);
			else
				;
			if(state[a-length] == 0)
				unite(a, a-length);
			else
				;						
		}
		
		void unite(int a, int b){
			int pid = root(a);
			int qid = root(b);
			
			if(pid == qid)
				return;
			else if(size[pid] < size[qid]){
				num[pid] = qid;
				size[qid] += size[pid];
			}
			else{
				num[qid] = pid;
				size[pid] += size[qid];
			}
		}
		
		bool connected(int a, int b){
			return root(a) == root(b);
		}
		
		PercolationUF(int len){
			count = 0, length = len;
			
			//Created the array with all in closed state i.e. state = -1.
			//And size value 1
			for(i = 0;i < len;i++){
				for(j = 0;j < len;j++){
					num[count] = count;//Initializing root of every element is the array D.S.
					//to be itself, i.e. num[count] = count;
					//Here num is the root.
					size[count] = 1;
					state[count] = -1;
					count++;
				}
			}
			//The top and bottom points
			num[count] = count;
			size[count] = 1;
			num[count+1] = count+1;
			size[count+1] = 1;//Is this a bug?Yes it is. I just found a bug in my own program.
			for(i = 0;i < len;i++){
				unite(i, count);//Create the top sites
			}
			for(i = count - 1;i >count - len + 1;i--){
				unite(i, count+1);//Create the bottom sites
			}
		}
};

int main(){
	int n, top_main, bottom_main;
	int site, count_call = 0;
	float prob;
	cout<<"\nEnter the number of row/col: ";
	cin>>n;
	PercolationUF uf(n);
	top_main = uf.count;
	bottom_main = top_main+1;
	while(uf.connected(top_main, bottom_main) == false){
		cout<<"\nEnter the site to open: (less than"<<n*n<<")";
		cin>>site;
		uf.open(site);
		count_call++;
	}
	count_call--;
	prob = (float)(count_call)/(float)(n*n);
	cout<<"\nThe system percolates with a p* = "<<prob;
	return 0;
}
