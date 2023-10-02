#pragma once

#include <string>
#include <vector>

#pragma pack (push, 1)
struct ValveSVGData_t
{
	struct
	{
		uint8_t pad[ 38 ];
	} header;

	char svg_string[];
};
#pragma pack (pop, 1)

#pragma pack (push, 1)
struct ValveSVGHeader_t
{
	uint16_t hash;
	uint8_t pad[ 30 ];
	uint16_t file_offset_to_svg_data;
};
#pragma pack (pop, 1)

namespace ValveSVG
{
	std::string Parse( const std::vector<char>& file_bytes )
	{
		const auto header = reinterpret_cast< const ValveSVGHeader_t* >( file_bytes.data() );
		const auto data = reinterpret_cast< const ValveSVGData_t* >( file_bytes.data() + header->file_offset_to_svg_data );

		const auto total_header_size = header->file_offset_to_svg_data + offsetof( ValveSVGData_t, svg_string );

		auto str = std::string( file_bytes.begin(), file_bytes.end() );
		str = str.substr( total_header_size );

		return str;
	}
}