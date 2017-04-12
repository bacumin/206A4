#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rManna=0, pManna=1, rGold=0, pGold=0, occupied=0;
char* game_name="http://cgi.cs.mcgill.ca/~naharo/cgi-bin/challenge.py";
char* csv="resources.csv";
const char * redirect_page_format =
"<html>\n"
"<head>\n"
"<meta http-equiv=\"REFRESH\"\n"
"content=\"0;url=%s?inventory=%d%%2C%d\">\n"
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
"<h3> Your Manna is: %d <br>"
"             Your Gold is: %d \n"
"        </h3>"
""
"  <form action=\"room.cgi\" method=\"get\" align=\"center\">"
"  <input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">"
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
"        <form action=\"http://cs.mcgill.ca/~naharo/cgi-bin/transporter.py\">"
"        <input type=\"hidden\" name=\"inv\" value=\"%d,%d\">"
"        <input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory=%d%%2C%d&user_input=REFRESH\">"
"        <input type=\"submit\" value=\"North\" />"
"        </form>"
"      </th>"
"      <th></th>"
"    </tr>"
"    <tr>"
"      <td>"
"        <form action=\"http://cs.mcgill.ca/~naharo/cgi-bin/transporter.py\">"
"        <input type=\"hidden\" name=\"inv\" value=\"%d,%d\">"
"        <input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory=%d%%2C%d&user_input=REFRESH\">"
"        <input type=\"submit\" value=\"West\" />"
"        </form>"
"      </td>"
"      <td></td>"
"      <td>"
"        <form action=\"http://cs.mcgill.ca/~naharo/cgi-bin/transporter.py\">"
"        <input type=\"hidden\" name=\"inv\" value=\"%d,%d\">"
"        <input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory=%d%%2C%d&user_input=REFRESH\">""        <input type=\"submit\" value=\"East\" />"
"        </form>"
"      </td>"
"    </tr>"
"    <tr>"
"      <td></td>"
"      <td> <!-- SHOULD CHANGE THIS TO TRANSPORTER.PY FOR TARGET WEB PAGE -->"
"        <form action=\"http://cs.mcgill.ca/~mcamin/cgi-bin/transporter.py\">"
"        <input type=\"hidden\" name=\"inv\" value=\"%d,%d\">"
"        <input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory=%d%%2C%d&user_input=REFRESH\">"
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
int drop(int n){
	char* error_command="Error: cannot drop an odd amount of gold pieces. Cannotdrop more than the amount you have.";
	if (pGold>=n && n%2==0){
		rGold=rGold+n;
		pGold=pGold-n;
		pManna=pManna+(n/2);
		writeCsv();
		refresh("Drop was successful. Enter the next command to find out what's the question goat's goaty question!");
		return 0;
	}
	else {
		refresh(error_command);
	}
	
	return -1;

}


//activates the room's game
int play(){
/*	char command[100];
	snprintf(command, sizeof(command), "%s %d %d", "challenge.py", pManna, pGold);
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("%s", command);
	system(command);*/
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf (redirect_page_format, game_name, pManna, pGold);
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
int refresh(char* message){
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	char* page_message="You have been visited by the question goat.\nAnswer his goat-related questions for 7 years of goat luck!";
	if (strlen(message)!=0){
		page_message=message;
	}
	printf (page_print, page_message\
		,pManna, pGold, pManna, pGold,pManna, pGold,pManna, pGold, pManna, pGold,pManna, pGold, pManna, pGold,pManna, pGold,pManna \
		, pGold,pManna,pGold);
	return 0;
}


int error1(char* command){
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	char* past_url=getenv("HTTP_REFERER");
	printf(page_print,"Error. Command not found.", pManna, pGold, pManna, pGold,pManna, pGold,pManna, pGold,pManna, pGold, \
		pManna, pGold, pManna, pGold,pManna, pGold,pManna, pGold);

	return 0;
}

int game_over(){
	occupied=0;
	rGold=pGold+rGold;
	writeCsv();
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);

	FILE *f = fopen("dead.html", "r");      // open the specified file
    if (f != NULL)
    {
        int c;

        while ((c = fgetc(f)) != EOF)     // read character from file until EOF
        {
            putchar(c);                   // output character
        }
        fclose(f);
    }
	return 0;
}


int game_won(){
	occupied=0;
	writeCsv();
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	FILE *f = fopen("success.html", "r");      // open the specified file
    if (f != NULL)
    {
        int c;

        while ((c = fgetc(f)) != EOF)     // read character from file until EOF
        {
            putchar(c);                   // output character
        }
    fclose(f);
	}
}



//read command and compare
int main(void){
//general variables
getCsv();
occupied=1;
//get from GET
char *data=getenv("QUERY_STRING");
char command[50];
int n=0;

	if (strlen(data)!=0)
	{
		sscanf(data, "inventory=%d%%2C%d&user_input=%s", &pManna, &pGold, command);
		if (pManna<=0)
			game_over();
		else if (pGold>=100)
			game_won();
		else if (strncmp(command, "DROP", 4)==0 || strncmp(command, "drop", 4)==0){
			n=command[5]-'0';
			drop(n);
		}
		else if (strcmp(command, "PLAY")==0 || strcmp(command, "play")==0)
			play();
		else if (strcmp(command, "EXIT")==0 || strcmp(command, "exit")==0)
			exit1();
		else if (strcmp(command, "REFRESH")==0 || strcmp(command, "refresh")==0)
			refresh("");
		else
			error1(command);
	}
	else {
		refresh("");
	}
	writeCsv();
		

}
