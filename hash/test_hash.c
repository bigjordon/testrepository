#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

/** NOTE: Arguments are modified. */       
#define __vs_jhash_mix(a, b, c) \
{ \
  a -= b; a -= c; a ^= (c>>13);\
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}                                          

/* The golden ration: an arbitrary value */
#define JHASH_GOLDEN_RATIO      0x9e3779b9 

/**                                                                      
 * jhash - hash an arbitrary key.                                        
 *                                                                       
 * @param key sequence of bytes as key                                   
 * @param length the length of the key                                   
 * @param initval the previous hash, or an arbitray value                
 *                                                                       
 * The generic version, hashes an arbitrary sequence of bytes.           
 * No alignment or length assumptions are made about the input key.      
                                                                         
 * @return                                                               
 *   Returns the hash value of the key. The result depends on endianness.
 */                                                                      

static inline uint32_t vs_jhash(const void *key, uint32_t length, uint32_t initval)           
{                                                                                             
        uint32_t a, b, c, len;                                                                
        const uint8_t *k = key;                                                               
                                                                                              
        len = length;                                                                         
        a = b = JHASH_GOLDEN_RATIO;                                                           
        c = initval;                                                                          
                                                                                              
        while (len >= 12) {                                                                   
                a += (k[0] +((uint32_t)k[1]<<8) +((uint32_t)k[2]<<16) +((uint32_t)k[3]<<24)); 
                b += (k[4] +((uint32_t)k[5]<<8) +((uint32_t)k[6]<<16) +((uint32_t)k[7]<<24)); 
                c += (k[8] +((uint32_t)k[9]<<8) +((uint32_t)k[10]<<16)+((uint32_t)k[11]<<24));
                                                                                              
                __vs_jhash_mix(a,b,c);                                                        
                                                                                              
                k += 12;                                                                      
                len -= 12;                                                                    
        }                                                                                     
                                                                                              
        c += length;                                                                          
        switch (len) {                                                                        
        case 11: c += ((uint32_t)k[10]<<24);                                                  
        case 10: c += ((uint32_t)k[9]<<16);                                                   
        case 9 : c += ((uint32_t)k[8]<<8);                                                    
        case 8 : b += ((uint32_t)k[7]<<24);                                                   
        case 7 : b += ((uint32_t)k[6]<<16);                                                   
        case 6 : b += ((uint32_t)k[5]<<8);                                                    
        case 5 : b += k[4];                                                                   
        case 4 : a += ((uint32_t)k[3]<<24);                                                   
        case 3 : a += ((uint32_t)k[2]<<16);                                                   
        case 2 : a += ((uint32_t)k[1]<<8);                                                    
        case 1 : a += k[0];                                                                   
        };
                                                                                              
        __vs_jhash_mix(a,b,c);
                              
        return c;             
}                             

/**                                                                             
 * vs_jhash2 - hash an array of u32's.                                          
 *                                                                              
 * @param k the key which must be an array of u32's                             
 * @param length the number of u32's in the key                                 
 * @param initval the previous hash, or an arbitray value                       
 *                                                                              
 * @return                                                                      
 *    Returns the hash value of the key.                                        
 */                                                                             
static inline uint32_t vs_jhash2(uint32_t *k, uint32_t length, uint32_t initval)
{                                                                               
        uint32_t a, b, c, len;                                                  
                                                                                
        a = b = JHASH_GOLDEN_RATIO;                                             
        c = initval;                                                            
        len = length;                                                           
                                                                                
        while (len >= 3) {                                                      
                a += k[0];                                                      
                b += k[1];                                                      
                c += k[2];                                                      
                __vs_jhash_mix(a, b, c);                                        
                k += 3; len -= 3;                                               
        }                                                                       
                                                                                
        c += length * 4;                                                        
                                                                                
        switch (len) {                                                          
        case 2 : b += k[1];                                                     
        case 1 : a += k[0];                                                     
        };                                                                      
                                                                                
        __vs_jhash_mix(a,b,c);
	return c;
}

/**                                                                                          
 * A special ultra-optimized versions that knows they are hashing exactly                    
 * 3, 2 or 1 word(s).                                                                        
 *                                                                                           
 * NOTE: In partilar the "c += length; __vs_jhash_mix(a,b,c);" normally                      
 *       done at the end is not done here.                                                   
 *                                                                                           
 * @param a  word a                                                                          
 * @param b  word b                                                                          
 * @param c  word c                                                                          
 * @param initval the previous hash, or an arbitray value                                    
 *                                                                                           
 * @return                                                                                   
 *    Returns the hash value of the key.                                                     
 */                                                                                          
static inline uint32_t vs_jhash_3words(uint32_t a, uint32_t b, uint32_t c, uint32_t initval) 
{                                                                                            
        a += JHASH_GOLDEN_RATIO;                                                             
        b += JHASH_GOLDEN_RATIO;                                                             
        c += initval;                                                                        
                                                                                             
        __vs_jhash_mix(a, b, c);                                                             
                                                                                             
        return c;                                                                            
}                                                                                            
                                                                                             
/**                                                                               
 * A special ultra-optimized versions that knows they are hashing exactly         
 * 2 or 1 word(s).                                                                
 *                                                                                
 * NOTE: In partilar the "c += length; __vs_jhash_mix(a,b,c);" normally           
 *       done at the end is not done here.                                        
 * @param a  word a                                                               
 * @param b  word b                                                               
 * @param initval the previous hash, or an arbitray value                         
 *                                                                                
 * @return                                                                        
 *    Returns the hash value of the key.                                          
 */                                                                               
static inline uint32_t vs_jhash_2words(uint32_t a, uint32_t b, uint32_t initval)  
{                                                                                 
        return vs_jhash_3words(a, b, 0, initval);                                 
}                                                                                 

/**                                                                       
 * A special ultra-optimized versions that knows they are hashing exactly 
 * 1 word(s).                                                             
 *                                                                        
 * NOTE: In partilar the "c += length; __vs_jhash_mix(a,b,c);" normally   
 *       done at the end is not done here.                                
 * @param a  word a                                                       
 * @param initval the previous hash, or an arbitray value                 
 *                                                                        
 * @return                                                                
 *    Returns the hash value of the key.                                  
 */                                                                       
static inline uint32_t vs_jhash_1word(uint32_t a, uint32_t initval)       
{                                                                        
        return vs_jhash_3words(a, 0, 0, initval);                         
}


int main(int argc, char ** argv)
{
	int table_size = 1000;
	int zone = 0;
	int hash_rnd = 33443;
	unsigned int sourceIP   = 0x12344321;
	unsigned int sourcePort = 1111;
	unsigned int dest__IP   = 0x44556677;
	unsigned int dest__Port = 80;
	printf("0x%x\n", vs_jhash_3words(sourceIP, dest__IP ^ dest__Port, zone ^ (sourcePort | dest__Port << 16), hash_rnd ) % table_size );

	return 0;
}
