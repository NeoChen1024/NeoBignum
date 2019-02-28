#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bignum.h>

#define	LENGTH		(1<<24)
#define LAST		-1

bignum_t *num[3];
char str[LENGTH];
int mode = 0;

unsigned long long int max=ULONG_MAX, i=0;

int main(int argc, char **argv)
{
	for(i=0; i < 3; i++)
		num[i] = bignum_init(LENGTH);

	bignum_inttonum(num[0], 1);
	bignum_inttonum(num[1], 0);
	bignum_inttonum(num[2], 0);

	if(argc >= 2)
	{
		if(argv[1][0] == '-')
		{
			max = strtoull(argv[1] + 1, NULL, 10);
			mode = LAST;
		}
		else
			max = strtoull(argv[1], NULL, 10);
	}

	i=0;
	if(mode)
	{
		while(i <= max)
		{
			switch(i % 3)
			{
				case 0:
					bignum_add(num[0], num[1], num[2]);
					break;
				case 1:
					bignum_add(num[1], num[2], num[0]);
					break;
				case 2:
					bignum_add(num[2], num[0], num[1]);
					break;
			}
			i++;
		}
		switch((i -= 1) % 3)
		{
			case 0:
				bignum_prints(str, LENGTH, num[1]);
				break;
			case 1:
				bignum_prints(str, LENGTH, num[2]);
				break;
			case 2:
				bignum_prints(str, LENGTH, num[0]);
				break;
		}
		printf("%llu,\t%s\n", i, str);
	}
	else
	{
		while(i <= max)
		{
			switch(i % 3)
			{
				case 0:
					bignum_add(num[0], num[1], num[2]);
					bignum_prints(str, LENGTH, num[1]);
					break;
				case 1:
					bignum_add(num[1], num[2], num[0]);
					bignum_prints(str, LENGTH, num[2]);
					break;
				case 2:
					bignum_add(num[2], num[0], num[1]);
					bignum_prints(str, LENGTH, num[0]);
					break;
			}
			printf("%llu,\t%s\n", i, str);
			i++;
		}
	}
}
