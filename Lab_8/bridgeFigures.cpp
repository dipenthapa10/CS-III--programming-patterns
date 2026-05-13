// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// abstract body
class Fill
{
public:
   Fill(char border, char internal) : borderChar(border), internalChar(internal) {}
   virtual char getBorder() = 0;
   virtual char getInternal() = 0;
   virtual ~Fill() {}

protected:
   char borderChar;
   char internalChar;
};

// concrete body
class Hollow : public Fill
{
public:
   Hollow(char border, char internal) : Fill(border, internal) {}
   char getBorder() override { return borderChar; }
   char getInternal() override { return ' '; }
   ~Hollow() override {}
};

// another concrete body
class Filled : public Fill
{
public:
   Filled(char border, char internal) : Fill(border, internal) {}
   char getBorder() override { return borderChar; }
   char getInternal() override { return internalChar; }
   ~Filled() override {}
};

// abstract handle
class Figure
{
public:
   Figure(int size, Fill *fill) : size_(size), fill_(fill) {}
   virtual void draw() = 0;
   virtual ~Figure() {}

protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square : public Figure
{
public:
   Square(int size, Fill *fill) : Figure(size, fill) {}
   void draw() override;
};

class FullyFilled : public Filled
{
public:
   FullyFilled(char border, char internal) : Filled(border, internal) {}
};

class RandomFilled : public Fill
{
public:
   RandomFilled(char charOne, char charTwo) : Fill(charOne, charTwo) {}

   char getBorder() override
   {
      if (rand() % 2 == 0)
         return borderChar;
      else
         return internalChar;
   }

   char getInternal() override
   {
      if (rand() % 2 == 0)
         return borderChar;
      else
         return internalChar;
   }
};

void Square::draw()
{
   for (int i = 0; i < size_; ++i)
   {
      for (int j = 0; j < size_; ++j)
         if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
            cout << fill_->getBorder();
         else
            cout << fill_->getInternal();
      cout << endl;
   }
}

int main()
{

   Fill *hollowPaintStar = new Hollow('*', ' ');
   Fill *filledPaintJ = new Filled('j', '-');
   Fill *randomPaint = new RandomFilled('@', '$');
   Fill *fullyFilled = new FullyFilled('f', 'f');

   Figure *smallBox = new Square(24, hollowPaintStar);
   Figure *bigBox = new Square(40, filledPaintJ);
   Figure *randomBox = new Square(7, randomPaint);
   Figure *fullyFilledBox = new Square(7, fullyFilled);

   smallBox->draw();
   cout << endl;
   bigBox->draw();
   cout << endl;
   randomBox->draw();
   cout << endl;
   fullyFilledBox->draw();
   cout << endl;

   // ask user for figure parameters
   // cout << "Enter fill character: ";
   // char fchar;
   // cin >> fchar;

   char borderChar, internalChar;
   cout << "Enter border character: ";
   cin >> borderChar;
   cout << "Enter internal character: ";
   cin >> internalChar;
   cout << "Choose: Filled, hollow, randomly filled, or fully filled? [f/h/r/F] ";
   char ifFilled;
   cin >> ifFilled;
   cout << "Enter size: ";
   int size;
   cin >> size;
   /*
   Figure *userBox = new Square(size, ifFilled == 'f'?
          static_cast<Fill *>(new Filled(fchar)):
          static_cast<Fill *>(new Hollow(fchar))
          );
   */

   /*
   Figure *userBox = new Square(size, ifFilled == 'f'?
          new Filled(fchar):
          new Hollow(fchar)
          );
   */

   // Figure *userBox = ifFilled == 'f' ? new Square(size, new Filled(fchar)) : new Square(size, new Hollow(fchar));

   Figure *userBox;
   if (ifFilled == 'f')
   {
      userBox = new Square(size, new Filled(borderChar, internalChar));
   }
   else if (ifFilled == 'h')
   {
      userBox = new Square(size, new Hollow(borderChar, internalChar));
   }
   else if (ifFilled == 'r')
   {
      userBox = new Square(size, new RandomFilled(borderChar, internalChar));
   }
   else if (ifFilled == 'F')
   {
      userBox = new Square(size, new FullyFilled(borderChar, internalChar));
   }

   userBox->draw();
   cout << endl;
}
