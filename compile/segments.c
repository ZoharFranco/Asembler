/*
 ============================================================================
 Name        : segments.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Segments file - to create function and declarations of segments handling
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../errors/errors_handling.h"

#include "segments.h"



Table * init_segment_table(){
	return init_table();
}

int add_segment_entry(Table* segments_table, SegmentEntry* segment_entry){
	return add_entry(segments_table, segment_entry, segment_entry->label, sizeof(SegmentEntry));
}

SegmentEntry * get_segment_entry_by_assembly_line(Table* segments_table, int assembly_line){
	for (int i = 0; i < segments_table->size; i++) {
		SegmentEntry * segment_entry = segments_table->entries[i].data;
		if (segment_entry->assembly_line == assembly_line) return segment_entry;
	}
	return &(SegmentEntry){};
}
