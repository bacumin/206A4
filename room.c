#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
	//general variables


	//get from POST
	char *data=getenv("QUERY_STRING");
	int i=0;
	data=data+strlen("user_input=");

	char *command=strtok(data, "+");

	//output to browser
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);


	printf("you wrote:\n %s", data);

	//info from csv
	char* csv="resources.csv";
	int manna=0, gold=0, occupied=0;


	//manna and gold pieces cannot go below 0, 
	//player cannot take them when below zero
}

/**
//drop n gold pieces
//for every 2 gold pieces user gets 1 manna from the universe
//the gold pieces are added to the hidden resources of the room
//and removed from the player's inventory
int drop(n){
	gold=gold+2;
	return 0;
}


//activates the room's game
int play(){
	return 0;
}


//writes new CSV with updated gold/manna/occupied
int csvIO(int manna, int gold, int occupied){

}

//marks room as not occupied
//all of the player's manna and gold are added to the room's hidden resources
//sorry to leave screen is displayed
int exit(){

}

//redraw the screen with the player's inventory preserved
int refresh(){
	
}
**/
