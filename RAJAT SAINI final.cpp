#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>

using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ofstream outputFile("History.txt", ios::app);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR EXCEPTIONAL HANDLING
class ExceptionHandling
{
public:
    void checkException()
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            throw runtime_error("\n\t\tINVALID INPUT!! \n\t\tPLEASE ENTER A VALID INPUT!!");
        }
    }

    void checkBinary(int bin)
    {
        while(bin!=0)
        {
            if(bin<0)
            {
                throw invalid_argument("NOT A BINARY!!");
            }
            int last_digit = bin%10;
            if(last_digit>1)
            {
                throw invalid_argument("NOT A BINARY!!");
            }
            bin = bin/10;
        }
    }

    void checkOctal(char oct[30])
    {
        int len = strlen(oct);
        for(int i=0;i<len;i++)
        {
            if(oct[i] < '0' || oct[i] > '7')
            {
                throw invalid_argument("NOT AN OCTAL!!");
            }
        }
    }

    void checkLog(int number, int base)
    {
        if(number < 0 || base < 0 || base == 1)
        {
            throw invalid_argument("NOT A VALID LOG EXPRESSION!!");
        }
    }

    void checkRadius(double r)
    {
        if(r<=0)
        {
            //throw invalid_argument("This number cannot be negative.");
            throw invalid_argument("THIS NUMBER IS NOT VALID (OUT OF BOUND)!!");
        }
    }
    void checkDecimal(int num)
    {
        if(num<0)
        {
            //throw invalid_argument("This number cannot be negative.");
            throw invalid_argument("NEGATIVE NUMBERS NOT ALLOWED!!");
        }
    }
    void checkHexa(char num[30])
    {
         int len = strlen(num);
        for(int i=0;i<len;i++)
        {
            if (!isxdigit(num[i]))
            {
                throw invalid_argument("NOT HEXADECIMAL NUMBER!!");
            }
        }
    }

};
ExceptionHandling obj;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR - INHERITANCE: BASE AND DERIVED CLASSES
// Base class
class Operation {
public:
    virtual double calculate(double a, double b) {
        cout << "Base arithmetic operation." << endl;
        return 0.0;
    }
};

// Derived class 1: Addition
class Addition : public Operation {
public:
    double calculate(double a, double b) override {
        return a + b;
    }
};

// Derived class 2: Subtraction
class Subtraction : public Operation {
public:
    double calculate(double a, double b) override {
        return a - b;
    }
};

// Derived class 3: Multiplication
class Multiplication : public Operation {
public:
    double calculate(double a, double b) override {
        return a * b;
    }
};

// Derived class 4: Division
class Division : public Operation {
public:
    double calculate(double a, double b) override {
        if (b != 0.0) {
            return a / b;
        } else {
            throw invalid_argument("Division by zero");
            //return 0.0;
        }
    }
};

// Calculator class
class Calculator {
private:
    Operation* operation;

public:
    Calculator() {
        operation = nullptr;
    }

    ~Calculator() {
        delete operation;
    }

    void selectOperation() {
        int operationType;
        cout << "\nSELECT OPERATION TYPE: ";
        cout << "\n1: ADDITION";
        cout << "\n2: SUBTRACTION";
        cout << "\n3: MULTIPLICATION";
        cout << "\n4: DIVISION\n";
        cin >> operationType;

        // Create the appropriate derived class object based on user input
        if (operationType == 1) {
            operation = new Addition();
        } else if (operationType == 2) {
            operation = new Subtraction();
        } else if (operationType == 3) {
            operation = new Multiplication();
        } else if (operationType == 4) {
            operation = new Division();
        } else {
            cout << "Invalid operation type." << endl;
        }
    }

    void performCalculation() {
        if (operation == nullptr) {
            cout << "No operation selected." << endl;
            return;
        }

        double num1, num2;
        cout << "Enter two numbers: ";
        cin >> num1 >> num2;
        obj.checkException();


        // Perform the calculation based on the selected operation
        double result = operation->calculate(num1, num2);
        cout << "RESULT: " << result << endl;
        outputFile << "\n\nRESULT: " << result;
        //fprintf(fp,"\n\nRESULT: %lf",result);

    }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR - MULTIPLE INHERITANCE: TWO OR MORE BASE CLASSES
// Base class 1: LogarithmicCalculator
class LogarithmicCalculator {
public:
    double calculateLog(double number, double base) {
        return log(number) / log(base);
    }
};

// Base class 2: TrigonometricCalculator
class TrigonometricCalculator {
public:
    double calculateSin(double angle) {
        return sin(angle);
    }

