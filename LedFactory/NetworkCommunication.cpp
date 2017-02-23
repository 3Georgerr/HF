// 
// 
// 

#include "NetworkCommunication.h"


/**
 * queryString: the string with is to be parsed.
  * WARNING! This function overwrites the content of this string. Pass this function a copy
   * if you need the value preserved.
    * results: place to put the pairs of param name/value.
	 * resultsMaxCt: maximum number of results, = sizeof(results)/sizeof(*results)
	  * decodeUrl: if this is true, then url escapes will be decoded as per RFC 2616
	   */

int NetworkCommunication::parseUrlParams(char *queryString, char *results[][2], int resultsMaxCt, boolean decodeUrl) {
	int ct = 0;

	while (queryString && *queryString && ct < resultsMaxCt) {
		results[ct][0] = strsep(&queryString, "&");
		results[ct][1] = strchrnul(results[ct][0], '=');
		if (*results[ct][1]) *results[ct][1]++ = '\0';

		if (decodeUrl) {
			percentDecode(results[ct][0]);
			percentDecode(results[ct][1]);
		}

		ct++;
	}

	return ct;
}

void NetworkCommunication::loop()
{
		 index = 0;
		 resultsCt = 0;
		EthernetClient client = server.available();

		if (client) {
			// an http request ends with a blank line
			boolean current_line_is_blank = true;
			// reset the input buffer
			index = 0;
			while (client.connected()) {
				if (client.available()) {
					char c = client.read();
					// If it isn't a new line, add the character to the buffer
					if (c != '\n' && c != '\r') {
						clientline[index] = c;
						index++;
						// are we too big for the buffer? start tossing out data
						if (index >= BUFSIZ)
							index = BUFSIZ - 1;
						// continue to read more data!
						continue;
					}
					// got a \n or \r new line, which means the string is done
					clientline[index] = 0;
					// Print it out for debugging
					//	Serial.println(clientline);
					// Look for substring such as a request to get the root file
					if (strstr(clientline, "GET / ") != 0) {
						// send a standard http response header
						client.println("HTTP/1.1 200 OK");
						client.println("Content-Type: text/html");
						client.println();
						// print all the files, use a helper to keep it clean
						client.println("<h2>Files:</h2>");
						client.println(clientline);
					}
					else if (strstr(clientline, "GET /") != 0) {
						// this time no space after the /, so a sub-file!
						char *filename;
						filename = clientline + 5; // look after the "GET /" (5 chars)
												   // a little trick, look for the " HTTP/1.1" string and 
												   // turn the first character of the substring into a 0 to clear it out.
						(strstr(clientline, " HTTP"))[0] = 0;
						// print the file we want
					//	Serial.println(filename);
						/*   if (! file.open(&root, filename, O_READ)) {
						client.println("HTTP/1.1 404 Not Found");
						client.println("Content-Type: text/html");
						client.println();
						client.println("<h2>File Not Found!</h2>");
						break;
						}
						*/
						//	Serial.println("Opened!");
						client.println("HTTP/1.1 200 OK");
						client.println("Content-Type: text/plain");
						client.println();
						int16_t c;
						// while ((c = file.read()) > 0) {
						// uncomment the serial to debug (slow!)
						//Serial.print((char)c);
						client.println(clientline);

						/*

						//char buf[BUFSIZ];
						char *params[5][2];
						// copy test[i] into the buffer
						// because the parser overwrites what is i the string it is passed. And copy shifted to 5 letter - "GET /"
						//strcpy nefunguje ok s posunem
						//strcpy(buf, clientline);
						//memmove ok, ale zbytecne pouzivat dalsi buffer
						//memmove(buf, &clientline[5],BUFSIZ-5);
						// parse the buffer into params[][]
						//pokud bychom pouzili buffer
						//int resultsCt = parseUrlParams(bud, params, 5, true);
						resultsCt = parseUrlParams(&clientline[5], params, 5, true);

						client.println("\" produced ");
						client.println(resultsCt);
						client.println(" parameters:");
						client.println();
						
						for (int i = 0; i < resultsCt; i++) {
							client.println("param ");
							client.println(i);
							client.println(" name \"");
							client.println(params[i][0]);
							client.println("\", param \"");
							client.println(params[i][1]);
							client.println("\".");
							client.println();
						}
						*/
						// }
						//          file.close();
					}
					else {
						// everything else is a 404
						client.println("HTTP/1.1 404 Not Found");
						client.println("Content-Type: text/html");
						client.println();
						client.println("<h2>File Not Found!</h2>");
					}
					break;
				}
			}
			// give the web browser time to receive the data
			delay(1);
			client.stop();
		}
	
}

void NetworkCommunication::start()
{
	//uint8_t macv[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	//Ethernet.begin(macv, IPAddress(10, 0, 0, 34), IPAddress(8, 8, 8, 8), IPAddress(10, 0, 0, 138));
	Ethernet.begin(this->mac, this->myIP);
	server.begin();
}

uint8_t NetworkCommunication::getResults()
{
	return resultsCt;
}

NetworkCommunication::NetworkCommunication(uint8_t mac[6], IPAddress myIP)
{
	this->myIP = myIP;
	for (int i = 0; i < 6; i++) {
		this->mac[i] = mac[i];
	}
	index = 0;
	resultsCt = 0;	
}

/**
 * Perform URL percent decoding.
  * Decoding is done in-place and will modify the parameter.
   */
void NetworkCommunication::percentDecode(char * src)
{
	char *dst = src;

	while (*src) {
		if (*src == '+') {
			src++;
			*dst++ = ' ';
		}
		else if (*src == '%') {
			// handle percent escape

			*dst = '\0';
			src++;

			if (*src >= '0' && *src <= '9') {
				*dst = *src++ - '0';
			}
			else if (*src >= 'A' && *src <= 'F') {
				*dst = 10 + *src++ - 'A';
			}
			else if (*src >= 'a' && *src <= 'f') {
				*dst = 10 + *src++ - 'a';
			}

			// this will cause %4 to be decoded to ascii @, but %4 is invalid
			// and we can't be expected to decode it properly anyway

			*dst <<= 4;

			if (*src >= '0' && *src <= '9') {
				*dst |= *src++ - '0';
			}
			else if (*src >= 'A' && *src <= 'F') {
				*dst |= 10 + *src++ - 'A';
			}
			else if (*src >= 'a' && *src <= 'f') {
				*dst |= 10 + *src++ - 'a';
			}

			dst++;
		}
		else {
			*dst++ = *src++;
		}

	}
	*dst = '\0';
}
