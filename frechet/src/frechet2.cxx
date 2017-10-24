#include <bits/stdc++.h> 

using namespace std;

#define FOR(i,n) for(int i=0;i<(int)n;i++)
#define FORA(a,i,n) for(int i=a;i<(int)n;i++)

struct Point {
	/* Point data structure to save coordinates(x,y) where:
	 * x - is the horizontal axis
	 * y - is the verticial axis
	 * */
	int x;
	int y;
	Point():x(0),y(0){}
	Point(int _x, int _y):x(_x),y(_y){}
	/* Function that takes other point and return the
	 * square distance between the current point(x,y)
	 * and the point passed by parameter (p.x,p.y)
	 */ 
	int sqrtDist(Point p){
		return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
	}
	/* Function that print the current point coordinates*/
	void print(){
		cout<<x<<" "<<y;
	}
};

/*
 * Variables
 * n - size of P
 * m - size of Q
 * p - Set of points P
 * q - Set of points Q
 * 
 */
int n,m;
vector<Point> p;
vector<Point> q;
int** dp;
vector<Point> parcour;
bool debug = false;
/* Function that read s points and save it in a
 * vector of points passed by reference, where:
 * v - Set of points
 * s - size of points to read 
 */
void read_points(vector<Point>& v, int s){
	FOR(i,s){
		Point temp;
		
		cin>>temp.x>>temp.y;
		v.push_back(temp);
	}
}
/* Print the frechet distance, and one of the optimal routes
 * to find it, in the form of a number that represent the size of the points
 * that represent the route, and after print the points.
 */
void print_answer( int d, vector<Point> v){
	cout<<d<<endl;
	cout<<v.size()<<endl;
	FOR(i,v.size()){
		if(i!=0)cout<<" ";
		v[v.size()-1-i].print();
	}
	cout<<endl;
}



void reconstruct(int i, int j, int h){
	parcour.push_back(Point((i+1),(j+1)));
	if(i==0 && j==0) return;
	if( i>0 && j==0){
		reconstruct(i-1,j,dp[i-1][j]);
	}else if(i==0 && j>0){
		reconstruct(i,j-1,dp[i][j-1]);
	}else{
		int k,l;
		k=i,l=j;
		if(dp[i-1][j-1]<=dp[i][j-1] && dp[i-1][j-1]<=dp[i-1][j] && dp[i-1][j-1]<=h) k=i-1,l=j-1;
		else if(dp[i-1][j]<=dp[i][j-1] && dp[i-1][j]<=dp[i-1][j-1] && dp[i-1][j]<=h) k=i-1,l=j;
		else if(dp[i][j-1]<=dp[i-1][j] && dp[i][j-1]<=dp[i-1][j-1] && dp[i][j-1]<=h) k=i,l=j-1;
		reconstruct(k,l,dp[k][l]);
		if(debug) printf("(i,j):%d,%d k: %d, l: %d\n",i,j,k,l);
	}
	
	
}

int min3( int p, int q, int r){
	return min(p,(min(q,r)));
}
int distanceCalc(){
	dp[0][0] = p[0].sqrtDist(q[0]);
	
	FORA(1,i,n) dp[i][0] = max(p[i].sqrtDist(q[0]), dp[i-1][0]);
	
	FORA(1,i,m) dp[0][i] = max(p[0].sqrtDist(q[i]), dp[0][i-1]);
	
	FORA(1,i,n) FORA(1,j,m)
		dp[i][j] = max(
		p[i].sqrtDist(q[j]),
		min3(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])
		);
	return dp[n-1][m-1];
}

int main(int argc, char *argv[]){
	
	ios_base::sync_with_stdio(0);
	if(argc<2) return -1;
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	cin>>n>>m;
	
	dp = new int *[n];
	for(int i=0;i<n;i++) dp[i] = new int [m];
	//FOR(j,n) malloc(m);
	read_points( p, n );
	read_points( q, m );
	
	int distFrechet = distanceCalc();
	reconstruct(n-1,m-1,distFrechet);
	print_answer( distFrechet, parcour);
/*FOR(i,n){
		FOR(j,m){
		cout<<(i+1)<<":"<<(j+1)<<"->";
		cout<<dp[i][j]<<endl;
		}
		
	}
	FOR(i,n){
		FOR(j,m){
		
		cout<<dp[i][j]<<" ";
		}cout<<endl;
		
	}
	FOR(i,n){
		FOR(j,m){
		
		cout<<dp[i][j];
		}cout<<endl;
		
	}
*/

	
	
}
