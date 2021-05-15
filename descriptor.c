/*
 * descriptor.c
 *
 *  Created on: Feb 19, 2014
 *      Author: aeon29
 */

#include "descriptor.h"

void adaptation_field_data_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char adaptation_field_data_identifier = descriptor[0];
	fprintf(stderr, "\t\t\t\tadaptation_field_data_identifier (8 bits) : %u (0x%x)\n",adaptation_field_data_identifier,adaptation_field_data_identifier);
}

void ancillary_data_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char ancillary_data_identifier = descriptor[0];
	fprintf(stderr, "\t\t\t\tancillary_data_identifier (8 bits) : %u (0x%x)\n",ancillary_data_identifier,ancillary_data_identifier);
}

void announcement_support_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned short announcement_support_indicator;
	memcpy(&announcement_support_indicator,descriptor,2);
	announcement_support_indicator = ntohs(announcement_support_indicator);
	fprintf(stderr, "\t\t\tannouncement_support_indicator (16 bits) : %u (0x%04x)\n",announcement_support_indicator,announcement_support_indicator);

	unsigned long N = descriptor_length - 2;
	unsigned char *announcement_info = descriptor + 2;

	while(N>0) {
		unsigned char accouncement_type = (announcement_info[0] >> 4) & 0x0F;
		fprintf(stderr, "\t\t\t\taccouncement_type (4 bits) : %u (0x%x)\n",accouncement_type,accouncement_type);

		fprintf(stderr, "\t\t\t\tSkipping reserved_future_use (1 bit)\n");

		unsigned char reference_type = announcement_info[0] & 0x07;
		fprintf(stderr, "\t\t\t\treference_type (3 bits) : %u (0x%x)\n",reference_type,reference_type);

		N -= 1;
		announcement_info += 1;
		if(reference_type == 0x01 || reference_type == 0x02 || reference_type == 0x03) {
			unsigned short original_network_id;
			memcpy(&original_network_id,announcement_info,2);
			original_network_id = ntohs(original_network_id);
			fprintf(stderr, "\t\t\t\t\toriginal_network_id (16 bits) : %u (0x%04x)\n",original_network_id,original_network_id);

			unsigned short transport_stream_id;
			memcpy(&transport_stream_id,announcement_info+2,2);
			transport_stream_id = ntohs(transport_stream_id);
			fprintf(stderr, "\t\t\t\t\ttransport_stream_id (16 bits) : %u (0x%04x)\n",transport_stream_id,transport_stream_id);

			unsigned short service_id;
			memcpy(&service_id,announcement_info + 4,2);
			service_id = ntohs(service_id);
			fprintf(stderr, "\t\t\t\t\tservice_id (16 bits) : %u (0x%04x)\n",service_id,service_id);

			unsigned char component_tag__ = announcement_info[6];
			fprintf(stderr, "\t\t\t\t\tcomponent_tag__ (8 bits) : %u (0x%x)\n",component_tag__,component_tag__);

			N -= 7;
			announcement_info += 7;
		}
	}
}

void bouquet_name_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *bouquet_info = descriptor;
	unsigned long N = descriptor_length;

	while(N>0) {
		unsigned char char_ = bouquet_info[0];
		fprintf(stderr, "\t\t\tchar_ (8 bits) : %u (0x%x)\n",char_,char_);

		N -= 1;
		bouquet_info += 1;
	}
}

void CA_identifier_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *CA_info = descriptor;
	unsigned long N = descriptor_length;

	while(N>0) {
		unsigned short CA_system_id;
		memcpy(&CA_system_id,CA_info,2);
		CA_system_id = ntohs(CA_system_id);
		fprintf(stderr, "\t\t\tCA_system_id (16 bits) : %u (0x%04x)\n",CA_system_id,CA_system_id);

		N -= 2;
		CA_info += 2;
	}
}

