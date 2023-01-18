#ifndef __LIST__H__
#define __LIST__H__
	
	#include <stdbool.h>
	#include "pathfinding.h"

	#define TYPE node

	// Definition d'une case de la liste.
	typedef struct ListNode
	{
		TYPE value; 
		struct ListNode* back;
		struct ListNode* next;
	}ListNode;

	// Definition d'une liste.
	typedef struct List
	{
		int len;
		struct ListNode* begin;
		struct ListNode* end;
	}*List;

	// Prototypes :

	// Crée une liste vide.
	List empty_List(void);

	// Regarde si la liste est vide (true oui / false non).
	bool is_empty_List(List l);

	// Donne la longueur de la liste.
	int len_List(List l);

	// Donne la première valeur de la liste.
	TYPE fst_List(List l);

	// Donne la valeur à une position dans la liste.
	TYPE nth_List(List l, int pos);
	
	// Donne la dernière valeur de la liste.
	TYPE lst_List(List l);

	// Affiche toute la liste.
	void print_List(List l);

	// Ajoute "number" au debut de la liste.
	List add_fst_List(List l, TYPE number);

	// Ajoute "number" à la fin de la liste.
	List add_lst_List(List l, TYPE number);

	// Enleve le debut de la liste.
	List rem_fst_List(List l);

	// Enleve la fin de la liste.
	List rem_lst_List(List l);
	
	// Remet la liste à 0 élément.S
	List clear_List(List l);

	// Crée une autre liste identique à la liste donnée
	List copie_List(List l);

#endif // __LIST__H__