    double calculateCos(double angle) {
        return cos(angle);
    }

    double calculateTan(double angle) {
        return tan(angle);
    }

    double calculateArcSin(double value) {
        return asin(value);
    }

    double calculateArcCos(double value) {
        return acos(value);
    }

    double calculateArcTan(double value) {
        return atan(value);
    }
};

// Child class: AdvancedCalculator
class AdvancedCalculator : public LogarithmicCalculator, public TrigonometricCalculator {
public:
    void performCalculations() {
        int choice;
        cout << "\nSELECT CALCULATION TYPE: \n";
        cout<<"\n1. LOGARITHMIC\n";
        cout<<"\n2. TRIGONOMETRIC\n";
        cin >> choice;

        if (choice == 1) {
            double number, base;
            cout << "Enter a number: ";
            cin >> number;
            obj.checkException();

            cout << "Enter the base: ";
            cin >> base;
            obj.checkException();
            obj.checkLog(number, base);

            double logResult = calculateLog(number, base);
            cout << "Log base " << base << " of " << number << " = " << logResult << endl;
            outputFile << "\n\nLog base " << base << " of " << number << " = " << logResult;
        }
        else if (choice == 2)
        {
            int trigChoice;
            cout <<"\nSELECT TRIGONOMETRIC FUNCTION: ";
            cout<<"\n1. Sin\n";
            cout<<"\n2. Cos\n";
            cout<<"\n3. Tan\n";
            cout<<"\n4. ArcSin\n";
            cout<<"\n5. ArcCos\n";
            cout<<"\n6. ArcTan\n";

            cin >> trigChoice;

            double angle;
            double value;
            double sinResult;
            double cosResult;
            double tanResult;
            double arcSinResult;
            double arcCosResult;
            double arcTanResult;

            switch (trigChoice)
            {
                case 1:
                    cout << "Enter an angle in radians: ";
                    cin >> angle;
                    obj.checkException();
                    sinResult = calculateSin(angle);
                    cout << "Sin(" << angle << ") = " << sinResult << endl;
                    outputFile << "\n\nSin(" << angle << ") = " << sinResult;
                    break;

                case 2:
                    cout << "Enter an angle in radians: ";
                    cin >> angle;
                    obj.checkException();
                    cosResult = calculateCos(angle);
                    cout << "Cos(" << angle << ") = " << cosResult << endl;
                    outputFile << "\n\nCos(" << angle << ") = " << cosResult;
                    break;

                case 3:
                    cout << "Enter an angle in radians: ";
                    cin >> angle;
                    obj.checkException();
                    tanResult = calculateTan(angle);
                    cout << "Tan(" << angle << ") = " << tanResult << endl;
                    outputFile << "\n\nTan(" << angle << ") = " << tanResult;
                    break;

                case 4:
                    cout << "Enter a value: ";
                    cin >> value;
                    obj.checkException();
                    arcSinResult = calculateArcSin(value);
                    cout << "ArcSin(" << value << ") = " << arcSinResult << endl;
                    outputFile << "\n\nArcSin(" << value << ") = " << arcSinResult;
                    break;

                case 5:
                    cout << "Enter a value: ";
                    cin >> value;
                    obj.checkException();
                    arcCosResult = calculateArcCos(value);
                    cout << "ArcCos(" << value << ") = " << arcCosResult << endl;
                    outputFile << "\n\nArcCos(" << value << ") = " << arcCosResult;
                    break;

                case 6:
                    cout << "Enter a value: ";
                    cin >> value;
                    obj.checkException();
                    arcTanResult = calculateArcTan(value);
                    cout << "ArcTan(" << value << ") = " << arcTanResult << endl;
                    outputFile << "\n\nArcTan(" << value << ") = " << arcTanResult;
                    break;

                default:
                    cout << "INVALID TRIGONOMETRIC FUNCTION CHOICE!!" << endl;
                    break;
            }
        }
        else
        {
            cout << "INVALID CHOICE." << endl;
        }
    }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR - OPERATOR OVERLOADING WITH LOCAL AND GLOBAL OPERATIONS
class Number {
    double value;

public:
    Number(double n) : value(n) {}

    double operator~() {
        return sqrt(value); // Square root calculation (local operator overload)
    }

    double operator^(double exponent) {
        return pow(value, exponent); // Exponential calculation (local operator overload)
    }

