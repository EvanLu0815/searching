#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct snode {
	char word;
	struct snode *child;
} node;

int FindBegin(void);

int main(void)
{
	unsigned char word;
	int i, found_pattern, j, len_msg = 0, len_msg_network = 0;

	//unsigned char SOURCE[] = {5C, 45, 27, 79, F2, 5A};

	i = 1;
	word = '1';
	while (len_msg == len_msg_network) {
		printf("%d:", i); 				// index of frame
		found_pattern = FindBegin();
		printf("\nLink layer:");						// Link layer
		printf("\n    Destination address:");
		printf("\n      01 00 5e ");
		j = 2;											// index of byte
		while ((word = getchar()) != 0xA) {
			j++;
			if (j == 6) {
				printf("\n    Source address:\n");
				printf("      ");
			} else if (j == 12) {
				printf("\n    Type:\n");
				printf("      ");
			} else if (j == 14) {
				printf("\n\nNetwork layer:\n");			// Network layer
				printf("    Version and Header length:\n");
				printf("      ");
			} else if (j == 15) {
				printf("\n    Differentiated Service Field:\n");
				printf("      ");
			} else if (j == 16) {
				printf("\n    Total Length:\n");
				printf("      ");
			} else if (j == 18) {
				printf("\n    ID:\n");
				printf("      ");
			} else if (j == 20) {
				printf("\n    Flags:\n");
				printf("      ");
			} else if (j == 21) {
				printf("\n    Offset:\n");
				printf("      ");
			} else if (j == 22) {
				printf("\n    Time to Live:\n");
				printf("      ");
			} else if (j == 23) {
				printf("\n    Protocol:\n");
				printf("      ");
			} else if (j == 24) {
				printf("\n    Header Checksum:\n");
				printf("      ");
			} else if (j == 26) {
				printf("\n    Source IP:\n");
				printf("      ");
			} else if (j == 30) {
				printf("\n    Destination IP:\n");
				printf("      ");
			} else if (j == 34) {
				printf("\n\nTransport layer:\n");	// Transport layer
				printf("    Source Port:\n");
				printf("      ");
			} else if (j == 36) {
				printf("\n    Destination Port:\n");
				printf("      ");
			} else if (j == 38) {
				printf("\n    Length:\n");
				printf("      ");
			} else if (j == 40) {
				printf("\n    Checksum:\n");
				printf("      ");
			} else if (j == 42) {
				printf("\n\nMessage:\n");				// data
				printf("   Target:\n");
				printf("      ");
			}
			if (j == 42) {
				len_msg = 1;
			}
			else if (j >= 42) {
				len_msg++;
			}
			if (j >= 42) {
				if (j % 16 == 0)
					printf("\n      ");
			}
			printf("%.2X ", word);
			if (j == 38 || j == 39) {
				len_msg_network = (len_msg_network << 8) + ((int)(word/16 * 16 + word % 16)) - 8;
				// printf("  %d  ", len_msg_network);
			}
		}
		printf("%.2X\n", word);
		len_msg++;										// The last word in msg
		printf("The length of payload: %d\n", len_msg);
		printf("The length of payload recorded in network: %d\n", len_msg_network);
		i++;
		len_msg_network = 0;
		len_msg = 0;
	}

	
	return 0;
}

int FindBegin(void)
{
	char word[3], word_tmp;
	int found_pattern = 0;

	word[0] = getchar();
	word[1] = getchar();
	word[2] = getchar();
	while (!found_pattern) {	
		if (word[0] == 0x1) {
			if (word[1] == 0x0) {
				if (word[2] == 0x5e) {
					found_pattern = 1;
					return 1;
				}
			}
		}
		word_tmp = getchar();
		if (!found_pattern) {
			word[0] = word[1];
			word[1] = word[2];
			word[2] = word_tmp;
		}
	}
}
