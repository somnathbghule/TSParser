/*
 * nit.c
 *
 *  Created on: 07-Mar-2014
 *      Author: aeon25
 */

#include "nit.h"
void network_information_section(unsigned char *section){
	fprintf(stderr,"\n\t\tDecoding NIT...\n\n");
	unsigned char table_id   = section[0];
	fprintf(stderr, "\t\ttable_id (8 bits) : %u (0x%x)\n",table_id,table_id);

	unsigned char section_index_indicator = (section[1]>>7) & 0x01;
	fprintf(stderr, "\t\tsection_index_indicator (1 bits) : %u (0x%x)\n",section_index_indicator,section_index_indicator);
	fprintf(stderr, "\t\tSkipping reserved_future_use (1 bit)\n");
	fprintf(stderr, "\t\tSkipping reserved (2 bits)\n");

	unsigned short section_length;
	memcpy(&section_length,section+1,2);
	section_length = ntohs(section_length);
	section_length  = section_length & 0x0fff;
	fprintf(stderr, "\t\tsection_length (12 bits) : %u (0x%x)\n",section_length,section_length);

	unsigned short network_id;
	memcpy(&network_id,section+3,2);
	network_id = ntohs(network_id);
	network_id= network_id & 0xffff;
	fprintf(stderr, "\t\tnetwork_id (16 bits) : %u (0x%x)\n",network_id,network_id);
	fprintf(stderr, "\t\tSkipping reserved (2 bits)\n");
	unsigned char version_number  = (section[5] >>1) & 0x1f;
	fprintf(stderr, "\t\tversion_number (5 bits) : %u (0x%x)\n",version_number,version_number);

	unsigned char current_next_indicator =(section[5]) & 0x01;
	fprintf(stderr, "\t\tcurrent_next_indicator (1 bits) : %u (0x%x)\n",current_next_indicator,current_next_indicator);
	unsigned char section_number = section[6];
	fprintf(stderr, "\t\tsection_number (8 bits) : %u (0x%x)\n",section_number,section_number);

	unsigned char last_section_number = section[7];
	fprintf(stderr, "\t\tlast_section_number (8 bits) : %u (0x%x)\n",last_section_number,last_section_number);
										//number of bytes after section length , CRC bytes
	unsigned short network_descriptor_length;
	memcpy(&network_descriptor_length,section+8,2);
	network_descriptor_length = ntohs(network_descriptor_length);
	network_descriptor_length = network_descriptor_length& 0x0fff;
	fprintf(stderr, "\t\tnetwork_descriptor_length (12 bits) : %u (0x%x)\n",network_descriptor_length,network_descriptor_length);

	unsigned long N1 = network_descriptor_length;

	unsigned char *descriptor_info1 = section + 10;


	while(N1>0){
		//descriptor
		unsigned char descriptor_tag = descriptor_info1[0];
		fprintf(stderr, "\t\t\t\tdescriptor_tag (8 bits) : %u (0x%x)\n",descriptor_tag,descriptor_tag);

		unsigned char descriptor_length = descriptor_info1[1];
		fprintf(stderr, "\t\t\t\tdescriptor_length (8 bits) : %u (0x%x)\n",descriptor_length,descriptor_length);
		fprintf(stderr, "\n");

		descriptorParser(descriptor_info1+2,descriptor_tag,descriptor_length);

		N1 -= (descriptor_length + 2);
		descriptor_info1 += (descriptor_length + 2);

	}

	unsigned short transport_stream_loop_length;
	memcpy(&transport_stream_loop_length,section+10+network_descriptor_length,2);
	transport_stream_loop_length = ntohs(transport_stream_loop_length);
	transport_stream_loop_length = transport_stream_loop_length & 0x0fff;
	fprintf(stderr, "\t\tSkipping reserved_future_use (4 bits)\n");
	fprintf(stderr, "\t\t\ttransport_stream_loop_length (12 bits) : %u (0x%04x)\n",transport_stream_loop_length,transport_stream_loop_length);

	unsigned long N2 = transport_stream_loop_length;
	unsigned char *network_info = section + 12 + network_descriptor_length;
	unsigned char *descriptor_info;
	unsigned long N3;
	//for(i=0;i<N2;i++){
	while(N2>0){
		unsigned short transport_stream_id;
		memcpy(&transport_stream_id,network_info,2);
		transport_stream_id  = ntohs(transport_stream_id);
		transport_stream_id = transport_stream_id & 0xffff;
		fprintf(stderr, "\t\t\t\ttransport_stream_id (16 bits) : %u (0x%04x)\n",transport_stream_id,transport_stream_id);

		unsigned short original_network_id;
		memcpy(&original_network_id,network_info+2,2);
		original_network_id = ntohs(original_network_id);
		original_network_id = original_network_id & 0xffff;
		fprintf(stderr, "\t\t\t\toriginal_network_id (16 bits) : %u (0x%04x)\n",original_network_id,original_network_id);
		fprintf(stderr, "\t\t\t\tSkipping reserved_future_use (4 bits)\n");

		unsigned short transport_descriptors_length;
		memcpy(&transport_descriptors_length,network_info+4,2);
		transport_descriptors_length = ntohs(transport_descriptors_length);
		transport_descriptors_length  = transport_descriptors_length & 0x0fff;
		fprintf(stderr, "\t\t\t\ttransport_descriptors_length (12 bits) : %u (0x%04x)\n",transport_descriptors_length,transport_descriptors_length);

		network_info += 6;
		N2 -= (transport_descriptors_length + 6);
		descriptor_info = network_info;
		N3 = transport_descriptors_length;
		network_info += transport_descriptors_length;



		while(N3>0){
			unsigned char descriptor_tag = descriptor_info[0];
			fprintf(stderr, "\t\t\t\tdescriptor_tag (8 bits) : %u (0x%x)\n",descriptor_tag,descriptor_tag);

			unsigned char descriptor_length = descriptor_info[1];
			fprintf(stderr, "\t\t\t\tdescriptor_length (8 bits) : %u (0x%x)\n",descriptor_length,descriptor_length);
			fprintf(stderr, "\n");

			descriptorParser(descriptor_info+2,descriptor_tag,descriptor_length);

			N3 -= (descriptor_length + 2);
			descriptor_info += (descriptor_length + 2);
		}

	}
	unsigned long CRC_32;
	memcpy(&CRC_32,network_info,4);
	CRC_32 = ntohl(CRC_32);
	fprintf(stderr, "\t\t\tCRC_32 (32 bits) : %lu (0x%lx)\n",CRC_32,CRC_32);

}


void nitParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size){

	unsigned char pointer_field;
	if(payload_unit_start_indicator){
		pointer_field = section[0];
		fprintf(stderr,"\tpointer_field (8 bits) : %u (0x%x)\n",pointer_field, pointer_field);
	}
	printf("***************************************************");
	unsigned char *new_section = section + pointer_field + 1;
	network_information_section(new_section);
}


