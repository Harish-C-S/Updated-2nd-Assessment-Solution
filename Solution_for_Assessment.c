#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void size_file(char *file_name);
void count_lines(char *file_name);
void split_base_size(char *file_name, int max);
void split_base_lines(char *file_name, size_t max_lines);
void help();
int main(int argc,char *argv[])
{
    if(strcmp(argv[1],"-h")==0)
    {
	    help();
    }
    else if(strcmp(argv[1],"-c")==0)
    {
	    count_lines(argv[2]);
    }
    else if(strcmp(argv[1],"-m")==0)
    {
	    size_file(argv[2]);
    }
    else if(strcmp(argv[1],"-S_kB")==0)
    {
	    int b;
	    b=atoi(argv[2]);
	    split_base_size(argv[3],b);
    }
    else if(strcmp(argv[1],"-S_l")==0)
    {
        int max=0;
	max=atoi(argv[2]);
        split_base_lines(argv[3],max+8);
    }
    else
    {
      printf("Only below Arguments are available");
      help();
    }
    return 1;
}
void help()
{
	printf("\n Use   -c to count the lines                              ->>>>  solution binary -c <input file> ");
	printf("\n Use   -m to display memory of the file                   ->>>>  solution_binary -m <input file>");
	printf("\n Use   -S_kB to split the file based on size  example     ->>>>  solution_binary -S_KB 2 <input file> ");
	printf("\n use   -S_l  to split the file based on lines example     ->>>>  solution_binary -S_l  100 <input file \n");
}
void size_file(char *file_name)
{
	FILE *fp=fopen(file_name,"r");
	fseek(fp,0L,SEEK_END);
	long double result=ftell(fp);
	//printf("Size of Bytes %Lf",result);
	float a=result/1024;
	printf(" \n Size of File in  Kilo Bytes : %.2fkB \n",a);
	fclose(fp);
}
void count_lines(char *file_name)
{
	FILE *fp;int count=0;char c;
	fp=fopen(file_name,"r");
	for(c=getc(fp);c!=EOF;c=getc(fp))
	{
		if(c=='\n')
		{
			count++;
		}
	}
	printf("\nThe Number of Lines in the File is %d\n",count);
	fclose(fp);
}
void split_base_size(char *file_name, int max)
{
	FILE *file_input,*file_output;max=max*1024;
	char buffer[(1024*16)];size_t size,read,written;
	file_input=fopen(file_name,"rb");
	int result=0;
	while(!feof(file_input))
	{
		sprintf(buffer,"%04d-%s",result,file_name);
		file_output=fopen(buffer,"wb");
		size=0;

		read=sizeof(buffer);
		if((size+read)>max)
		{
			read=max-size;
		}
		read=fread(buffer,1,read,file_input);
		written=fwrite(buffer,1,read,file_output);
		size +=written;

		if(size>=max)
		{
			fclose(file_output);
			file_output=NULL;
			result++;
		}
	}
	fclose(file_input);
        //	printf("\n Use ls Command to view the files \n");
}
void split_base_lines(char *file_name, size_t max_lines)
{
        FILE *fp;int count=0;char c;
        fp=fopen(file_name,"r");
        for(c=getc(fp);c!=EOF;c=getc(fp))
        {
                if(c=='\n')
                {
			if(count==max_lines)
			{
			    fseek(fp,0,count);
		           // printf("\n Line Number is %d \n",count);
			    long int result=ftell(fp);
			    long int a=result/1024;
			    //printf("\n Line in Kilo Bytes %ld \n",a);
			    split_base_size(file_name,a);
			    break; 
		            	    
			}
                        count++;
                }
        }
        //printf("\nThe Number of Lines in the File is %d\n",count);
        fclose(fp);
	printf("\n Use ls Command to see the files \n");
}

