#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rManna=0, pManna=0, rGold=0, pGold=0, occupied=0;
char* game_name="http://cgi.cs.mcgill.ca/~naharo/cgi-bin/challenge.py";
char* csv="resources.csv";
const char * redirect_page_format =
"<html>\n"
"<head>\n"
"<meta http-equiv=\"REFRESH\"\n"
"content=\"0;url=%s\">\n"
"</head>\n"
"</html>\n";

//drop n gold pieces
//for every 2 gold pieces user gets 1 manna from the universe
//the gold pieces are added to the hidden resources of the room
//and removed from the player's inventory
int drop(n){
	if (pGold>2*n){
		rGold=rGold+2*n;
		pGold=pGold-2*n;
		pManna=pManna+n;
		writeCsv();
		refresh();
		return 0;
	}
	refresh();
	return -1;
	
}


//activates the room's game
int play(){
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf (redirect_page_format, game_name);
	return 0;
}


//writes new CSV with updated gold/manna/occupied
int getCsv(){
	FILE *f = fopen(csv, "r");
	fscanf(f, "%d,%d,%d", &rManna, &rGold, &occupied);
	fclose(f);
	return 0;
}


int writeCsv(){
	FILE *f = fopen(csv, "w");
	fprintf(f, "%d,%d,%d", rManna, rGold, occupied);
	fclose(f);
	return 0;
}

//marks room as not occupied
//all of the player's manna and gold are added to the room's hidden resources
//sorry to leave screen is displayed
int exit1(){
	rManna=pManna+rManna;
	rGold=pGold+rGold;
	occupied=0;
	writeCsv();
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<h1>Sorry to see you leave.");
	return 0;
}

//redraw the screen with the player's inventory preserved
int refresh(){
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf (redirect_page_format, getenv ("HTTP_REFERER"));
	return 0;
}


int error1(char* command){
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("Error. Command not found.");
	
	// printf(file);

	printf("<html>\n");
	printf("<h1>hello, your command was:%s\n", command);
	return 0;
}
//read command and compare
int main(void){
	//general variables

	getCsv();

	//get from POST
	char *data=getenv("QUERY_STRING");
	int n=0;
	data=data+strlen("user_input=");

	
	char *command=strtok(data, "+");
	//should the compariswon be made regardless of case?
	if (strcmp(command, "DROP")==0){
		n=atoi(strtok(NULL, "+"));
		drop(n);
	}
	else if (strcmp(command, "PLAY")==0)
		play();
	else if (strcmp(command, "EXIT")==0)
		exit1();
	else if (strcmp(command, "REFRESH")==0)
		refresh();
	else
		error1(command);

	//output to browser


	//manna and gold pieces cannot go below 0, 
	//player cannot take them when below zero
}



