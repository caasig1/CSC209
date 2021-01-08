#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char board[9];
int turn = 1;
struct client {
    int fd;
    struct in_addr ipaddr;
    struct client *next;    
}
*top = NULL;
struct client *p1 = NULL;
struct client *p2 = NULL;
char *symbols = "xo";

static int listenfd;

void showboard(int fd);
void newconnection();
void activity(struct client *user);
void setboard();
void makemove(struct client *user, char *move);
void send_all_but_one(char *message, struct client *user, int size);

int game_is_over();
int allthree(int start, int offset);
int isfull();

int main(int argc, char **argv)
{
    int c, port = 3000, status = 0;
    struct sockaddr_in r;
    struct client *p;

    while ((c = getopt(argc, argv, "p:")) != EOF) {
        switch (c) {
        case 'p':
            port = atoi(optarg);
            break;
        default:
            status = 1;
        }
    }
    if (status || optind < argc) {
        fprintf(stderr, "usage: %s [-p port]\n", argv[0]);
        return(1);
    }

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return(1);
    }

    memset(&r, '\0', sizeof r);
    r.sin_family = AF_INET;
    r.sin_addr.s_addr = INADDR_ANY;
    r.sin_port = htons(port);
    if (bind(listenfd, (struct sockaddr *)&r, sizeof r) < 0) {
        perror("bind");
        return(1);
    }
    if (listen(listenfd, 5)) {
        perror("listen");
        return(1);
    }

    setboard(); // Initialize the board

    while (1){
	// make an fd list of everyclient in the linked list, including the listening fd
	fd_set fds;
	int maxfd = listenfd;
	FD_ZERO(&fds);
	FD_SET(listenfd, &fds); // add the listening fd
	for (p = top; p; p = p->next){ // add all client fds
		FD_SET(p->fd, &fds);
		if (p->fd > maxfd){
			maxfd = p->fd;
		}
	}
	if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0) {
		perror("select");
	} else {
		// find the first thing in the linked list that select returns, meaning it wants to read/write
		for (p = top; p; p = p->next)
			if (FD_ISSET(p->fd, &fds))
				break;
		if (p)
			activity(p); // do something with p
		if (FD_ISSET(listenfd, &fds)) // if there is someone else trying to connect
			newconnection();
	}
    }
    return 0;
}

void activity(struct client *user){
    // there is something happening accoring to the select
    char *recmsg = malloc(sizeof(char) * 102);
    if (recmsg == NULL) {
	fprintf(stderr, "out of memory!\n");
	exit(1);
    }
    memset(recmsg, '\0', 102);
    int bytes = 0;
    int len = 1;
    while (recmsg[bytes - 1] != '\n' && len != 0) {
	if ((len = read(user->fd, recmsg + bytes, 1)) < 0){
	    perror("read");
	    exit(1);
	}
	bytes += len;
    }
    if (len > 0) {
        if (isdigit(recmsg[0]) && (recmsg[1] == '\r' || recmsg[1] == '\n')) {
		if (user != p1 && user != p2) {
			write(user->fd, "You can't make moves; you can only watch the game\r\n", 51);
		} else {
			makemove(user, recmsg);
		}
        } else {
	        recmsg[100] = '\r';
	        recmsg[101] = '\n';
	        recmsg[102] = '\0';
		send_all_but_one(recmsg, user, 101);
		printf("chat message: %s", recmsg);
        }
    } else if (len == 0) {
        printf("disconnecting client %s\n", inet_ntoa(user->ipaddr));
        fflush(stdout);
	struct client **p;
	for (p = &top; *p && (*p)->fd != user->fd; p = &(*p)->next);

	// msg is the message to the client you are talking to
	// msgo is the message sent to everyone else but the client (o for other)
	char *msg = malloc(200);
        char *msgo = malloc(200);
        if (msg == NULL || msgo == NULL){
            fprintf(stderr, "out of memory!\n");
            exit(1);
        }
	memset(msg, '\0', 200);
	memset(msgo, '\0', 200);
	strcat(msg, "Now you get to play! You are now ");
	if (user == p1){
	    struct client *n;
	    int indicator = 1;
	    for(n = top; n; n = n-> next){
		if (n != user && n != p2) {
			p1 = n;
			strcat(msgo, inet_ntoa(p1->ipaddr));
			strcat(msgo, " is now playing '");
			if (symbols[0] == 'x') {
				strcat(msg, "x");
				strcat(msgo, "x");
			} else {
				strcat(msg, "o");
				strcat(msgo, "o");
			}			
			strcat(msg, ".\r\n");
			strcat(msgo, "'.\r\n");
			write(p1->fd, msg, 200);
			indicator = 0;
			send_all_but_one(msgo, p1, 200);
			
			free(msg);
			free(msgo);
			break;
		}
	    }
	    if (indicator) {
		p1 = NULL;
	    }
	} else if (user == p2){
	    struct client *n; 
            int indicator = 1;
            for(n = top; n; n = n-> next){
                if (n != user && n != p1) {
                        p2 = n;
                        strcat(msgo, inet_ntoa(p2->ipaddr));
                        strcat(msgo, " is now playing '");
                        if (symbols[1] == 'x') {
                                strcat(msg, "x");
                                strcat(msgo, "x");
                        } else {
                                strcat(msg, "o");
                                strcat(msgo, "o");
                        }
                        strcat(msg, ".\r\n");
                        strcat(msgo, "'.\r\n");
                        write(p2->fd, msg, 200);
                        indicator = 0;
                        send_all_but_one(msgo, p2, 200);
			
			free(msg);
			free(msgo);
                        break;
		}
            }   
            if (indicator) {
                p2 = NULL;
            }
	}

	if (*p) {
	    struct client *t = (*p) -> next;
	    free(*p);
	    *p = t;
	} else {
	    fprintf(stderr, "trying to remove something that doesnt exist\n");
            fflush(stderr);
	}
    }
    free(recmsg);
}

