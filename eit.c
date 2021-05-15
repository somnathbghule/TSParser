/*
 * eit.c
 *
 *  Created on: Feb 18, 2014
 *      Author: aeon29
 */
#include "eit.h"

void event_information_section(unsigned char *section ) {
	fprintf(stderr,"\n\t\tDecoding EIT/ST...\n\n");
	unsigned char table_id = section[0];
	fprintf(stderr, "\t\ttable_id (8 bits) : %u (0x%x)\n",table_id,table_id);

	if(table_id == 0x72) {
		//TODO:stuffing_section();
		return;
	} else if (table_id == 0x4E) {
		fprintf(stderr,"\t\t[event_information_section - actual_transport_stream, present/following]\n");
	} else if (table_id == 0x4F) {
		fprintf(stderr,"\t\t[event_information_section - other_transport_stream, present/following]\n");
	} else if (table_id >= 0x50 && table_id <= 0x5F) {
		fprintf(stderr,"\t\t[event_information_section - actual_transport_stream, schedule]\n");
	} else if (table_id >= 0x60 && table_id <= 0x6F) {
		fprintf(stderr,"\t\t[event_information_section - other_transport_stream, schedule]\n");
	} else {
		return;
	}

	fprintf(stderr,"\n\t\tDecoding EIT specific...\n\n");

	unsigned char section_syntax_indicator = (section[1] >> 7) & 0x01;
	fprintf(stderr, "\t\tsection_syntax_indicator (1 bit) : %u (0x%x)\n",section_syntax_indicator,section_syntax_indicator);
	fprintf(stderr, "\t\tSkipping reserved_future_use (1 bit)\n");
	fprintf(stderr, "\t\tSkipping reserved (2 bits)\n");

	unsigned short section_length;
	memcpy(&section_length, section + 1, 2);
	section_length = ntohs(section_length);
	section_length = section_length & 0x0FFF;
	fprintf(stderr, "\t\tsection_length (12 bits) : %u (0x%04x)\n",section_length,section_length);

	if(section_length > 4093){
		return;
	}

	unsigned short service_id;
	memcpy(&service_id, section + 3, 2);
	service_id = ntohs(service_id);
	fprintf(stderr, "\t\tservice_id (16 bits) : %u (0x%04x)\n",service_id,service_id);

	fprintf(stderr, "\t\tSkipping reserved (2 bits)\n");
	unsigned char version_number = (section[5]>>1) & 0x1F;
	fprintf(stderr, "\t\tversion_number (5 bits) : %u (0x%x)\n",version_number,version_number);

	unsigned char current_next_indicator = section[5] & 0x01;
	fprintf(stderr, "\t\tcurrent_next_indicator (1 bit) : %u (0x%x)\n",current_next_indicator,current_next_indicator);

	unsigned char section_number = section[6];
	fprintf(stderr, "\t\tsection_number (8 bits) : %u (0x%x)\n",section_number,section_number);

	unsigned char last_section_number = section[7];
	fprintf(stderr, "\t\tlast_section_number (8 bits) : %u (0x%x)\n",last_section_number,last_section_number);

	unsigned short transport_stream_id;
	memcpy(&transport_stream_id, section + 8, 2);
	transport_stream_id = ntohs(transport_stream_id);
	fprintf(stderr, "\t\ttransport_stream_id (16 bits) : %u (0x%04x)\n",transport_stream_id,transport_stream_id);

	unsigned short original_network_id;
	memcpy(&original_network_id, section + 10, 2);
	original_network_id = ntohs(original_network_id);
	fprintf(stderr, "\t\toriginal_network_id (16 bits) : %u (0x%04x)\n",original_network_id,original_network_id);

	unsigned char segment_last_section_number = section[12];
	fprintf(stderr, "\t\tsegment_last_section_number (8 bits) : %u (0x%x)\n",segment_last_section_number,segment_last_section_number);

	unsigned char last_table_id = section[13];
	fprintf(stderr, "\t\tlast_table_id (8 bits) : %u (0x%x)\n\n",last_table_id,last_table_id);

	unsigned long N1 = section_length - 11-4;
	unsigned char *event_info = section + 14;

	while(N1>4) {
		unsigned short event_id;
		memcpy(&event_id, event_info, 2);
		event_id = ntohs(event_id);
		fprintf(stderr, "\t\t\tevent_id (16 bits) : %u (0x%04x)\n",event_id,event_id);

		unsigned long long start_time;
		memcpy(&start_time, event_info + 2, 5);
		start_time = ntohl(start_time);
		fprintf(stderr, "\t\t\tstart_time (40 bits) : %llu (0x%06llx)\n",start_time,start_time);

		unsigned long duration;
		memcpy(&duration, event_info + 7, 3);
		duration = ntohl(duration);
		fprintf(stderr, "\t\t\tduration (24 bits) : %lu (0x%lx)\n",duration,duration);

		unsigned char running_status = (event_info[10] >> 5) & 0x07;
		fprintf(stderr, "\t\t\trunning_status (3 bits) : %u (0x%x)\n",running_status,running_status);

		unsigned char free_CA_mode = (event_info[10] >> 4) & 0x01;
		fprintf(stderr, "\t\t\tfree_CA_mode (1 bit) : %u (0x%x)\n",free_CA_mode,free_CA_mode);

		unsigned short descriptors_loop_length;
		memcpy(&descriptors_loop_length, event_info + 10, 2);
		descriptors_loop_length = ntohs(descriptors_loop_length);
		descriptors_loop_length = descriptors_loop_length & 0x0FFF;
		fprintf(stderr, "\t\t\tdescriptors_loop_length (12 bits) : %u (0x%04x)\n\n",descriptors_loop_length,descriptors_loop_length);

		event_info += 12;
		N1 -= (12 + descriptors_loop_length);
		unsigned char *descrpitor_info = event_info;
		unsigned long  N2 = descriptors_loop_length;
		event_info += descriptors_loop_length;

		while(N2>0) {
			unsigned char descriptor_tag = descrpitor_info[0];
			fprintf(stderr, "\t\t\t\tdescriptor_tag (8 bits) : %u (0x%x)\n",descriptor_tag,descriptor_tag);

			unsigned char descriptor_length = descrpitor_info[1];
			fprintf(stderr, "\t\t\t\tdescriptor_length (8 bits) : %u (0x%x)\n",descriptor_length,descriptor_length);

			descriptorParser(descrpitor_info+2,descriptor_tag,descriptor_length);

			fprintf(stderr, "\n");
			N2 -= (descriptor_length + 2);
			descrpitor_info += descriptor_length + 2;
		}
	}

	unsigned long CRC32;
	memcpy(&CRC32, event_info, 4);
	CRC32 = ntohl(CRC32);
	fprintf(stderr, "\t\tCRC32 (32 bits) : %lu (0x%lx)\n",CRC32,CRC32);
}

void eitParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size) {
	unsigned char pointer_field;
	if(payload_unit_start_indicator) {
		pointer_field = section[0];
		fprintf(stderr,"\tpointer_field (8 bits) : %u (0x%x)\n",pointer_field, pointer_field);
	}
	unsigned char *new_section = section + pointer_field + 1;
	event_information_section(new_section);
}
