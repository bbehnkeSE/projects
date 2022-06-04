// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko, Brian Behnke
// 11/3/2021

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char borderChar, char internalChar):borderChar_(borderChar), internalChar_(internalChar){}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char borderChar_, internalChar_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char borderChar):Fill(borderChar, ' '){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~Hollow(){}
};


// another concrete body
class Filled: public Fill {
public:
   Filled(char borderChar):Fill(borderChar, borderChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~Filled(){}
};


// a third concrete body
class EnhancedFilled: public Fill {
public:
   EnhancedFilled(char borderChar, char internalChar):Fill(borderChar, internalChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return internalChar_;}
   ~EnhancedFilled(){}
};


// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){

   /*
   Fill* hollowPaintY = new Hollow('Y');
   Fill* filledPaintStar = new Filled('*');

   
   Figure *smallBox = new Square(6, filledPaintStar);
   Figure *bigBox = new Square(10, hollowPaintY);

   smallBox->draw();
   cout << endl;
   bigBox -> draw();
   */
   
   // ask user for figure parameters
   cout << "Enter fill character: "; 
            char fchar; cin >> fchar;
   cout << "Filled, hollow, enhanced filled, or all three? [f/h/e/a] "; 
           char ifFilled; cin >> ifFilled;
   
   char internal;
   if(ifFilled == 'e' || ifFilled == 'a') {
      cout << "Enter internal character: ";
      cin >> internal;
   }
   cout << "Enter size: "; int size; cin >> size;

   /*
   Figure *userBox = new Square(size, ifFilled == 'f'? 
	       static_cast<Fill *>(new Filled(fchar)):
	       static_cast<Fill *>(new Hollow(fchar))
	       ); 
   */  

   /*
   Figure *userBox = new Square(size,
	       ifFilled == 'f'? new Filled(fchar): new Hollow(fchar)
               );
   */
   
   /*
   Figure *userBox = ifFilled == 'f'?
      new Square(size, new Filled(fchar)):
      new Square(size, new Hollow(fchar));
   */

   Figure *userBox;
   if(ifFilled == 'f') { userBox = new Square(size, new Filled(fchar)); }
   if(ifFilled == 'h') { userBox = new Square(size, new Hollow(fchar)); }
   if(ifFilled == 'e') { userBox = new Square(size, new EnhancedFilled(fchar, internal)); }
   if(ifFilled == 'a') {
      userBox = new Square(size, new Filled(fchar));
      std::cout << "\nFilled:\n";
      userBox->draw(); cout << endl;

      std::cout << "Hollow:\n";
      userBox = new Square(size, new Hollow(fchar));
      userBox->draw(); cout << endl;

      std::cout << "Enhanced:\n";
      userBox = new Square(size, new EnhancedFilled(fchar, internal));
      userBox->draw(); cout << endl;
   }
   else {
      userBox -> draw();
      cout << endl;
   }

   return 0;
}