void newconnection(){
    int fd;
    struct sockaddr_in r;
    socklen_t socklen = sizeof r;
    
    if ((fd = accept(listenfd, (struct sockaddr *) &r, &socklen)) < 0) {
	perror("accept");
    } else {
	struct client *p = malloc (sizeof(struct client));
	if (!p){
	    fprintf(stderr, "no memory\n");
	    exit(1);
	}
    	fflush(stdout);
	p->fd = fd;
	p->ipaddr = r.sin_addr;
	p->next = top;
	top = p;
	showboard(fd);
    	printf("new connection from %s\n", inet_ntoa(r.sin_addr));
        
	// send1 is It is _'s turn
	char *send1;
	if (symbols[turn - 1] == 'x'){
	    send1 = "It is x's turn.\r\n";	
	} else {
	    send1 = "It is o's turn.\r\n";
	}
	
	write(p->fd, send1, 17);

	// send2 is the message Now you get to play! You are now _.
	// send3 is the message IP address is now playing '_'.
	char *send2;
	char *send3 = malloc(200);
	memset(send3, '\0', 200);
	strcat(send3, inet_ntoa(r.sin_addr));
	strcat(send3, " is now playing '");
	if (p1 == NULL) {
	    p1 = p;
	    if (symbols[0] == 'x'){
		send2 = "Now you get to play! You are now x.\r\n"; 
		strcat(send3, "x");
	    } else {
		send2 = "Now you get to play! You are now o.\r\n"; 
	        strcat(send3, "o");
	    }
	    strcat(send3, "'.\r\n");
	    write(p1->fd, send2, 37);
	    send_all_but_one(send3, p1, 200);	
	    printf("cient from %s is now %c\n", inet_ntoa(r.sin_addr), symbols[0]);
        } else if (p2 == NULL) {
	    p2 = p;
	    if (symbols[1] == 'x'){
                send2 = "Now you get to play! You are now x.\r\n";
            	strcat(send3, "x");
	    } else {
                send2 = "Now you get to play! You are now o.\r\n";
            	strcat(send3, "o");
	    }
	    strcat(send3, "'.\r\n");
            write(p2->fd, send2, 37);
	    send_all_but_one(send3, p2, 200);
	    printf("cient from %s is now %c\n", inet_ntoa(r.sin_addr), symbols[1]);
        }
	free(send3);
    }
}

