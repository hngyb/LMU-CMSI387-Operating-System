/* lsmod.c: list the status of kernel modules.
    Copyright (C) 2002  Rusty Russell, IBM Corporation.
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <asm/unistd.h>


static void print_usage(const char *progname)
{
        fprintf(stderr, "Usage: %s\n", progname);
        exit(1);
}

int main(int argc, char *argv[])
{
        char line[4096];
        FILE *file;

        file = fopen("/proc/modules", "r");
        if (!file) {
                perror("Opening /proc/modules");
                exit(1);
        }
        if (argc == 1) { // If the user types "lsmod" only.
            printf("Module                  Size  Used by\n");
            while (fgets(line, sizeof(line), file)) {
                char *tok;

                tok = strtok(line, " \t");
                printf("%-19s", tok);
                tok = strtok(NULL, " \t\n");
                printf(" %8s", tok);
                tok = strtok(NULL, " \t\n");
                /* Null if no module unloading support. */
                if (tok) {
                        printf("  %s", tok);
                        tok = strtok(NULL, "\n");
                        if (!tok)
                                tok = "";
                        /* New-style has commas, or -.  If so,
                           truncate (other fields might follow). */
                        else if (strchr(tok, ',')) {
                                tok = strtok(tok, "\t ");
                                /* Strip trailing comma. */
                                if (tok[strlen(tok)-1] == ',')
                                        tok[strlen(tok)-1] = '\0';
                        } else if (tok[0] == '-'
                                   && (tok[1] == '\0' || isspace(tok[1])))
                                tok = "";
                        printf(" %s", tok);
                }
                printf("\n");
            }
        fclose(file);
        exit(0);
        }

        else if ((argc == 2) && ((argv[1][0] == '-' && argv[1][1] == 'g')||(argv[1][0] == '-' && argv[1][1] == 'l'))) {
            char arr[5000][4096];
			char temp[4096];
            int numarr[5000] = {0}, i = 0, j = 0, arrnum = 0, key;
			
            while (fgets(line, sizeof(line), file)) {
                char *tok;
                strcpy(arr[i], line);

                tok = strtok(line, " \t");
                tok = strtok(NULL, " \t\n");
                numarr[i] = atoi(tok);
                tok = strtok(NULL, " \t\n");

                i++;
                    
                }
                arrnum = i;
                
                printf("Module                  Size  Used by\n");
			
            if (argv[1][1] == 'g'){ // Descending order
			
                for(i = 1;i < arrnum; i++){
                    key = numarr[i];
                    strcpy(temp, arr[i]);
                    for(j = i - 1; j >= 0 && numarr[j] < key; j--){
                        numarr[j+1] = numarr[j];
                        for(int k = 0; k < 4096; k++) arr[j+1][k] = '\0';
                        strcpy(arr[j+1], arr[j]);
					
					}
                    for(int k = 0; k < 4096; k++) arr[j+1][k] = '\0';
                    strcpy(arr[j+1], temp);                    
                    for(int k = 0; k < 4096; k++) temp[k] = '\0';
                }
                for(i = 0;i < arrnum; i++){
                    char *tok;

                    tok = strtok(arr[i], " \t");
                    printf("%-19s", tok);
                    tok = strtok(NULL, " \t\n");
                    printf(" %8s", tok);
	  			    tok = strtok(NULL, " \t\n");
                    
                    if (tok) {
                        printf("  %s", tok);
                        tok = strtok(NULL, "\n");
                        if (!tok)
                            tok = "";
                        
                        else if (strchr(tok, ',')) {
                            tok = strtok(tok, "\t ");
                                
                            if (tok[strlen(tok)-1] == ',')
                                tok[strlen(tok)-1] = '\0';
                        } 
                        else if (tok[0] == '-' && (tok[1] == '\0' || isspace(tok[1])))
                            tok = "";
                        printf(" %s", tok);
                    }
                    printf("\n");

                }				
				
            }
            else if (argv[1][1] == 'l'){ // Ascending order
                for(i = 1;i < arrnum; i++){
                    key = numarr[i];
                    strcpy(temp, arr[i]);
                    for(j = i - 1; j >= 0 && numarr[j] > key; j--){
                        numarr[j+1] = numarr[j];
                        for(int k = 0; k < 4096; k++) arr[j+1][k] = '\0';
                        strcpy(arr[j+1], arr[j]);
					
					}
                    for(int k = 0; k < 4096; k++) arr[j+1][k] = '\0';
                    strcpy(arr[j+1], temp);                    
                    for(int k = 0; k < 4096; k++) temp[k] = '\0';
                }
                for(i = 0;i < arrnum; i++){
                    char *tok;

                    tok = strtok(arr[i], " \t");
                    printf("%-19s", tok);
                    tok = strtok(NULL, " \t\n");
                    printf(" %8s", tok);
	  			    tok = strtok(NULL, " \t\n");
                    
                    if (tok) {
                        printf("  %s", tok);
                        tok = strtok(NULL, "\n");
                        if (!tok)
                            tok = "";
                        
                        else if (strchr(tok, ',')) {
                            tok = strtok(tok, "\t ");
                                
                            if (tok[strlen(tok)-1] == ',')
                                tok[strlen(tok)-1] = '\0';
                        } 
                        else if (tok[0] == '-' && (tok[1] == '\0' || isspace(tok[1])))
                            tok = "";
                        printf(" %s", tok);
                    }
                    printf("\n");

                }			
            
			
            }
        }
		
        else { // If the user types wrong arguments. (two or more)
            print_usage("lsmod");
        }
}
