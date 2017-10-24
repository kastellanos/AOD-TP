#include <bits/stdc++.h> 

using namespace std;

#define FOR(i,n) for(int i=0;i<(int)n;i++)
#define FORA(a,i,n) for(int i=a;i<(int)n;i++)

struct Point {
	int x;
	int y;
	Point():x(0),y(0){}
	Point(int _x, int _y):x(_x),y(_y){}
	
	int sqrtDist(Point p){
		return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
	}
	void print(){
		cout<<x<<" "<<y;
	}
};
int n,m;
vector<Point> p;
vector<Point> q;
void read_points(vector<Point>& v, int s){
	FOR(i,s){
		Point temp;
		
		cin>>temp.x>>temp.y;
		v.push_back(temp);
	}
}
void print_answer( int d, vector<Point> v){
	cout<<d<<endl;
	cout<<v.size()<<endl;
	FOR(i,v.size()){
		if(i!=0)cout<<" ";
		v[v.size()-1-i].print();
		
	}cout<<endl;
}
int dp[10000][10000];
int vs[10000][10000];
vector<Point> mapa;
int discreteDistance(int k, int l){
	if( dp[k][l] != -1 )
		return dp[k][l];
	else if( k==0 && l==0 )
		dp[k][l] = p[k].sqrtDist(q[l]);
	else if( k>0 && l==0)
		dp[k][l] = max(p[k].sqrtDist(q[l]), discreteDistance(k-1,0));
	else if( k==0 && l>0)
		dp[k][l] = max(p[k].sqrtDist(q[l]), discreteDistance(0,l-1));
	else
		dp[k][l] = max(p[k].sqrtDist(q[l]), min(discreteDistance(k-1,l),min(discreteDistance(k,l-1),discreteDistance(k-1,l-1))));


	return dp[k][l];
}
vector<Point> parcour;
void reconstruct(int i, int j, int h){
	
	Point p;parcour.push_back(Point((i+1),(j+1)));
	if(i==0 && j==0){ p=Point(i+1,j+1);return;}
	if( i>0 && j==0){
		reconstruct(i-1,j,dp[i-1][j]);
		//reconstruct(i-1,j,h);
	}else if(i==0 && j>0){
		reconstruct(i,j-1,dp[i][j-1]);
		//reconstruct(i,j-1,h);
	}else{
		int k,l;
		k=i,l=j;
		if(dp[i-1][j-1]<=dp[i][j-1] && dp[i-1][j-1]<=dp[i-1][j] && dp[i-1][j-1]<=h) k=i-1,l=j-1;
		else if(dp[i-1][j]<=dp[i][j-1] && dp[i-1][j]<=dp[i-1][j-1] && dp[i-1][j]<=h) k=i-1,l=j;
		else if(dp[i][j-1]<=dp[i-1][j] && dp[i][j-1]<=dp[i-1][j-1] && dp[i][j-1]<=h) k=i,l=j-1;
		//printf("(i,j):%d,%d k: %d, l: %d\n",i,j,k,l);
		if(k!=i || l!=j)
			reconstruct(k,l,dp[k][l]);
		else{
			cout<<"**********problem"<<"("<<k<<","<<l<<")"<<endl;
		}
	}
	
	
}
int distanceCalc(){
	memset(dp,-1,sizeof(dp));
	return discreteDistance(p.size()-1, q.size()-1);
}

int main(int argc, char *argv[]){
	if(argc<2) return -1;
	freopen(argv[1],"r",stdin);
	//freopen(argv[2],"w",stdout);
	cin>>n>>m;
	cout<<n<<m<<endl;
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
		
	}FOR(i,n){
		FOR(j,m){
		
		cout<<dp[i][j]<<" ";
		}cout<<endl;
		
	}*/
	/*FOR(i,n){
		FOR(j,m){
		
		cout<<dp[i][j];
		}cout<<endl;
		
	}
	FOR(i,mapa.size()){
		mapa[i].print();
		cout<<endl;
	}*/

	
	
}
