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

const char * page_print=
"<!DOCTYPE html>"
"<html>"
"	<head>"
"	 <h1 style=\"color:red;text-align:center;\"> %s"
"    </h1>"
"	</head>"
"  <body background=\"http://image.shutterstock.com/z/stock-photo-seamless-pattern-with-petroglyph-goats-handmade-blue-watercolor-goats-on-white-background-222380659.jpg\">"
"    <p align=\"center\"> "
"    <img src=\"https://thinkplanrun2014.files.wordpress.com/2015/07/goat.jpg\""
"          alt=\"goat master\""
"          style=\"width:700px;height:400px;margin: 0px auto; display:block;\">"
"    </p>"
""
"  <form action=\"room.cgi\" method=\"get\" align=\"center\">"
"    <input align=\"center\" style=\"width: 750px; height 100px ; opacity:0.6;\""
"    type=\"text\" name=\"user_input\" placeholder=\"Enter your answer\">"
"    <br />"
"    <input title=\"commands: PLAY, DROP, EXIT, REFRESH\" style=\"width:100p; height:20px;\" type=\"submit\" value=\"Enter\">"
"  </form>"
""
"  <table>"
"    <tr>"
"      <th></th>"
"      <th>"
"        <form action=\"http://cs.mcgill.ca/~bcumin1/transporter.py\">"
"        <input type=\"submit\" value=\"North\" />"
"        </form>"
"      </th>"
"      <th></th>"
"    </tr>"
"    <tr>"
"      <td>"
"        <form action=\"http://google.com\">"
"        <input type=\"submit\" value=\"West\" />"
"        </form>"
"      </td>"
"      <td></td>"
"      <td>"
"        <form action=\"http://google.com\">"
"        <input type=\"submit\" value=\"East\" />"
"        </form>"
"      </td>"
"    </tr>"
"    <tr>"
"      <td></td>"
"      <td> <!-- SHOULD CHANGE THIS TO TRANSPORTER.PY FOR TARGET WEB PAGE -->"
"        <form action=\"http://cgi.cs.mcgill.ca/~mcamin/room.html\">"
"        <input type=\"submit\" value=\"South\" />"
"        </form>"
"      </td>"
"      <td></td>"
"    </tr>"
"  </table>"
"  </body>"
"</html>";

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
	printf (page_print, "THIS PAGE WAS REFRESHED");
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

	//get from GET
	char *data=getenv("QUERY_STRING");
	int n=0;
	if (strlen(data)!=0)
	{
		data=data+strlen("user_input=");
		char *command=strtok(data, "+");
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
	}
	else {
		refresh();
	}

}