void cell_frequency_link_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *cell_frequency_info = descriptor;
	unsigned long N1 = descriptor_length;

	while(N1 > 0){
		unsigned short cell_id;
		memcpy(&cell_id,cell_frequency_info,2);
		cell_id = ntohs(cell_id);
		fprintf(stderr, "\t\t\tcell_id (16 bits) : %u (0x%04x)\n",cell_id,cell_id);

		unsigned long frequency;
		memcpy(&frequency,cell_frequency_info+2,4);
		frequency = ntohl(frequency);
		fprintf(stderr, "\t\t\tfrequency (32 bits) : %lu (0x%lx)\n",frequency,frequency);

		unsigned char subcell_info_loop_length = cell_frequency_info[6];
		fprintf(stderr, "\t\t\tsubcell_info_loop_length (8 bits) : %u (0x%x)\n",subcell_info_loop_length,subcell_info_loop_length);

		unsigned long N2 = descriptor_length;
		unsigned char *cell_id_info = cell_frequency_info;
		N1 -= (descriptor_length + 7);
		cell_frequency_info += (descriptor_length + 7);

		while(N2 > 0) {
			unsigned char cell_id_extension = cell_id_info[0];
			fprintf(stderr, "\t\t\tcell_id_extension (8 bits) : %u (0x%x)\n",cell_id_extension,cell_id_extension);

			unsigned long transponder_frequency;
			memcpy(&transponder_frequency,cell_id_info+1,4);
			transponder_frequency = ntohl(transponder_frequency);
			fprintf(stderr, "\t\t\ttransponder_frequency (32 bits) : %lu (0x%lx)\n",transponder_frequency,transponder_frequency);
			N2 -= 5;
			cell_id_info += 5;
		}
	}
}

void cell_list_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *cell_list_info = descriptor;
	unsigned long N1 = descriptor_length;

	while(N1>0){
		unsigned short cell_id;
		memcpy(&cell_id,cell_list_info,2);
		cell_id = ntohs(cell_id);
		fprintf(stderr, "\t\t\tcell_id (16 bits) : %u (0x%04x)\n",cell_id,cell_id);

		unsigned short cell_latitude;
		memcpy(&cell_latitude,cell_list_info+2,2);
		cell_latitude = ntohs(cell_latitude);
		fprintf(stderr, "\t\t\tcell_latitude (16 bits) : %u (0x%04x)\n",cell_latitude,cell_latitude);

		unsigned short cell_longitude;
		memcpy(&cell_longitude,cell_list_info+4,2);
		cell_longitude = ntohs(cell_longitude);
		fprintf(stderr, "\t\t\tcell_longitude (16 bits) : %u (0x%04x)\n",cell_longitude,cell_longitude);

		unsigned short cell_extend_of_latitude;
		memcpy(&cell_extend_of_latitude,cell_list_info+6,2);
		cell_extend_of_latitude = ntohs(cell_extend_of_latitude);
		cell_extend_of_latitude = (cell_extend_of_latitude >> 4) & 0x0FFF;
		fprintf(stderr, "\t\t\tcell_extend_of_latitude (12 bits) : %u (0x%04x)\n",cell_extend_of_latitude,cell_extend_of_latitude);

		unsigned short cell_extend_of_longitude;
		memcpy(&cell_extend_of_longitude,cell_list_info+7,2);
		cell_extend_of_longitude = ntohs(cell_extend_of_longitude);
		cell_extend_of_longitude = cell_extend_of_longitude & 0x0FFF;
		fprintf(stderr, "\t\t\tcell_extend_of_longitude (12 bits) : %u (0x%04x)\n",cell_extend_of_longitude,cell_extend_of_longitude);

		unsigned char subcell_info_loop_length = cell_list_info[9];
		fprintf(stderr, "\t\t\tsubcell_info_loop_length (8 bits) : %u (0x%x)\n",subcell_info_loop_length,subcell_info_loop_length);

		unsigned long N2 = subcell_info_loop_length;
		unsigned char *subcell_info = cell_list_info;
		N1 -= (descriptor_length + 10);
		cell_list_info += (descriptor_length + 10);

		while(N2 > 0) {
			unsigned char cell_id_extension = subcell_info[0];
			fprintf(stderr, "\t\t\tcell_id_extension (8 bits) : %u (0x%x)\n",cell_id_extension,cell_id_extension);

			unsigned short subcell_latitude;
			memcpy(&subcell_latitude,subcell_info+1,2);
			subcell_latitude = ntohs(subcell_latitude);
			fprintf(stderr, "\t\t\tsubcell_latitude (16 bits) : %u (0x%04x)\n",subcell_latitude,subcell_latitude);

			unsigned short subcell_longitude;
			memcpy(&subcell_longitude,subcell_info+1,2);
			subcell_longitude = ntohs(subcell_longitude);
			fprintf(stderr, "\t\t\tsubcell_longitude (16 bits) : %u (0x%04x)\n",subcell_longitude,subcell_longitude);

			unsigned short subcell_extend_of_latitude;
			memcpy(&subcell_extend_of_latitude,subcell_info+1,2);
			subcell_extend_of_latitude = ntohs(subcell_extend_of_latitude);
			subcell_extend_of_latitude = (subcell_extend_of_latitude >> 4) & 0x0FFF;
			fprintf(stderr, "\t\t\tsubcell_extend_of_latitude (12 bits) : %u (0x%04x)\n",subcell_extend_of_latitude,subcell_extend_of_latitude);

			unsigned short subcell_extend_of_longitude;
			memcpy(&subcell_extend_of_longitude,subcell_info+1,2);
			subcell_extend_of_longitude = ntohs(subcell_extend_of_longitude);
			subcell_extend_of_longitude = subcell_extend_of_longitude & 0x0FFF;
			fprintf(stderr, "\t\t\tsubcell_extend_of_longitude (12 bits) : %u (0x%04x)\n",subcell_extend_of_longitude,subcell_extend_of_longitude);

			N2 -= 8;
			subcell_info += 8;
		}
	}
}

