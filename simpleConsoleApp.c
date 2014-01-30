#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int stringLength( char *s )	{
    int c = 0;
    while( *(s+c) )
	c++;
    return c;
}

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)
	return str;
    while( EOF != ( ch=fgetc(fp) ) && ch != '\n' )	{
        str[len++]=ch;
        if(len==size)	{
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)
		return str;
        }
    }
    str[len++]='\0';
    return realloc(str, sizeof(char)*len);
}


void mergeStr( char *a, char *b ) {
//  Find the shorter string; merge short string; append rest of longer string

    int i, j, aLen, bLen, cLen, smallLen;
    aLen = stringLength(a);
    bLen = stringLength(b);
    cLen = aLen + bLen;
    char c[cLen+1];

    if ( aLen > bLen )
        smallLen = bLen;
    else if ( aLen < bLen )  
        smallLen = aLen;
    else if ( aLen == bLen ) 
	smallLen = aLen;

    for ( i = 0; i < smallLen; i++ ) {
	c[2*i]   = a[i];
	c[2*i+1] = b[i];
    }

    if ( aLen != bLen ) {
        j = 0;
    	for ( i = 2 * smallLen; i < cLen; i++ ) {
	    if( aLen > bLen ) 
		c[i] = a[j+smallLen];
            else if( aLen < bLen ) 
		c[i] = b[j+smallLen];
	    j++;
    	}
    }	
    c[cLen] = '\0';
    printf("(strings were merged)\n\t%s\n", c );
}

void reverseStrings( char *a, char *b ) {
    int i, aLen, bLen;
    char *c = malloc(sizeof(a )+1 );
    char *d = malloc(sizeof(b )+1 );
    aLen = stringLength( a );
    bLen = stringLength( b );
    for ( i = 0; i < aLen; i++ ) {
	c[i] = a[aLen-i-1];
    }
    for ( i = 0; i < bLen; i++ ) {
	d[i] = b[bLen-i-1];
    }
    printf("(strings were reversed)\n");
    printf("\tString1 = %s\n", c );
    printf("\tString2 = %s\n", d );
    free( c );
    free( d );
}

void reverseMergeStrings( char *a, char *b ) {
    int i, aLen, bLen;
    char *c = malloc(sizeof(a )+1 );
    char *d = malloc(sizeof(b )+1 );
    aLen = stringLength( a );
    bLen = stringLength( b );
    for ( i = 0; i < aLen; i++ ) {
	c[i] = a[aLen-i-1];
    }
    for ( i = 0; i < bLen; i++ ) {
	d[i] = b[bLen-i-1];
    }
    printf("(Strings were inverted)\n");
    mergeStr( c, d );
    free( c );
    free( d );
}


int myStrCmp( char *a, char *b ) {
    int i, diff;
    int strLen = stringLength( a );
    // strcmp Function:
    for(i=0; a[i]==b[i]; i++) {
	if (a[i] == '\0') {
	    mergeStr( a, b );   
	    return 0;
	}
    }            
    diff = a[i]-b[i];
    if ( diff < 0 ) 
	reverseStrings( a, b );
    else if ( diff > 0 )  
	reverseMergeStrings( a, b );	    
    return diff;
}

int testFun( char *a, char *b) {
    int c = strcmp( a, b );
    return c;
}

int main(void) {
    char *m, *n;
    int mLen, nLen, value, c;

    printf("input string1 : ");
    m = inputString(stdin, 10);
    printf("input string2 : ");
    n = inputString( stdin, 1);
    printf("==============================\n");

    printf("SOLUTION OUTPUT:\n");
    
    value = myStrCmp(m,n);
    c     = testFun(m,n);
    printf("------------------------------\n");
    printf("value from MyStrCmp = %d\n", value );
    printf("value from strcmp   = %d\n", value );
    printf("==============================\n");

    free(m);
    free(n);

    return 0;
}
