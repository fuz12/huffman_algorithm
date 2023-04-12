//#define _CRT_SECURE_NO_WARNINGS
//
//#include "defines.h"
//#include "nodes.h"
//
//int main(void) {
//	node* tree = create_node();
//	tree->frequency = 10;
//	tree->left = create_node();
//	tree->left->symbol = 'A';
//	tree->left->isSym = 1;
//	tree->left->frequency = 5;
//	tree->right = create_node();
//	tree->right->frequency = 4;
//	tree->right->left = create_node();
//	tree->right->left->symbol = 'B';
//	tree->right->left->isSym = 1;	
//	tree->right->left->frequency = 2;	
//	tree->right->right = create_node();
//	tree->right->right->symbol = 'C';
//	tree->right->right->isSym = 1;
//	tree->right->right->frequency = 2;
//
//	clean_node* recover_tree = create_clean_node();
//	FILE* f = fopen("test.txt", "wb+");
//	if (f != NULL) {
//		fwrite(&tree->frequency, sizeof(int), 1, f);
//		write(tree, f);		
//	}
//	FILE* f_read = fopen("test.txt", "rb");
//	if (f_read != NULL) {
//		fseek(f, 0, SEEK_SET);
//		int a;
//		fread(&a, sizeof(int), 1, f);
//		recover_tree = read(f);
//	}
//	//printf("%d\n", recover_tree->isSym);
//	printf("%d %d\n", recover_tree->left->symbol, recover_tree->left->isSym);
//	printf("%d %d\n", recover_tree->right->left->symbol, recover_tree->right->left->isSym);
//	printf("%d %d\n", recover_tree->right->right->symbol, recover_tree->right->right->isSym);
//
//	return 0;
//}