void component_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *component_info = descriptor;

	fprintf(stderr, "\t\t\tSkipping reserved_future_use (4 bits)\n");
	unsigned char stream_content = component_info[0];
	stream_content = stream_content & 0x0F;
	fprintf(stderr, "\t\t\tstream_content (4 bits) : %u (0x%x)\n",stream_content,stream_content);

	unsigned char component_type = component_info[1];
	fprintf(stderr, "\t\t\tcomponent_type (8 bits) : %u (0x%x)\n",component_type,component_type);

	unsigned char component_tag = component_info[2];
	fprintf(stderr, "\t\t\tcomponent_tag (8 bits) : %u (0x%x)\n",component_tag,component_tag);

	unsigned long ISO_639_language_code;
	memcpy(&ISO_639_language_code,component_info+3,3);
	ISO_639_language_code = ntohl(ISO_639_language_code);
	ISO_639_language_code = ISO_639_language_code & 0x00FFFFFF;
	fprintf(stderr, "\t\t\tISO_639_language_code (24 bits) : %lu (0x%lx)\n",ISO_639_language_code,ISO_639_language_code);

	unsigned long N = descriptor_length - 6;
	unsigned char *text_info = component_info + 6;

	while(N>0) {
		unsigned char text_char = text_info[0];
		fprintf(stderr, "\t\t\ttext_char (8 bits) : %u (0x%x)\n",text_char,text_char);

		N -= 1;
		text_info += 1;
	}
}

void content_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *content_info = descriptor;
	unsigned long N = descriptor_length;

	while(N>0) {
		unsigned char content_nibble_level_1 = (content_info[0] >> 4) & 0x0F;
		fprintf(stderr, "\t\t\tcontent_nibble_level_1 (4 bits) : %u (0x%x)\n",content_nibble_level_1,content_nibble_level_1);

		unsigned char content_nibble_level_2 = content_info[0] & 0x0F;
		fprintf(stderr, "\t\t\tcontent_nibble_level_2 (4 bits) : %u (0x%x)\n",content_nibble_level_2,content_nibble_level_2);

		unsigned char user_nibble_1 = (content_info[1] >> 4) & 0x0F;
		fprintf(stderr, "\t\t\tuser_nibble_1 (4 bits) : %u (0x%x)\n",user_nibble_1,user_nibble_1);

		unsigned char user_nibble_2 = content_info[1] & 0x0F;
		fprintf(stderr, "\t\t\tuser_nibble_1 (4 bits) : %u (0x%x)\n",user_nibble_2,user_nibble_2);

		N -= 2;
		content_info += 2;
	}
}

void country_availability_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *country_info = descriptor;

	unsigned char country_availability_flag = (country_info[0] >> 7) & 0x01;
	fprintf(stderr, "\t\t\tcountry_availability_flag (1 bit) : %u (0x%x)\n",country_availability_flag,country_availability_flag);

	fprintf(stderr, "\t\t\tSkipping reserver_future_use (1 bit)\n");

	unsigned long N = descriptor_length - 1;
	unsigned char *code_info = country_info + 1;

	while (N>0) {
		unsigned long country_code;
		memcpy(&country_code,code_info,3);
		country_code = ntohl(country_code);
		country_code = country_code & 0x00FFFFFF;
		fprintf(stderr, "\t\t\tcountry_code (24 bits) : %lu (0x%lx)\n",country_code,country_code);

		code_info += 3;
		N -=  3;
	}
}

