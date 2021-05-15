/*
 * pat1.h
 *
 *  Created on: Feb 17, 2014
 *      Author: aeon29
 */

#ifndef PAT1_H_
#define PAT1_H_

#include "tp.h"

/*
program_association_section() {
	table_id																			// 8	//uimsbf
	section_syntax_indicator															// 1	//bslbf
	'0'																					// 1	//bslbf
	reserved																			// 2	//bslbf
	section_length																		// 12	//uimsbf
	transport_stream_id																	// 16	//uimsbf
	reserved																			// 2	//bslbf
	version_number																		// 5	//uimsbf
	current_next_indicator																// 1	//bslbf
	section_number																		// 8	//uimsbf
	last_section_number																	// 8	//uimsbf
	for (i = 0; i < N; i++) {
		program_number																	// 16	//uimsbf
		reserved																		// 3	//bslbf
		if (program_number == '0') {
			network_PID																	// 13	//uimsbf
		}
		else {
			program_map_PID																// 13	//uimsbf
		}
	}
	CRC_32																				// 32	//rpchof
}
*/

void patParser(unsigned char *section, unsigned char payload_unit_start_indicator, int size);

#endif /* PAT1_H_ */
