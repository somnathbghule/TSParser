/*
 * eit.h
 *
 *  Created on: Feb 18, 2014
 *      Author: aeon29
 */

#ifndef EIT_H_
#define EIT_H_

#include "tp.h"

/*
event_information_section() {
	table_id									//8 	//uimsbf
	section_syntax_indicator					//1 	//bslbf
	reserved_future_use							//1 	//bslbf
	reserved									//2 	//bslbf
	section_length								//12 	//uimsbf
	service_id									//16 	//uimsbf
	reserved									//2 	//bslbf
	version_number								//5 	//uimsbf
	current_next_indicator						//1 	//bslbf
	section_number								//8 	//uimsbf
	last_section_number							//8 	//uimsbf
	transport_stream_id							//16 	//uimsbf
	original_network_id							//16 	//uimsbf
	segment_last_section_number					//8 	//uimsbf
	last_table_id								//8 	//uimsbf
	for(i=0;i<N;i++) {
		event_id								//16 	//uimsbf
		start_time								//40 	//bslbf
		duration								//24 	//uimsbf
		running_status							//3 	//uimsbf
		free_CA_mode							//1 	//bslbf
		descriptors_loop_length					//12 	//uimsbf
		for(i=0;i<N;i++) {
			descriptor()
		}
	}
	CRC_32										//32 	//rpchof
}
*/

void eitParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size);


#endif /* EIT_H_ */