void data_broadcast_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *data_broadcast_info = descriptor;

	unsigned short data_broadcast_id;
	memcpy(&data_broadcast_id,data_broadcast_info,2);
	data_broadcast_id = ntohs(data_broadcast_id);
	fprintf(stderr, "\t\t\tdata_broadcast_id (16 bits) : %u (0x%04x)\n",data_broadcast_id,data_broadcast_id);

	unsigned char component_tag = data_broadcast_info[2];
	fprintf(stderr, "\t\t\tcomponent_tag (8 bits) : %u (0x%x)\n",component_tag,component_tag);

	unsigned char selector_length = data_broadcast_info[3];
	fprintf(stderr, "\t\t\tselector_length (8 bits) : %u (0x%x)\n",selector_length,selector_length);

	unsigned long  N1 = selector_length;
	unsigned char *selector_info = data_broadcast_info + 4;

	while(N1>0) {
		unsigned char selector_byte = selector_info[0];
		fprintf(stderr, "\t\t\tselector_byte (8 bits) : %u (0x%x)\n",selector_byte,selector_byte);

		selector_info += 1;
		N1 -= 1;
	}

	unsigned long ISO_639_language_code;
	memcpy(&ISO_639_language_code,data_broadcast_info + 4 + selector_length ,3);
	ISO_639_language_code = ntohl(ISO_639_language_code);
	ISO_639_language_code = ISO_639_language_code & 0x00FFFFFF;
	fprintf(stderr, "\t\t\tISO_639_language_code (24 bits) : %lu (0x%lx)\n",ISO_639_language_code,ISO_639_language_code);

	unsigned char text_length = data_broadcast_info[7 + selector_length];
	fprintf(stderr, "\t\t\ttext_length (8 bits) : %u (0x%x)\n",text_length,text_length);

	unsigned long  N2 = text_length;
	unsigned char *text_info = data_broadcast_info + 8 + selector_length;

	while (N2>0) {
		unsigned char text_char = text_info[0];
		fprintf(stderr, "\t\t\ttext_char (8 bits) : %u (0x%x)\n",text_char,text_char);

		text_info += 1;
		N2 -= 1;
	}
}

void data_broadcast_id_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *data_broadcast_id_info = descriptor;

	unsigned short data_broadcast_id;
	memcpy(&data_broadcast_id,data_broadcast_id_info,2);
	data_broadcast_id = ntohs(data_broadcast_id);
	fprintf(stderr, "\t\t\tdata_broadcast_id (16 bits) : %u (0x%04x)\n",data_broadcast_id,data_broadcast_id);

	unsigned long N = (descriptor_length - 2);
	unsigned char *id_selector_info = data_broadcast_id_info + 2;

	while (N>0) {
		unsigned char id_selector_byte = id_selector_info[0];
		fprintf(stderr, "\t\t\tid_selector_byte (8 bits) : %u (0x%x)\n",id_selector_byte,id_selector_byte);

		N -= 1;
		id_selector_info += 1;
	}
}

void cable_delivery_system_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *cable_delivery_system_info = descriptor;

	unsigned long frequency;
	memcpy(&frequency,cable_delivery_system_info ,4);
	frequency = ntohl(frequency);
	fprintf(stderr, "\t\t\tfrequency (32 bits) : %lu (0x%lx)\n",frequency,frequency);

	fprintf(stderr, "\t\t\tSkipping reserved_future_use (12 bits)\n");

	unsigned char FEC_outer = cable_delivery_system_info[5];
	FEC_outer = FEC_outer & 0x0F;
	fprintf(stderr, "\t\t\tFEC_outer (4 bits) : %u (0x%x)\n",FEC_outer,FEC_outer);

	unsigned char modulation = cable_delivery_system_info[6];
	fprintf(stderr, "\t\t\tmodulation (8 bits) : %u (0x%x)\n",modulation,modulation);

	unsigned long symbol_rate;
	memcpy(&symbol_rate,cable_delivery_system_info + 7,4);
	symbol_rate = ntohl(symbol_rate);
	symbol_rate = (symbol_rate >> 4) & 0x0FFFFFFF;
	fprintf(stderr, "\t\t\tsymbol_rate (28 bits) : %lu (0x%lx)\n",symbol_rate,symbol_rate);

	unsigned char FEC_inner = cable_delivery_system_info[10];
	FEC_inner = FEC_inner & 0x0F;
	fprintf(stderr, "\t\t\FEC_inner (4 bits) : %u (0x%x)\n",FEC_inner,FEC_inner);
}

