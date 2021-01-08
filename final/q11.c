fd_set read_fds;
FD_ZERO(&read_fds);
int max = clientfd[0];
for (int i = 0; i < nclients; i++){
	FD_SET(clientfd[i], &read_fds);
	if (clientfd[i] > max){
		max = clientfd[i];
	}
}

if (select(max, &read_fds, NULL, NULL, NULL) != 1){
	perror("select");
	exit(1);
}

int maxsize = 1000;
char *line;
for (int i = 0; i < nclients; i++){
        if (FD_ISSET(clientfd[i], &read_fds)){
		if (( r = read(clientfd[i], line, maxsize)) < 0 ) {
			perror("read");
		} else if (r > 0) {
			// if it reads, we only want to read one client so break the for loop
			break;
		}
		// if it is 0, then it is closed, no data has been read so continue
	}
}
