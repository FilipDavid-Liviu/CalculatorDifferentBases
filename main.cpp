#include <iostream>
#include <cstring>
using namespace std;

struct number_base{
    char text[100];
    int base;
};

int transform_in_digit(char x)
{
    if (x <= '9')
        return x - '0';
    else return x - 'A' + 10;
}

char transform_in_char(int x)
{
    if (x <= 9)
        return char(x + '0');
    else return char(x + 'A' - 10);
}

void delete_0(char a[])
{
    int i = 0;
    while((a[i] == '0')  && (a[i+1] != '\0'))
        i++;
    strcpy(a, a+i);
}

bool check_number_base(number_base x)
{
    for (int i = 0; i < strlen(x.text); i++)
        if (transform_in_digit(x.text[i]) >= x.base)
            return false;
    return true;
}

bool check_rapid_conversion_compatibility(int base1, int base2)
{
    if (base1 > base2){
        while (base1 % base2 == 0)
            base1 /= base2;
        if (base1 == 1)
            return true;
        return false;
    }
    else {
        while (base2 % base1 == 0)
            base2 /= base1;
        if (base2 == 1)
            return true;
        return false;
    }
}

bool is_first_bigger(number_base x, number_base y)
{
    if (strlen(x.text) < strlen(y.text))
        return false;
    if (strlen(x.text) == strlen(y.text)){
        for (int i = 0; i <= strlen(x.text); i++)
            if (x.text[i] < y.text[i])
                return false;
            else if (x.text[i] > y.text[i])
                return true;
    }
    return true;
}

number_base addition(number_base x, number_base y)
{
    int base = x.base;
    int c = 0, i, val;
    number_base z{.base = base};
    for (i = 0; i < strlen(x.text) && i < strlen(y.text); i++){
        val = c + transform_in_digit(x.text[strlen(x.text)-1-i])
              + transform_in_digit(y.text[strlen(y.text)-1-i]);
        c = 0;
        if (val >= base)
            c = 1;
        z.text[i] = transform_in_char(val % base);
    }
    while (i < strlen(x.text)){
        val = c + transform_in_digit(x.text[strlen(x.text)-1-i]);
        c = 0;
        if (val >= base)
            c = 1;
        z.text[i] = transform_in_char(val % base);
        i++;
    }
    while (i < strlen(y.text)){
        val = c + transform_in_digit(y.text[strlen(y.text)-1-i]);
        c = 0;
        if (val >= base)
            c = 1;
        z.text[i] = transform_in_char(val % base);
        i++;
    }
    if (c == 1)
        z.text[i] = '1';
    strrev(z.text);
    return z;
}

number_base subtraction(number_base x, number_base y)
{
    int base = x.base;
    int c = 0, i, val;
    number_base z{.base = base};
    for (i = 0; i < strlen(x.text) && i < strlen(y.text); i++){
        val = c + transform_in_digit(x.text[strlen(x.text)-1-i])
              - transform_in_digit(y.text[strlen(y.text)-1-i]);
        c = 0;
        if (val < 0){
            c = -1;
            z.text[i] = transform_in_char(val + base);
        }
        else z.text[i] = transform_in_char(val);
    }
    while (i < strlen(x.text)){
        val = transform_in_digit(x.text[strlen(x.text)-1-i]) + c;
        c = 0;
        if (val < 0){
            z.text[i] = transform_in_char(val + base);
            c = -1;
        }
        else z.text[i] = transform_in_char(val);
        i++;
    }
    strrev(z.text);
    delete_0(z.text);
    return z;
}

number_base multiplication_one_digit(number_base x, number_base y)
{
    int base = x.base;
    int c = 0, i, val;
    number_base z{.base = base};
    for (i = 0; i < strlen(x.text); i++){
        val = c + transform_in_digit(x.text[strlen(x.text)-1-i])
                  * transform_in_digit(y.text[0]);
        c = 0;
        if (val >= base){
            c = val / base;
        }
        z.text[i] = transform_in_char(val % base);
    }
    if (c > 0)
        z.text[i] = transform_in_char(c);
    strrev(z.text);
    delete_0(z.text);
    return z;
}

