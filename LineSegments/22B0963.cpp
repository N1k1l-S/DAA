#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
// #include <chrono>
// #pragma GCC optimize("O1")

using namespace std;

typedef long long ll;

class Point {
 public:
  float x;
  float y;

 public:
  Point()
      : x(0), y(0) {}  // Default constructor initializing coordinates to (0,0)
  Point(float xVal, float yVal)
      : x(xVal), y(yVal) {}  // Parameterized constructor

  float X() const { return x; }  // Accessor for x coordinate
  float Y() const { return y; }  // Accessor for y coordinate

};

// Non-member functions for comparisons
bool operator==(const Point& lhs, const Point& rhs) {
    return fabsf(lhs.x - rhs.x) < 1e-5 && fabsf(lhs.y - rhs.y) < 1e-5;
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs); 
}

// Useful geometry functions
float solve_pt_on_line(Point P1, Point P2, float x){ // returns y value
    // y = y1 + ((y2-y1)/(x2-x1)) * (x-x1)
    float y1 = P1.Y();
    float x1 = P1.X();
    float y2 = P2.Y();
    float x2 = P2.X();
    return y1 + ((y2 - y1)/(x2 - x1))*(x - x1);
}

Point intersection_pt(Point P1,Point P2,Point P3,Point P4){
    float x,y;
    float y1 = P1.Y();
    float x1 = P1.X();
    float y2 = P2.Y();
    float x2 = P2.X();
    float y3 = P3.Y();
    float x3 = P3.X();
    float y4 = P4.Y();
    float x4 = P4.X();
    
    x = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
    y = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

    return Point(x,y);
}

// CRUX
vector<Point> merge(vector <Point> &O1,vector <Point> &O2){
    vector<Point> merged_vec;
    ll len1 = O1.size();
    ll len2 = O2.size();
    ll p1=0, p2=0; // indices of points in outlines
    float height1=0, height2=0; // current heights
    int dom = 1; // True if first outline height greater than second
    if(O2[0].X() < O1[0].X()) dom = 2;

    while(p1<len1 && p2<len2){
        if( O1[p1].X() < O2[p2].X()){ // first outline point comes before
            height1 = O1[p1].Y();
            // y = y1 + ((y2-y1)/(x2-x1)) * (x-x1)
            height2 = solve_pt_on_line(O2[p2],O2[p2-1],O1[p1].X());
            if(dom == 1){ // there's a point in between
                if(height1 >= height2){
                    merged_vec.push_back(O1[p1]);
                }
                else{ //height1 < height2
                    merged_vec.push_back( intersection_pt(O1[p1],O1[p1-1],O2[p2],O2[p2-1]) );
                    merged_vec.push_back( Point(O1[p1].X(),height2) );
                    dom = 2;
                }
            }
            else{ // dom == 2
                if(height2 >= height1){
                    merged_vec.push_back(Point(O1[p1].X(),height2));
                }
                else{
                    merged_vec.push_back( intersection_pt(O1[p1],O1[p1-1],O2[p2],O2[p2-1]) );
                    merged_vec.push_back( O1[p1] );
                    dom = 1;
                }
            }
            p1++;
        }        
        else {// ( O1[p1].X() >= O2[p2].X()) // first outline point comes before
            height2 = O2[p2].Y();
            // y = y1 + ((y2-y1)/(x2-x1)) * (x-x1)
            height1 = solve_pt_on_line(O1[p1],O1[p1-1],O2[p2].X());
            if(dom == 2){ // there's a point in between
                if(height2 >= height1){
                    merged_vec.push_back(O2[p2]);
                }
                else{ //height2 < height1
                    merged_vec.push_back( intersection_pt(O2[p2],O2[p2-1],O1[p1],O1[p1-1]) );
                    merged_vec.push_back( Point(O2[p2].X(),height1) );
                    dom = 1;
                }
            }
            else{ // dom == 1
                if(height1 >= height2){
                    merged_vec.push_back(Point(O2[p2].X(),height1));
                }
                else{
                    merged_vec.push_back( intersection_pt(O2[p2],O2[p2-1],O1[p1],O1[p1-1]) );
                    merged_vec.push_back( O2[p2] );
                    dom = 2;
                }
            }
            p2++;
        }
    }
    while(p1<len1){
        merged_vec.push_back(O1[p1]);
        p1++;
        dom = 1;
    }
    while(p2<len2){
        merged_vec.push_back(O2[p2]);
        p2++;
        dom = 2;
    }
    return merged_vec;
}