    long long operator!() {
        long long result = 1;
        for (int i = 2; i <= value; ++i) {
            result *= i;
        }
        return result; // Factorial calculation (local operator overload)
    }
};

class Menu {
private:
    int choice;
    double number;

public:
    int getUserChoice() {
        cout << "CHOOSE AN OPERATION TO PERFORM: " << endl;
        cout << "1. CALCULATE SQUARE ROOT" << endl;
        cout << "2. CALCULATE EXPONENTIAL" << endl;
        cout << "3. CALCULATE FACTORIAL" << endl;
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;
        return choice;
    }

    void getUserInput() {
        cout << "ENTER A NUMBER: ";
        cin >> number;
        obj.checkException();
    }

    void performOperation() {
        double result;
        double factorialResult;
        if (choice == 1) {
            obj.checkRadius(number);
            Number num(number);
            result = ~num; // Using the local operator overload (~) for square root
            cout << "Square root of " << number << " is: " << result << endl;
            outputFile << "\n\nSquare root of (" << number << ") is: " << result;
        } else if (choice == 2) {
            double exponent;
            cout << "Enter the exponent: ";
            cin >> exponent;
            obj.checkException();
            Number num(number);
            result = num ^ exponent; // Using the local operator overload (^) for exponential
            cout << number << " Raised to the power of " << exponent << " is: " << result << endl;
            outputFile << "\n\nRaised to the power of (" << exponent << ") is: " << result;
        } else if (choice == 3) {
            obj.checkRadius(number);
            Number num(number);
            factorialResult = !num; // Using the local operator overload (!) for factorial
            cout << "Factorial of " << number << " is: " << factorialResult << endl;
            outputFile << "\n\nFactorial of (" << number << ") is: " << factorialResult;
        } else {
            cout << "Invalid choice." << endl;
            return;
        }
    }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR NUMBER CONVERSIONS
class NumberConverter
{
private:

public:

    void askForConversion();
    void binToDec();
    void binToOct();
    void binToHex();
    void octToDec();
    void octToBin();
    void decToBin();
    void decToOct();
    void decToHex();
    void HexToDec();
    void HexToBin();
    void HexToOct();
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::askForConversion()
{
        int op = 0;
        cout << "Select type of Number Conversion\n";
        cout << "[1] Binary to Decimal\n";
        cout << "[2] Binary to Octal\n";
        cout << "[3] Binary to Hexadecimal\n";
        cout << "[4] Octal to Decimal\n";
        cout << "[5] Octal to Binary\n";
        cout << "[6] Decimal to Binary\n";
        cout << "[7] Decimal to Octal\n";
        cout << "[8] Decimal to Hexadecimal\n";
        cout << "[9] Hexadecimal to Decimal\n";
        cout << "[10] Hexadecimal to Binary\n";
        cout << "[11] Hexadecimal to Octal\n";
        cin >> op;

        switch(op)
        {
            case 1:
                binToDec();
                break;
            case 2:
                binToOct();
                break;
            case 3:
                binToHex();
                break;
            case 4:
                octToDec();
                break;
            case 5:
                octToBin();
                break;
            case 6:
                decToBin();
                break;
            case 7:
                decToOct();
                break;
            case 8:
                decToHex();
                break;
            case 9:
                HexToDec();
                break;
            case 10:
                HexToBin();
                break;
            case 11:
                HexToOct();
                break;
            default:
                cout << "INVALID OPTION SELECTED. PLEASE TRY AGAIN!!\n";
                askForConversion();
                break;
            }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::binToDec()
{
    int a[20], i, j, temp, flag = 0, sum = 0;
    int num;
    cout << "Enter Binary Number: ";
    cin >> num;

    obj.checkException();
    obj.checkBinary(num);
    i = 0;
    while (num)
    {
        temp = num % 10;
        num = num / 10;
        flag++;
        a[i] = temp;
        i++;
    }
    for (i = 0; i < flag; i++) {
        sum += (pow(2, i) * a[i]);
    }
    cout << "\nDecimal Number of Entered Binary Number is: " << sum << endl;
    outputFile << "\n\nDecimal Number of Entered Binary Number is: " << sum;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::binToOct()
{
    long int bi, oc = 0, i = 1, re;
    cout << "Enter Binary Number: ";
    cin >> bi;
    obj.checkException();
    obj.checkBinary(bi);

    while (bi != 0) {
        re = bi % 10;
        oc = oc + re * i;
        i = i * 2;
        bi = bi / 10;
    }
    cout << "\nOctal Number of Entered Binary Number is: " << oc << endl;
    outputFile << "\n\nOctal Number of Entered Binary Number is: " << oc;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::binToHex()
{
    int binaryNum, hex = 0, mul = 1, chk = 1, rem, i = 0;
    char hexDecNum[20];
    cout << "Enter Binary Number: ";
    cin >> binaryNum;
    obj.checkException();
    obj.checkBinary(binaryNum);

    while (binaryNum != 0) {
        rem = binaryNum % 10;
        hex = hex + (rem * mul);
        if (chk % 4 == 0) {
            if (hex < 10)
                hexDecNum[i] = hex + 48;
            else
                hexDecNum[i] = hex + 55;
            mul = 1;
            hex = 0;
            chk = 1;
            i++;
        }
        else {
            mul = mul * 2;
            chk++;
        }
        binaryNum = binaryNum / 10;
    }
    if (chk != 1)
        hexDecNum[i] = hex + 48;
    if (chk == 1)
        i--;
    cout << "\nHexadecimal Number of Entered Binary Number is: ";
    outputFile << "\n\nHexadecimal Number of Entered Binary Number is: ";

    for (i = i; i >= 0; i--)
    {
        cout << hexDecNum[i];
        outputFile << hexDecNum[i];
        //fprintf(fp,"%c",hexDecNum[i]);
    }
    cout << endl;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::octToDec()
{
    char num[30];
    int i, sum = 0, temp = 0;
    cout << "Enter Octal Number: ";
    cin >> num;
    obj.checkException();
    obj.checkOctal(num);

    int len = strlen(num);
    for (i = len - 1; i >= 0; i--) {
        sum += (pow(8, temp)) * (((int)num[i]) - 48);
        temp++;
    }
    cout << "\nDecimal Number of Entered Octal number is: " << sum << endl;
    outputFile << "\n\nDecimal Number of Entered Octal number is: " << sum;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::octToBin()
{
    char octnum[30];
    long i = 0;

    cout << "Enter Octal Number : ";
    cin >> octnum;
    obj.checkException();
    obj.checkOctal(octnum);

    string result = "";
    while (octnum[i]) {
        switch (octnum[i]) {
            case '0':
                result += "000";
                break;
            case '1':
                result += "001";
                break;
            case '2':
                result += "010";
                break;
            case '3':
                result += "011";
                break;
            case '4':
                result += "100";
                break;
            case '5':
                result += "101";
                break;
            case '6':
                result += "110";
                break;
            case '7':
                result += "111";
                break;
            default:
                cout << "\n Invalid octal digit " << octnum[i];
                outputFile << "\nInvalid octal digit " << octnum[i];

                return;
        }
        i++;
    }
    cout<<"Binary of Entered Octal Number is : "<<result;
    outputFile << "\n\nBinary of Entered Octal Number is: " << result;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::decToBin()
{
    int num,temp,i=0,bin[20];
    cout << "Enter Decimal Number : ";
    cin >> num;
    obj.checkException();
    obj.checkDecimal(num);

    while(num>0)
    {
        temp=num%2;
        bin[i++]=temp;
        num=num/2;
    }

    string result = "";
    for(int j=i-1;j>=0;j--)
    {
        result += to_string(bin[j]);
    }
    cout<<"Binary Number of Entered Decimal Number is : "<<result;
    outputFile << "\n\nBinary Number of Entered Decimal Number is: " << result;


}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::decToOct()
{
    int num,temp,i=0,octal[20];
    cout << "Enter Decimal Number : ";
    cin >> num;
    obj.checkException();
    obj.checkDecimal(num);

    while(num>0) {
        temp=num%8;
        num=num/8;
        octal[i]=temp;
        i++;
    }

    string result = "";
    for(int j=i-1;j>=0;j--) {
        result += to_string(octal[j]);
    }
    cout<<"Octal Number of Entered Decimal Number is : "<<result;
    outputFile << "\n\nOctal Number of Entered Decimal Number is: " << result;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::decToHex()
{
    int decimal, quot, rem;
    int i, j = 0;
    char hexa[50];
    cout << "Enter Decimal Number: ";
    cin >> decimal;
    obj.checkException();
    obj.checkDecimal(decimal);

    quot = decimal;
    while (quot != 0) {
        rem = quot % 16;
        if (rem < 10)
            hexa[j++] = 48 + rem;                                                                       //[Function for Decimal to Hexadecimal Conversions]
        else
            hexa[j++] = 55 + rem;
        quot = quot / 16;
    }
    cout << "\nHexadecimal Number of Entered Decimal Number is: ";
    outputFile << "\n\nHexadecimal Number of Entered Decimal Number is: ";

    // display integer into character
    for (i = j; i >= 0; i--)
    {
        cout << hexa[i];
        outputFile << hexa[i];
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::HexToDec()
{
    char num[30];
    int i,sum=0,temp=0;
    cout << "Enter HexaDecimal Number : ";
    cin >> num;
    obj.checkException();
    obj.checkHexa(num);

    int len=strlen(num);
    for(i=len-1;i>=0;i--)
        {
        if(num[i]=='A')
            sum+=(pow(16,temp))*10;
        else if(num[i]=='B')
            sum+=(pow(16,temp))*11;
        else if(num[i]=='C')
            sum+=(pow(16,temp))*12;                                                                      //[Function for Hexadecimal to Decimal Conversions]
        else if(num[i]=='D')
            sum+=(pow(16,temp))*13;
        else if(num[i]=='E')
            sum+=(pow(16,temp))*14;
        else if(num[i]=='F')
            sum+=(pow(16,temp))*15;
        else {
            sum+=(pow(16,temp))*(((int)num[i])-48);
             }
        temp++;
        }
    cout << "\nDecimal Number of Entered HexaDecimal Number is: " << sum;
    outputFile << "\n\nDecimal Number of Entered Hexadecimal Number is: " << sum;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::HexToBin()
{
    char num[30];
    int i, sum = 0, temp = 0, bin[30];
    cout << "Enter HexaDecimal Number : ";
    cin >> num;
    obj.checkException();
    obj.checkHexa(num);

    int len = strlen(num);
    for (i = len - 1; i >= 0; i--)
    {
        if (num[i] == 'A')
            sum += (pow(16, temp)) * 10;
        else if (num[i] == 'B')
            sum += (pow(16, temp)) * 11;
        else if (num[i] == 'C')
            sum += (pow(16, temp)) * 12;
        else if (num[i] == 'D')
            sum += (pow(16, temp)) * 13;
        else if (num[i] == 'E')
            sum += (pow(16, temp)) * 14;
        else if (num[i] == 'F')
            sum += (pow(16, temp)) * 15;
        else
            sum += (pow(16, temp)) * (((int)num[i]) - 48);
        temp++;
    }
    temp = 0;
    i = 0;
    while (sum > 0)
    {
        temp = sum % 2;
        bin[i++] = temp;
        sum = sum / 2;
    }
    cout << "\nBinary Number of Entered HexaDecimal Number is : ";
    outputFile << "\n\nBinary Number of Entered Hexadecimal Number is: ";
    for (int j = i - 1; j >= 0; j--)
    {
        cout << bin[j];
        outputFile << bin[j];
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void NumberConverter::HexToOct()
{
        char hex[30];
        int n;
        cout << "Enter Hexadecimal Number : ";
        cin >> hex;
        obj.checkException();
        obj.checkHexa(hex);

        int i,len, dec=0, oct=0;
        for(len=0; hex[len]!='\0'; len++);
        for(i=0; hex[i]!='\0'; i++,len--)
        {
         if(hex[i]>='0' && hex[i]<='9')
         {
         dec= dec + (hex[i]-'0')*pow(16,len-1);
         }
         if(hex[i]>='A' && hex[i]<='F')
         {
         dec = dec + (hex[i]-55)*pow(16,len-1);
         }
         if(hex[i]>='a' && hex[i]<='f')
         {
         dec = dec + (hex[i]-87)*pow(16,len-1);
         }
        }
        i=1;
        while(dec!=0)
        {
         oct = oct + (dec%8)*i;
         dec = dec/8;
         i = i*10;
        }
        cout << "\nOctal Number of Entered Hexadecimal Number is : " << oct << endl;
        outputFile << "\n\nOctal Number of Entered Hexadecimal Number is: " << oct;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR DYNAMIC MEMORY MANAGEMENT (NEW/DELETE)
//[CODE FOR MATRIX OPERATIONS]
class matrix
{

public:
int mainmenufun()
{
    cout << "\nEnter the operation you want to perform \n[1] (Addition)\n[2] (Subtraction)\n[3] (Multiplication)\n[4] (Transpose)\n[5] (Determinent)\n";
    int v;
    cin >> v;
    switch(v)
    {
        case 1: addition();
                break;

        case 2: subtract();
                break;

        case 3: multiply();
                break;

        case 4: transpose();
                break;

        case 5: determinent();
                break;

        default:
            cout << "Invalid choice" << endl;
    }

    return 0;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Function for Creation of matrix
double** createmat(int N)
{
    double** mat = new double*[N];
    for (int i = 0; i < N; i++)
    {
        mat[i] = new double[N];
    }

    cout << "Enter the matrix elements:\n"; // Entering the Matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
            obj.checkException();
        }
    }
    cout << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    return mat;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double** matadd(double** p, double** q, int N)
{
    int i, j;

    double** sum = new double*[N];
    for (int i = 0; i < N; i++)
    {
        sum[i] = new double[N];
    }

    // adding of two matrices
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            sum[i][j] = p[i][j] + q[i][j];
        }
    }

    // printing the result
    cout << "\nAddition of two matrices: \n";
    outputFile << "\n\nAddition of two matrices: \n";

    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            cout << sum[i][j] << "   ";
            outputFile << sum[i][j] << "   ";
            if (j == N - 1)
            {
                cout << "\n\n";
                outputFile << "\n\n";
            }
        }
    }

    return sum;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// [Function for Subtraction of matrix]
double** matsub(double** p, double** q, int N)
{
    int i, j;
    double** diff = new double*[N];

    for (i = 0; i < N; i++) {
        diff[i] = new double[N];
    }

    // Subtraction of two matrices
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            diff[i][j] = p[i][j] - q[i][j];
        }
    }

    // printing the result
    cout << "\nSubtraction of two matrices: \n"; //[Printing Result]
    outputFile << "\n\nSubtraction of two matrices: \n";

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            cout << diff[i][j] << "   ";
            outputFile << diff[i][j] << "   ";

            if (j == N - 1)
            {
                cout << "\n\n";
                outputFile << "\n\n";
            }
        }
    }

    return diff;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double **matmult(double **p, double **q, int N)
{
    int i, j, k;
    double **sum = new double*[N];

    for (i = 0; i < N; i++)
    {
        sum[i] = new double[N];
    }

    // Multiplication of two matrices
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            sum[i][j] = 0;
            for (k = 0; k < N; k++)
            {
                sum[i][j] += p[i][k] * q[k][j];
            }
        }
    }

    // Printing the result of multiplication
    cout << "\nMultiplication of two matrices: \n";
    outputFile << "\n\nMultiplication of two matrices: \n";     //[Printing Result]

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << sum[i][j] << "   ";
            outputFile << sum[i][j] << "   ";
            if (j == N - 1)
            {
                cout << "\n\n";
                outputFile << "\n\n";
            }
        }
    }

    return sum;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Transpose of matrix]
void mattrans(double **p, int N)
{
    int i, j;
    cout << "\nThe Transpose of the matrix:\n";
    outputFile << "\n\nThe Transpose of the matrix: \n";     //[Printing Result]

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            cout << p[j][i] << " ";
            outputFile << p[j][i] << "   ";
        }
        cout << endl;
        outputFile << "\n\n";
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Determinent of matrix]
void matdet(double **p, int N)
{
    double ratio;
    double det = 1;
    int i, j, k;

    /* (Her Gauss Elimination Technique is used for transforming matrix to upper triangular matrix */
    /* (Now Applying Gauss Elimination)*/
    for (i = 0; i < N; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            ratio = ((p[j][i]) /(p[i][i]));
            for (k = 0; k < N; k++)
            {
                p[j][k] = ((p[j][k])) - ((ratio * (p[i][k])));
            }
        }
    }

    /* (Displaying the upper triangular matrix) */

    /* (It is done just for better understanding) */

    /* (By analyzing upper triangular matrix we will get idea about the determinent) */
    cout << "\nUpper Triangular Matrix: \n";
    //fprintf(fp, "\nUpper Triangular Matrix: \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << fixed << (p[i][j]) << "\t";
        }
        cout << endl;
    }

    /* (Now finding determinant by multiplying elements in principal diagonal elements) */
    for (i = 0; i < N; i++)
    {
        det = ((det) * ((p[i][i])));
    }
    cout << "\n\nDeterminant of given matrix is: " << fixed << det;
    outputFile << "\n\nDeterminant of given matrix is: " << det;

}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for freeing the memory]
void freemat(double **p, double **q, double **x, int N)
{
    for(int i = 0; i < N; i++)
    {
        delete[] p[i];
        delete[] q[i];
        delete[] x[i];
    }

    delete[] p;
    delete[] q;
    delete[] x;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for freeing the memory]
void freemat2(double **p, int N)
{
    for(int i = 0; i < N; i++)
    {
        delete[] p[i];
    }
    delete[] p;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Addition of Matrices]
void addition()
{
    int N;
    cout << "Enter the size of 1st array: ";
    cin >> N;
    obj.checkException();
    obj.checkRadius(N);

    double **p = createmat(N);
    double **q = createmat(N);
    double **x = matadd(p,q,N);
    freemat(p,q,x,N);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Subtraction of Matrices]
void subtract()
{
    int N;
    cout << "\nEnter the size of 1st array: "; // Entering the 1st Matrix
    cin >> N;
    obj.checkException();
    obj.checkRadius(N);

    double** p = createmat(N);
    double** q = createmat(N);
    double** x = matsub(p, q, N);
    freemat(p, q, x, N);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Multiplication of Matrices]
void multiply()
{
    int N;
    cout << "\nEnter the size of 1st array: ";
    cin >> N;
    obj.checkException();
    obj.checkRadius(N);

    double** p = createmat(N);
    double** q = createmat(N);
    double** x = matmult(p, q, N);
    freemat(p, q, x, N);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Transpose of Matrix]
void transpose()
{
    int N;
    cout << "\nEnter the size of array: ";
    cin >> N;
    obj.checkException();
    obj.checkRadius(N);

    double** p = createmat(N);
    mattrans(p, N);
    freemat2(p, N);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//[Function for Determinent of Matrix]
void determinent()
{
    int N;
    cout << "\nEnter the size of array: ";
    cin >> N;
    obj.checkException();
    obj.checkRadius(N);

    double** p = createmat(N);
    matdet(p, N);
    freemat2(p, N);
}

};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR - POLYMORPHISM: ABSTRACT CLASSES AND VIRTUAL FUNCTIONS
// Abstract base class
class Shape {
public:
    // Pure virtual functions for area and circumference
    virtual double calculateArea() const = 0;
    virtual double calculateCircumference() const = 0;
    virtual ~Shape() {}
};

// Derived classes

class Square : public Shape {
private:
    double side;
public:
    Square(double side) : side(side) {}