void satellite_delivery_system_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *satellite_delivery_system_info = descriptor;

	unsigned long frequency;
	memcpy(&frequency,satellite_delivery_system_info ,4);
	frequency = ntohl(frequency);
	fprintf(stderr, "\t\t\tfrequency (32 bits) : %lu (0x%lx)\n",frequency,frequency);

	unsigned short orbital_position;
	memcpy(&orbital_position,satellite_delivery_system_info+4,2);
	orbital_position = ntohs(orbital_position);
	fprintf(stderr, "\t\t\torbital_position (16 bits) : %u (0x%04x)\n",orbital_position,orbital_position);

	unsigned char west_east_flag = satellite_delivery_system_info[6];
	west_east_flag = (west_east_flag >> 7) & 0x01;
	fprintf(stderr, "\t\t\twest_east_flag (1 bit) : %u (0x%x)\n",west_east_flag,west_east_flag);

	unsigned char polarization = satellite_delivery_system_info[6];
	polarization = (polarization >> 5) & 0x03;
	fprintf(stderr, "\t\t\tpolarization (2 bits) : %u (0x%x)\n",polarization,polarization);

	unsigned char modulation = satellite_delivery_system_info[6];
	modulation = modulation & 0x1F;
	fprintf(stderr, "\t\t\tmodulation (5 bits) : %u (0x%x)\n",modulation,modulation);

	unsigned long symbol_rate;
	memcpy(&symbol_rate,satellite_delivery_system_info + 7,4);
	symbol_rate = ntohl(symbol_rate);
	symbol_rate = (symbol_rate >> 4) & 0x0FFFFFFF;
	fprintf(stderr, "\t\t\tsymbol_rate (28 bits) : %lu (0x%lx)\n",symbol_rate,symbol_rate);

	unsigned char FEC_inner = satellite_delivery_system_info[10];
	FEC_inner = FEC_inner & 0x0F;
	fprintf(stderr, "\t\t\FEC_inner (4 bits) : %u (0x%x)\n",FEC_inner,FEC_inner);
}

void terrestrial_delivery_system_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *terrestrial_delivery_system_info = descriptor;

	unsigned long centre_frequency;
	memcpy(&centre_frequency,terrestrial_delivery_system_info ,4);
	centre_frequency = ntohl(centre_frequency);
	fprintf(stderr, "\t\t\tcentre_frequency (32 bits) : %lu (0x%lx)\n",centre_frequency,centre_frequency);

	unsigned char bandwidth = terrestrial_delivery_system_info[4];
	bandwidth = (bandwidth >> 5) & 0x07;
	fprintf(stderr, "\t\t\tbandwidth (3 bits) : %u (0x%x)\n",bandwidth,bandwidth);

	fprintf(stderr, "\t\t\tSkipping reserved_future_use (5 bits)\n");

	unsigned char constellation = terrestrial_delivery_system_info[5];
	constellation = (constellation >> 6) & 0x03;
	fprintf(stderr, "\t\t\tconstellation (2 bits) : %u (0x%x)\n",constellation,constellation);

	unsigned char hierarchy_information = terrestrial_delivery_system_info[5];
	hierarchy_information = (hierarchy_information >> 3) & 0x07;
	fprintf(stderr, "\t\t\thierarchy_information (3 bits) : %u (0x%x)\n",hierarchy_information,hierarchy_information);

	unsigned char code_rate_HP_stream = terrestrial_delivery_system_info[5];
	code_rate_HP_stream = code_rate_HP_stream & 0x07;
	fprintf(stderr, "\t\t\tcode_rate_HP_stream (3 bits) : %u (0x%x)\n",code_rate_HP_stream,code_rate_HP_stream);

	unsigned char code_rate_LP_stream = terrestrial_delivery_system_info[6];
	code_rate_LP_stream = (code_rate_LP_stream >> 5) & 0x07;
	fprintf(stderr, "\t\t\tcode_rate_LP_stream (3 bits) : %u (0x%x)\n",code_rate_LP_stream,code_rate_LP_stream);

	unsigned char gaurd_interval = terrestrial_delivery_system_info[6];
	gaurd_interval = (gaurd_interval >> 3)& 0x03;
	fprintf(stderr, "\t\t\tgaurd_interval (2 bits) : %u (0x%x)\n",gaurd_interval,gaurd_interval);

	unsigned char transmission_mode = terrestrial_delivery_system_info[6];
	transmission_mode = transmission_mode & 0x03;
	fprintf(stderr, "\t\t\ttransmission_mode (2 bits) : %u (0x%x)\n",transmission_mode,transmission_mode);

	unsigned char other_frequency_flag = terrestrial_delivery_system_info[6];
	other_frequency_flag = other_frequency_flag & 0x01;
	fprintf(stderr, "\t\t\tother_frequency_flag (1 bit) : %u (0x%x)\n",other_frequency_flag,other_frequency_flag);

	fprintf(stderr, "\t\t\tSkipping reserved_future_use (32 bits)\n");
}

