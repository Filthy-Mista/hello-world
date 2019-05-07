#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <cmath>
#define DIM 30

using namespace std;


class A{
    private:
        string sa;
        float * p;
        short l;
    protected:
        float val(short j){
            return this->p[j%l];
        }
        
    public:
        A(string s1, short n){
            for(int i=0; i<s1.length(); i++){
                if((s1[i]>= '0' && s1[i]<= '9') || (s1[i] >= 'a' && s1[i] <= 'z')){
                    this->sa += s1[i];
                }
            }
            this->p = new float[n];
            
            for(int i=0; i<n; i++){
                this->p[i] = (float)rand()/RAND_MAX;
            }
            this->l = n;
        }
        
        virtual float f(short i, float x)=0;
        
        virtual ostream& put(ostream &os)const{
            os << "sa=" << sa << " p=[";
            for(int i=0; i<l; i++){
                os << this->p[i] << " ";
            }
            os << "]";
            return os;
        }
};
ostream& operator<<(ostream & os, const A & a){
    return a.put(os);
}


class B: public A{
    private:
        string str;
    public:
        B(string w, short k, int v):A(w,k){
            if(v%2 == 0){
                for(int i= 0; i<k; i++){
                    str +=w[i];
                }
            }
            else{
                str = w.substr(w.length()-k);
            }
        }
        
        float f(short i, float x){
            if(x < val(i)) return x;
            else return val(i);
        }
        
        ostream & put(ostream & os)const{
            os << "Class 1B: ";
            A::put(os);
            os << "{str=" << str << "}";
            return os;
        }
};



class C: public A{
    private:
        float y;
    public:
        C(string a1, string a2):A((a1+a2), abs ((int) (a1.length()-a2.length())*2)+1){
            y = (a1.length() + a2.length())/2.0;
        }
        
        float f(short i, float x){
            if( x =! 0){
                if(i%2 == 0){
                    return sin(val(i)*x);
                }
                else if(i%2 == 1){
                    return val(i)/x;
                }
            }
            else{
                return 0;
            }
            return 0;
        }
        
        float g(){
            return log(y);
        }
        
        ostream & put(ostream & os)const{
            os << "Class 1C: ";
            A::put(os);
            os << "{ y = "<< y << "}";
            return os;
        }
};





int main(){
    srand(111222333);
    A *vett[DIM];

    string s1, s2;
    int l1, l2;
    short k;

    for(int i=0; i<DIM; i++){
        if(rand()%2==0){ // B
            s1 = "";
            l1 = rand()%5 + 5;
            k = rand()% (l1/2)+1;
            for(int j=0; j<l1; j++)
                s1+=((rand()%2) ? (char) (rand()%26 + 'a') : (char) (rand()%10 + '0'));
            vett[i] = new B(s1, k, rand()%100);
        }
        else{ // C
            s1 = "";
            s2 = "";
            l1 = rand()%5 +5;
            l2 = rand()%5 +5;
            for(int j=0; j<l1; j++)
                s1+=(rand()%2 ? (char) (rand()%26 + 'a') : (char) (rand()%10 + '0')); 
            for(int k=0; k<l2; k++)
                s2+=(rand()%2 ? (char) (rand()%26 + 'a') : (char) (rand()%10 + '0'));
            vett[i] = new C(s1, s2);
        }
    }
    
    for(int i= 0; i<DIM; i++){
        cout << i <<")";
        cout << *vett[i]<< endl;
        if(typeid(*vett[i]) == typeid(C)){
            cout<< "g()=" <<((C*)(vett[i]))->g()<<endl;
        }
    }
    
    cout << "Punto II: Indici per f( 5, 0.5 )<0.5: ";
    for(int i=0; i<DIM; i++){
        if((vett[i]->f(5,0.5)) < 0.5){
            cout << i << " ";
        }
    }
    cout << endl;
    float somma= 0;
    int counter=0;
    for(int i=0; i<DIM; i++){
        C* ptr = dynamic_cast <C*> (vett[i]);
        if(ptr){
            counter++;
            somma += ptr->g();
        }
    }    
    cout << "Punto III (media dei valori del metodo g()): "<< somma/counter << endl;
    
    return 0;
}
