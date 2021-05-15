/*
 * pat1.c
 *
 *  Created on: Feb 17, 2014
 *      Author: aeon29
 */

#include "pat.h"

void program_association_section(unsigned char *section ) {
	fprintf(stderr,"\n\t\tDecoding PAT...\n\n");
	unsigned char table_id = section[0];
	fprintf(stderr, "\t\ttable_id (8 bits) : %u (0x%x)\n",table_id,table_id);

	unsigned char section_syntax_indicator = (section[1] >> 7) & 0x01;
	fprintf(stderr, "\t\tsection_syntax_indicator (1 bit) : %u (0x%x)\n",section_syntax_indicator,section_syntax_indicator);
	fprintf(stderr, "\t\tSkipping '0' (1 bit)\n");
	fprintf(stderr, "\t\tSkipping reserved (2 bits)\n");

	unsigned short section_length;						//TODO: 1st 2 bits '00' && should not exceed 0x3FD
	memcpy(&section_length, section + 1, 2);
	section_length = ntohs(section_length);
	section_length = section_length & 0x0FFF;
	fprintf(stderr, "\t\tsection_length (12 bits) : %u (0x%04x)\n",section_length,section_length);

	if(section_length > 0x3FD){
		return;
	}

	unsigned short transport_stream_id;
	memcpy(&transport_stream_id, section + 3, 2);
	transport_stream_id = ntohs(transport_stream_id);
	fprintf(stderr, "\t\ttransport_stream_id (16 bits) : %u (0x%04x)\n",transport_stream_id,transport_stream_id);

	fprintf(stderr, "\t\tSkipping reserved (2 bits)\n");
	unsigned char version_number = (section[5]>>1) & 0x1F;
	fprintf(stderr, "\t\tversion_number (5 bits) : %u (0x%x)\n",version_number,version_number);

	unsigned char current_next_indicator = section[5] & 0x01;
	fprintf(stderr, "\t\tcurrent_next_indicator (1 bit) : %u (0x%x)\n",current_next_indicator,current_next_indicator);

	unsigned char section_number = section[6];
	fprintf(stderr, "\t\tsection_number (8 bits) : %u (0x%x)\n",section_number,section_number);

	unsigned char last_section_number = section[7];
	fprintf(stderr, "\t\tlast_section_number (8 bits) : %u (0x%x)\n\n",last_section_number,last_section_number);

	// n = section_length - CRC - front bytes
	unsigned long N = section_length - 4 - 5;
	unsigned long section_header_len = 8;

	for (;N>=4; N-=4) {
		unsigned short program_number;
		memcpy(&program_number, section + section_header_len, 2);
		program_number = ntohs(program_number);
		fprintf(stderr, "\t\t\tprogram_number (16 bits) : %u (0x%x)\n",program_number,program_number);

		fprintf(stderr, "\t\t\tSkipping reserved (3 bits)\n");

		section_header_len += 2;
		if(program_number == 0){
			unsigned short network_PID;
			memcpy(&network_PID, section + section_header_len, 2);
			network_PID = ntohs(network_PID);
			network_PID = network_PID & 0x1FFF;
			fprintf(stderr, "\t\t\tnetwork_PID (13 bits) : %u (0x%x)\n\n",network_PID,network_PID);

		} else {
			unsigned short program_map_PID;
			memcpy(&program_map_PID, section + section_header_len, 2);
			program_map_PID = ntohs(program_map_PID);
			program_map_PID = program_map_PID & 0x1FFF;
			fprintf(stderr, "\t\t\tprogram_map_PID (13 bits) : %u (0x%x)\n\n",program_map_PID,program_map_PID);

		}
		section_header_len += 2;
	}

	unsigned long CRC32;
	memcpy(&CRC32, section + section_header_len, 4);
	CRC32 = ntohl(CRC32);
	fprintf(stderr, "\t\t\tCRC32 (32 bits) : %lu (0x%lx)\n",CRC32,CRC32);

}

void patParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size) {
	unsigned char pointer_field;
	if(payload_unit_start_indicator) {
		pointer_field = section[0];
		fprintf(stderr,"\tpointer_field (8 bits) : %u (0x%x)\n",pointer_field, pointer_field);
	}
	unsigned char *new_section = section + pointer_field + 1;
	program_association_section(new_section);
}
