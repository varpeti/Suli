#include <set>
#include <vector>
#include <climits>
#include "iostream"

using namespace std;


struct S { int a, b; };

int f(const vector< vector<S> > &t, int s, int n) {
    vector<int> q( t.size(), INT_MAX );
    q[ s ] = 0;
    set< pair<int,int> > v;
    v.insert( {0,s} );
   	 
    while (!v.empty()) {
    	int w = v.begin()->second;
    	if (w == n) return q[w];
    	v.erase( v.begin() );
    	for (auto ed : t[w])
   	 if (q[ed.a] > q[w] + ed.b) {
   	 	v.erase( { q[ed.a], ed.a } );
   	 	q[ed.a] = q[w] + ed.b;
   	 	v.insert( { q[ed.a], ed.a } );
   	 }
    }
    return INT_MAX;
}

int main()
{
	vector< vector<S> > t;
	for (int i = 0; i < 3; ++i)
	{
		vector<S> seged;
		for (int j = 0; j < 3; ++j)
		{
			S ss;
			ss.a=i;
			ss.b=j;
			seged.push_back(ss);
		}
		t.push_back(seged);
	}
	
	cout << f(t,0,2);
	getchar();
} 