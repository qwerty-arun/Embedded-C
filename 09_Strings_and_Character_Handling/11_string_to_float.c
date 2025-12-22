// Convert a String to Float

/*
You are given a null-terminated string representing a floating-point number, which may contain:
- An optional sign (+ or -)
- A decimal point
- Only valid digits and one dot

Your task is to convert this string to its floating-point value (float), without using standard library functions like atof() or strtof().

Do not handle scientific notation (e.g., "1.2e5").

Example-1
Input: "123.45"
Output: 123.45

Example-2
Input: "-0.75"
Output: -0.75

Example-3
Input: "100"
Output: 100.00

Example-4
Input: "+9.99"
Output: 9.99
*/

#include <stdio.h>
#include <stdint.h>

int power(int num, int exp){
    int result = 1;
    for(int i = 0; i < exp; i++){
        result*= num;
    }
    return result;
}

float custom_atof(const char *str) {
    // Your logic here
    float result = 0.f;
    int i = 0;
    int sign = 1;
    if(str[i]=='+'){
        i++;
    }
    if(str[i]=='-'){
        i++;
        sign = -1;
    }
    while(str[i]!='\0'){
        if(str[i]=='.'){
            i++;
            int decimal_place = 1;
            while(str[i]!='\0'){
                result += (float)(str[i]-'0') / (float)power(10, decimal_place);
                decimal_place++;
                i++;
            }
            return sign * result;
        }
        result = result * 10.f + (str[i]-'0');
        i++;
    }
    return sign * result;
}

int main() {
    char str[101];
    fgets(str, sizeof(str), stdin);

    // Remove newline
    uint8_t i = 0;
    while (str[i]) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }

    float value = custom_atof(str);
    printf("%.2f", value);
    return 0;
}

/*
What’s the Goal?

Simulate atof() behavior: convert valid string like "123.45" to 123.45 as a float.

Why it matters in firmware?
- Some embedded applications use floating-point sensors, telemetry, etc.
- Minimal controller Compiler C libraries often lack atof()
- Useful when parsing config strings or serial inputs with decimals

Solution Logic
- Handle optional sign
- Parse integer part normally (result = result * 10 + digit)
- After encountering ., switch to fractional parsing
- Use digit / divisor, and increment divisor by 10× per digit (e.g., 10, 100, 1000)
- Combine both integer and fractional values
*/