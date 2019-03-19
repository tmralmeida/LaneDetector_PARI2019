/**
 *      @file  server.cpp
 *      @brief  Complete TCP/IP server that deals with multiple clients
 *
 *	Based on http://www.linuxhowtos.org/C_C++/socket.htm
 *	A simple server in the internet domain using TCP
 *	The port number is passed as an argument 
 *	This version runs forever, forking off a separate 
 *	process for each connection
 *
 *     @author  The main function Vitor Santos, vitor@ua.pt And the process Client Tiago Almeida, tm.almeida@ua.pt
 *     @date   Dez 2015-2018 and 2019
 *
 * =====================================================================================
 */

#define _MAIN_C_
#include "myserver.h"
/**
 * @brief Test if a server is responding in a given port
 *
 * @param  adrr - String with the IP address
 * @param  port - Integet with the port number
 * @param  tv -   Address of a struct timeval with the timeout
 *                NB. On returning, the tv structure holds the time
 *                left after the connection attempt. Can be useful to assess
 *                the speed of the connection.
 * @return srv_status value (NOTAVAILABLE, PORTOPEN, PORTCLOSED, ...)
 */

int main(int argc, char *argv[])
{
	int sockfd, clientsockfd, portno, pid;
	int ret;
	char clntName[INET_ADDRSTRLEN]; // String to contain client name
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	//To avoid defuncts due to the fork() below.
	//It is actually the default action and occurs when Child stopped or terminated
	signal(SIGCHLD, SIG_IGN);

	//To catch CTRL_C and allow the closure of port
	signal(SIGINT, ManageCTRL_C);

	if (argc < 2)
	{
		fprintf(stderr, "Syntax: %s <port_num>\n", argv[0]);
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //create a INET socket to communicate
	if (sockfd < 0)
		myerror("ERROR opening socket");

	bzero((char *)&serv_addr, sizeof(serv_addr)); //fill with zeros
	portno = atoi(argv[1]);						  //get port number from command line
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //bind the name to the socket
	if (ret < 0)
		myerror("ERROR on binding");

	listen(sockfd, 20); //start waiting for connections on the socket up to a maximum of 20 connections
	clilen = sizeof(cli_addr);

	//make socket non blocking so other events may be processed inside the infinite loop
	//An equivalent action could also be done at the socket creation...
	int flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	//até aqui é sempre igual
	infinite_loopG = 1;
	//-------------------------------------------------------------------------
	do
	{
		clientsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); //accept the connection
		if (clientsockfd < 0)												  //some error occured.
		{
			if (errno == EAGAIN)
				continue; //simply absence of data on nonblocking socket. Not really an error.
			myerror("ERROR on accept");
		}

		/*notify that you know the client: this is optional */
		if (inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
			printf("Client %s connected/%d\n", clntName, ntohs(cli_addr.sin_port));
		else
			printf("Unable to get client address\n");

		pid = fork(); //create a process child to manage the connection
		if (pid < 0)
			myerror("ERROR on fork"); //rare but may occur!
		if (pid == 0)				  //It is the child... proceed accordingly
		{
			close(sockfd);						   //child no longer needs the parent socket. Close it, after all it's simply a handle
												   //Cf. http://stackoverflow.com/questions/14427898/socket-from-parent-to-child
			processclient(clientsockfd, clntName); //Process client request (a new process)
			exit(0);							   //Exits when finishing processing the client request
		}
		else
		{ //It is the parent... does nothing: closes the client socket and resume accepting...
			close(clientsockfd);
		}
		usleep(1000000);
	} while (infinite_loopG);

	close(sockfd);
	return 0; /* we only get here when someone breaks the infinite loop */
}

/**
 * @brief  Function to process client request in this case with simple request and the main request: an image!!
 *
 * There will be a separate instance of this function 
 * for each connection established by clients. It handles 
 * all communications once a connection has been established.
 *
 * @param  sock The socket ID
 * @param  clientID The client ID (normally the IP)
 * @return  Nothing. It will return to terminate immediatly
 */

using namespace cv;
using namespace std;

void processclient(int sock, char *clientID)
{
	const int BUFFSIZE = 1024; /*If this is small, enlarge it or use dynamic allocation */
	int n, numBytesSent, bufLen;
	char inbuffer[BUFFSIZE], outbuffer[BUFFSIZE], *str;
	int keepGoing = 1;
	char nameofimage[50];
	char number_image[3];
	int bytes;
	int number_totimages = 10;
	int bytesTransferred;
	int imgSize;
	char str_cols[7] = {0};
	char str_rows[7] = {0};
	char str_size[50] = {0};
	int number_cols = 0;
	int number_rows = 0;
	Mat frame;
	count_images = 0;

	while (keepGoing)
	{
		bzero(inbuffer, BUFFSIZE); //empty buffer
		n = recv(sock, inbuffer, BUFFSIZE - 1, 0);
		if (n == BUFFSIZE - 1) //means read the entire buffer... there is the chance that more data may be waiting
		{
			printf("Buffer filled\n");
			//mysocketflush(sock);
			//in that case additional memory should be allocated
			//to read the remainder of the message and build it entirely to deal with it.
			//Not done in this example but may be necessary if large bunchs of data were sent from client.
		}
		if (n < 0)
			myerror("ERROR reading from socket");

		if (strlen(inbuffer) > 0)
			printf("Message received from the client %s: %s\n", clientID, inbuffer);

		if (strncmp(inbuffer, "estou a pedir uma ligacao ao servidor", sizeof("estou a pedir uma ligacao ao servidor")) == 0)
		{
			sprintf(outbuffer, "You are connected to Server...\n");
			bufLen = strlen(outbuffer);
			numBytesSent = send(sock, outbuffer, bufLen, 0);
			if (numBytesSent < 0)
			{
				myerror("send()/write() failed");
			}
		}
		else if (strncmp(inbuffer, "quit", 4) == 0)
		{
			sprintf(outbuffer, "Closing the program...\n");
			keepGoing = 0;
			bufLen = strlen(outbuffer);
			numBytesSent = send(sock, outbuffer, bufLen, 0);
			if (numBytesSent < 0)
			{
				myerror("send()/write() failed");
			}
		}
		else if (strncmp(inbuffer, "imagem anterior", sizeof("imagem anterior")) == 0)
		{
			nameofimage[50] = {0};
			number_image[3] = {0};
			bytes = 0;
			bytesTransferred = 0;
			imgSize = 0;
			count_images--;
			if (count_images == 0)
			{
				count_images--;
			}
			if (count_images > 10)
			{
				count_images = 1;
			}
			if (count_images < 0)
			{
				count_images = number_totimages;
			}

			strcpy(nameofimage, "IMG");
			sprintf(number_image, "%d", count_images);
			strcat(nameofimage, number_image);
			strcat(nameofimage, ".jpg");

			frame = imread(nameofimage, CV_LOAD_IMAGE_COLOR);
			if (!frame.data) // Check for invalid input
			{
				cout << "Could not open or find the image" << std::endl;
			}

			//Para enviar o tamanho da imagem:

			number_cols = frame.cols;
			number_rows = frame.rows;

			sprintf(str_cols, "%d", number_cols);
			strcpy(str_size, str_cols);
			sprintf(str_rows, "%d", number_rows);
			strcat(str_size, ",");
			strcat(str_size, str_rows);
			//printf("\nTamanho da imagem:%s\n", str_size);
			//printf("\nTamanho da string:%d\n", (int)strlen(str_size));
			numBytesSent = send(sock, str_size, sizeof(str_size), 0);
			if (numBytesSent < 0)
			{
				myerror("send()/write() failed");
			}
		}

		//Here you can add other elseifs
		else if (strncmp(inbuffer, "mais uma imagem", sizeof("mais uma imagem")) == 0)
		{
			nameofimage[50] = {0};
			number_image[3] = {0};
			bytes = 0;
			bytesTransferred = 0;
			imgSize = 0;
			count_images++;

			if (count_images == 0)
			{
				count_images++;
			}
			if (count_images > 10)
			{
				count_images = 1;
			}
			if (count_images < 0)
			{
				count_images = number_totimages;
			}

			strcpy(nameofimage, "IMG");
			sprintf(number_image, "%d", count_images);
			strcat(nameofimage, number_image);
			strcat(nameofimage, ".jpg");

			frame = imread(nameofimage, CV_LOAD_IMAGE_COLOR);
			if (!frame.data) // Check for invalid input
			{
				cout << "Could not open or find the image" << std::endl;
			}

			//Para enviar o tamanho da imagem:
			number_cols = frame.cols;
			number_rows = frame.rows;
			sprintf(str_cols, "%d", number_cols);
			strcpy(str_size, str_cols);
			sprintf(str_rows, "%d", number_rows);
			strcat(str_size, ",");
			strcat(str_size, str_rows);
			//printf("\nTamanho da imagem:%s\n", str_size);
			//printf("\nTamanho da string:%d\n", (int)strlen(str_size));
			numBytesSent = send(sock, str_size, sizeof(str_size), 0);
			if (numBytesSent < 0)
			{
				myerror("send()/write() failed");
			}
		}
		else if (strncmp(inbuffer, "agora manda-me a imagem", sizeof("agora manda-me a imagem")) == 0)
		{
			//Enviar a imagem:
			frame = (frame.reshape(0, 1)); // to make it continuous
			imgSize = frame.total() * frame.elemSize();

			while (bytesTransferred < imgSize)
			{

				bytes = send(sock, frame.data, imgSize, 0);
				if (bytes < 0)
				{
					perror("send_size()");
					exit(errno);
				}
				bytesTransferred += bytes;
				if (bytesTransferred != 0)
				{
					printf("\nNumero de bytes enviados do servidor:%d\n", bytesTransferred);
				}
			}
			frame.release();
		}
	}
	printf("\nConnection to client %s terminated.\n", clientID);
}
