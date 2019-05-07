#include <iostream>
#include <string>
#include <cmath>
#define DIM 30


using namespace std;


class A{
    private:
        string w;
    protected:
        short par;
    public:
        A(string s, short n):w(s),par(n){}
        
        int getSum(){
            int sumv = 0;
            int sumt = 0;
            for(int i=0; i<w.length(); i++){
                if(w[i] == 'a' || w[i] == 'e' || w[i] == 'i' || w[i] == 'o' || w[i] == 'u' || w[i] == 'A' || w[i] == 'E' || w[i] == 'I' || w[i] == 'O' || w[i] == 'U'){
                    sumv += (int)(w[i]);
                }
                sumt +=(int)(w[i]);
            }
            return sumt-sumv;
        }
        
        virtual float* val(short *len)= 0;
        virtual ostream& put(ostream & os)const{
            os << "w=" << w << ", par=" << par <<" ";
            return os;
        }
};


class B:public A{
    private:
        string str;
    public:
        B(string s, short n):A(s,n){
            this-> str="";
            for(int i=0; i<s.length(); i++){
                if(s[i] != 'a' || s[i] != 'e' || s[i] != 'i' || s[i] != 'o' || s[i] != 'u' || s[i] < '0' || s[i] > '9'){
                    this->str += s[i];
                }
            }
        }
        
        float* val(short *len){
            float *arr = new float[str.length()];
            for(int i= 0; i< str.length(); i++){
                arr[i]= (int)(str[i])/(float)(par);
            }
            *len = str.length();
            return arr;
        }
        
        ostream& put(ostream & os)const{
            os << "Class 1B: ";
            A::put(os);
            os << "{ str=" << str << "}"<< endl;
            
            return os;
        }
        
};


class C: public A{  
    private:
        float x;
        string sc;
    public:
        C(string s, short n): A(s,n){
            x= (float)(abs(sin(((s.length())/(float)(par)))));
            int lung= (x*n)+0.5;
            sc = s.substr(0,lung);
        }
        
        float * val(short *len){
            float * arry =new float[sc.length()];
            for(int i= 0; i<sc.length(); i++){
                arry[i]= log((int)(sc[i])/x);
            }
            *len= sc.length();
            return arry;
        }
        
        bool moreThan(float y){
            return (x >= y);
        }
        
        ostream& put(ostream & os)const{
            os << "Class 1C: ";
            A::put(os);
            os << "{ x=" << x << ", sc=" << sc << "}" << endl;
            
            return os;
        }
};


ostream & operator <<(ostream & os, const A& a){
    return a.put(os);
}



int main(){
    srand(111222333);
    A* vett[DIM];
    short r,r1,select;
    int l ;
    string str;
    for(int i=0; i<DIM; i++){
        str = "";
        r = rand()%5+5;
        r1 = rand()%2;
        l = rand()%8+5;
        for(int j =0;  j<l ;  j++){
            select = rand()%3;
            switch(select){
                case 0:
                    str+=(char)('a' + rand()%25);
                    break;
                case 1:
                    str+=(char)('0' + rand()%10);
                    break;
                case 2:
                    str+=(char)('A'+ rand()%25);
                    break;
                
            }
            if(r1)vett[i] = new B(str,r);
            else vett[i] = new C(str,r);
            
        }
        
    }
    
    for(int i= 0; i<DIM; i++){
        cout << i <<")";
        cout << *vett[i];
        cout << "getSum()=" << (*vett[i]).getSum() << endl;
    }
    
    cout << "Punto II (valori medi degli array):" << endl;
    for(int i= 0; i<DIM; i++){
        short * dim = new short;
        float sum = 0;
        float media = 0;
        ((vett[i])->val(dim));
        for(int j=0; j<*dim; j++){
            sum += ((((vett[i])->val(dim)))[j]);
        }
        media = sum / *dim ;
        cout << media << " ";
    }
    
    cout << ";" << endl;
    
    
    cout << "Punto III (indici degli elementi per cui moreThan(0.9) vale true)" << endl;
    
    for(int i= 0; i<DIM ; i++){
        C* ptr = dynamic_cast <C*> (vett[i]);
        if (ptr){
            if(ptr->moreThan(0.9)) cout << i << " "; 
        }
    }
    
    cout << ";" << endl;
    
    return 0;
    
    
}
