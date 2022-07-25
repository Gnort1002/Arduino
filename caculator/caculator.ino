#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 11, en = 12, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte rowPins[ROWS] = {6, 7, 8, 9}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int compare(String s1, String s2) {
  if (s1.length() == s2.length()) return s1.compareTo(s2);
  else return s1.length() - s2.length();
}

// Check invalid operator expression
int checkExp(String str) {
    return str.indexOf("+-") != -1 || str.indexOf("-+") != -1 || str.indexOf("++") != -1 || str.indexOf("--") != -1;
}

// Format string
String standalize(char c[], int n) {
  
  // Convert char array to string
  String str = "";
  for (int i = 0; i < n; i++) {
    str += c[i];
  }
  
  // Add 0 before positive or negative number if exists operator
  if (str[0] == '+' || str[0] == '-') {
    str = '0' + str;
  }
  
  // Reduce redundant operators
  while (checkExp(str)) {
    str.replace("++", "+");
    str.replace("+-", "-");
    str.replace("-+", "-");
    str.replace("--", "+");
  }
  return str;
}

// Convert string to double
double stringToDouble(String str) {
  
  // Reduce 0 at the first of the string
  while (str.length() > 1 && str[0] == '0') {
    str = str.substring(1);
  }
  
  // Convert to double
  int n = str.length();
  long long exp = 1;
  long long res = 0;
  for (int i = n-1; i >= 0; i--) {
    if (str[i] >= '0' && str[i] <= '9') {
      res += (str[i] - '0')*exp;
      exp *= 10;
    }
  }
  return (double)res;
}

String doubleToString(double value) {
  String str = String(value);
  Serial.println(str);
  while (str.indexOf(".") != -1) {
    int n = str.length();
    if (str[n-1] == '0' || str[n-1] == '.') str = str.substring(0, n-1);
    else break;
  }
  if (str.length() == 0) return "0";
  return str;
}

// Calculate 2 variables with 1 operator
double cal(double num1, double num2, char oper) {
  switch (oper) {
    case '+':
      return num1 + num2;
    case '-':
      return num2 - num1;
    case '*':
      return num1 * num2;
    case '/':
      return num2 / num1;
  }
}

int i = 0, clear = 0;
char customKey;
char res[16];

void errorString(String str) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str);
  lcd.setCursor(0,1);
  lcd.print("[C]: Restart");
  do {
    customKey = customKeypad.getKey();
    if (customKey == 'C') {
      lcd.clear();
      return;
    }
  }
  while (1);
}

// Main calculation
void calculate(char c[], int n) {
  
  // Format string
  String str = standalize(c, n);
  
  // Check error string
  if (str[0] == '*' || str[0] == '/') {
    errorString("Syntax ERROR!");
    return;
  }
  if (str[str.length()-1] < '0' || str[str.length()-1] > '9') {
    errorString("Syntax ERROR!");
    return;
  }
  for (int i = 0; i < str.length()-1; i++) {
    if (isOperator(str[i]) && isOperator(str[i+1])) {
      errorString("Syntax ERROR!");
      return;
    }
  }
  
  // Setup
  double numStack[16]; // number stack
  char opStack[16]; // operator stack
  int num = 0, op = 0; // for counting nodes in stack
  String tmp = ""; // for storing number before pushed to stack
  double num1, num2; // for calculate 2 variables
  char ope; // for extracting the operator
  
  // Using stack to calculate
  for (int i = 0; i < str.length(); i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      tmp += str[i];
    }
    else {
      if (stringToDouble(tmp) == -1) {
        errorString("Range ERROR!");
        return;
      }
      numStack[num++] = stringToDouble(tmp);
      tmp = "";
      if ((str[i] == '+' || str[i] == '-') && op != 0) {
        while (opStack[op-1] == '*' || opStack[op-1] == '/') {
          num1 = numStack[--num];
          num2 = numStack[--num];
          ope = opStack[--op];
          if (num1 == 0 && ope == '/') {
            errorString("Math ERROR!");
            return;
          }
          else numStack[num++] = cal(num1, num2, ope);
        }
      }
      opStack[op++] = str[i];
    }
  }
  if (tmp.length() != 0) {
    if (stringToDouble(tmp) == -1) {
      errorString("Range ERROR!");
      return;
    }
    numStack[num++] = stringToDouble(tmp);
  }
  
  double res;
  
  while (opStack[op-1] == '*' || opStack[op-1] == '/') {
    num1 = numStack[--num];
    num2 = numStack[--num];
    ope = opStack[--op];
    if (num1 == 0 && ope == '/') {
      errorString("Math ERROR!");
      return;
    }
    else numStack[num++] = cal(num1, num2, ope);
  }
  
  lcd.print("= ");
  
  if (op > 0) {
    int j = 0;
    res = numStack[j++];
    for (int i = 0; i < op; i++) {
      res = cal(numStack[j++], res, opStack[i]);
    }
    lcd.print(doubleToString(res));
  }
  else lcd.print(doubleToString(numStack[0]));  
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // Get key
  customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
  }
  // Check key to display in lcd
  if (customKey && i <= 16) {
    if (clear) {
      lcd.clear();
      i = 0;
      clear = 0;
    }
    if (customKey == 'C') {
      if (i != 0) {
        --i;
        lcd.setCursor(i,0);
        lcd.print(" ");
      }
    }
    else if (customKey == '=') {
      if (i != 0) {
        lcd.setCursor(0,1);
        calculate(res, i);
        clear = 1;
      }
    }
    else {
      if (i < 16) {
        res[i] = customKey;
        lcd.setCursor(i,0);
        lcd.print(customKey);
        i = i+1;
      }
    }        
  }
}
