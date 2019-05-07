#include <iostream>
#include <string>
#include <cstdlib>
#define DIM 30


using namespace std;


class A{
    private:
        string w;
    
    public:
        A(string s): w(s){};
        int getSum(){
            
            int somma= 0;
            
            for(unsigned int j=0; j< w.length(); j++){
                int counter = 0;
                for(unsigned int i=0; i < w.length(); i++){
                    if(w[i] == w[j]){
                        counter ++;
                    }
                }
                if(counter >= 2){
                    somma += static_cast <int> (w[j]);
                }
            }
            
            return somma + 1;
        }
           
        virtual int* values()=0;
        
        virtual ostream& put(ostream & os)const{
            os << "w="  << w << "   ";
            return os;
        }
};


class B: public A{
    private:
        string s;
        int l;
    public:
        B(string s1, string s2, short n): A(s1.substr(0,n) + s2.substr(s2.length()-n)){
            if(s1.length()< s2.length()){
                for(int i= 0; i< s1.length(); i++){
                    s+= s1[i];
                    s+= s2[i];
                    
                }
                l = (s1.length()*2) -1;
            }
            else if(s1.length() > s2.length()){
                for(int i= 0; i< s2.length(); i++){
                    s+= s1[i];
                    s+= s2[i];
                }
                this->l = (s2.length()*2);
            }
        }
        
        int* values(){
            int *Array = new int[l];
            for(int i= 0; i<l; i++){
                Array[i]= ((int)(s[i]))%10;
            }
            return Array;
        }
        
        float res(){
            int somma = 0;
            for(int i= 0; i<l; i++){
                somma += *(values());
            }
            return somma / (float)(getSum());
        }
        ostream & put(ostream & os)const{
            os << "Class B: ";
            A::put(os);
            os << "s=" << s << "    l=" << l;
            return os;
        }
};


class C: public A{
    private:
        string t;
        int n;
    public:
        C(string s): A(s){
            
            for(int i= 0; i<s.length(); i++){
                if(s[i]>= 'a' && s[i] <= 'z'){
                    this->t+= (char)((int)(s[i])-32);
                }
                else if(s[i]>= 'A' && s[i] <= 'Z'){
                    this->t+= (char)((int)(s[i])+32);
                }
                else t+= s[i];
            }
            this->n = (this->t).length();
        }
        
        int* values(){
            int* Array = new int[this->n];
            for(int i= 0; i<this->n; i++){
                if(this->t[i] >= '0' && this->t[i] <= '9'){
                    Array[i] = 0;
                }
                else Array[i] = 1;
            }
            return Array;
        }
        
        short zeros(){
            short counter= 0;
            for(int i= 0; i<this->n; i++){
                if((values())[i] == 0) counter++;
            }
            return counter;
        }
        
        ostream& put(ostream & os)const{
            os << "Class C: ";
            A::put(os);
            os << "t=" << t << "   n=" << n;
            return os;
        }
};

ostream & operator <<(ostream & os, const A& a ){
    return a.put(os);
}





int main(){
    
    A* vett[DIM];
    srand(111222333);
    for ( int i=0; i<DIM ; i++){
        string str1 = "" ; 
        string str2 = "" ;
        if ( rand()%2==0){
            short l1 = rand()%5+3; short l2 = rand()%5+6;
            for( int j =0; j <l1 ; j++)
                str1 +=((char)('a' + rand()% 25 ));
            for (int j=0; j<l2 ; j++)
                str2 +=((char)('a'+rand()% 25));
            short n = rand()%3+1;
            vett[i] = new B(str1 , str2 , n );
        }
        else{
            for(int j=0; j<10; j++){
                int r = rand();
                if(r%2==0)
                    str1 +=((char)('0'+rand()% 9));
                else if(r%3==0)
                    str1 +=((char)('a'+rand()% 25));
                else
                    str1 +=((char)('A'+rand()% 25));
            }
            vett[i] = new C(str1);
        }
    }
    
    
    for(int i= 0; i< 18; i++){
        cout << i << ")";
        cout << *vett[i] << "   res="<< ((B*)(vett[i]))->res() << endl;
    }
    for(int i= 18; i< DIM; i++){
        cout << i << ")";
        cout << *vett[i]<< endl;
    }
    cout << "obj di tipo C con zeros() >= 7 :";
    for(int i=0; i<DIM; i++){
        C* ptr = dynamic_cast <C*>(vett[i]);
        if(ptr){
            if((*ptr).zeros() >= 7) cout << i << ", ";
        }
    }
    int max= 0;
    int min= 99999;
    int sum= 0;
    int n=0;
    for(int i= 0; i<DIM; i++){
        B* ptr_b = dynamic_cast <B*>(vett[i]);
            if(ptr_b){
                n++;
                if((*ptr_b).getSum() > max) max = (*ptr_b).getSum();
                if((*ptr_b).getSum() < min) min = (*ptr_b).getSum();
                sum += (*ptr_b).getSum();
            }
    }
    cout << endl;
    cout << "getSum:"<<endl;
    cout << "max=" << max <<endl;
    cout << "min=" << min <<endl;
    cout << "media= " << sum/static_cast <double>(n) << endl;
    
    return 0;
}
