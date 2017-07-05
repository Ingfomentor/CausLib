/*
 * matrixSinglyLinkedLists.c
 * 
 * Copyright 2017 Angel Oswaldo Vázquez Patiño <angel.vazquezp@ucuenca.edu.ec>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/**
 * @brief dynamic matrix of singly-linked lists
 * @details Dynamic matrix for very big matrices of singly-linked lists by using
 * queue.h
 * @file matrixSinglyLinkedLists.c
 * @author Angel Vázquez-Patiño
 * @date 05 Jul 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <time.h>

struct sizetEntry {
		size_t value;
		SLIST_ENTRY(sizetEntry) ptr2Next;     // Singly-linked List. queue.h
};

int main(int argc, char **argv)
{
	int p=10;
	
	/**
	 * Dynamic matrix for very big p's
	 * 
	 */
	
	SLIST_HEAD(slisthead, sizetEntry) (*head)[p]; //cols
	head = malloc(sizeof(*head) * p); // rows
	
	
	//SLIST_HEAD(slisthead, sizetEntry) head[p][p];	/* Singly-linked List head. */
	
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<p;j++)
		{
			SLIST_INIT(&head[i][j]);
		}
	}
	srand(time(NULL));
	for (int i=0;i<p;i++) {
		for (int j=0;j<p;j++) {
			for (int k=0; k<rand()%5+1; k++) {
				struct sizetEntry *sizetNode;
				sizetNode = malloc(sizeof(struct sizetEntry));
				sizetNode->value = k+1;                       //!< 
	
				SLIST_INSERT_HEAD(&head[i][j], sizetNode, ptr2Next);
			}
		}
	}
	
	for (int i=0;i<p;i++) {
		for (int j=0;j<p;j++) {
			struct sizetEntry *np;
			printf("head[%i][%i]: ", i, j);
			SLIST_FOREACH(np, &head[i][j], ptr2Next)
				printf("%zu ", np->value);
			printf("\n");
		}
	}
	
	struct sizetEntry *n1;
	for (int i=0;i<p;i++) {
		for (int j=0;j<p;j++) {
			while (!SLIST_EMPTY(&head[i][j])) {           /* List Deletion. */
				n1 = SLIST_FIRST(&head[i][j]);
				SLIST_REMOVE_HEAD(&head[i][j], ptr2Next);
				free(n1);
			}
		}
	}
	
	free(head);
	
	return 0;
}
