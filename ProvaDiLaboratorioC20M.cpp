#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cmath>
#define DIM 30


using namespace std;


class A{
    private:
        int *vec;
        short len;
    protected:
        short moreThan(int k){
            int count = 0;
            for(int i=0; i<len; i++){
                if(vec[i] >= k) count++;
            }
            return count;
        }
        
    public:
        A(int lower, int upper, short n){
            int *arr = new int[n];
            srand(time(0));
                for(int i=0; i<n; i++){
                    arr[i]= rand()%(upper-lower +1)+lower;
                }
            vec = arr;
            len = n;
        }
        
        virtual float v()=0;
        
        virtual ostream& put(ostream &os)const{
            os << "vec=[" ;
            for(int i=0; i< len; i++){
                os << vec[i] <<" ";
            }
            os << "], len=" << len << " ";
            return os;
        }
};


class B: public A{
    private:
        string s;
        short l;
    public:
        B(string w, short k): A(2*k, 4*k, k){
            for(int i=w.length()-1; i>= 0; i--){
                s+= w[i];
            }
            l = s.length();
        }
        
        float v(){
            return (float)(l)/(moreThan(l)+1);
        }
        
        ostream & put(ostream &os)const{
            os << "Class 1B: ";
            A::put(os);
            os << "{ s=" << s << ", l=" << l << " }";
            return os;
        }
};


class C: public A{
    private:
        float y;
    public:
        C(int lower, int upper, short n): A(lower,upper,n){
            y= (upper - lower)/ (float)(n);
        }
        
        float v(){
            return (float)(sin(y) + log(moreThan((short)(y+0.5)) + 1));
        }
        
        bool r(short k, float x){
            return ((y/moreThan(k)) >= x);
        }
        
        ostream& put(ostream &os)const{
            os << "Class 1C: ";
            A::put(os);
            os << "{ y = " << y << "}";
            return os;
        }
};

ostream & operator <<(ostream &os, const A& a){
    return a.put(os);
}



int main(){
    srand(111222333);
    A *vett[DIM];

    int lo = 100; int up = 130;
    int lower, upper; short k;
    string s; int l;
    for(int i=0; i<DIM; i++){
        if(rand()%2==0){
            lower = lo + rand()%10;
            upper = up - rand()%10;
            k = rand()%10 + 3;
            vett[i] = new C(lower, upper, k);
        }
        else{
        s = "";
        l = rand()%10 +3;
        k = rand()%5 + 3;
        for(int j=0; j<l; j++){
            s+=((char) ('a' + rand()%25));
        }
        vett[i] = new B(s, k);
        }
    }
    
    float somma = 0;
    for(int i= 0; i<DIM; i++){
        cout << i <<")";
        cout << *vett[i] << endl;
        cout << "    v()=" << (vett[i])->v() << endl;
        somma += (vett[i])->v();
    }
    
    cout << endl;
    cout << "Punto II:AVG v(): "<< somma / DIM << endl;
    cout << endl;
    cout << "Punto III: indici per cui r(3,0.5) restituisce true" << endl;
    
    
    for(int i= 0; i<DIM; i++){
        C *ptr = dynamic_cast <C*> (vett[i]);
        if(ptr){
          if(ptr->r(3,0.5)) cout << i << " ";
        }
    }
    
    cout << endl;
    
    return 0;

}