    double calculateArea() const override {
        return side * side;
    }

    double calculateCircumference() const override {
        return 4 * side;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
public:
    Rectangle(double length, double width) : length(length), width(width) {}

    double calculateArea() const override {
        return length * width;
    }

    double calculateCircumference() const override {
        return 2 * (length + width);
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}

    double calculateArea() const override {
        return M_PI * radius * radius;
    }

    double calculateCircumference() const override {
        return 2 * M_PI * radius;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    Triangle(double base, double height) : base(base), height(height) {}

    double calculateArea() const override {
        return (base * height) / 2;
    }

    double calculateCircumference() const override {
        cout<<"\n PERIMETER OF A TRIANGLE CANNOT BE DETERMINED BY JUST BASE AND HEIGHT \n";
        return 0.0; // Triangle has no circumference
    }
};

// Base class
class ShapeCalculator {
public:
    void calculate() {
        int shapeChoice;
        cout << "\nSELECT THE SHAPE:\n";
        cout << "1. SQUARE\n";
        cout << "2. RECTANGLE\n";
        cout << "3. CIRCLE\n";
        cout << "4. TRIANGLE\n";
        cin >> shapeChoice;

        Shape* shape;

        switch (shapeChoice) {
            case 1:
                shape = createSquare();
                break;
            case 2:
                shape = createRectangle();
                break;
            case 3:
                shape = createCircle();
                break;
            case 4:
                shape = createTriangle();
                break;
            default:
                cout << "Invalid shape choice!\n";
                return;
        }

        int operationChoice;
        cout << "SELECT THE OPERATION:\n";
        cout << "1. CALCULATE AREA\n";
        cout << "2. CALCULATE CIRCUMFERENCE\n";
        cin >> operationChoice;

        double result;

        switch (operationChoice) {
            case 1:
                result = shape->calculateArea();
                cout << "AREA: " << result << endl;
                outputFile << "\n\nAREA: " << result;
                break;
            case 2:
                result = shape->calculateCircumference();
                cout << "CIRCUMFERENCE: " << result << endl;
                outputFile << "\n\nCIRCUMFERENCE: " << result;
                break;
            default:
                cout << "Invalid operation choice!\n";
        }

        delete shape;
    }

private:
    Square* createSquare() {
        double side;
        cout << "Enter the side length of the square: ";
        cin >> side;
        obj.checkException();
        return new Square(side);
    }

    Rectangle* createRectangle() {
        double length, width;
        cout << "Enter the length of the rectangle: ";
        cin >> length;
        cout << "Enter the width of the rectangle: ";
        cin >> width;
        obj.checkException();
        return new Rectangle(length, width);
    }

    Circle* createCircle() {
        double radius;
        cout << "Enter the radius of the circle: ";
        cin >> radius;
        obj.checkException();
        obj.checkRadius(radius);
        return new Circle(radius);
    }

    Triangle* createTriangle() {
        double base, height;
        cout << "Enter the base of the triangle: ";
        cin >> base;
        cout << "Enter the height of the triangle: ";
        cin >> height;
        obj.checkException();
        return new Triangle(base, height);
    }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CODE FOR - FILE MANAGEMENT
class History
{
public:
    void show()
    {
        cin.ignore();
        system("cls");
        ifstream file("History.txt");
        cout << "\n\n********************************************************************  (HISTORY)  ***************************************************************************\n";
        cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        if (!file) {
            cout << "ERROR: COULD NOT OPEN FILE History.txt";
        } else {
            char ch;
            while (file.get(ch)) {
                cout << ch;
            }
            file.close();
        }
    }
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    if (!outputFile)
    {
        cout << "Error: could not open file History.txt" << endl;
        return 1;
    }

    int again;
    int choice;

    do
    {
        cout<<"\n\n************************************************************  (SCIENTIFIC CALCULATOR)  *********************************************************************\n";
        cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        cout << "\t\t\t\t\t\t      SELECT ANY OF THE FOLLOWING OPERATIONS:\n" << endl;
        cout << "\t\t\t\t\t\t           1. ARITHMETIC OPERATIONS" << endl;
        cout << "\t\t\t\t\t\t           2. TRIGONOMETRIC FUNCTIONS & LOGARITHMIC FUNCTIONS" << endl;
        cout << "\t\t\t\t\t\t           3. SQUARE ROOT , EXPONENTIAL & FACTORIAL" << endl;
        cout << "\t\t\t\t\t\t           4. NUMBER CONVERSIONS" << endl;
        cout << "\t\t\t\t\t\t           5. MATRIX OPERATIONS" << endl;
        cout << "\t\t\t\t\t\t           6. SHAPE CALCULATIONS" << endl;
        cout << "\t\t\t\t\t\t           7. HISTORY" << endl;

        cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        cout <<"\t\t\t\t\t\t           ENTER YOUR CHOICE: ";
        cin >> choice;

        switch(choice)
        {
            case 1: {
                //CALL FOR ARITHMETIC OPERATIONS
                Calculator calculator;
                calculator.selectOperation();
                calculator.performCalculation();
                break;
            }

            case 2: {
                //CALL FOR TRIGONOMETRIC FUNCTIONS & LOGARITHMIC FUNCTIONS
                AdvancedCalculator calculator;
                calculator.performCalculations();
                break;
            }

            case 3: {
                //CALL FOR SQUARE ROOT , EXPONENTIAL & FACTORIAL
                Menu menu;
                menu.getUserChoice();
                menu.getUserInput();
                menu.performOperation();
                break;
            }

            case 4: {
                //CALL NUMBER CONVERSION CLASS
                NumberConverter NC;
                NC.askForConversion();
                break;
            }

            case 5: {
                //CALL MATRIX OPERATION CLASS
                matrix mx;
                mx.mainmenufun();
                break;
            }

            case 6: {
                //CALL SHAPECALCULATOR CLASS
                ShapeCalculator calculator;
                calculator.calculate();
                break;
            }

            case 7: {
                //CALL HISTORY CLASS
                History h;
                h.show();
                break;
            }

            default:
                cout << "INVALID CHOICE" << endl;
        }

            cout<<"\n\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout<<"\nDO YOU WANT TO SEE THE MENU AGAIN? \n\n PRESS: \n [1] = YES \n [0] = NO\n YOUR CHOICE: ";
            cin >> again;
            obj.checkException();

            cin.ignore();
            system("cls");

    }
    while(again!=0);
    outputFile.close();

        //CODE FOR - EXCEPTION HANDLING (TRY/CATCH)
        try
        {
            obj.checkException();
        }
        catch (const exception& e)
        {
            cerr << e.what() << endl;

        }


    return 0;
}


