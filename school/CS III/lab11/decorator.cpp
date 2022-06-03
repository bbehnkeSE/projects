// decorator pattern illustration using HTML 
// Mikhail Nesterenko
// 10/31/2019

#include <string>
#include <iostream>

using std::cout; using std::endl;
using std::string;

// component
class Paragraph{
public:
   virtual string getHTML() const =0;
};


// concrete component
class Text: public Paragraph{
public:
   Text(const string& text=""): text_(text){}
   string getHTML() const override {return text_;} 
private:
   const string text_;
};


// first decorator
class BoldParagraph : public Paragraph {
public:
   BoldParagraph(const Paragraph* wrapped): 
      wrapped_(wrapped) {}
   string getHTML() const override {
      return "<b>" + wrapped_->getHTML() + "</b>";
   }
private:
  const Paragraph *wrapped_;
};


// second decorator
class ItalicParagraph : public Paragraph {
public:
   ItalicParagraph(const Paragraph* wrapped):
      wrapped_(wrapped) {}
   string getHTML() const override {
      return "<i>" + wrapped_->getHTML() + "</i>";
   }
private:
   const Paragraph *wrapped_;
};


int main(){
   Text p("Hello, World!");
   Text q("Good bye, World!");
   
   cout << p.getHTML() << endl;
   cout << q.getHTML() << endl;
   cout << endl;

   // illustrates per-object application of decoration
   BoldParagraph bp(&p);
   ItalicParagraph iq(&q);
   cout << bp.getHTML() << endl;
   cout << iq.getHTML() << endl;
   cout << endl;

   ItalicParagraph iiq(&iq);
   cout << iiq.getHTML() << endl;
   cout << endl;

   // complex decorators
   BoldParagraph bip(&iq); 
   cout << bip.getHTML() << endl;
   cout << endl;

   ItalicParagraph ibp(&bp); 
   cout << ibp.getHTML() << endl;
   cout << endl;

   // dynamic decorator
   cout << BoldParagraph(&p).getHTML() << endl;
   cout << endl;

  
   // dynamic complex decorator
   cout << BoldParagraph(new ItalicParagraph(&bp)).getHTML() << endl;
   cout << ItalicParagraph(&bp).getHTML() << endl;

}