void extended_event_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//
	unsigned char *extended_event_info = descriptor;

	unsigned char descriptor_number = (extended_event_info[0] >> 4) & 0x0F;

	unsigned char last_descriptor_number = extended_event_info[0] & 0x0F;

	unsigned long ISO_639_language_code;
	memcpy(&ISO_639_language_code,extended_event_info + 1,3);
	ISO_639_language_code = ntohl(ISO_639_language_code);
	ISO_639_language_code = ISO_639_language_code & 0x00FFFFFF;

	unsigned char length_of_items = extended_event_info[4];

	unsigned long N1 = length_of_items;
	unsigned char *item_info = extended_event_info + 5;

	while(N1>0){
		unsigned char item_description_length = item_info[0];

		unsigned char *item_desc_info = item_info + 1;
		unsigned long N2 = item_description_length;

		while(N2>0){
			unsigned char item_description_char = item_desc_info[0];
			N2 -= 1;
			item_desc_info += 1;
		}

		unsigned char item_length = item_info + 1 + item_description_length;

		unsigned long N3 = item_length;
		unsigned char *item_char_info = item_info + 2 + item_description_length;

		while(N3>0){
			unsigned char item_char = item_char_info[0];

			N3 -= 1;
			item_char_info += 1;
		}
	}

	unsigned char text_length = extended_event_info + 5 + length_of_items;

	unsigned long N4 = text_length;
	unsigned char *text_info = extended_event_info + 6 + length_of_items;

	while(N4>0){
		unsigned char text_char = text_info[0];

		N4 -= 1;
		text_info += 1;
	}
}

void frequency_list_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *frequency_list_info = descriptor;

	//skip 6 bits reserved_future_use

	unsigned char coding_type = frequency_list_info[0] & 0x03;

	unsigned long N = descriptor_length - 1;
	unsigned char *frequency_info = frequency_list_info + 1;

	while(N>0) {
		unsigned long centre_frequency;
		memcpy(&centre_frequency,frequency_info, 4);
		centre_frequency = ntohl(centre_frequency);

		frequency_info += 4;
		N -= 4;
	}
}

void linkage_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//
	unsigned char *linkage_info = descriptor;

	unsigned short transport_stream_id;
	memcpy(&transport_stream_id,linkage_info, 2);
	transport_stream_id = ntohs(transport_stream_id);

	unsigned short original_network_id;
	memcpy(&original_network_id,linkage_info + 2, 2);
	original_network_id = ntohs(original_network_id);

	unsigned short service_id;
	memcpy(&service_id,linkage_info + 4, 2);
	service_id = ntohs(service_id);

	unsigned char linkage_type = linkage_info[6];

	if (linkage_type != 0x08) {
		unsigned long N = descriptor_length - 7;
		unsigned char * private_data_info = linkage_info + 7;
		while (N>0) {
			unsigned char private_data_byte = private_data_info[0];

			N -= 1;
			private_data_info += 1;
		}
	} else {
		unsigned char hand_over_type = (linkage_info[7] >> 4) & 0x0F;

		//skip 3 bitsreserved_future_use
		unsigned char  origin_type = linkage_info[7] & 0x01;

		unsigned long N = descriptor_length - 8;
		unsigned char * private_data_info = linkage_info + 8;


		if (hand_over_type == 0x01 || hand_over_type == 0x02 || hand_over_type == 0x03) {
			unsigned short network_id;
			memcpy(&network_id,linkage_info + 8, 2);
			network_id = ntohs(network_id);

			N -= 2;
			private_data_info += 2;
		}
		if (origin_type == 0x00) {
			unsigned short initial_service_id;
			memcpy(&initial_service_id,linkage_info + 8, 2);
			initial_service_id = ntohs(initial_service_id);

			N -= 2;
			private_data_info += 2;

		}
		while(N>0) {
			unsigned char private_data_byte = private_data_info[0];

			N -= 1;
			private_data_info += 1;
		}
	}

}

