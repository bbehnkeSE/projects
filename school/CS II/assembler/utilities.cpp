////////////////////////////////////////////////////////////
// Brian Behnke
// cs23001
// 11/5/2011
//
// CPP file for infix to postfix 
//

#include "utilities.hpp"

String postfix(String infix) {
  std::vector<String> token = infix.split(' ');
  String right, left, oper;
  stack<String> conversion;
  int i = 0;
  while(token[i] != ';') {
    if(token[i] == ')') {
      right = conversion.pop();
      oper  = conversion.pop();
      left  = conversion.pop();
      conversion.push(left + ' ' + right + ' ' + oper);
    } 
    else if(token[i] != '(') { 
      conversion.push(token[i]); 
    }
    ++i;
  }
  return conversion.pop();
}

String prefix(String infix) {
  std::vector<String> token = infix.split(' ');
  String right, left, oper;
  stack<String> conversion;
  int i = 0;
  while(token[i] != ';') {
    if(token[i] == ')') {
      right = conversion.pop();
      oper  = conversion.pop();
      left  = conversion.pop();
      conversion.push(oper + ' ' + left + ' ' + right);
    }
    else if(token[i] != '(') {
      conversion.push(token[i]);
    }
    ++i;
  }
  return conversion.pop();
}

std::ostream& assembler(std::ostream& ass_embly, String postFix) {
  std::vector<String> token = postFix.split(' ');
  String right, left;
  stack<String> converter;
  int tmpVar = 1;
  int i = 0;
  while(token[i] != ';') {
    if(token[i] != '+' && token[i] != '-' && token[i] != '*' && token[i] != '/')  
      converter.push(token[i]);
    else {
      right = converter.pop();
      left  = converter.pop();
      converter.push(evaluate(left, token[i], right, ass_embly, tmpVar++));
    }
    ++i;
  }
  return ass_embly;
}

String evaluate(String left, String t, String right, std::ostream& ass_embly, int tmpVar) {
  String result("TMP");
  if(t == '+') { t = "AD"; }
  if(t == '-') { t = "SB"; }
  if(t == '*') { t = "MU"; }
  if(t == '/') { t = "DV"; }
  ass_embly << "LD     "    << left   << std::endl
	    << t << "     " << right  << std::endl
	    << "ST     TMP" << tmpVar << std::endl;
  return result + toString(tmpVar);
}

String toString(int a) {
  String result;
  while(a != 0) {
    int tmp = a % 10;
    a /= 10;
    char ch = tmp + '0';
    result = String(ch) + result;
  }
  return result;
}
