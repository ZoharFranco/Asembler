/*
 ============================================================================
 Name        : node.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Node file, Node struct and useful node functions
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"


void print_node(Node node)
{
	printf("\n Name: %s, Value: %d, Next %p\n", node.name, node.value, node.next);
}
