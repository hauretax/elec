
  
#include <stdio.h> 
  
int addOne(int x) 
{ 
    int m = 1; 
      
    // Flip all the set bits  
    // until we find a 0  
    while( x & m ) 
    { 
        x = x ^ m;
        m <<= 1;
    }
      
    // flip the rightmost 0 bit  
    x = x ^ m; 
    printf("%d\n", x);
    m = 0b1000;
    for(int i = 0 ; i<4; i++){
        if(x & m)
            printf("1");
        else
            printf("0");
        
        m >>= 1;
    }
    printf("\n");
    return x; 
} 
  
/* Driver program to test above functions*/
int main() 
{ 
    printf("%d", addOne(12)); 
    getchar(); 
    return 0; 
} 