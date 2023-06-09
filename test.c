#include <stdio.h>

int main(){
	double a = 128.5;

	double b = (((int)a>>6)<<6) - 0.0001;
	printf("%f\n", b);
}
