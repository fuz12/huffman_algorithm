#include "write_read_Huffman.h"

void write(node* avlleaf, FILE* f) {
	char flag = 1; // 43 = '1', 45 = '0'
	fwrite(&avlleaf->symbol, sizeof(char), 1, f);
	fwrite(&avlleaf->isSym, sizeof(char), 1, f);
	if (avlleaf->left != NULL) {
		fwrite(&flag, sizeof(char), 1, f);
		write(avlleaf->left, f);
	}
	else {
		flag = 0;
		fwrite(&flag, sizeof(char), 1, f);
	}
	flag = 1;
	if (avlleaf->right != NULL) {
		fwrite(&flag, sizeof(char), 1, f);
		write(avlleaf->right, f);
	}
	else {
		flag = 0;
		fwrite(&flag, sizeof(char), 1, f);
	}
}

clean_node* read(FILE* f) {
	char flag;
	clean_node* avlleaf = create_clean_node();
	fread(&avlleaf->symbol, sizeof(char), 1, f);
	fread(&avlleaf->isSym, sizeof(char), 1, f);
	fread(&flag, sizeof(char), 1, f);
	if (flag == 1) avlleaf->left = read(f);
	fread(&flag, sizeof(char), 1, f);
	if (flag == 1) avlleaf->right = read(f);
	return avlleaf;
}