#include <bits/stdc++.h> 

using namespace std;

#define FOR(i,n) for(int i=0;i<(int)n;i++)

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
		if(i) cout<<" ";
		v[i].print();
	}
	cout<<endl;
}
int dp[10000][10000];
int discreteDistance(int k, int l){
	if( dp[k][l] != -1 )
		return dp[k][l];
	else if( k==0 && l==0 )
		dp[k][l] = p[k].sqrtDist(q[l]);
	else if( k>0 && l==0)
		dp[k][l] = max(p[k].sqrtDist(q[l]), discreteDistance(k-1,l));
	else if( k==0 && l>0)
		dp[k][l] = max(p[k].sqrtDist(q[l]), discreteDistance(k,l-1));
	else 
		dp[k][l] = max(p[k].sqrtDist(q[l]), min(discreteDistance(k-1,l),min(discreteDistance(k,l-1),discreteDistance(k-1,l-1))));
	return dp[k][l];
}
int distanceCalc(){
	memset(dp,-1,sizeof(dp));
	return discreteDistance(p.size()-1, q.size()-1);
}

int main(){
	cin>>n>>m;
	read_points( p, n );
	read_points( q, m );
	vector<Point> parcour;
	int distFrechet = distanceCalc();
	print_answer( distFrechet, parcour);
	
	
	
}
