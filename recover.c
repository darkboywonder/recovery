/**************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 **************************************/

#include <cs50.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  BYTE;

bool open(int open);

int main(void)
{
    
    BYTE buffer[512];
    BYTE check[4];
    int counter = 0;
    int toggle = 0;
    char title[8];
    FILE* img;
    
    // OPEN CARD FILE
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.raw.\n");
        return 2;
    }
    
    BYTE jpg1[4] = {0xff, 0xd8, 0xff, 0xe0};
    BYTE jpg2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    fread(&buffer, sizeof(buffer), 1, inptr);
    
    // while pointer doesn't point to end of file
    while(fread(&buffer,sizeof(buffer), 1 ,inptr) != 0)
    {
        for(int i = 0; i < 4 ; i++)
        {
            check[i] = buffer[i];
        }
        
        //IS BUFFER A START OF NEW JPEG?
        //if buffer's first four bites match struct    
        if((memcmp(jpg1, check, sizeof(check)) == 0) || (memcmp(jpg2, check, sizeof(check)) == 0))
        {      
        
            //if FILE pointer is writing to an open file, 
            if(open(toggle) == true)
            {
               // close the current file
               fclose(img);
               toggle = 0;
               
               // open a new file with new name
               sprintf(title,"%03d.jpg",counter);
               img = fopen(title, "w");
               if (img == NULL)
               {
               printf("Could not open img file.\n");
               return 3;
               } 
                 
               toggle = 1;
               
                // increase counter by 1
               counter = counter + 1;
               
               // write to the file
               fwrite(&buffer, sizeof(buffer) , 1 , img);
              
               
            }          
                
            else 
            {   
                toggle = 1;         
                
                // open file with new name
                sprintf(title,"%03d.jpg", counter); 
                img = fopen(title, "w");
                if (img == NULL)
                {
                    printf("Could not open img file.\n");
                    return 3;
                }
                
                // increase counter by 1
                counter = counter + 1;
                
                // write to the file.
                fwrite(&buffer, sizeof(buffer), 1, img);
               
            }            
        }        
         //else
         //ALREADY FOUND JPEG?(is file still open)
        else
        {        
            if(open(toggle) == true)
            {    
                // write buffer to file
                fwrite(&buffer, sizeof(buffer), 1 , img);
            }   
        }
    }
    fclose(img);
    fclose(inptr);
    return 0;                   
}

/**checks weather value is 1. if 1 img file is "open" or "found"
*if 0, img file is considered "closed" or not "found"
*/
bool open(int value)
{
    if(value == 0)
    {
        return false;
    }
    else if(value == 1)
    {
        return true;
    }
    else
    {
    return false;
    }
return false;    
}
