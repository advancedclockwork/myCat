/*
 * File:   myCat.c
 * Author: owen
 *
 * Created on October 19, 2015, 7:29 PM
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024

int main(int argc, char *argv[])
{
    int currentChar,file,i,x,eswitch = 0,nswitch = 0,sswitch = 0, currentLine = 1;
    char buf[BUFFSIZE];
	for ( i = 1; i < argc ; i++)
        {
            if (argv[i][0] == '-')
            {
                while ((x = getopt(argc,argv,"ens")) != EOF)
                {
                    switch(x)
                    {
                        case 'e' :
                        eswitch = 1;
                        break;

                        case 'n':
                        nswitch = 1;
                        break;

                        case 's':
                        sswitch = 1;
                        break;
                    }
                }
            }
            else
            {
                if (strcmp(argv[i],"-") != 0)
                {
                    file = open(argv[i],O_RDONLY);
                }
                else
                {
                    file = STDIN_FILENO;
                }
                while(( currentChar = read(file,buf,BUFFSIZE)) > 0)
                {
                    if (eswitch == 1 || nswitch == 1 || sswitch == 1)
                    {
                        int count = 0;
                        char newbuf[currentChar * 2];
                        int newbufcount = 0;
                        if (nswitch == 1)
                        {
                            //if (newbuf[newbufcount-1] != '\n' && newbuf[newbufcount-2] != '\r' && currentLine != 1)
                            {
                            //    newbuf[newbufcount]='\r';
                            //    newbufcount++;
                            //    newbuf[newbufcount]='\n';
                            //    newbufcount++;
                            }
                            newbuf[newbufcount] = currentLine/1000 +'0';
                            newbufcount++;
                            newbuf[newbufcount] = currentLine/100 +'0';
                            newbufcount++;
                            newbuf[newbufcount] = currentLine/10 + '0';
                            newbufcount++;
                            newbuf[newbufcount] = currentLine%10 + '0';
                            newbufcount++;
                            newbuf[newbufcount] = ' ';
                            newbufcount++;
                            currentLine++;
                        }
                        for (count; count < currentChar; count++)
                        {
                            if (sswitch == 1 && (buf[count]=='\r' || buf[count]=='\v'|| buf[count]=='\f'))
                            {
                                int spaceCheck = count+1;
                                while((buf[spaceCheck] == ' ' || buf[spaceCheck] == '\t' || buf[spaceCheck] == '\n' || buf[spaceCheck] == '\r'|| buf[spaceCheck]=='\v'|| buf[spaceCheck]=='\f') &&  spaceCheck < currentChar)
                                {
                                    if ((buf[spaceCheck]=='\r' && buf[spaceCheck+1]== '\n') || buf[spaceCheck]=='\v'|| buf[spaceCheck]=='\f'|| spaceCheck+1 == currentChar)
                                    {
                                        count = spaceCheck;
                                    }
                                    spaceCheck++;
                                }
                            }
                            if (nswitch == 1 && (newbuf[newbufcount-1]=='\n' /*|| newbuf[newbufcount-1]=='\r' || newbuf[newbufcount-1]=='\v'*/|| newbuf[newbufcount-1]=='\f'))
                            {
                                newbuf[newbufcount] = currentLine / 1000 +'0';
                                newbufcount++;
                                newbuf[newbufcount] = currentLine / 100 +'0';
                                newbufcount++;
                                newbuf[newbufcount] = currentLine / 10 +'0';
                                newbufcount++;
                                newbuf[newbufcount] = currentLine % 10 + '0';
                                newbufcount++;
                                newbuf[newbufcount] = ' ';
                                newbufcount++;
                                currentLine++;
                            }
                            if (eswitch == 1 && ((buf[count]=='\r' && buf[count+1] == '\n')|| count +1 == currentChar))
                            {
                                newbuf[newbufcount] = '$';
                                newbufcount++;
                            }
                            if(buf[count] != '\0')
                            {
                                newbuf[newbufcount] = buf[count];
                                newbufcount++;
                            }

                        }
                        if (sswitch == 1 && newbuf[newbufcount-1]!= '\n' && newbuf[newbufcount-2]!= '\r')
                        {
                            newbuf[newbufcount] = '\r';
                            newbufcount++;
                            newbuf[newbufcount] = '\n';
                            newbufcount++;
                        }
                        if (write(STDOUT_FILENO, newbuf ,newbufcount ) != newbufcount)//currentChar)
                        {
                                perror("Write Error");
                        }
                    }
                    else
                    {


                        if (write(STDOUT_FILENO, buf ,currentChar ) != currentChar)
                        {
                                perror("Write Error");
                        }
                    }

                }
                if ( currentChar < 0 ) {
                        perror("Read Error");
                }
                if (close(file) == -1) {
                        perror("Closing Error");
                }
            }
	}
    exit(0);
}
