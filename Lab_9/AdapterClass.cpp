// figures: class adapter pattern
// Mikhail Nesterenko
// 11/7/2022

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// adaptee/implementer
class LegacyRectangle
{
public:
   LegacyRectangle(int topLeftX,
                   int topLeftY,
                   int bottomRightX,
                   int bottomRightY) : topLeftX_(topLeftX),
                                       topLeftY_(topLeftY),
                                       bottomRightX_(bottomRightX),
                                       bottomRightY_(bottomRightY) {}

   void oldDraw() const
   {
      for (int i = 0; i < bottomRightY_; ++i)
      {
         for (int j = 0; j < bottomRightX_; ++j)
            if (i >= topLeftY_ && j >= topLeftX_)
               cout << '*';
            else
               cout << ' ';
         cout << endl;
      }
   }

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)
   {
      topLeftX_ = topLeftX;
      topLeftY_ = topLeftY;
      bottomRightX_ = bottomRightX;
      bottomRightY_ = bottomRightY;
   }

   int getTopLeftX() const
   {
      return topLeftX_;
   }

   int getTopLeftY() const
   {
      return topLeftY_;
   }
   int getBottomRightX() const
   {
      return bottomRightX_;
   }
   int getBottomRightY() const
   {
      return bottomRightY_;
   }
   // defining top/left and bottom/right coordinates
private:
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// target interface
class Square
{
public:
   virtual void draw() const = 0;
   virtual ~Square() {}
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Square,
                      private LegacyRectangle
{
public:
   SquareAdapter(int size) : LegacyRectangle(0, 0, size, size) {};
   void draw() const override
   {
      oldDraw();
   }

   int size() const
   {
      return getBottomRightX() - getTopLeftX();
   }

   void resize(int newSize)
   {
      move(getTopLeftX(), getTopLeftY(), getTopLeftX() + newSize, getTopLeftY() + newSize);
   }
};

int main()
{
   // Square *square = new SquareAdapter(12);
   // square->draw();

   int initialSize;
   cout << "Enter the initial square size: ";
   cin >> initialSize;
   SquareAdapter square(initialSize);
   square.draw();

   int newSize;
   cout << "Enter the new square size: ";
   cin >> newSize;

   square.resize(newSize);
   square.draw();
}
