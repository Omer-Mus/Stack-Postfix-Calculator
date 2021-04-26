/****************************************************/
// Programmer:Omer Mustel                           
// Date:      Oct 21, 2020                          
// Purpose:  Program to test Stack class            
// Input: none;                                     
// Output: the top of one stack.                    
/****************************************************/

#include "StackL.cpp"
#include <string>
//****************prototype****************

int precedence(char);
double applyOperation(double, double, char);
void evaluateExp1(Stack<char> &);
void evaluateExp(string);
//****************************************************
//****************************************************
int main() 
{
  Stack<char> infix;
  string expression;
   
  cout<< "\nPlease write your arithmetic expression:\n";
  getline(cin,expression);

  //insert the expression into the stack, without spaces.
  for (int i = 0; i < expression.size(); i++)
  {
    while (isspace(expression[i]))
      i++;
      char exp = expression[i];
    infix.push(exp);
  }
  
  cout << expression << " = ";
  evaluateExp1(infix);
  
  //try 2
  //string expression;
   
  cout<< "\nPlease write your arithmetic expression:\n";
  getline(cin,expression);

  cout << expression << " = ";
  evaluateExp(expression);
  return 0;
}
/****************************************************/
//precedence function
//Test for the presedence of the the symbol
/****************************************************/
int precedence(char symbol)
{
  if(symbol == '*'||symbol == '/')
    return 2;
  else if(symbol == '+' || symbol == '-')
    return 1;
  return 0;
}

/****************************************************/
//applyOp function
//applying operation by checking the operation char
/****************************************************/
double applyOperation(double a, double b, char operation)
{ 
  switch(operation)
  {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;        
    default:
      cout << "Invalid input: " << operation;
      cout << "\nprogram terminated.";
      exit(0);
      return 0;
  } 
}
 
/****************************************************/
//evaluateExp1 function - try1
//evaluating the expression using a stack, precedence 
//function, and applyOp function.
/****************************************************/

void evaluateExp1(Stack<char> &l)
{ 
    Stack<double> values;    //store numbers
    Stack<char> ops;     //store operators

    while (l.getLength() != 0) //loop until empty
    { //store the top in a char
      char value = l.getTop(); 
      l.pop();  

      if(isdigit(value)) //if it's a number
      {
        //string multinum(1, value);
        double num = (value-'0');
        double iter = 10;
        //if its a multi digit number
        while(isdigit(l.getTop()))
        {
          double temp = (l.getTop()-'0');
          num += (temp * iter);
          iter *= 10;
          l.pop();
        }
        values.push(num);
      }
      else
      {
        if(value == '(') //case 1
        {
          while(ops.getTop() != ')')
          {
            double num = values.getTop();
            values.pop();
            double num1 = values.getTop();
            values.pop();
            char sign = ops.getTop();
            ops.pop();
            values.push(applyOperation(num, num1, sign));
          } ops.pop(); //pop the closing brace
        }
        else //case 2
        {
          if(!isdigit(l.getTop()) && value == '-') //create a negative number if needed
          {
            double getNegative = values.getTop() * (-1);
            values.pop();
            values.push(getNegative);
          }
          else
          {
            if(precedence(value) >= precedence(ops.getTop()) || ops.isEmpty() || value == ')')
              ops.push(value);
            else
            {
              double num = values.getTop();
              values.pop();
              double num1 = values.getTop();
              values.pop();
              char symbol = ops.getTop();
              ops.pop();
              values.push(applyOperation(num, num1, symbol));
              ops.push(value);
            }
          }
        }
      }  
    } 
    while (!ops.isEmpty())
    {
      double num = values.getTop();
      values.pop();
      double num1 = values.getTop();
      values.pop();
      char symbol = ops.getTop();
      ops.pop();
      values.push(applyOperation(num, num1, symbol));
    }
    if (values.getLength() >= 1) //if there are extra item left.
    {
      double num = values.getTop();
      values.pop();
      double num1 = values.getTop();
      values.push(applyOperation(num, num1, '+'));
    }
    cout << values.getTop(); 
}

/****************************************************/
//evaluateExp function - try2
//evaluating the expression using a stack, precedence 
//function, and applyOp function.
/****************************************************/
void evaluateExp(string exp)
{
  int i;
     
  // valuex stack - store integer values.
  Stack <double> values;
     
  // ops stack - store operators.
  Stack <char> ops;
     
  for(int i = 0; i < exp.length(); i++)
  {
         
      // If the current char is an opening 
      // brace, push it to ops stack
      if(exp[i] == '(')
      {
        while(exp[i] == ')' && !isdigit(exp[i]))
        {
          ops.push(exp[i]);
          i++;
        }
      }
      // If current char is a number, push 
      // it to stack for numbers.
      else if(isdigit(exp[i]))
      {
        double val = 0;
           
        // There may be more than one
        // digits in the number
        while(isdigit(exp[i]))
        {
            val = (val*10) + (exp[i] -'0');
            i++;
        }
           
          values.push(val);
             
          // decrease the value of i by 1 to
          // correct the index.
          i--;
      }
         
      // Else if closing brace is in the stack, solve 
      // entire brace.
      else if(exp[i] == ')')
      {
          while(!ops.isEmpty() && ops.getTop() != '(')
          {
              double val2 = values.getTop();
              values.pop();
               
              double val1 = values.getTop();
              values.pop();
               
              char op = ops.getTop();
              ops.pop();
                 
              values.push(applyOperation(val1, val2, op));
          }
             
          // pop opening brace.
          if(!ops.isEmpty())
             ops.pop();
      }
         
      // Else current exp is an operator.
      else
      {
        // While ops.getTop() stack has same or greater 
        // precedence to current exp, which
        // is an operator. Apply operator on top 
        // of ops stack to top two elements in values stack.
        while(!ops.isEmpty() && precedence(ops.getTop())
        >= precedence(exp[i]))
          {
            double val2 = values.getTop();
            values.pop();
                 
            double val1 = values.getTop();
            values.pop();
               
            char op = ops.getTop();
            ops.pop();
                 
            values.push(applyOperation(val1, val2, op));
          }
             
          // Push current exp to ops stack.
          ops.push(exp[i]);
      }
  }
     
  // Entire expression has been parsed at this
  // point, apply remaining ops to remaining
  // values.
  while(!ops.isEmpty())
  {
    double val2 = values.getTop();
    values.pop();
                 
    double val1 = values.getTop();
    values.pop();

    char oper = ops.getTop();          
    ops.pop();
                 
    values.push(applyOperation(val1, val2, oper));
  }
     
    // Top of 'values' contains result, return it.
    cout << values.getTop();
}
