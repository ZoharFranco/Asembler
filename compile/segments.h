#ifndef SEGMENTS_H
#define SEGMENTS_H

#define CODE_SEGMENT_START 100
#define CODE_SEGMENT_SIZE 4096
#define DATA_SEGMENT_SIZE 4096


#include "../data_structures/table.h"
#include "instructions.h"

/*!
 * Enum of all segments types
 */
typedef enum {
    CODE_SEGMENT, DATA_SEGMENT
} SegmentType;


// Opcode struct contain string name, OpcodeNumber number, int number_of_args number of args that use, and function to handle opcode action
/*!
 *
 */
typedef struct SegmentEntry {
    MachineCodeContent machine_code_content;
    SegmentType type;
    int start_address;
    int assembly_line;
    char *label;
} SegmentEntry;


/*!
 *
 * @return
 */
Table *init_segment_table(); // Table of all symbols


/*!
 *
 * @param segments_table
 * @param segment_entry
 * @return
 */
int add_segment_entry(Table *segments_table, SegmentEntry *segment_entry);


/*!
 *
 * @param segments_table
 * @param assembly_line
 * @return
 */
SegmentEntry *get_segment_entry_by_assembly_line(Table *segments_table, int assembly_line);

#endif // SEGMENTS_H