number_base division_one_digit(number_base x, number_base y)
{
    int base = x.base;
    int c = 0, i, val;
    number_base z{.base = base};
    for (i = 0; i < strlen(x.text); i++){
        val = (c * base + transform_in_digit(x.text[i])) / transform_in_digit(y.text[0]);
        c = (c * base + transform_in_digit(x.text[i])) % transform_in_digit(y.text[0]);
        z.text[i] = transform_in_char(val);
    }
    delete_0(z.text);
    return z;
}

number_base division_one_digit_residue(number_base x, number_base y)
{
    int base = x.base;
    int c = 0, i;
    number_base z{.base = base};
    for (i = 0; i < strlen(x.text); i++){
        c = (c * base + transform_in_digit(x.text[i])) % transform_in_digit(y.text[0]);
    }
    z.text[0] = transform_in_char(c);
    return z;
}

number_base conversion_using_10(number_base x, int target_base)
{
    int val10 = 0, i, power = 1;
    number_base z{.base = target_base};
    strrev(x.text);
    for (i = 0; i < strlen(x.text); i++){
        val10 += transform_in_digit(x.text[i]) * power;
        power *= x.base;
    }
    cout<<"base 10 : "<<val10<<endl;
    for (i = 0; val10 > 0; i++){
        z.text[i] = transform_in_char(val10 % target_base);
        val10 /= target_base;
    }
    strrev(z.text);
    z.base = target_base;
    return z;
}

number_base conversion_using_division(number_base x, int target_base)
{
    number_base z{.base = target_base}, digit{};
    digit.text[0] = transform_in_char(target_base);
    digit.text[1]= '\0';
    digit.base = x.base;
    strcpy(z.text, "");
    while (strcmp(x.text, "0") != 0){
        number_base aux{};
        aux = division_one_digit_residue(x,digit);
        strcat(z.text, aux.text);
        x = division_one_digit(x, digit);
    }
    strrev(z.text);
    return z;
}

number_base conversion_using_substitution(number_base x, int target_base)
{
    number_base z{.base = target_base}, pow_target{}, pow_former{};
    strcpy(z.text, "0");
    pow_former.text[0] = transform_in_char(x.base);
    pow_former.text[1] = '\0';
    pow_former.base = target_base;
    strcpy(pow_target.text, "1");
    pow_target.base = target_base;
    strrev(x.text);
    for (int i = 0; i < strlen(x.text); i++){
        number_base digit{}, val_in_target_base{};
        digit.text[0] = x.text[i];
        digit.text[1] = '\0';
        digit.base = target_base;
        val_in_target_base = multiplication_one_digit(pow_target, digit);
        z = addition(z,val_in_target_base);
        pow_target = multiplication_one_digit(pow_target, pow_former);
    }
    return z;
}

int log_base(int a, int b)
{
    int p = 0;
    while (b % a == 0){
        b /= a;
        p++;
    }
    return p;
}

basic_string<char> corresponding_group(char x, int initial_base, int target_base)
{
    string from4_2[4] = {"00", "01", "10", "11"};
    string from8_2[8] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    string from16_2[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110",
                           "0111", "1000", "1001", "1010", "1011", "1100", "1101",
                           "1110", "1111"};
    string from16_4[16] = {"00", "01", "02", "03", "10", "11", "12", "13", "20",
                           "21", "22", "23", "30", "31", "32", "33"};
    string from9_3[9] = {"00", "01", "02", "10", "11", "12", "20", "21", "22"};
    if (target_base == 2){
        if (initial_base == 4)
            return from4_2[transform_in_digit(x)];
        else if (initial_base == 8)
            return from8_2[transform_in_digit(x)];
        else if (initial_base == 16)
            return from16_2[transform_in_digit(x)];
        return "";
    } else if (target_base == 3)
        return from9_3[transform_in_digit(x)];
    else if (target_base == 4)
        return from16_4[transform_in_digit(x)];
    return "";
}

char corresponding_digit(char x[], int initial_base)
{
    int value = 0;
    int power = 1;
    for (int i = 0; i < strlen(x); i++) {
        value += transform_in_digit(x[i]) * power;
        power *= initial_base;
    }
    return transform_in_char(value);
}

