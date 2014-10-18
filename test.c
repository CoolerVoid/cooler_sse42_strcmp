/*
 SImple PoC to test sse42
author: Antonio Costa aka "Cooler"
contact: c00f3r@gmail.com
 
 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <x86intrin.h>
#include <cpuid.h>
#include <inttypes.h>
#include <stdint.h>


void cpu_get(int* cpuinfo, int info)
{
	__asm__ __volatile__(
		"xchg %%ebx, %%edi;"
		"cpuid;"
		"xchg %%ebx, %%edi;"
		:"=a" (cpuinfo[0]), "=D" (cpuinfo[1]), "=c" (cpuinfo[2]), "=d" (cpuinfo[3])
		:"0" (info)
	);
}

void test_sse42_enable()
{
	int cpuinfo[4];
	int sse42=0;

	cpu_get(cpuinfo,1);

	sse42=cpuinfo[2] & (1 << 20) || 0;

	if(sse42)
		puts("SSE4.2 Test...\n OK SSE 4.2 instruction enable !\n");
	else {
		puts("SSE4.2 Not enabled\n your CPU need SSE 4.2 instruction to run this programm\n");
		exit(0);
	}
}

#define array_elements(array) (sizeof(array) / sizeof *(array))

extern int strcmp_sse42_32(const char *, const char *);
extern int strcmp_sse42_64(const char *, const char *);

#if UINTPTR_MAX == 0xffffffff
static int (*strcmp_sse42)(const char *, const char *) = strcmp_sse42_32;
#elif UINTPTR_MAX == 0xffffffffffffffff
static int (*strcmp_sse42)(const char *, const char *) = strcmp_sse42_64;
#else
	fprintf(stderr,"error in arch\n");
	exit(0);
#endif

int matchs = 0;

const char *text[] = {	"1234-1234","batman","1234 4321","abcd-1234","macaco","sopa-4321","1337-7331", "chaves","kiko","florinda", "chiquinha","madruga","senhor barriga",
			"girafales","inhonho","thundercats","he- man","dragon ball","naruto","3311-2399","sub-zero","raiden","ryu","power rangers","ranger-1337","1337-1337",
			"007","hulk","spider-man","darth vader","super-man","0071-1212","dragonite","mumia","fredy kruger","jason","golun","nozes","3135-9921","chupa-cabra",
			"abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331",
			"chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321",
			"1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco",
			"sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234",
			"macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves",
			"abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331",
			"chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321",
			"1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco",
			"sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234",
			"macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves",
			"abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331",
			"chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321",
			"1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco",
			"sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves","abcd-1234",
			"macaco","sopa-4321","1337-7331","chaves","abcd-1234","macaco","sopa-4321","1337-7331","chaves" };

static void call_count()
{
	int count = 0;
	const char *exp = "chaves";
	

	while(count != array_elements(text))
	{	 
		if(!strcmp_sse42(exp, text[count]))
			matchs++;		
		count++;
	}
}


static void call_count2()
{
	int count = 0;
	char *exp = "chaves";
	

	while(count != array_elements(text))
	{	 
		if (!strcmp(text[count], exp))
			matchs++;
		count++;
	}
}



int main()
{
	test_sse42_enable();

	long int x=0;
	uint32_t a = 0, b = 0, c = 0, d = 0;
	register long long y = 0;

  	x = 0;
  	do {
		__cpuid(0, a, b, c, d);
		y = _rdtsc();
		call_count();
		y = _rdtsc() - y;

	} while (++x < 2);
 
	printf(":::  strcmp() with SSE42: %lld  cicles\n", y);
	fprintf(stdout,"Array size of words is: %d \n", array_elements(text));	
	fprintf(stdout,"Benchmark strcmp() with SSE42 matchs is: %d \n\n", matchs);


	matchs=0;
  	x = 0;
  	do {
		__cpuid(0, a, b, c, d);
		y = _rdtsc();
		call_count2();
		y = _rdtsc() - y;

	} while (++x < 2);
 
	printf("::: simple strcmp(): %lld  cicles\n", y);
	fprintf(stdout,"Array size of words is: %d \n", array_elements(text));	
	fprintf(stdout,"Benchmark strcmp() matchs is: %d \n\n", matchs);



 exit(0);
}
