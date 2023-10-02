# ValveSVGParser
Barebones Parser/Extractor for Valve SVG format (.vsvg_c)

# Example
```c++
void ParseAndConvert( std::filesystem::path path )
{
	auto in = std::ifstream( path, std::ios::binary | std::ios::ate );
	const auto size = in.tellg();
	in.seekg( 0, std::ios::beg );

	auto buf = std::vector<char>{};
	buf.resize( size );

	if ( !in.read( buf.data(), size ) )
		return;

	auto svg = ValveSVG::Parse( buf );

	path += ".svg";
	auto out = std::ofstream( path, std::ios::out | std::ios::trunc );
	out << svg;
	out.close();

	std::cout << svg << std::endl;
}
```
