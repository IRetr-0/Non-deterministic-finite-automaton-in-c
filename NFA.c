/*
This software aims to simulate any Nondeterministic finite automaton using only matrices as data
structures. This software is distributed "as is" and can be modified at will by whoever wishes

like steal it for ur uni homework, Really don't care.
Plz no sellerino this.

Made by Retr_0 and Leonardo Rick;
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<locale.h>

int main()
{
	
	//_______________________________________________var declaration________________________________________________
    
	//util
	int i, j, k, l, m;
	int temp_final;
	int flag_final = 0;
	
	//readfile
	char alphabet[10]; //array of chars for the accepted symbols
	int final_states[20]; //arry of accepted states
	int alphabet_size, state_qty, fstate_qty, transition_qty, word_qty;
	
	//transition temp vars
	int temp_initial, temp_accepted;
	char temp_letter;
	
	//readfie - words
	char word[102] = {0};
	int word_size = 0;
	int letterToNum = 0;
	
	//arrays
	int delta[20][10][20]; //transition matrice [state][letter][stateTo]
	int aux[20];
	int aux2[20];
	
	//_______________________________________________array init_______________________________________________
	
	//Acepted states array
	for(i=0;i<20;i++){
		final_states[i] = 0;
	}
	
	//Matrice delta 3x3
	for(i=0;i<20;i++){
		for(j=0;j<10;j++){
			for(k=0;k<20;k++){
				delta[i][j][k] = 0;
			}		
		}	
	}
	//Aux arrays (used in transitions)
	aux[0] = 1;
	aux2[0] = 0;
	for (i=1; i<20; i++){
		aux[i] = 0;
		aux2[i] = 0;
	}
	
	//__________________________________________________readfile__________________________________________________
	
	//input.txt input file used
	FILE *fp;
	fp = fopen("input.txt","r");
	
	//tests if the file is open
	if(fp == NULL){
		printf("Error: File not found\n");
		return -1;
	}
	
	fscanf(fp,"%s", alphabet); // reads the alphabet
	fscanf(fp,"%d",&state_qty); //reads the ammount of states
	fscanf(fp,"%d",&fstate_qty); //reads the ammount of accepted states
	
	for(i=0;i<fstate_qty;i++){ // generates the accepted states array
		fscanf(fp, "%d", &temp_final);
		final_states[temp_final] = 1; 
	}
	fscanf(fp,"%d",&transition_qty); //reads the ammount of transitions
	
	alphabet_size = strlen(alphabet);//gets the ammount of chars on the alphabet
	
	printf("Alphabet: %s\n", alphabet);
	printf("Alphabet size: %d\n\n", alphabet_size);
	printf("Ammount of states %d\n", state_qty);
	printf("Ammount of accepted states: %d\n", fstate_qty);
	printf("Accepted states array: [ ");
	
	for(i=0;i<20;i++){
		printf("%d ", final_states[i]);
	}
	printf("]\n\n");		
	
	printf("Ammount of transitions: %d\n", transition_qty);
	
	
	//Reading and storing transitions on Delta
	for(i = 0; i < transition_qty; i++){
		
		fscanf(fp,"%d %c %d", &temp_initial,&temp_letter,&temp_accepted);
		printf("Delta(q%d,%c)=q%d\n", temp_initial,temp_letter,temp_accepted);
		
		int actual_letter = temp_letter - 'a';
		
		delta[temp_initial][actual_letter][temp_accepted] = 1;
	
	}
	
	/*
	//dev print, Prints the Delta matrice, removed cuz of spam
	printf("\nDelta:");
	printf("\n__________________________________________________________________________________________\n");
	
	for(i = 0; i < 20; i++){
		for(j = 0; j < 10; j++){
			printf("delta[%d][%d] = [", i, j);
			for(k = 0; k < 20; k++){
				printf(" %d ", delta[i][j][k]);
			}
			printf("]\n");		
		}	
	}
	printf("__________________________________________________________________________________________\n");
	
	*/
	
	//reads the inputed words 
		
	fscanf(fp,"%d",&word_qty); //reads the ammount of words inputed
	printf("\nAmmount of words: %d\n", word_qty);
	
	for(k = 0; k < word_qty; k++){

        fscanf(fp, "%s", word);
        printf("\n%s",word);
    	word_size = strlen(word);
		
	//___________________________________________Transitioning each word___________________________________________
	
		for(i = 0; i < word_size; i++){			
			char letter = word[i];
			letterToNum = letter - 'a';
			
			for(l = 0; l < 20 ; l ++){
				if (aux[l] == 1){
 					for (m = 0; m < 20; m++){
					 	if(delta[l][letterToNum][m] == 1){
					 		aux2[m] = 1;
						}
					}
				}
			}
					 
			for (m = 0; m < 20; m ++){
			 	aux[m] = aux2[m];
			 	aux2[m] = 0;
			}
								
			/*
			//dev print for the aux array
			printf("\naux: [ ");
			for (j = 0; j < 20; j++){
				printf("%d ", aux[j]); 
			}
			printf("]\n");
			*/
		}
		
		//Checking for valid word
		
		for(j=0; j < 20; j++){
			if(aux[j] == 1 && final_states[j] == 1){
				flag_final = 1;
			}
		}
		
		if (flag_final == 1){
			printf(" ok!");
			flag_final = 0;
		}
		else{
			printf(" not ok");
		}
		//resseting the aux array
		aux[0] = 1;
		for (m = 1; m < 20; m ++){
			aux[m] = 0;
		}
	}

	return 0;		
}

