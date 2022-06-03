// figures: object adapter pattern
// Mikhail Nesterenko, Brian Behnke
// 11/3/2021

#include <iostream>

using std::cout; using std::endl;

// base interface
class Figure {
public:
   virtual void resize(int) {};
   virtual void draw()=0;
   virtual ~Figure(){}
};

// implementer/adaptee
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
            int topLeftY, 
		      int bottomRightX, 
            int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

    void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        topLeftX_ = topLeftX;
        topLeftY_ = topLeftY;
        bottomRightX_ = bottomRightX;
        bottomRightY_ = bottomRightY;
    }

    int getTopLeftX()     const { return topLeftX_; }
    int getTopLeftY()     const { return topLeftY_; }
    int getBottomRightX() const { return bottomRightX_; }
    int getBottomRightY() const { return bottomRightY_; }

   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
         for(int j=0; j < bottomRightX_; ++j)
            if( i >= topLeftY_ && j>= topLeftX_ )
               cout << '*';
            else
               cout << ' ';
         cout << endl;
      }
   }
private: // defining top/left and bottom/right coordinates 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses composition to delegate 
// requests to adaptee
class SquareAdapter: public Figure{
public:
   SquareAdapter(int size){
      adaptee_= new LegacyRectangle(0,0,size,size);
   }
   void draw() override {
      adaptee_->oldDraw();
   }
   void resize(int newSize) override {
       adaptee_->move(0, 0, newSize, newSize);
   }
   int size() const {
       return adaptee_->getBottomRightX();
   }
private:
   LegacyRectangle *adaptee_;
};


int main(){
    std::cout << "Enter size of square: ";
    int size; std::cin >> size;

    Figure *square = new SquareAdapter(size);
    square->draw();

    std::cout << "Enter new size of square: ";
    int nSize; std::cin >> nSize;
    square -> resize(nSize);
    square -> draw();
}
