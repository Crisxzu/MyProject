#include <iostream>
using namespace std;
class Polygone {
  protected:
    int width, height;
  public:
    void update (int a, int b){ 
    width = a; 
    height = b; 
  }
  
  	void afficheaire()
  	{
		cout << "affiche aire" << endl;
  	}
  	
  	virtual int aire()
  	{
  		
  	}
};
class Rectangle: public Polygone {
  public:
    int aire(){
    afficheaire();
    return width * height; 
  }
};
class Triangle: public Polygone {
  public:
    int aire(){
    afficheaire();
    return width * height/2; 
  }
};
int main () {
  Rectangle r;
  Triangle t;
  Polygone * p[2];
  p[0]= &r;
  p[1]= &t;
  p[0]->update(2,3);
  p[1]->update(2,3);
  
  cout << p[0]->aire() << endl;
  cout << p[1]->aire() << endl;
  
  return 0;
}