void local_time_offset_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void mosaic_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void multilingual_bouquet_name_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void multilingual_component_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//

}

void multilingual_network_name_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void multilingual_service_name_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void NVOD_reference_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void network_name_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *network_name_info =  descriptor;

	unsigned long N1 = descriptor_length;

	while (N1>0){
		unsigned char char_ = network_name_info[0];
		//fprintf(stderr, "\t\t\tchar_ (8 bits) : %c (0x%x)\n",char_,char_);

		N1	-=1;
		network_name_info+=1;
	}
}

void parental_rating_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//

}

void PDC_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//

}

void private_data_specifier_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void short_smoothing_buffer_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//

}

void service_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *service_info = descriptor;

	unsigned char service_type = service_info[0];

	unsigned char service_provider_name_length = service_info[1];

	unsigned long N1 = service_provider_name_length;
	unsigned char *char_info1 = service_info + 2;

	while (N1>0){
		unsigned char char_ = char_info1[0];

		char_info1 += 1;
		N1 -= 1;
	}

	unsigned char service_name_length = service_info[2 + service_provider_name_length];
	unsigned long N2 = service_name_length;

	unsigned char *char_info2 = service_info + 3 + service_provider_name_length;

	while(N2>0){
		unsigned char char_ = char_info2[0];

		char_info2 += 1;
		N2 -= 1;
	}
}

void service_availability_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void service_list_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {
	unsigned char *service_list_info = descriptor;
	unsigned long N1 = descriptor_length;
	while(N1>0){
		unsigned short service_id;
		memcpy(&service_id,service_list_info,2);
		service_id = ntohs(service_id);
		//service_id = service_id & 0xffff;
		fprintf(stderr, "\t\t\t\t\tservice_id (16 bits) : %u (0x%04x)\n",service_id,service_id);
		unsigned short service_type = service_list_info[2];
		fprintf(stderr, "\t\t\t\t\tservice_type (8 bits) : %u (0x%x)\n",service_type,service_type);
		N1 -=3;
		service_list_info+=3;
	}

}

void service_move_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void short_event_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//
	unsigned char *short_event_info = descriptor;

	unsigned long ISO_639_language_code;
	memcpy(&ISO_639_language_code,short_event_info, 3);
	ISO_639_language_code = ntohl(ISO_639_language_code);
	ISO_639_language_code = ISO_639_language_code & 0x00FFFFFF;

	unsigned char event_name_length = short_event_info[3];
	unsigned long N1 = event_name_length;
	unsigned char *event_name_info = short_event_info + 4;

	while(N1>0){
		unsigned char event_name_char = event_name_info[0];

		event_name_info += 1;
		N1 -= 1;
	}
	unsigned char text_length = short_event_info + 4 + event_name_length;
	unsigned long N2 = text_length;
	unsigned char *text_info = short_event_info + 5 + event_name_length;

	while(N2>0){
		unsigned char text_char = text_info[0];

		text_info += 1;
		N2 -= 1;
	}

}

void stream_identifier_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void stuffing_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {	//

}

void subtitling_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void telephone_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//

}

void teletext_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void time_shifted_event_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {		//

}

void time_shifted_service_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void transport_stream_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void VBI_data_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void VBI_teletext_descriptor(unsigned char *descriptor,unsigned char descriptor_length) {

}