number_base conversion_using_rapid_conversion(number_base x, int target_base)
{
    number_base z{.base = target_base};
    strcpy(z.text, "");
    if (x.base > target_base){
        for (int i = 0; i < strlen(x.text); i++){
            string group = corresponding_group(x.text[i], x.base, target_base);
            strcat(z.text, group.c_str());
        }
        delete_0(z.text);
    }
    else {
        int digits_in_group = log_base(x.base, target_base);
        strrev(x.text);
        for (int i = 0; i < strlen(x.text); i = i + digits_in_group){
            while (strlen(x.text) - i < digits_in_group)
                strcat(x.text, "0");
            char aux[100];
            strcpy(aux, x.text + i);
            aux[digits_in_group] = '\0';
            char aux_digit = corresponding_digit(aux, x.base);
            char aux_source[2];
            aux_source[0] = aux_digit;
            aux_source[1] = '\0';
            strcat(z.text, aux_source);
        }
        strrev(z.text);
        delete_0(z.text);
    }
    return z;
}

int main() {
    while (true) {
        cout<<"\n1. Arithmetic operations for positive integers\n";
        cout<<"2. Conversions of natural numbers between two bases\n";
        cout<<"0. Exit the program\n";

        char option_main[100];
        cout<<">";
        cin >> option_main;

        if (option_main[0] == '0') {
            cout<<"Goodbye!\n";
            break;
        }
        else if (option_main[0] == '1') {
            cout<<"Arithmetic operations\n";
            while (true){
                cout<<"\n1. Addition\n";
                cout<<"2. Subtraction\n";
                cout<<"3. Multiplication by one digit\n";
                cout<<"4. Division by one digit\n";
                cout<<"0. Go back\n";

                char option_operation[100];
                cout<<">";
                cin >> option_operation;

                if (option_operation[0] == '0') {
                    break;
                }
                else if (option_operation[0] == '1') {
                    cout<<"Addition\n";
                    number_base operand1{}, operand2{};

                    cout<<"Base:";
                    cin>>operand1.base;
                    operand2.base = operand1.base;

                    cout<<"First number:";
                    cin>>operand1.text;
                    cout<<"Second number:";
                    cin>>operand2.text;

                    if (!check_number_base(operand1) || !check_number_base(operand2)) {
                        cout<<"ERROR: numbers not defined in base\n";
                    }
                    else {
                        number_base operand3{};
                        operand3 = addition(operand1, operand2);
                        cout<<operand3.text<<endl;
                    }
                }
                else if (option_operation[0] == '2'){
                    cout<<"Subtraction\n";
                    number_base operand1{}, operand2{};

                    cout<<"Base:";
                    cin>>operand1.base;
                    operand2.base = operand1.base;

                    cout<<"First number:";
                    cin>>operand1.text;
                    cout<<"Second number:";
                    cin>>operand2.text;

                    if (!check_number_base(operand1) || !check_number_base(operand2)) {
                        cout<<"ERROR: numbers not defined in base\n";
                    }
                    else if(!is_first_bigger(operand1, operand2)){
                        cout<<"ERROR: result is not a natural number\n";
                    }
                    else {
                        number_base operand3{};
                        operand3 = subtraction(operand1, operand2);
                        cout<<operand3.text<<endl;
                    }
                }
                else if (option_operation[0] == '3'){
                    cout<<"Multiplication by one digit\n";
                    number_base operand1{}, operand2{};

                    cout<<"Base:";
                    cin>>operand1.base;
                    operand2.base = operand1.base;

                    cout<<"First number:";
                    cin>>operand1.text;
                    cout<<"Second number:";
                    cin>>operand2.text;
                    strcpy(operand2.text + 1,"\0");

                    if (!check_number_base(operand1) || !check_number_base(operand2)) {
                        cout<<"ERROR: numbers not defined in base\n";
                    }
                    else {
                        number_base operand3{};
                        operand3 = multiplication_one_digit(operand1, operand2);
                        cout<<operand3.text<<endl;
                    }
                }
                else if (option_operation[0] == '4'){
                    cout<<"Division by one digit\n";
                    number_base operand1{}, operand2{};

                    cout<<"Base:";
                    cin>>operand1.base;
                    operand2.base = operand1.base;

                    cout<<"First number:";
                    cin>>operand1.text;
                    cout<<"Second number:";
                    cin>>operand2.text;
                    strcpy(operand2.text + 1,"\0");

                    if (!check_number_base(operand1) || !check_number_base(operand2)) {
                        cout<<"ERROR: numbers not defined in base\n";
                    }
                    else {
                        number_base operand3{}, operand4{};
                        operand3 = division_one_digit(operand1, operand2);
                        operand4 = division_one_digit_residue(operand1, operand2);
                        cout<<operand3.text<<",  residue: "<<operand4.text<<endl;
                    }
                }
                else {
                    cout<<"ERROR: No valid value inserted\n";
                }
            }
        } else if (option_main[0] == '2') {
            cout<<"Conversions of natural numbers between 2 bases\n";
            while (true){
                cout<<"\n1. Conversion using 10 as an intermediate base\n";
                cout<<"2. Conversion through successive divisions\n";
                cout<<"3. Conversion using the substitution method\n";
                cout<<"4. Rapid conversions\n";
                cout<<"0. Go back\n";

                char option_convert[100];
                cout<<">";
                cin >> option_convert;

                if (option_convert[0] == '0') {
                    break;
                }
                else if (option_convert[0] == '1') {
                    cout<<"Using 10 as an intermediate base\n";
                    number_base operand{};
                    int new_base;
                    cout<<"Initial base:";
                    cin>>operand.base;
                    cout<<"Number:";
                    cin>>operand.text;
                    cout<<"Base to be converted into:";
                    cin >> new_base;

                    if (!check_number_base(operand)) {
                        cout<<"ERROR: number not defined in original base\n";
                    }
                    else {
                        operand = conversion_using_10(operand, new_base);
                        cout<<"base "<<new_base<<" : "<<operand.text<<endl;
                    }
                }
                else if (option_convert[0] == '2'){
                    cout<<"Successive division method\n";
                    number_base operand{};
                    int new_base;

                    cout<<"Initial base:";
                    cin>>operand.base;
                    cout<<"Number:";
                    cin>>operand.text;
                    cout<<"Base to be converted into:";
                    cin >> new_base;

                    if (!check_number_base(operand)) {
                        cout<<"ERROR: number not defined in original base\n";
                    }
                    else if (operand.base < new_base){
                        cout<<"ERROR: the chosen bases are not compatible for successive division method\n";
                    }
                    else {
                        operand = conversion_using_division(operand, new_base);
                        cout<<"base "<<new_base<<" : "<<operand.text<<endl;
                    }
                }
                else if (option_convert[0] == '3'){
                    cout<<"Substitution method\n";
                    number_base operand{};
                    int new_base;

                    cout<<"Initial base:";
                    cin>>operand.base;
                    cout<<"Number:";
                    cin>>operand.text;
                    cout<<"Base to be converted into:";
                    cin >> new_base;

                    if (!check_number_base(operand)) {
                        cout<<"ERROR: number not defined in original base\n";
                    }
                    else if (operand.base > new_base){
                        cout<<"ERROR: the chosen bases are not compatible for substitution method\n";
                    }
                    else {
                        operand = conversion_using_substitution(operand, new_base);
                        cout<<"base "<<new_base<<" : "<<operand.text<<endl;
                    }
                }
                else if (option_convert[0] == '4'){
                    cout<<"Rapid conversions\n";
                    number_base operand{};
                    int new_base;

                    cout<<"Initial base:";
                    cin>>operand.base;
                    cout<<"Number:";
                    cin>>operand.text;
                    cout<<"Base to be converted into:";
                    cin >> new_base;

                    if (!check_number_base(operand)) {
                        cout<<"ERROR: number not defined in original base\n";
                    }
                    else if (new_base > 16 or operand.base > 16 or new_base < 2 or operand.base < 2){
                        cout<<"ERROR: bases must be between 2 and 16";
                    }
                    else if (!check_rapid_conversion_compatibility(operand.base, new_base)){
                        cout<<"ERROR: the chosen bases are not compatible for rapid conversion\n";
                    }
                    else {
                        operand = conversion_using_rapid_conversion(operand, new_base);
                        cout<<"base "<<new_base<<" : "<<operand.text<<endl;
                    }
                }
                else {
                    cout<<"ERROR: No valid value inserted\n";
                }
            }
        } else {
            cout<<"ERROR: No valid value inserted\n";
        }
    }
    return 0;
}
