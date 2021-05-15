/*
 * descriptor.h
 *
 *  Created on: Feb 19, 2014
 *      Author: aeon29
 */

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

/*
	unsigned char last_section_number = section[7];
	fprintf(stderr, "\t\tlast_section_number (8 bits) : %u (0x%x)\n",last_section_number,last_section_number);

	unsigned short transport_stream_id;
	memcpy(&transport_stream_id, section + 8, 2);
	transport_stream_id = ntohs(transport_stream_id);

	unsigned short original_network_id;
	memcpy(&original_network_id, section + 10, 2);
	original_network_id = ntohs(original_network_id);
	fprintf(stderr, "\t\toriginal_network_id (16 bits) : %u (0x%04x)\n",original_network_id,original_network_id);

	unsigned char segment_last_section_number = section[12];


	unsigned char last_table_id = section[13];
	fprintf(stderr, "\t\tlast_table_id (8 bits) : %u (0x%x)\n\n",last_table_id,last_table_id);

	unsigned long N1 = section_length - 11;
	unsigned char *event_info = section + 14;

*/

#include "tp.h"

void descriptorParser(unsigned char *descriptor, unsigned char descriptor_tag, unsigned char descriptor_length);

#endif /* DESCRIPTOR_H_ */
