/*
 * sdt.c
 *
 *  Created on: 07-Mar-2014
 *      Author: abhishek
 */
#include "sdt.h"

void service_information_section(unsigned char *section){

	unsigned char 	table_id = section[0];
	fprintf(stderr, "\t\t\t\ttable_id (8 bits) : %u (0x%x)\n",table_id,table_id);

	unsigned char section_syntex_indicator = (section[1]>>7) &  0x01;
	fprintf(stderr, "\t\t\t\tsection_syntex_indicator (1 bits) : %u (0x%x)\n",section_syntex_indicator,section_syntex_indicator);
	//reserved future use 1 bit
	//reserved 2 bit

	unsigned short section_length;
	memcpy(&section_length,section+1,2);
	section_length = ntohs(section_length);
	section_length =section_length & 0x0fff;
	fprintf(stderr, "\t\t\t\tsection_length (12 bits) : %u (0x%x)\n",section_length,section_length);

	unsigned short transort_stream_id;
	memcpy(&transort_stream_id,section+3,2);
	transort_stream_id = ntohs(transort_stream_id);
	fprintf(stderr, "\t\t\t\ttransort_stream_id (16 bits) : %u (0x%x)\n",transort_stream_id,transort_stream_id);

	//reserved 2 bit
	unsigned char version_number  = (section[5] >>1 ) & 0x1f;
	fprintf(stderr, "\t\t\t\tversion_number (5 bits) : %u (0x%x)\n",version_number,version_number);

	unsigned char current_next_indicator = section[5] & 0x01;
	fprintf(stderr, "\t\t\t\tversion_number (5 bits) : %u (0x%x)\n",version_number,version_number);

	unsigned char section_number = section[6];
	fprintf(stderr, "\t\t\t\tsection_number (8 bits) : %u (0x%x)\n",section_number,section_number);

	unsigned char last_section_number =section[7];
	fprintf(stderr, "\t\t\t\tlast_section_number (8 bits) : %u (0x%x)\n",last_section_number,last_section_number);

	unsigned short original_network_id;
	memcpy(&original_network_id,section+8,2);
	original_network_id = ntohs(original_network_id);
	fprintf(stderr, "\t\t\t\toriginal_network_id (16 bits) : %u (0x%04x)\n",original_network_id,original_network_id);

	//reserved for future use 8 bit

	unsigned long N1 = section_length - 8;
	unsigned char *service_info = section+11;

	while(N1>0){

		unsigned short service_id;
		memcpy(&service_id,service_info,2);
		service_id = ntohs(service_id);
		fprintf(stderr, "\t\t\t\tservice_id (16 bits) : %u (0x%04x)\n",service_id,service_id);

		//reserved for future use 6 bit
		unsigned char EIT_scheduled_flag = (service_info[2] >>1 ) & 0x01;
		fprintf(stderr, "\t\t\t\tEIT_scheduled_flag (1 bits) : %u (0x%x)\n",EIT_scheduled_flag,EIT_scheduled_flag);

		unsigned char EIT_present_following_flag = (service_info[2] ) & 0x01;
		fprintf(stderr, "\t\t\t\tEIT_present_following_flag (1 bits) : %u (0x%x)\n",EIT_present_following_flag,EIT_present_following_flag);

		unsigned char running_status = (service_info[3]>>5)& 0x07;
		fprintf(stderr, "\t\t\t\trunning_status (3 bits) : %u (0x%04x)\n",running_status,running_status);

		unsigned char free_CA_mode =(service_info[3]>>4)&0x01;
		fprintf(stderr, "\t\t\t\tfree_CA_mode (1 bits) : %u (0x%04x)\n",free_CA_mode,free_CA_mode);

		unsigned short descriptor_loop_length;
		memcpy(&descriptor_loop_length,service_info+3,2);
		descriptor_loop_length = ntohs(descriptor_loop_length);
		descriptor_loop_length = descriptor_loop_length & 0x0fff;
		fprintf(stderr, "\t\t\t\tdescriptor_loop_length (12 bits) : %u (0x%04x)\n",descriptor_loop_length,descriptor_loop_length);

		unsigned long N2 =descriptor_loop_length;
		service_info= service_info+5;

		unsigned char *descriptor_info = service_info;

		while(N2>0){
			//descriptor();
			unsigned char descriptor_tag = descriptor_info[0];
			fprintf(stderr, "\t\t\t\tdescriptor_tag (8 bits) : %u (0x%x)\n",descriptor_tag,descriptor_tag);

			unsigned char descriptor_length = descriptor_info[1];
			fprintf(stderr, "\t\t\t\tdescriptor_length (8 bits) : %u (0x%x)\n",descriptor_length,descriptor_length);

			//parse desciptor()
			N2 -= (descriptor_length+2);
			descriptor_info +=(descriptor_length+2);
		}

		N1 -=(descriptor_loop_length+5);
		service_info +=(descriptor_loop_length);
}

	unsigned long CRC_32;
	memcpy(&CRC_32,service_info,4);
	CRC_32 = ntohl(CRC_32);
	fprintf(stderr, "\t\t\tCRC_32 (32 bits) : %lu (0x%lx)\n",CRC_32,CRC_32);

}
void sdtParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size){
	unsigned char pointer_field;
	if(payload_unit_start_indicator){
		pointer_field = section[0];
		fprintf(stderr,"\tpointer_field (8 bits) : %u (0x%x)\n",pointer_field, pointer_field);
	}
	printf("***************************************************");
	unsigned char *new_section = section + pointer_field + 1;
	service_information_section(new_section);
}