void descriptorParser(unsigned char *descriptor, unsigned char descriptor_tag, unsigned char descriptor_length) {
	if(descriptor_tag > 0xFF || descriptor_tag < 0x40) {
		return;
	}
	switch(descriptor_tag) {
	case 0x40:
		network_name_descriptor(descriptor,descriptor_length);
		break;
	case 0x41:
		service_list_descriptor(descriptor,descriptor_length);
		break;
	case 0x42:
		stuffing_descriptor(descriptor,descriptor_length);
		break;
	case 0x43:
		satellite_delivery_system_descriptor(descriptor,descriptor_length);
		break;
	case 0x44:
		cable_delivery_system_descriptor(descriptor,descriptor_length);
		break;
	case 0x45:
		VBI_data_descriptor(descriptor,descriptor_length);
		break;
	case 0x46:
		VBI_teletext_descriptor(descriptor,descriptor_length);
		break;
	case 0x47:
		bouquet_name_descriptor(descriptor,descriptor_length);
		break;
	case 0x48:
		service_descriptor(descriptor,descriptor_length);
		break;
	case 0x49:
		country_availability_descriptor(descriptor,descriptor_length);
		break;
	case 0x4A:
		linkage_descriptor(descriptor,descriptor_length);
		break;
	case 0x4B:
		NVOD_reference_descriptor(descriptor,descriptor_length);
		break;
	case 0x4C:
		time_shifted_service_descriptor(descriptor,descriptor_length);
		break;
	case 0x4D:
		short_event_descriptor(descriptor,descriptor_length);
		break;
	case 0x4E:
		extended_event_descriptor(descriptor,descriptor_length);
		break;
	case 0x4F:
		time_shifted_event_descriptor(descriptor,descriptor_length);
		break;
	case 0x50:
		component_descriptor(descriptor,descriptor_length);
		break;
	case 0x51:
		mosaic_descriptor(descriptor,descriptor_length);
		break;
	case 0x52:
		stream_identifier_descriptor(descriptor,descriptor_length);
		break;
	case 0x53:
		CA_identifier_descriptor(descriptor,descriptor_length);
		break;
	case 0x54:
		content_descriptor(descriptor,descriptor_length);
		break;
	case 0x55:
		parental_rating_descriptor(descriptor,descriptor_length);
		break;
	case 0x56:
		teletext_descriptor(descriptor,descriptor_length);
		break;
	case 0x57:
		telephone_descriptor(descriptor,descriptor_length);
		break;
	case 0x58:
		local_time_offset_descriptor(descriptor,descriptor_length);
		break;
	case 0x59:
		subtitling_descriptor(descriptor,descriptor_length);
		break;
	case 0x5A:
		terrestrial_delivery_system_descriptor(descriptor,descriptor_length);
		break;
	case 0x5B:
		multilingual_network_name_descriptor(descriptor,descriptor_length);
		break;
	case 0x5C:
		multilingual_bouquet_name_descriptor(descriptor,descriptor_length);
		break;
	case 0x5D:
		multilingual_service_name_descriptor(descriptor,descriptor_length);
		break;
	case 0x5E:
		multilingual_component_descriptor(descriptor,descriptor_length);
		break;
	case 0x5F:
		private_data_specifier_descriptor(descriptor,descriptor_length);
		break;
	case 0x60:
		service_move_descriptor(descriptor,descriptor_length);
		break;
	case 0x61:
		short_smoothing_buffer_descriptor(descriptor,descriptor_length);
		break;
	case 0x62:
		frequency_list_descriptor(descriptor,descriptor_length);
		break;
	case 0x63:
		//partial_transport_stream_descriptor(descriptor,descriptor_length);
		break;
	case 0x64:
		data_broadcast_descriptor(descriptor,descriptor_length);
		break;
	case 0x65:
		//reserved for future use
		break;
	case 0x66:
		data_broadcast_id_descriptor(descriptor,descriptor_length);
		break;
	case 0x67:
		transport_stream_descriptor(descriptor,descriptor_length);
		break;
	case 0x68:
		//DSNG_descriptor(descriptor,descriptor_length);
		break;
	case 0x69:
		PDC_descriptor(descriptor,descriptor_length);
		break;
	case 0x6A:
		//AC_3_descriptor(descriptor,descriptor_length);
		break;
	case 0x6B:
		ancillary_data_descriptor(descriptor,descriptor_length);
		break;
	case 0x6C:
		cell_list_descriptor(descriptor,descriptor_length);
		break;
	case 0x6D:
		cell_frequency_link_descriptor(descriptor,descriptor_length);
		break;
	case 0x6E:
		announcement_support_descriptor(descriptor,descriptor_length);
		break;
	case 0x6F:
		//application_signalling_descriptor(descriptor,descriptor_length);
		break;
	case 0x70:
		adaptation_field_data_descriptor(descriptor,descriptor_length);
		break;
	case 0x71:
		//service_identifier_descriptor(descriptor,descriptor_length);
		break;
	case 0x72:
		service_availability_descriptor(descriptor,descriptor_length);
		break;
	default:
		break;
	}
}

