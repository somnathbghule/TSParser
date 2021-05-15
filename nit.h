/*
 * nit.h
 *
 *  Created on: 07-Mar-2014
 *      Author: aeon25
 */

#ifndef NIT_H_
#define NIT_H_
#include "tp.h"

/*network_information_section(){
	table_id						8
	section_index_indicator			1
	reserved_future_use				1

	reserved						2
	section_length					12
	network_id						16
	reserved						2
	version_number					5
	current_next_indicator			1
	section_number					8
	last_section_number				8
	reserved_future_use				4
	network_descriptor_length		12
	for(i=0;i<N;i++){
	descriptor();
	}
	reserved_future_use				4
	transport_stream_loop_length	12
	for(i=0;i<N;i++) {
	transport_stream_id 			16
	original_network_id 			16
	reserved_future_use 			4
	transport_descriptors_length 	12
		for(i=0;i<N;i++) {
			descriptor();
		}
	}
	CRC_32							32
}*/

/*service_list_descriptor() {
	descriptor_tag					8
	descriptor_length				8
	for (i=0;i<N;I++) {
		service_id					16
		service_type				8
	}
}*/

/*
network_name_descriptor(){
descriptor_tag						8
descriptor_length					8
for (i=0;i<N;i++){
char								8
}
*/


void nitParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size);

#endif /* NIT_H_ */