void makemove(struct client *user, char *move){
    // move is 1-9 and user is p1 or p2
    if((user == p1 && turn == 2) || (user == p2 && turn == 1)) {
	write(user->fd, "It is not your turn\r\n", 21);
    	printf("%s tries to make move %c, but it's not their turn\n",inet_ntoa(user->ipaddr), move[0]);
    } else {
	if (board[move[0] - '1'] != move[0]) {
		write(user->fd, "That space is taken\r\n", 21);
		printf("%s tries to make move %c, but that space is taken\n",inet_ntoa(user->ipaddr), move[0]);
	} else {
	    char *msg = malloc(200);
	    memset(msg, '\0', 200);
	    if (symbols[turn-1] == 'x')
	    	strcat(msg, "x");
	    else
		strcat(msg, "o");
	    strcat(msg, " makes move ");
	    char mov[2];
	    mov[0] = move[0];
	    move[1] = '\0';
	    strcat(msg, mov);
	    strcat(msg, "\n");
	    printf("%s (%c) makes move %s\n", inet_ntoa(p1->ipaddr),symbols[turn - 1], move);
	    if (user == p1) {
	        board[move[0] - '1'] = symbols[0];
		turn = 2;
	    } else {
		board[move[0] - '1'] = symbols[1];
		turn = 1;
	    }
	    struct client *p;
	    for (p = top; p; p = p->next){
		write(p->fd, msg, 200);
		showboard(p->fd);
	    }
	    memset(msg, '\0', 200);

	    strcat(msg, "It is ");
	    if (symbols[turn-1] == 'x')
                strcat(msg, "x");
            else
                strcat(msg, "o");
	    strcat(msg, "'s turn.\r\n");
	    for (p = top; p; p = p->next){
                if (turn == 1 && p == p1) {
		    write(p1->fd, "It is your turn.\r\n", 18);      
		} else if (turn == 2 && p == p2) {
		    write(p2->fd, "It is your turn.\r\n", 18);
		} else {
		    write(p->fd, msg, 200);
		}
            }
	    free(msg);

	    int results = game_is_over();
            if (results != 0) {
		char *message;    
		for (p = top; p; p = p->next){
                	write(p->fd, "Game over!\r\n", 12);
			showboard(p->fd);
            		if (results == 'x'){
				write(p->fd, "x wins.\r\n", 9);
				message = "x wins.\n";
                	} else if (results == 'o'){
				write(p->fd, "o wins. \r\n", 9);
				message = "o wins.\n";
			} else {
				write(p->fd, "It is a draw.\r\n", 15);
				message = "It is a draw.\n";
			}
			write(p->fd, "Let's play again!\r\n", 19);
		}
		printf("Game over!\n");
		printf("%s", message);
		if ((strcmp(symbols, "xo")) == 0) {
			symbols = "ox";
			write(p2->fd, "You are x.\r\n", 12);
			write(p1->fd, "You are o.\r\n", 12);
		} else {
			symbols = "xo";
			write(p2->fd, "You are o.\r\n", 12);
			write(p1->fd, "You are x.\r\n", 12);
		}
		setboard();
	    }
	}
    }
}

void send_all_but_one(char *message, struct client *user, int size){
	struct client *p;
        for (p = top; p; p = p->next){
            if (p != user)
                write(p->fd, message, size);
        }
}

void showboard(int fd)
{
    char buf[100], *bufp, *boardp;
    int col, row;

    for (bufp = buf, col = 0, boardp = board; col < 3; col++) {
        for (row = 0; row < 3; row++, bufp += 4)
            sprintf(bufp, " %c |", *boardp++);
        bufp -= 2;  // kill last " |"
        strcpy(bufp, "\r\n---+---+---\r\n");
        bufp = strchr(bufp, '\0');
    }
    if (write(fd, buf, bufp - buf) != bufp-buf)
        perror("write");
}

void setboard(){
    for (int i = 0; i < 10; i++){
	board[i] = '1' + i;
    }
}

int game_is_over()  // returns winner, or ' ' for draw, or 0 for not over
{
    int i, c;
    extern int allthree(int start, int offset);
    extern int isfull();

    for (i = 0; i < 3; i++)
        if ((c = allthree(i, 3)) || (c = allthree(i * 3, 1)))
            return(c);
    if ((c = allthree(0, 4)) || (c = allthree(2, 2)))
        return(c);
    if (isfull())
        return(' ');
    return(0);
}

int allthree(int start, int offset)
{
    if (board[start] > '9' && board[start] == board[start + offset]
            && board[start] == board[start + offset * 2])
        return(board[start]);
    return(0);
}

int isfull()
{
    int i;
    for (i = 0; i < 9; i++)
        if (board[i] < 'a')
            return(0);
    return(1);
}