vector<Point> mergesort(vector <pair<Point, Point> > &posters, int i, int j){
    if( i == j ) { // Single poster
        vector<Point> O;
        O.push_back(Point(posters[i].first.X(),0));
        O.push_back(posters[i].first);
        O.push_back(posters[i].second);
        O.push_back(Point(posters[i].second.X(),0));

        return O;
    }
    int mid = (i+j)/2;
    vector<Point> O1 = mergesort(posters,i,mid);
    vector<Point> O2 = mergesort(posters,mid+1,j);
    return merge(O1,O2);
}

// remove repeated points in the outline:
vector<Point> remove_pts(vector<Point> vec){
    if(vec.size() <= 1){
        return vec;
    }

    vector<Point> retvec;
    retvec.push_back(vec[0]);
    for(ll i=1; i < vec.size(); i++){
        if(vec[i] != vec[i-1]){
            retvec.push_back(vec[i]);
        }
    }

    return retvec;
}

// area and length
float area_of_outline(vector<Point> vec){
    if(vec.size() <= 1){
        return 0;
    }

    float area = 0, h, w;

    for(ll i=0; i < vec.size()-1; i++){
        w = vec[i+1].X() - vec[i].X();
        h = (vec[i+1].Y() + vec[i].Y())/2;
        area += h*w;
    }

    return area;
}

float lengthCovered_of_outline(vector<Point> vec){
    if(vec.size() <= 1){
        return 0;
    }

    float len = 0;

    for(ll i=0; i < vec.size()-1; i++){
        if( fabsf(vec[i+1].Y()) < 1e-5 && fabsf(vec[i].Y()) < 1e-5 ){
            continue;
        }
        len += vec[i+1].X() - vec[i].X()  ;
    }

    return len;
}

int main(){
	   /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    // auto start = std::chrono::steady_clock::now();
 
	int n;
	cin >> n;
	float a,b,c,d;

	vector <pair<Point, Point> > posters; 

	for(int i=0; i<n; i++){
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;

		posters.push_back(make_pair(Point(a,b), Point(c,d)));	
	}

    vector<Point> merged_vector = mergesort(posters,0,n-1);
    
    // auto t1 = std::chrono::steady_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - start);
    // cout << "Time taken for merge: " << duration.count() << " milliseconds" << endl;

    merged_vector = remove_pts(merged_vector);
    // auto t2 = std::chrono::steady_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    // cout << "Time taken for remove: " << duration.count() << " milliseconds" << endl;

    // for(auto i:merged_vector){
    //     cout << i.X() << " " << i.Y() << endl;
    // }
    // auto t3 = std::chrono::steady_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
    // cout << "Time taken for printing: " << duration.count() << " milliseconds" << endl;

	float lengthCovered = lengthCovered_of_outline(merged_vector); 
    // auto t4 = std::chrono::steady_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t2);
    // cout << "Time taken for length: " << duration.count() << " milliseconds" << endl;

	float area = area_of_outline(merged_vector);
    // auto t5 = std::chrono::steady_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(t5 - t4);
    // cout << "Time taken for area: " << duration.count() << " milliseconds" << endl;
 
	cout << static_cast<int>(lengthCovered)<< endl;
	
	cout << static_cast<int>(area)<< endl;

	return 0;
}

