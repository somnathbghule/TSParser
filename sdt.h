/*
 * sdt.h
 *
 *  Created on: 07-Mar-2014
 *      Author: abhishek
 */

#ifndef SDT_H_
#define SDT_H_
#include "tp.h"



/*
 * service_descriptio_section(){
 * 		table_id					8
 * 		section_syntex_indicator	1
 * 		reserved_future_use			1
 * 		reserved					2
 * 		section_length				12
 * 		transort_stream_id			16
 * 		reserved					2
 * 		version_number				5
 * 		current_next_indicator		1
 * 		section_number				8
 * 		last_section_number			8
 * 		original_network_id			16
 * 		reserved_future_use			8
 * 		for(i=0;i<N;i++){
 * 			service_id				16
 * 			reserved_future_use		6
 * 			EIT_scheduled_flag		1
 * 			EIT_present_following_flag 1
 * 			running_status				3
 * 			free_CA_mode				1
 * 			descriptor_loop_length		12
 * 			for(j=0;j<N;j++){
 * 				descriptor();
 * 			}
 * 		}
 * 		CRC_32						32s
 * }
 */
void sdtParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size);

#endif /* SDT_H_ */
